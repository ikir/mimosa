#include "error-handler.hh"
#include "server-channel.hh"

namespace mimosa
{
  namespace http
  {
    ServerChannel::ServerChannel(stream::FdStream::Ptr stream,
                                 Handler::Ptr          handler,
                                 runtime::Time         read_timeout,
                                 runtime::Time         write_timeout)
      : stream_(stream),
        handler_(handler),
        read_timeout_(read_timeout),
        write_timeout_(write_timeout),
        timeout_(0),
        request_(new RequestReader(stream_)),
        response_(new ResponseWriter(stream_))
    {
    }

    ServerChannel::~ServerChannel()
    {
    }

    void
    ServerChannel::run()
    {
      do {
        request_->clear();
        response_->clear();
        if (!readRequest() ||
            !runHandler() ||
            !sendResponse())
          break;
      } while (response_->keep_alive_);
    }

    bool
    ServerChannel::readRequest()
    {
      bool found = false;
      stream::Buffer::Ptr buffer = stream_->readUntil("\r\n\r\n", 5 * 1024, readTimeout(), &found);
      if (!buffer)
      {
        requestTimeout();
        return false;
      }

      if (!found)
      {
        ErrorHandler::basicResponse(*request_, *response_, kStatusRequestEntityTooLarge);
        return false;
      }

      if (!request_->parse(buffer->data(), buffer->size() + 2))
      {
        badRequest();
        return false;
      }

      return request_->prepare();
    }

    bool
    ServerChannel::runHandler()
    {
      return handler_->handle(*request_, *response_);
    }

    bool
    ServerChannel::sendResponse()
    {
      return response_->finish(writeTimeout()) && request_->flush();
    }

    void
    ServerChannel::requestTimeout()
    {
      ErrorHandler::basicResponse(*request_, *response_, kStatusRequestTimeout);
    }

    void
    ServerChannel::badRequest()
    {
      ErrorHandler::basicResponse(*request_, *response_, kStatusBadRequest);
    };
  }
}
