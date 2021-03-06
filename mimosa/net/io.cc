#include <climits>

#include "io.hh"

namespace mimosa
{
  namespace net
  {
    bool
    waitForFdReady(int fd, int events, runtime::Time timeout)
    {
      ::pollfd pfd;
      int      ret;

      if (timeout == 0)
        return true;

      pfd.fd     = fd;
      pfd.events = events;

      auto time = (timeout - runtime::Time()) / runtime::millisecond;
      if (time <= 0)
        goto err_timeout;

      ret = ::poll(&pfd, 1, time);
      if (ret < 0)
        return false;

      if (ret == 0)
        goto err_timeout;

      if (pfd.revents & (POLLHUP | POLLERR))
      {
        errno = EPIPE;
        return false;
      }

      if (pfd.revents & events)
        return true;

      return false;

      err_timeout:
      errno = ETIMEDOUT;
      return false;
    }

    int64_t
    write(int fd, const char * data, uint64_t nbytes, runtime::Time timeout)
    {
      if (!waitForFdReady(fd, POLLOUT | POLLWRNORM | POLLWRBAND, timeout))
        return -1;
      return ::write(fd, data, nbytes);
    }

    int64_t
    writev(int fd, const struct iovec *iov, int iovcnt, runtime::Time timeout)
    {
      if (!waitForFdReady(fd, POLLOUT | POLLWRNORM | POLLWRBAND, timeout))
        return -1;
      return ::writev(fd, iov, iovcnt < IOV_MAX ? iovcnt : IOV_MAX);
    }

    int64_t
    read(int fd, char * data, uint64_t nbytes, runtime::Time timeout)
    {
      if (!waitForFdReady(fd, POLLIN | POLLRDNORM | POLLRDBAND | POLLPRI, timeout))
        return -1;
      return ::read(fd, data, nbytes);
    }

    int64_t
    readv(int fd, const struct iovec *iov, int iovcnt, runtime::Time timeout)
    {
      if (!waitForFdReady(fd, POLLIN | POLLRDNORM | POLLRDBAND | POLLPRI, timeout))
        return -1;
      return ::readv(fd, iov, iovcnt < IOV_MAX ? iovcnt : IOV_MAX);
    }
  }
}
