#ifndef PARSER_H
#define PARSER_H

#include "utilities.h"

#include <vector>

class Parser{
    Parser(std::vector<Token> input_tokens);
    ~Parser();
    void parse();

};

#endif // PARSER_H
