#include "lexer.h"

Lexer::Lexer(std::string input) : input_text(input),
                                  i(0), j(0),
                                  decimal_count(0),
                                  int_num(0),
                                  real_num(0.0f),
                                  name("nothing") {};

Lexer::~Lexer() = default;

Token Lexer::get_next_token()
{
    State state = S;

    while (state != F && state != FF && state != O)
    {
    }
}

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
        if (table_encoding.find(name) != table_encoding.end())
        {
            type = table_encoding.find(name)->second;
        }
        else
        {
            type = NAME;
        }
        break; //
    case 8:
        i = 0;
        j += 1;
        break; //
    case 9:
        int_num = int_num * 10 + (input_text[i] - '0');
        i += 1;
        break; //
    case 10:
        real_num = int_num;
        i += 1;
        decimal_count = 10;
        break; //
    case 11:
        type = INTEGER;
        i -= 1;
        break; //
    case 12:
        type = EQUALS;
        i += 1;
        break; //
    case 13:
        type = input_text[i];
        i -= 1;
        break; //
    case 14:
        i -= 1;
        break; //
    case 15:
        type = NOT_EQUALS;
        break; //
    case 16:
        real_num += (input_text[i] - '0') / decimal_count;
        decimal_count *= 10;
        i += 1;
        break; //
    case 17:
        type = REAL;
        i -= 1;
        break; //
    case 18:
        type = GREATER_OR_EQUAL;
        i += 1;
        break; //
    case 19:
        type = LESS_OR_EQUAL;
        i += 1;
        break; //
    }
}
