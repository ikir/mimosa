#ifndef MIMOSA_HTTP_COOKIE_HH
# define MIMOSA_HTTP_COOKIE_HH

# include <string>

# include "../ref-countable.hh"
# include "../container/intrusive-slist.hh"

namespace mimosa
{
  namespace http
  {
    class Cookie : public RefCountable<Cookie>
    {
    public:
      container::IntrusiveSlistHook<Cookie::Ptr> next_;
      typedef container::IntrusiveSlist<Cookie, Cookie::Ptr, &Cookie::next_> Slist;

      Cookie();

      inline void setDomain(const std::string & domain) { domain_ = domain; }
      inline const std::string & domain() const { return domain_; }
      inline void setExpires(const std::string & expires) { expires_ = expires; }
      inline const std::string & expires() const { return expires_; }
      inline void setPath(const std::string & path) { path_ = path; }
      inline const std::string & path() const { return path_; }
      inline void setKey(const std::string & key) { key_ = key; }
      inline const std::string & key() const { return key_; }
      inline void setValue(const std::string & value) { value_ = value; }
      inline const std::string & value() const { return value_; }
      inline void setSecure(bool enable) { is_secure_ = enable; }
      inline bool isSecure() const { return is_secure_; }
      inline void setHttpOnly(bool enable) { is_http_only_ = enable; }
      inline bool isHttpOnly() const { return is_http_only_; }

    private:
      std::string key_;
      std::string value_;
      std::string domain_;
      std::string path_;
      std::string expires_;
      bool        is_secure_;
      bool        is_http_only_;
    };
  }
}

#endif /* !MIMOSA_HTTP_COOKIE_HH */
