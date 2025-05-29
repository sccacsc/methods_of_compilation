#include "parser.h"

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>

Parser::Parser(std::vector<Token> input_tokens) : tokens(input_tokens){}

Parser::~Parser() = default;

bool Parser::is_terminal(const std::string& symbol) {
    return !(symbol[0] >= 'A' && symbol[0] <= 'Z');
}

using Rule = std::vector<std::string>;
using ParsingTable = std::map<std::string, std::map<Type, Rule>>;

ParsingTable parsing_table = {
    {"F", {
           {NAME,     {"name", "H", "=", "E", ";", "Q"}},
           {READ,     {"read", "(", "name", "H", ")", ";", "Q"}},
           {PRINT,    {"print", "(", "E", ")", ";", "Q"}},
           {IF,       {"if", "(", "C", ")", "{", "Q", "}", "K", "Q"}},
           {WHILE,    {"while", "(", "C", ")", "{", "Q", "}", "Q"}},
           {INTEGER,  {"int", "M", "F"}},
           {REAL,     {"real", "M", "F"}},
{END_OF_INPUT, {}},
           }},
    {"Q", {
           {NAME,     {"name", "H", "=", "E", ";", "Q"}},
           {READ,     {"read", "(", "name", "H", ")", ";", "Q"}},
           {PRINT,    {"print", "(", "E", ")", ";", "Q"}},
           {IF,       {"if", "(", "C", ")", "{", "Q", "}", "K", "Q"}},
           {WHILE,    {"while", "(", "C", ")", "{", "Q", "}", "Q"}},
           {ELSE,     {}},
           {RBRACE,   {}},
 {END_OF_INPUT, {}},
           }},
    {"M", {
              {NAME, {"name", ";"}}
          }},
    {"H", {
           {LBRACKET, {"[", "E", "]"}},
           {ASSIGN,   {}},
           {SEMICOLON, {}},
           }},
    {"C", {
           {NAME,     {"name", "H", "V", "U", "D"}},
           {INTEGER,  {"int", "V", "U", "D"}},
           {REAL,     {"real", "V", "U", "D"}},
           {LPAREN,   {"(", "E", ")", "V", "U", "D"}},
           }},
    {"D", {
           {EQUAL,            {"==", "E"}},
           {GREATER,          {">", "E"}},
           {GREATER_OR_EQUAL, {">=", "E"}},
           {LESS,             {"<", "E"}},
           {LESS_OR_EQUAL,    {"<=", "E"}},
           {NOT_EQUALS,       {"!=", "E"}},
           }},
    {"K", {
           {ELSE, {"else", "{", "Q", "}"}},
           {NAME, {}},
           {READ, {}},
           {PRINT, {}},
           {IF, {}},
           {WHILE, {}},
           }},
    {"E", {
           {NAME,    {"name", "H", "V", "U"}},
           {INTEGER, {"int", "V", "U"}},
           {REAL,    {"real", "V", "U"}},
           {LPAREN,  {"(", "E", ")", "V", "U"}},
           }},
    {"U", {
           {PLUS,  {"+", "T", "U"}},
           {MINUS, {"-", "T", "U"}},
           {RPAREN, {}},
           {SEMICOLON, {}},
           {RBRACKET, {}},
           }},
    {"T", {
           {NAME,    {"name", "H", "P"}},
           {INTEGER, {"int", "P"}},
           {REAL,    {"real", "P"}},
           {LPAREN,  {"(", "E", ")", "P"}},
           }},
    {"V", {
           {MULTIPLY, {"*", "P", "V"}},
           {DIVIDE,   {"/", "P", "V"}},
           {PLUS,     {}},
           {MINUS,    {}},
           {RPAREN,   {}},
           {SEMICOLON, {}},
           {RBRACKET, {}},
           }},
    {"P", {
              {NAME,    {"name", "H"}},
              {INTEGER, {"int"}},
              {REAL,    {"real"}},
              {LPAREN,  {"(", "E", ")"}},
              }},
    };


/*ParsingTable parsing_table = {
    {"F", {
           {NAME,     {"NAME", "H", "=", "E", ";", "Q"}},
           {READ,     {"READ", "(", "NAME", "H", ")", ";", "Q"}},
           {PRINT,    {"PRINT", "(", "E", ")", ";", "Q"}},
           {IF,       {"IF", "(", "C", ")", "{", "Q", "}", "K", "Q"}},
           {WHILE,    {"WHILE", "(", "C", ")", "{", "Q", "}", "Q"}},
           {INTEGER,  {"INTEGER", "M", "F"}},
           {REAL,     {"REAL", "M", "F"}},
           }},
    {"Q", {
           {NAME,     {"NAME", "H", "=", "E", ";", "Q"}},
           {READ,     {"READ", "(", "NAME", "H", ")", ";", "Q"}},
           {PRINT,    {"PRINT", "(", "E", ")", ";", "Q"}},
           {IF,       {"IF", "(", "C", ")", "{", "Q", "}", "K", "Q"}},
           {WHILE,    {"WHILE", "(", "C", ")", "{", "Q", "}", "Q"}},
           {ELSE,     {}},
           {RBRACE,   {}},
           }},
    {"M", {
              {NAME, {"NAME", ";"}}
          }},
    {"H", {
           {LBRACKET, {"[", "E", "]"}},
           {ASSIGN,   {}},
           {SEMICOLON, {}},
           }},
    {"C", {
           {NAME,     {"NAME", "H", "V", "U", "D"}},
           {INTEGER,  {"INTEGER", "V", "U", "D"}},
           {REAL,     {"REAL", "V", "U", "D"}},
           {LPAREN,   {"(", "E", ")", "V", "U", "D"}},
           }},
    {"D", {
           {EQUAL,            {"==", "E"}},
           {GREATER,          {">", "E"}},
           {GREATER_OR_EQUAL, {">=", "E"}},
           {LESS,             {"<", "E"}},
           {LESS_OR_EQUAL,    {"<=", "E"}},
           {NOT_EQUALS,       {"!=", "E"}},
           }},
    {"K", {
           {ELSE, {"ELSE", "{", "Q", "}"}},
           {NAME, {}},
           {READ, {}},
           {PRINT, {}},
           {IF, {}},
           {WHILE, {}},
           }},
    {"E", {
           {NAME,    {"NAME", "H", "V", "U"}},
           {INTEGER, {"INTEGER", "V", "U"}},
           {REAL,    {"REAL", "V", "U"}},
           {LPAREN,  {"(", "E", ")", "V", "U"}},
           }},
    {"U", {
           {PLUS,  {"+", "T", "U"}},
           {MINUS, {"-", "T", "U"}},
           {RPAREN, {}},
           {SEMICOLON, {}},
           {RBRACKET, {}},
           }},
    {"T", {
           {NAME,    {"NAME", "H", "P"}},
           {INTEGER, {"INTEGER", "P"}},
           {REAL,    {"REAL", "P"}},
           {LPAREN,  {"(", "E", ")", "P"}},
           }},
    {"V", {
           {MULTIPLY, {"*", "P", "V"}},
           {DIVIDE,   {"/", "P", "V"}},
           {PLUS,     {}},
           {MINUS,    {}},
           {RPAREN,   {}},
           {SEMICOLON, {}},
           {RBRACKET, {}},
           }},
    {"P", {
              {NAME,    {"NAME", "H"}},
              {INTEGER, {"INTEGER"}},
              {REAL,    {"REAL"}},
              {LPAREN,  {"(", "E", ")"}},
              }},
    };*/

void Parser::parse(){
    std::stack<std::string> st;     // Магазин (стек) для хранения ожидаемых символов
    st.push("F");                  // Начальный символ грамматики
    size_t index = 0;              // Индекс текущего токена

    while (!st.empty()) {
        std::string top = st.top(); st.pop(); // Получаем верхний элемент стека
        Token current_token = tokens[index];   // Получаем текущий токен

        // Если верхушка стека — терминал
        if (is_terminal(top)) {
            // Сравнение терминала с текущим токеном по значению и типу
            if (top == current_token.value ||
                (current_token.type == NAME) ||
                (top == "int" && current_token.type == INTEGER) ||
                (top == "real" && current_token.type == REAL) ||
                (top == "==" && current_token.type == EQUAL) ||
                (top == "!=" && current_token.type == NOT_EQUALS) ||
                (top == ">=" && current_token.type == GREATER_OR_EQUAL) ||
                (top == "<=" && current_token.type == LESS_OR_EQUAL)) {

                std::cout << "Match: " << top << std::endl;
                index++; // Успешное совпадение — переходим к следующему токену
            } else {
                std::cerr << "Syntax error: expected '" << top << "' but got '" << current_token.value << "'\n";
                return;
            }
        } else {
            // Вершина стека — нетерминал, ищем правило
            if (parsing_table[top].count(current_token.type)) {
                Rule rule = parsing_table[top][current_token.type];

                std::cout << top << " -> ";
                for (const auto& s : rule) std::cout << s << ' ';
                std::cout << std::endl;

                // Добавляем символы правила в стек в обратном порядке
                for (auto it = rule.rbegin(); it != rule.rend(); ++it) {
                    if (!it->empty()) st.push(*it);
                }
            } else {
                std::cerr << "No rule for nonterminal '" << top << "' with input '" << current_token.value << "'\n";
                return;
            }
        }
    }

    // Проверка на конец ввода
    if (tokens[index].type != END_OF_INPUT) {
        std::cerr << "Unexpected end of input\n";
    } else {
        std::cout << "Parsing completed successfully.\n";
    }
}
