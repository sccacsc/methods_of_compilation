#ifndef PARSER_H
#define PARSER_H

#include "utilities.h"

#include <vector>

class Parser{
private:
    std::vector<Token> tokens;
public:
    Parser(std::vector<Token> input_tokens);
    ~Parser();
    void parse();
    bool is_terminal(const std::string& symbol);

};

#endif // PARSER_H
