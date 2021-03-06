#ifndef MIMOSA_HTTP_RESPONSE_HH
# define MIMOSA_HTTP_RESPONSE_HH

# include <string>
# include <unordered_map>

# include "coding.hh"
# include "status.hh"
# include "cookie.hh"
# include "../container/kvs.hh"

namespace mimosa
{
  namespace http
  {
    class Response
    {
    public:
      Response();

      /** convert the response to an http response header */
      std::string toHttpHeader() const;

      void clear();

      Status         status_;
      bool           keep_alive_;
      Coding         content_encoding_;
      Coding         transfer_encoding_;
      int64_t        content_length_;     ///< -1: auto
      std::string    content_type_;
      Cookie::Slist  cookies_;
      container::kvs unparsed_headers_;
    };
  }
}

#endif /* !MIMOSA_HTTP_RESPONSE_HH */
