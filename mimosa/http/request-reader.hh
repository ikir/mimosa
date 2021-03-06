#ifndef MIMOSA_HTTP_REQUEST_READER_HH
# define MIMOSA_HTTP_REQUEST_READER_HH

# include "request.hh"
# include "../stream/stream.hh"

namespace mimosa
{
  namespace http
  {
    class  ServerChannel;
    class RequestReader : public stream::Stream,
                          public Request
    {
    public:
      MIMOSA_DEF_PTR(RequestReader);

      RequestReader(ServerChannel & channel,
                    runtime::Time   read_timeout);

      void clear();

      /** Stream related stuff
       * @{ */
      /** @warning this should never be called, will abort */
      virtual int64_t write(const char * data, uint64_t nbytes, runtime::Time timeout = 0);
      /** reads the body (PUT and POST) */
      virtual int64_t read(char * data, uint64_t nbytes, runtime::Time timeout = 0);
      /** reads and discards all remaining body data */
      virtual bool flush(runtime::Time timeout = 0);
      /** @} */

      container::kvs & form();

      inline runtime::Time readTimeout() const
      {
        return read_timeout_ > 0 ? runtime::time() + read_timeout_ : 0;
      }

      inline ServerChannel & channel() const { return channel_; }

    private:

      friend class ServerChannel;

      bool prepare();

      ServerChannel &     channel_;
      int64_t             bytes_left_;
      bool                parsed_form_;
      container::kvs      form_;
      runtime::Time       read_timeout_;
    };
  }
}

#endif /* !MIMOSA_HTTP_REQUEST_READER_HH */
