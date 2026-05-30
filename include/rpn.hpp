#ifndef RPN_CALCULATOR
#define RPN_CALCULATOR

#include "Stack.hpp"
#include "Parser.hpp"

namespace rpn {

    using stack_t = Stack<int, max_stack_size>;

    constexpr int parse_int(std::string_view sv) {
        int result = 0;
        for (char c : sv) {
            if (c < '0' || c > '9') break;
            result = result * 10 + (c - '0');
        }
        return result;
    }

    constexpr bool is_not_operation(const Token& token) {
        return token.token_type == rpn::LITERAL_INTEGER;
    }

    constexpr int pow_int(const int base, const int exp) {
        int result = 1;
        for (int i = 0; i < exp; ++i) result *= base;
        return result;
    }

    constexpr int apply_operation(const int a, const int b, TokenType operation_type) {
        switch (operation_type) {
            case OPERATOR_PLUS: return a + b;
            case OPERATOR_MINUS: return a - b;
            case OPERATOR_MUL: return a * b;
            case OPERATOR_POW: return pow_int(a, b);
            case OPERATOR_DIV:
                assert(b != 0);
                return a / b;
            case OPERATOR_MOD:
                assert(b != 0);
                return a % b;
            default: throw std::runtime_error("unknown operation");
        }
    }

    constexpr int operator""_rpn(const char* str, std::size_t len) {
        const std::string_view sv(str, len);
        constexpr Parser parser;
        auto token_array = parser(sv);

        stack_t stack;
        std::size_t i = 0;

        while (token_array[i].token_type != rpn::NULL_TOKEN) {
            assert(i < token_array.size());

            Token& current_token = token_array[i];

            if (is_not_operation(current_token)) {
                stack.push(parse_int(current_token.value));
            }
            else {
                const int op2 = stack.pop();
                const int op1 = stack.pop();
                stack.push(apply_operation(op1, op2, current_token.token_type));
            }

            ++i;
        }

        return stack.top();
    }
}

#endif // RPN_CALCULATOR