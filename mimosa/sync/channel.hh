#ifndef MIMOSA_SYNC_CHANNEL_HH
# define MIMOSA_SYNC_CHANNEL_HH

# include <queue>

# include "mutex.hh"
# include "condition.hh"
# include "../ref-countable.hh"

namespace mimosa
{
  namespace sync
  {
    template <typename T, typename QueueType = std::queue<T> >
    class Channel : public RefCountable<Channel<T, QueueType> >,
                    private NonCopyable
    {
    public:
      inline Channel()
        : closed_(false),
          queue_(),
          mutex_(),
          cond_()
      {
      }

      inline bool push(const T & t)
      {
        Mutex::Locker locker(mutex_);
        if (closed_)
          return false;

        queue_.push(t);
        cond_.wakeOne();
        return true;
      }

      inline bool pop(T & t)
      {
        Mutex::Locker locker(mutex_);
        while (!closed_)
        {
          if (!queue_.empty())
          {
            t = queue_.front();
            queue_.pop();
            return true;
          }
          else
            cond_.wait(mutex_);
        }
        return false;
      }

      inline bool tryPop(T & t)
      {
        Mutex::Locker locker(mutex_);
        if (closed_ || queue_.empty())
          return false;

        t = queue_.front();
        queue_.pop();
        return true;
      }

      inline void close()
      {
        Mutex::Locker locker(mutex_);
        closed_ = true;
        cond_.wakeAll();
      }

      inline bool empty() const
      {
        return queue_.emtpy();
      }

      bool      closed_;
      QueueType queue_;
      Mutex     mutex_;
      Condition cond_;
    };
  }
}

#endif /* !MIMOSA_SYNC_CHANNEL_HH */
