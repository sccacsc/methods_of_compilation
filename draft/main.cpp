#include "lexer.h"
#include "parser.h"

int main()
{
    Lexer lex("real n;");
    //lex.get_tokens();
    Parser par(lex.get_tokens());
    par.parse();
}
