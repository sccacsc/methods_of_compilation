#ifndef LEXER_H
#define LEXER_H

#include "token.h"

enum state
{
    S,
    I,
    C,
    B,
    R,
    G,
    D,
    F,
    FF,
    O
}; // FF(f*)

const int transition_table[7][20] = {
    {I, C, O, F, F, F, F, F, F, B, F, F, F, F, R, R, S, G, S, F},              // S
    {I, I, O, FF, FF, FF, FF, FF, FF, FF, FF, FF, O, O, FF, FF, FF, FF, O, F}, // I
    {O, C, D, FF, FF, FF, FF, O, FF, FF, O, FF, O, O, FF, FF, FF, FF, O, F},   // C
    {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, F, O, O, O},         // B
    {FF, FF, O, FF, FF, O, O, FF, O, F, O, O, O, O, O, O, F, O, O, O},         // R
    {O, O, O, O, O, O, O, O, O, F, O, O, O, O, O, O, O, O, O, O},              // G
    {O, D, O, FF, FF, FF, FF, O, FF, FF, O, O, O, O, FF, FF, FF, FF, O, FF}
};

class Lexer
{
public:
private:
    void semantic_program(int num);
};

#endif // LEXER_H
