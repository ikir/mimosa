#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <sstream>
#include <algorithm>

#include "../string/string-ref.hh"
#include "../stream/copy.hh"
#include "../stream/direct-fd-stream.hh"
#include "fs-handler.hh"
#include "error-handler.hh"
#include "mime-db.hh"

namespace mimosa
{
  namespace http
  {
    FsHandler::FsHandler(const std::string & root, int nskip, bool enable_readdir)
      : root_(root),
        nskip_(nskip),
        can_readdir_(enable_readdir)
    {
    }

    bool
    FsHandler::handle(RequestReader & request, ResponseWriter & response) const
    {
      string::StringRef path(request.location());
      for (auto nskip = nskip_; nskip > 0; --nskip)
      {
        auto pos = path.find('/', 1);
        if (pos == string::StringRef::npos)
        {
          if (nskip == 1 && path.size() > 1) // our location is root and is not terminated by '/'
          {
            path = string::StringRef("/");
            break;
          }
          else
            // TODO: error reporting
            return ErrorHandler::basicResponse(request, response, kStatusInternalServerError);
        }
        path = path.substr(pos);
      }
      // TODO: check every component for symlinks going out of root.

      std::string real_path(root_);
      real_path.append(path.data(), path.size());

      struct stat st;
      if (::stat(real_path.c_str(), &st))
        return ErrorHandler::basicResponse(request, response, kStatusNotFound);

      if (S_ISREG(st.st_mode))
        return streamFile(request, response, real_path, st);
      else if (S_ISDIR(st.st_mode) && can_readdir_)
        return readDir(request, response, real_path);
      return ErrorHandler::basicResponse(request, response, kStatusForbidden);
    }

    bool
    FsHandler::streamFile(RequestReader &     request,
                          ResponseWriter &    response,
                          const std::string & real_path,
                          struct stat &       st) const
    {
      response.content_length_ = st.st_size;
      response.content_type_ = MimeDb::instance().mimeType(real_path);
      response.sendHeader(response.writeTimeout());

      int fd = ::open(real_path.c_str(), O_RDONLY, 0644);
      if (fd < 0)
        return ErrorHandler::basicResponse(request, response, kStatusInternalServerError);
      stream::DirectFdStream::Ptr file(new stream::DirectFdStream(fd));
      int64_t ret = stream::copy(*file, response, st.st_size);
      return ret == st.st_size;
    }

    bool
    FsHandler::readDir(RequestReader &     request,
                       ResponseWriter &    response,
                       const std::string & real_path) const
    {
      DIR * dir = ::opendir(real_path.c_str());
      if (!dir)
        return ErrorHandler::basicResponse(request, response, kStatusNotFound);

      response.content_type_ = "text/html";
      response.sendHeader(response.writeTimeout());
      assert(response.transfer_encoding_ == kCodingChunked);

      std::ostringstream os;

      os << "<html><head></head><body><h1>Directory listing: " << request.location()
         << "</h1><hr/>";

      std::vector<std::string> directories;
      std::vector<std::string> files;

      struct dirent * entry;
      while ((entry = ::readdir(dir)))
      {
        std::ostringstream tmp;
        tmp << real_path << '/' << entry->d_name;

        std::string file_path(tmp.str());

        struct ::stat st;
        if (::stat(file_path.c_str(), &st))
          continue;

        if (S_ISDIR(st.st_mode))
          directories.push_back(entry->d_name);
        else
          files.push_back(entry->d_name);
      }

      std::sort(directories.begin(), directories.end());
      std::sort(files.begin(), files.end());

      for (auto it = directories.begin(); it != directories.end(); ++it)
        os << "<a href=\"" << *it << "/\">" << *it << "/</a><br/>";

      for (auto it = files.begin(); it != files.end(); ++it)
        os << "<a href=\"" << *it << "\">" << *it << "</a><br/>";

      os << "</body></html>";

      ::closedir(dir);
      std::string data(os.str());
      response.write(data.data(), data.size());
      return true;
    }
  }
}
