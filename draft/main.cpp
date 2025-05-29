#include "lexer.h"

int main()
{
    Lexer lex("n =       ;     10;");
    lex.get_tokens();
}
