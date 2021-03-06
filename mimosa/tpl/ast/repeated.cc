#include "repeated.hh"
#include "../abstract-value.hh"

namespace mimosa
{
  namespace tpl
  {
    namespace ast
    {
      void
      Repeated::execute(stream::Stream::Ptr   stream,
                        const AbstractValue & value,
                        runtime::Time         timeout) const
      {
        auto v = value.lookup(var_);
        if (!v || v->empty())
          return;

        for (auto it = v->begin(); !it->end(); it->next())
        {
          for (auto child = childs_.begin(); child != childs_.end(); ++child)
            if (it->value())
              child->execute(stream, *it->value(), timeout);
        }
      }
    }
  }
}
