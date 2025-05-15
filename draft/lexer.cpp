#include "lexer.h"

Lexer::Lexer(std::string input) : input_text(input),
                                  i(0), j(0),
                                  decimal_count(0),
                                  int_num(0),
                                  real_num(0.0f),
                                  name(""),
                                  result("") {};

Lexer::~Lexer() = default;

Token Lexer::get_next_token()
{
    State state = S;

    while (state != F && state != FF && state != O)
    {
        int col = encode_char(input_text[i]);
        int sem = semantic_table[state][col];
        semantic_program(sem);
        state = static_cast<State>(transition_table[state][col]);
    }

    return {type, result, i, j};
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
        result = "Ошибка";
        break; //
    case 4:
        type = input_text[i];
        result = input_text[i];
        i += 1;
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
            result = table_encoding.find(name)->second;
        }
        else
        {
            type = NAME;
            result = name;
        }
        //i -= 1;
        break; //
    case 8:
        i += 1;
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
        //i -= 1;
        result = int_num;
        break; //
    case 12:
        type = EQUALS;
        result = "==";
        i += 1;
        break; //
    case 13:
        type = input_text[i];
        result = input_text[i];
        i -= 1;
        break; //
    case 14:
        i -= 1;
        break; //
    case 15:
        type = NOT_EQUALS;
        result = "!=";
        i += 1;
        break; //
    case 16:
        real_num += (input_text[i] - '0') / decimal_count;
        decimal_count *= 10;
        i += 1;
        break; //
    case 17:
        type = REAL;
        i -= 1;
        result = real_num;
        break; //
    case 18:
        type = GREATER_OR_EQUAL;
        i += 1;
        result = ">=";
        break; //
    case 19:
        type = LESS_OR_EQUAL;
        i += 1;
        result = "<=";
        break; //
    case 20:
        type = END_OF_INPUT;
        i += 1;
        result = "конец";
        break; //
    }
}

int Lexer::encode_char(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return 0; // «б»
    if (isdigit(ch))
        return 1; // «ц»
    if (ch == '.')
        return 2; //
    if (ch == '+')
        return 3; //
    if (ch == '-')
        return 4; //
    if (ch == '*')
        return 5; //
    if (ch == '/')
        return 6; //
    if (ch == '(')
        return 7; //
    if (ch == ')')
        return 8; //
    if (ch == '=')
        return 9; //
    if (ch == '[')
        return 10; //
    if (ch == ']')
        return 11; //
    if (ch == '{')
        return 12; //
    if (ch == '}')
        return 13; //
    if (ch == '>')
        return 14; //
    if (ch == '<')
        return 15; //
    if (isspace(ch))
        return 16; //
    if (ch == '!')
        return 17; //
    if (ch == '\n')
        return 18; //
    if (ch == ';')
        return 19; //
    if (ch == '\0')
        return 20; //
    return -1;
}
