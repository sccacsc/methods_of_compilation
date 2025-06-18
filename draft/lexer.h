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
    // ïåðåäà÷à íîìåðà ñåìàíòè÷åñêîé ïðîãðàììû è å¸ âûïîëíåíèå
    void semantic_program(int num);

    std::string input_text; // âõîäíîé òåêñò
    int i, j;               // íîìåð ñèìâîëà â ñòðîêå, íîìåð ñòðîêè âõîäíîãî òåêñòà
    int pos;
    int decimal_count;      // ñ÷åò÷èê äëÿ âåùåñòåâåííîãî ÷èñëà
    int int_num;            // öåëîå ÷èñëî, ëèáî öåëàÿ ÷àñòü âåùåñâåííîãî
    float real_num;         // âåùåñòâåííîå ÷èñëî
    std::string name;       // ñòðîêà ñèìâîëîâ, ëèáî èìÿ
    std::string result;

    Type type = ERROR;

    // ñîñòîÿíèÿ
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

    // îïðåäåëèòü ñòîëáåö
    int encode_char(char ch);

    // òàáëèöà ïåðåõîäîâ
    const int transition_table[8][21] = {
        {I, C, O, F, F, F, F, F, F, B, F, F, F, F, R, L, S, G, S, F, F},              // S
        {I, I, O, FF, FF, FF, FF, FF, FF, FF, FF, FF, O, O, FF, FF, FF, FF, O, F, O}, // I
        {O, C, D, FF, FF, FF, FF, O, FF, FF, O, FF, O, O, FF, FF, FF, FF, O, F, O},   // C
        {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, FF, O, O, O, O},         // B
        {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, FF, O, O, O, O},         // R
        {FF, FF, O, FF, FF, O, O, FF, FF, F, O, O, O, O, O, O, FF, O, O, O, O},         // L
        {O, O, O, O, O, O, O, O, O, F, O, O, O, O, O, O, O, O, O, O, O},              // G
        {O, D, O, FF, FF, FF, FF, O, FF, FF, O, O, O, O, FF, FF, FF, FF, O, FF, O}    // D
    };

    // òàáëèöà ñåìàíòè÷åñêèõ äåéñòâèé
    const int semantic_table[8][21] = {
        {1, 2, 3, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 4, 5, 4, 8, 4, 20},             // S
        {6, 6, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7, 3, 7, 3},              // I
        {3, 9, 10, 11, 11, 11, 11, 3, 11, 11, 3, 11, 3, 3, 11, 11, 11, 11, 3, 11, 3}, // C
        {13, 13, 3, 13, 13, 3, 3, 13, 3, 12, 3, 3, 3, 3, 3, 3, 13, 3, 3, 3, 3},        // B
        {4, 4, 3, 4, 4, 3, 3, 4, 3, 18, 3, 3, 3, 3, 3, 3, 13, 3, 3, 3, 3},             // R
        {4, 4, 3, 4, 4, 3, 3, 4, 4, 19, 3, 3, 3, 3, 3, 3, 13, 3, 3, 3, 3},             // L
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 15, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},             // G
        {3, 16, 3, 17, 17, 17, 17, 3, 17, 17, 3, 3, 3, 3, 17, 17, 17, 17, 3, 17, 3}   // D
    };
};

#endif // LEXER_H
