#include "utilities.h"

void error_output(Token token) {
    throw std::runtime_error("Îøèáêà àíàëèçà | Íîìåð ñòðîêè: " + std::to_string(token.line) +
                             " | Íîìåð ñèìâîëà â ñòðîêå: " + std::to_string(token.pos));
}
