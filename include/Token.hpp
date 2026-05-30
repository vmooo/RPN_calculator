#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string_view>

namespace rpn {
    enum TokenType {
        NULL_TOKEN = 0,
        LITERAL_INTEGER,
        OPERATOR_PLUS, // +
        OPERATOR_MINUS, // -
        OPERATOR_MUL, // *
        OPERATOR_DIV, // /
        OPERATOR_MOD, // %
        OPERATOR_POW // ^
    };

    struct Token {
        std::string_view value;
        TokenType token_type;
    };
}

#endif // TOKEN_HPP
