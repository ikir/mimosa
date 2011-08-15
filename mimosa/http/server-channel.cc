#include "server-channel.hh"

namespace mimosa
{
  namespace http
  {
    ServerChannel::ServerChannel(BufferedStream::Ptr stream,
                                 Handler::Ptr        handler,
                                 runtime::Time       read_timeout,
                                 runtime::Time       write_timeout)
      : stream_(stream),
        handler_(handler),
        read_timeout_(read_timeout),
        write_timeout_(write_timeout)
    {
    }

    void
    ServerChannel::run()
    {
      do {
        if (!readRequest() ||
            !setupBodyReader() ||
            !setupResponseWriter() ||
            !runHandler() ||
            !sendResponse())
          break;
      } while (response_.keep_alive_);
    }

    bool
    ServerChannel::readRequest()
    {
      stream::Buffer::Ptr buffer = stream_->readUntil("\r\n\r\n", readTimeout());
      if (!buffer)
      {
        requestTimeout();
        return false;
      }

      if (!request_.parse(buffer->data(), buffer->size() + 2))
      {
        badRequest();
        return false;
      }

      return true;
    }

    bool
    ServerChannel::setupBodyReader()
    {
      if (!request_.hasBody())
        return true;
      assert(false && "TODO");
      return true;
    }

    bool
    ServerChannel::setupResponseWriter()
    {
      response_.stream_ = new ResponseWriter(response_, stream_);
      return true;
    }

    bool
    ServerChannel::runHanlder()
    {
      return handler_->handle(request_, response_);
    }

    bool
    ServerChannel::sendResponse()
    {
      if (response_.is_response_header_sent_)
        return true;
      return response_.sendResponseHeader();
      assert(false && "TODO");
      if (!response_.stream_->flush(writeTimeout()))
        return false;
      return true;
    }
  }
}
