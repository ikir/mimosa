#include "abstract-value.hh"

namespace mimosa
{
  namespace tpl
  {
    AbstractValue::AbstractValue(AbstractValue * parent)
      : parent_(parent)
    {
    }

    AbstractValue::SingleValueIterator::SingleValueIterator(AbstractValue * value)
      : value_(value)
    {
    }

    const AbstractValue *
    AbstractValue::SingleValueIterator::value() const
    {
      return value_;
    }

    void
    AbstractValue::SingleValueIterator::next()
    {
      value_ = nullptr;
    }

    bool
    AbstractValue::SingleValueIterator::end() const
    {
      return value_;
    }
  }
}
