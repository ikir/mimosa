#ifndef MIMOSA_TPL_PARSER_HH
# define MIMOSA_TPL_PARSER_HH

# include <string>
# include <vector>

# include "template.hh"

namespace mimosa
{
  namespace tpl
  {
    class Parser
    {
    public:
      Parser(const Template & tpl);

      ast::Root::Ptr parse();

      bool parseText();
      bool parseAction();

    private:
      std::string                 action_start_;
      std::string                 action_end_;

      string::StringRef           input_;

      std::vector<ast::Node::Ptr> stack_;
      int                         line_;
      int                         column_;

      ast::Root::Ptr              root_;
    };
  }
}

#endif /* !MIMOSA_TPL_PARSER_HH */
