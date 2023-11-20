#ifndef DUMMYLISP_TOKEN_H
#define DUMMYLISP_TOKEN_H

#include <iostream>
#include <utility>

class Token {
public:
    enum TokenType {
        OpenBracket,
        ClosedBracket,
        Symbol,
        Integer,
        String,
        Invalid
    };

    TokenType type;
    std::string token;

    Token() : type(Token::Invalid) {}

    Token(TokenType type, std::string token)
            : type(type),
              token(std::move(token)) {}

    bool operator==(const Token &object) const {
        return token == object.token;
    }
};

#endif
