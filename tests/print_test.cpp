#include "evaluation/builtin_functions/print/Print.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(print_test, ShouldPrintStringArgument) {
    const std::vector<SyntaxTreeNode *> args = {
            new SyntaxTreeNode(new Token(Token::String, "\"Hello World\"")),
    };

    const auto actual = Print().evaluate(args);

    EXPECT_EQ(*actual->token->token == "Hello World", true);
}

TEST(print_test, ShouldPrintMultipleStringArguments) {
    const std::vector<SyntaxTreeNode *> args = {
            new SyntaxTreeNode(new Token(Token::String, "\"Hello\"")),
            new SyntaxTreeNode(new Token(Token::String, "\" World\"")),
    };

    const auto expected = SyntaxTreeNode(new Token(Token::String, "Hello World"));
    const auto actual = *Print().evaluate(args);

    EXPECT_EQ(actual == expected, true);
}

TEST(print_test, ShouldPrintIntegers) {
    const std::vector<SyntaxTreeNode *> args = {
            new SyntaxTreeNode(new Token(Token::Integer, "1")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    const auto expected = SyntaxTreeNode(new Token(Token::String, "12"));
    const auto actual = *Print().evaluate(args);

    EXPECT_EQ(actual == expected, true);
}

TEST(print_test, ShouldEvaluateOperandsBeforePrinting) {
    const std::vector<SyntaxTreeNode *> args = {
            new SyntaxTreeNode(new Token(Token::String, "\"The result is: \"")),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "+"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "1")),
                            new SyntaxTreeNode(new Token(Token::Integer, "2")),
                    }),
    };

    const auto expected = SyntaxTreeNode(new Token(Token::String, "The result is: 3"));
    const auto actual = *Print().evaluate(args);

    EXPECT_EQ(actual == expected, true);
}
