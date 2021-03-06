#include <endian.h>
#include <cassert>

#include "../runtime/thread.hh"
#include "channel.hh"
#include "protocol.hh"

namespace mimosa
{
  namespace rpc
  {
    Channel::Channel(stream::BufferedStream::Ptr stream,
                     ServiceMap::ConstPtr        service_map)
      : stream_(stream),
        service_map_(service_map),
        scalls_(),
        rcalls_(),
        status_(kOk),
        write_queue_(),
        next_tag_(0)
    {
    }

    Channel::~Channel()
    {
    }

    uint32_t
    Channel::nextTag()
    {
      return __sync_add_and_fetch(&next_tag_, 1);
    }

    void
    Channel::start()
    {
      Channel::Ptr channel(this);
      runtime::Thread([channel]() { channel->readLoop(); }).start();
      runtime::Thread([channel]() { channel->writeLoop(); }).start();
    }

    void
    Channel::writeLoop()
    {
      while (status_ == kOk)
      {
        stream::Buffer::Ptr buffer;
        if (!write_queue_.pop(buffer))
        {
          stream_->flush();
          continue;
        }
        int64_t ret = 0;
        if ((ret = stream_->loopWrite(buffer->data(), buffer->size())) != buffer->size())
        {
          close();
          return;
        }
        stream_->flush();
      }
    }

    void
    Channel::readLoop()
    {
      while (status_ == kOk)
      {
        uint8_t msg_type;
        int ret = 0;
        if ((ret = stream_->read((char*)&msg_type, 1)) != 1)
        {
          close();
          return;
        }

        bool ok = false;
        switch (msg_type)
        {
        case kCall:   ok = handleCall(); break;
        case kResult: ok = handleResult(); break;
        case kError:  ok = handleError(); break;

        case kClose:  ok = false; break;
        default:      ok = false; break;
        }

        if (!ok)
        {
          close();
          return;
        }
      }
    }

    void
    Channel::sendCall(BasicCall::Ptr call)
    {
      call->setTag(nextTag());

      uint32_t rq_size = call->request_->ByteSize();
      stream::Buffer::Ptr buffer = new stream::Buffer(rq_size + sizeof (MsgCall));
      MsgCall * msg    = reinterpret_cast<MsgCall *> (buffer->data());
      msg->type_       = kCall;
      msg->tag_        = htole32(call->tag());
      msg->service_id_ = htole32(call->serviceId());
      msg->method_id_  = htole32(call->methodId());
      msg->rq_size_    = htole32(rq_size);
      call->request_->SerializeToArray(msg->rq_, rq_size);
      {
        sync::Mutex::Locker locker(scalls_mutex_);
        while (true)
        {
          auto it = scalls_.find(call->tag());
          if (it == scalls_.end())
            break;
          call->setTag(nextTag());
          msg->tag_ = htole32(call->tag());
        }
        scalls_[call->tag()] = call;
      }
      if (!write_queue_.push(buffer))
      {
        sync::Mutex::Locker locker(scalls_mutex_);
        scalls_.erase(call->tag());
        call->cancel();
      }
    }

    void
    Channel::sendResponse(BasicCall::Ptr call)
    {
      uint32_t rp_size  = call->response_->ByteSize();
      stream::Buffer::Ptr buffer = new stream::Buffer(rp_size + sizeof (MsgResult));
      MsgResult * msg  = reinterpret_cast<MsgResult *> (buffer->data());
      msg->type_       = kResult;
      msg->tag_        = htole32(call->tag());
      msg->rp_size_    = htole32(rp_size);
      call->response_->SerializeToArray(msg->rp_, rp_size);
      write_queue_.push(buffer);

      sync::Mutex::Locker locker(rcalls_mutex_);
      rcalls_.erase(call->tag());
    }

    void
    Channel::sendError(ErrorType error, uint32_t tag, TagOrigin tag_origin)
    {
      stream::Buffer::Ptr buffer = new stream::Buffer(sizeof (MsgError));
      MsgError * msg   = reinterpret_cast<MsgError *> (buffer->data());
      msg->type_       = kError;
      msg->error_      = error;
      msg->tag_        = htole32(tag);
      msg->tag_origin_ = tag_origin;
      write_queue_.push(buffer);

      sync::Mutex::Locker locker(rcalls_mutex_);
      rcalls_.erase(tag);
    }

    bool
    Channel::handleCall()
    {
      MsgCall msg;
      char *  data = 1 + (char *)&msg.type_;
      if (stream_->loopRead(data, sizeof (msg) - 1) != sizeof (msg) - 1)
        return false;
      msg.tag_        = le32toh(msg.tag_);
      msg.service_id_ = le32toh(msg.service_id_);
      msg.method_id_  = le32toh(msg.method_id_);
      msg.rq_size_    = le32toh(msg.rq_size_);

      BasicCall::Ptr call = new BasicCall();
      call->setTag(msg.tag_);
      call->setServiceId(msg.service_id_);
      call->setMethodId(msg.method_id_);

      // read the end of the message
      data = (char *)::malloc(msg.rq_size_);
      if (!data)
        return false;
      if (stream_->loopRead(data, msg.rq_size_) != msg.rq_size_)
      {
        free(data);
        return false;
      }

      // find service
      auto service = service_map_->find(call->serviceId());
      if (!service)
      {
        free(data);
        sendError(kServiceNotFound, call->tag(), kOriginYou);
        return true;
      }

      // check for duplicate tag
      {
        sync::Mutex::Locker locker(rcalls_mutex_);
        auto it = rcalls_.find(msg.tag_);
        if (it != rcalls_.end())
        {
          free(data);
          sendError(kDuplicateTag, call->tag(), kOriginYou);
          return true;
        }
        rcalls_[call->tag()] = call;
      }

      // call method
      Channel::Ptr channel(this);
      auto data_size = msg.rq_size_;
      runtime::Thread([channel, call, data, data_size, service] () {
          auto ret = service->callMethod(call, data, data_size);
          free(data);
          if (ret != Service::kSucceed)
            channel->sendError(static_cast<ErrorType> (ret), call->tag(), kOriginYou);
          else
            channel->sendResponse(call);
        }).start();
      return true;
    }

    bool
    Channel::handleResult()
    {
      MsgResult msg;
      char *    data = 1 + (char *)&msg.type_;
      if (stream_->loopRead(data, sizeof (msg) - 1) != sizeof (msg) - 1)
        return false;
      msg.tag_     = le32toh(msg.tag_);
      msg.rp_size_ = le32toh(msg.rp_size_);

      data = (char *)::malloc(msg.rp_size_);
      if (!data)
        return false;
      if (stream_->loopRead(data, msg.rp_size_) != msg.rp_size_)
      {
        free(data);
        return false;
      }

      BasicCall::Ptr call;
      {
        sync::Mutex::Locker locker(scalls_mutex_);
        auto it = scalls_.find(msg.tag_);
        if (it == scalls_.end())
        {
          free(data);
          return true;
        }
        call = it->second;
        scalls_.erase(it);
      }
      call->response_->ParseFromArray(data, msg.rp_size_);
      free(data);
      call->finished();
      return true;
    }

    bool
    Channel::handleError()
    {
      MsgError msg;
      char *   data = 1 + (char *)&msg;
      if (stream_->loopRead(data, sizeof (msg) - 1) != sizeof (msg) - 1)
        return false;
      msg.tag_ = le32toh(msg.tag_);

      switch (msg.tag_origin_)
      {
      case kOriginYou:
      {
        sync::Mutex::Locker locker(scalls_mutex_);
        auto it = scalls_.find(msg.tag_);
        if (it == scalls_.end())
          return true;
        it->second->cancel();
        scalls_.erase(it);
        return true;
      }

      case kOriginMe:
      {
        sync::Mutex::Locker locker(rcalls_mutex_);
        auto it = rcalls_.find(msg.tag_);
        if (it == rcalls_.end())
          return true;
        it->second->cancel();
        rcalls_.erase(it);
        return true;
      }

      default:
        // TODO ????
        return true;
      }
    }

    void
    Channel::close()
    {
      status_ = kClosed;
      stream_->close();
      write_queue_.close();
    }
  }
}
