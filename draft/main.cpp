#include <iostream>
#include <vector>

#include "lexer.h"

int main()
{
    Lexer lex("n = 10;");
    lex.get_tokens();

    Lexer lex1("n =! 10");
    lex1.get_tokens();
}
