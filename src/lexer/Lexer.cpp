#include "Lexer.h"
#include <regex>

std::vector<Token> Lexer::tokenize(const std::string &line) {
    std::vector<Token> result;
    std::string currentToken;
    int currentLine = 1;
    int currentLineChar = 0;
    int currentColumn = 0;

    for (auto c: line) {
        currentLineChar++;

        if (c != '(' && c != ')' && (c != ' ' || currentToken[0] == '"') &&
            (c != '"' || currentToken[0] != '"') && c != '\n') {
            currentToken.append(1, c);
            continue;
        }
        currentColumn++;

        if (!currentToken.empty()) {
            if (std::regex_match(currentToken, std::regex("[+-]?[0-9]+"))) {
                result.emplace_back(Token::Integer, currentToken,
                                    currentLine, currentColumn);
            } else if (std::regex_match(currentToken,
                                        std::regex("-?[0-9]+([\\.][0-9]+)?"))) {
                result.emplace_back(Token::Decimal, currentToken,
                                    currentLine, currentColumn);
            } else if (c != '"') {
                result.emplace_back(Token::Symbol, currentToken,
                                    currentLine, currentColumn);
            } else {
                currentToken.append(1, '"');
                result.emplace_back(Token::String, currentToken,
                                    currentLine, currentColumn);
            }
            if (c == '\n') {
                currentLine++;
                currentLineChar = 0;
            }
            currentColumn = currentLineChar;
        }

        currentToken = "";
        if (c == '(')
            result.emplace_back(Token::OpenBracket, "(",
                                currentLine, currentColumn);
        else if (c == ')')
            result.emplace_back(Token::ClosedBracket, ")",
                                currentLine, currentColumn);
    }

    return result;
}
