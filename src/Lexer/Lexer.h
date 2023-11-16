#ifndef DUMMYLISP_LEXER_H
#define DUMMYLISP_LEXER_H

#include "../Tokens/Tokens.h"
#include <vector>


class Lexer {
public:
    static std::vector<Token> parse(const std::string &);
};


#endif
