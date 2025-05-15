#include "lexer.h"

Lexer::Lexer(std::string input) : input_text(input),
                                  i(0), j(0),
                                  decimal_count(0),
                                  int_num(0),
                                  real_num(0.0f),
                                  name("nothing") {};

Lexer::~Lexer() = default;

void Lexer::semantic_program(int num)
{
    switch (num)
    {
    case 1:
        name = input_text[i];
        i += 1;
        break; //
    case 2:
        int_num = input_text[i] - '0';
        i += 1;
        break; //
    case 3:
        type = ERROR;
        i += 1;
        break; //
    case 4:
        type = input_text[i];
        break; //
    case 5:
        i += 1;
        break; //
    case 6:
        name += input_text[i];
        i += 1;
        break; //
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    }
}
