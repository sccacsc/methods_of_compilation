#include <iostream>

#include "lexer.h"

int main()
{
    Lexer lexer("1 > 2;1 < 2;");//временно
    auto token = lexer.get_next_token();
    while (token.type != 8 && token.type != -1)
    {
        if (token.type == -1)
        {
            std::cout << "ошибка"                       << " | Line: " << token.line
                                                      << " | Column: " << token.column << std::endl;
            break;
        }
        else if (token.type == 8)
        {
            std::cout << "конец анализа" << std::endl;
            break;
        }
        else
        {
            std::cout << "Token: " << token.value
                      << " | Type: " << token.type
                      << " | Line: " << token.line
                      << " | Column: " << token.column << std::endl;
        }
        token = lexer.get_next_token();
    }
}
