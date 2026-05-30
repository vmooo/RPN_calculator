#ifndef RPN_CALCULATOR
#define RPN_CALCULATOR

#include "Stack.hpp"

namespace rpn {
    constexpr int operator""_rpn(const char* str, std::size_t len);
}

#endif // RPN_CALCULATOR