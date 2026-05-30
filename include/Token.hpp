#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace rpn {
    enum Token {
        LITERAL_INTEGER = 0,
        OPERATOR_PLUS, // +
        OPERATOR_MINUS, // -
        OPERATOR_MUL, // *
        OPERATOR_DIV, // /
        OPERATOR_MOD, // %
        OPERATOR_POW // ^
    };
}

#endif // TOKEN_HPP
