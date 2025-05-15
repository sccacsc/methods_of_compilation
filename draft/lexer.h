#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <map>

class Lexer
{
public:
    Lexer(std::string input);
    ~Lexer();
    Token get_next_token();

private:
    // передача номера семантической программы и её выполнение
    void semantic_program(int num);

    std::string input_text; // входной текст
    int i, j;               // номер символа в строке, номер строки входного текста
    int decimal_count;      // счетчик для вещестевенного числа
    int int_num;            // целое число, либо целая часть вещесвенного
    float real_num;         // вещественное число
    std::string name;       // строка символов, либо имя
    std::string result;

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
    int type = ERROR;

    // состояния
    enum State
    {
        S,  //
        I,  //
        C,  //
        B,  //
        R,  //
        G,  //
        D,  //
        F,  //
        FF, //
        O   //
    };

    // определить столбец
    int encode_char(char ch);

    // таблица переходов
    const int transition_table[8][21] = {
        {I, C, O, F, F, F, F, F, F, B, F, F, F, F, R, R, S, G, S, F, F},              // S
        {I, I, O, FF, FF, FF, FF, FF, FF, FF, FF, FF, O, O, FF, FF, F, FF, O, F, O}, // I
        {O, C, D, FF, FF, FF, FF, O, FF, FF, O, FF, O, O, FF, FF, FF, FF, O, F, O},   // C
        {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, F, O, O, O, O},         // B
        {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, F, O, O, O, O},         // R
        {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, F, O, O, O, O},         // L
        {O, O, O, O, O, O, O, O, O, F, O, O, O, O, O, O, O, O, O, O, O},              // G
        {O, D, O, FF, FF, FF, FF, O, FF, FF, O, O, O, O, FF, FF, FF, FF, O, FF, O}    // D
    };
    // таблица служебных слов
    const std::map<std::string, int> table_encoding = {
        {"if", 100},
        {"else", 101},
        {"while", 102},
    };
    // таблица семантических действий
    const int semantic_table[8][21] = {
        {1, 2, 3, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 5, 5, 5, 4, 8, 4, 20},             // S
        {6, 6, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7, 3, 7, 3},              // I
        {3, 9, 10, 11, 11, 11, 11, 3, 11, 11, 3, 11, 3, 3, 11, 11, 11, 11, 3, 11, 3}, // C
        {13, 13, 3, 13, 13, 3, 3, 13, 3, 12, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3},        // B
        {4, 4, 3, 4, 4, 3, 3, 4, 3, 18, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 3},             // R
        {4, 4, 3, 4, 4, 3, 3, 4, 3, 19, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 3},             // L
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 15, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},             // G
        {3, 16, 3, 17, 17, 17, 17, 3, 17, 17, 3, 3, 3, 3, 17, 17, 17, 17, 3, 17, 3}   // D
    };
};

#endif // LEXER_H
