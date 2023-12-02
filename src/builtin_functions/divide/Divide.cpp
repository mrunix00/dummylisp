#include "Divide.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"

SyntaxTreeNode Divide::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int result = std::stoi(Evaluate::evaluate(args[0]).token.token);

    for (int i = 1; i < args.size(); i++) {
        auto arg = Evaluate::evaluate(args[i]).token;
        if (arg.type != Token::Integer) {
            throw SyntaxError(args[i].token.token + " is not a number",
                              args[i].token.line, args[i].token.column);
        }
        result /= std::stoi(arg.token);
    }

    return SyntaxTreeNode(Token(Token::Integer, std::to_string(result)));
}
