#ifndef LEXER_H
#define LEXER_H

#include "utilities.h"
#include <vector>

class Lexer
{
public:
    Lexer(std::string input);
    ~Lexer();
    Token get_next_token();
    std::vector<Token> get_tokens();

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

    Type type = ERROR;

    // состояния
    enum State
    {
        S,  //
        I,  //
        C,  //
        B,  //
        R,  //
        L,  //
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
        {I, C, O, F, F, F, F, F, F, B, F, F, F, F, R, L, S, G, S, F, F},              // S
        {I, I, O, FF, FF, FF, FF, FF, FF, FF, FF, FF, O, O, FF, FF, FF, FF, O, F, O}, // I
        {O, C, D, FF, FF, FF, FF, O, FF, FF, O, FF, O, O, FF, FF, FF, FF, O, F, O},   // C
        {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, FF, O, O, O, O},         // B
        {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, F, O, O, O, O},         // R
        {FF, FF, O, FF, FF, O, O, FF, FF, F, O, O, O, O, O, O, F, O, O, O, O},         // L
        {O, O, O, O, O, O, O, O, O, F, O, O, O, O, O, O, O, O, O, O, O},              // G
        {O, D, O, FF, FF, FF, FF, O, FF, FF, O, O, O, O, FF, FF, FF, FF, O, FF, O}    // D
    };

    // таблица семантических действий
    const int semantic_table[8][21] = {
        {1, 2, 3, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 5, 5, 5, 4, 8, 4, 20},             // S
        {6, 6, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7, 3, 7, 3},              // I
        {3, 9, 10, 11, 11, 11, 11, 3, 11, 11, 3, 11, 3, 3, 11, 11, 11, 11, 3, 11, 3}, // C
        {13, 13, 3, 13, 13, 3, 3, 13, 3, 12, 3, 3, 3, 3, 3, 3, 13, 3, 3, 3, 3},        // B
        {4, 4, 3, 4, 4, 3, 3, 4, 3, 18, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 3},             // R
        {4, 4, 3, 4, 4, 3, 3, 4, 4, 19, 3, 3, 3, 3, 3, 3, 5, 3, 3, 3, 3},             // L
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 15, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},             // G
        {3, 16, 3, 17, 17, 17, 17, 3, 17, 17, 3, 3, 3, 3, 17, 17, 17, 17, 3, 17, 3}   // D
    };
};

#endif // LEXER_H
