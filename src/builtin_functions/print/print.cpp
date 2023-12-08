#include "print.h"
#include "eval/eval.h"
#include "parser/SyntaxTreeNode.h"
#include <string>

SyntaxTreeNode Print::evaluate(const std::vector<SyntaxTreeNode> &args) {
    std::string result;
    for (const SyntaxTreeNode &arg: args) {
        const auto evArg = Evaluate::evaluate(arg).token;
        if (evArg.type == Token::String) {
            result += evArg.token.substr(1, evArg.token.size() - 2);
        } else if (evArg.type == Token::Integer) {
            result += evArg.token;
        }
    }
    return SyntaxTreeNode(Token(Token::String, result));
}