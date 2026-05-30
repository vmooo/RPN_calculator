#include <gtest/gtest.h>

#include "../include/Parser.hpp"
#include "../include/rpn.hpp"

TEST(test_stack, test_initialization_1) {
    constexpr rpn::Stack<int, 10> stack;
    ASSERT_TRUE(stack.data.size() == 10);
}

TEST(test_stack, test_initialization_2) {
    constexpr rpn::Stack<int, 10> stack;
    ASSERT_TRUE(stack.capacity == 0);
}

TEST(test_stack, test_is_empty) {
    constexpr rpn::Stack<int, 10> stack;
    ASSERT_TRUE(stack.is_empty());
}

TEST(test_stack, test_throw_if_empty) {
    try {
        constexpr rpn::Stack<int, 10> stack;
        stack.throw_if_empty();
    }
    catch (...) {
        ASSERT_TRUE(true);
    }
}

TEST(test_stack, test_push) {
    constexpr auto makeStack = []() {
        rpn::Stack<int, 5> s;
        s.push(2);
        s.push(3);
        return s;
    };

    constexpr auto stack = makeStack();
    ASSERT_TRUE(stack.data[0] == 2 && stack.data[1] == 3);
}

TEST(test_stack, test_top) {
    constexpr auto stack = []() {
        rpn::Stack<int, 5> s;
        s.push(2);
        s.push(3);
        return s;
    }();

    ASSERT_TRUE(stack.top() == 3);
}

TEST(test_stack, test_pop) {
    constexpr auto stack = []() {
        rpn::Stack<int, 5> s;
        s.push(2);
        s.push(3);
        s.pop();
        return s;
    }();

    ASSERT_TRUE(stack.top() == 2);
}

TEST(test_stack, test_pop2) {
    auto stack = []() {
        rpn::Stack<int, 5> s;
        s.push(2);
        s.push(3);
        return s;
    }();
    ASSERT_TRUE(stack.pop() == 3);
}

TEST(test_parser, test1) {
    constexpr rpn::Parser parser;
    constexpr auto array = parser("1");
    ASSERT_TRUE(array[0].value == "1");
}

TEST(test_parser, test2) {
    constexpr auto array = rpn::Parser().operator()("1");
    ASSERT_TRUE(array[0].token_type == rpn::TokenType::LITERAL_INTEGER);
}

TEST(test_parser, test3) {
    constexpr auto array = rpn::Parser().operator()("^");
    ASSERT_TRUE(array[0].token_type == rpn::OPERATOR_POW);
}

TEST(test_parser, test4) {
    constexpr auto array = rpn::Parser().operator()("2 3");
    ASSERT_TRUE(array[0].value == "2" && array[1].value == "3");
}

TEST(test_parser, test5) {
    constexpr auto array = rpn::Parser().operator()("2 3 +");
    ASSERT_TRUE(array[2].token_type == rpn::OPERATOR_PLUS && array[2].value == "+");
}

TEST(test_parser, test6) {
    constexpr auto array = rpn::Parser().operator()("2 3 + -");
    ASSERT_TRUE(array[3].token_type == rpn::OPERATOR_MINUS && array[3].value == "-");
}

TEST(test_parser, test7) {
    constexpr auto array = rpn::Parser().operator()("2 3 + - *");
    ASSERT_TRUE(array[4].token_type == rpn::OPERATOR_MUL && array[4].value == "*");
}

TEST(test_parser, test8) {
    constexpr auto array = rpn::Parser().operator()("2 3 + - * /");
    ASSERT_TRUE(array[5].token_type == rpn::OPERATOR_DIV && array[5].value == "/");
}

TEST(test_parser, test9) {
    constexpr auto array = rpn::Parser().operator()("2 3 + - * / %");
    ASSERT_TRUE(array[6].token_type == rpn::OPERATOR_MOD && array[6].value == "%");
}

TEST(test_rpn, test_is_not_operation) {
    rpn::Token token;
    token.token_type = rpn::OPERATOR_MINUS;
    ASSERT_FALSE(rpn::is_not_operation(token));
}

TEST(test_rpn, test_is_not_operation_2) {
    rpn::Token token;
    token.token_type = rpn::LITERAL_INTEGER;
    ASSERT_TRUE(rpn::is_not_operation(token));
}

TEST(test_rpn, test_sum) {
    using namespace rpn;
    ASSERT_TRUE("2 3 +"_rpn == 5);
}


