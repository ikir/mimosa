#ifndef MIMOSA_SYNC_BARRIER_HANDLE_HH
# define MIMOSA_SYNC_BARRIER_HANDLE_HH

# include "barrier.hh"

namespace mimosa
{
  namespace sync
  {
    class BarrierHandle
    {
    public:
      inline BarrierHandle(Barrier & barrier)
        : barrier_(barrier)
      {
        barrier_.add();
      }

      inline BarrierHandle(const BarrierHandle & handle)
        : BarrierHandle(handle.barrier_)
      {
      }

      inline ~BarrierHandle()
      {
        barrier_.release();
      }

      inline void wait() { barrier_.wait(); }

    private:
      BarrierHandle & operator=(const BarrierHandle & handle);

      Barrier & barrier_;
    };
  }
}

#endif /* !MIMOSA_SYNC_BARRIER_HANDLE_HH */
