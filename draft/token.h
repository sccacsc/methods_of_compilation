#ifndef TOKEN_H
#define TOKEN_H

#include <string>

struct Token {
    int type;
    std::string value;
    int line, column;
};

#endif // TOKEN_H
