#include "lexer.h"
#include <iostream>
#include <stdexcept>


Lexer::Lexer(std::string input) : input_text(input),
    i(0), j(0),
    pos(0),
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

    return { type, result, pos, j + 1 };
}

std::vector<Token> Lexer::get_tokens() {
    std::vector<Token> tokens;

    auto token = get_next_token();

    tokens.push_back(token);

    while (true)
    {
        // ÏÐÈ ÎØÈÁÊÅ ÂÛÂÎÄÈÒÑß ÍÅ ÒÎÒ POS!!!
        if (token.type == -1)
        {
            error_output(token);
        }
        else if (token.type == 8)
        {
            tokens.push_back(token);
            break;
        }
        else
        {
            //debug
            //std::cout << "Token: " << token.value
            // << " | Type: " << token.type
            //<< " | Pos: " << token.line
            // << " | Column: " << token.column << std::endl;
        }
        token = get_next_token();
        tokens.push_back(token);
    }
    return tokens;
}
void Lexer::semantic_program(int num)
{
    switch (num)
    {
    case 1:
        name = input_text[i];
        i += 1;
        pos += 1;
        break; //
    case 2:
        int_num = input_text[i] - '0';
        i += 1;
        pos += 1;
        break; //
    case 3:
        type = ERROR;
        i = input_text.length();
        result = "Îøèáêà";
        break; //
    case 4:
        type = static_cast<Type>(input_text[i]);
        result = input_text[i];
        i += 1;
        pos += 1;
        break; //
    case 5:
        i += 1;
        pos += 1;
        break; //
    case 6:
        name += input_text[i];
        i += 1;
        pos += 1;
        break; //
    case 7:
        if (table_encoding.find(name) != table_encoding.end())
        {
            type = static_cast<Type>(table_encoding.find(name)->second);
            result = table_encoding.find(name)->first;
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
        pos = 0;
        j += 1;
        break; //
    case 9:
        int_num = int_num * 10 + (input_text[i] - '0');
        i += 1;
        pos += 1;
        break; //
    case 10:
        real_num = int_num;
        i += 1;
        pos += 1;
        decimal_count = 10;
        break; //
    case 11:
        type = INTEGER;
        //i -= 1;
        result = std::to_string(int_num);
        break; //
    case 12:
        type = EQUAL;
        result = "==";
        i += 1;
        pos += 1;
        break; //
    case 13:
        type = static_cast<Type>(input_text[i - 1]);
        result = input_text[i - 1];
        //i -= 1;
        break; //
    case 14:
        i -= 1;
        break; //
    case 15:
        type = NOT_EQUALS;
        result = "!=";
        i += 1;
        pos += 1;
        break; //
    case 16:
        real_num += (input_text[i] - '0') / decimal_count;
        decimal_count *= 10;
        i += 1;
        pos += 1;
        break; //
    case 17:
        type = REAL;
        //i -= 1;
        result = real_num;
        break; //
    case 18:
        type = GREATER_OR_EQUAL;
        i += 1;
        pos += 1;
        result = ">=";
        break; //
    case 19:
        type = LESS_OR_EQUAL;
        i += 1;
        pos += 1;
        result = "<=";
        break; //
    case 20:
        type = END_OF_INPUT;
        //i += 1;
        result = "";
        break; //
    }
}

/*void Lexer::semantic_program(int num)
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
        i = input_text.length();
        result = "Îøèáêà";
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
            result = table_encoding.find(name)->first;
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
        result = std::to_string(int_num);
        break; //
    case 12:
        type = EQUALS;
        result = "==";
        i += 1;//
        break; //
    case 13:
        type = input_text[i - 1];
        result = input_text[i - 1];
        //i -= 1;
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
        //i -= 1;
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
        //i += 1;
        result = "êîíåö";
        break; //
    }
}*/



int Lexer::encode_char(char ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return 0; // «á»
    if (isdigit(ch))
        return 1; // «ö»
    if (ch == '\n')
        return 18;
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
        return 17; // //
    if (ch == ';')
        return 19; //
    if (ch == '\0')
        return 20; //
    return -1;
}
