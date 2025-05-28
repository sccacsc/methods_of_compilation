#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <map>

struct Token
{
    int type;
    std::string value;
    int line;
    int column;
};


// типы распознаной лексемы
enum Type
{
    ERROR = -1,           // ошибка
    NAME = 1,             // имя
    INTEGER = 2,          // целое число
    REAL = 3,             // вещественное число
    EQUALS = 4,           // знак равенства ==
    NOT_EQUALS = 5,       // знак сравнения !=
    GREATER_OR_EQUAL = 6, // больше или равно >=
    LESS_OR_EQUAL = 7,    // меньше или равно <=
    END_OF_INPUT = 8

};

// таблица служебных слов
const std::map<std::string, int> table_encoding = {
    {"if", 100},
    {"else", 101},
    {"while", 102},
    {"print", 103},
    {"read", 104},
    {"else", 105},
    {"int", 106},
    {"real", 107}
};

#endif // UTILITIES_H
