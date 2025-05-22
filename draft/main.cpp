#include <iostream>

#include "lexer.h"

int main()
{
    Lexer lexer("");//временно
    auto token = lexer.get_next_token();
    while (true)
 {
        if (token.type == -1)
        {
            std::cout << "ошибка"                       << " | Pos: " << token.line
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
                      << " | Pos: " << token.line
                      << " | Column: " << token.column << std::endl;
        }
        token = lexer.get_next_token();
    }
}
