#include <gtest/gtest.h>
#include "../include/rpn.hpp"

TEST(test_stack, test_initialization_1) {
    constexpr rpn::compile_time_stack<int, 10> stack;
    ASSERT_TRUE(stack.data.size() == 10);
}

TEST(test_stack, test_initialization_2) {
    constexpr rpn::compile_time_stack<int, 10> stack;
    ASSERT_TRUE(stack.capacity == 0);
}

TEST(test_stack, test_is_empty) {
    constexpr rpn::compile_time_stack<int, 10> stack;
    ASSERT_TRUE(stack.is_empty());
}

TEST(test_stack, test_throw_if_empty) {
    try {
        constexpr rpn::compile_time_stack<int, 10> stack;
        stack.throw_if_empty();
    }
    catch (...) {
        ASSERT_TRUE(true);
    }
}

TEST(test_stack, test_push) {
    constexpr auto makeStack = []() {
        rpn::compile_time_stack<int, 5> s;
        s.push(2);
        s.push(3);
        return s;
    };

    constexpr auto stack = makeStack();
    ASSERT_TRUE(stack.data[0] == 2 && stack.data[1] == 3);
}

TEST(test_stack, test_top) {
    constexpr auto stack = []() {
        rpn::compile_time_stack<int, 5> s;
        s.push(2);
        s.push(3);
        return s;
    }();

    ASSERT_TRUE(stack.top() == 3);
}

TEST(test_stack, test_pop) {
    constexpr auto stack = []() {
        rpn::compile_time_stack<int, 5> s;
        s.push(2);
        s.push(3);
        s.pop();
        return s;
    }();

    ASSERT_TRUE(stack.top() == 2);
}


