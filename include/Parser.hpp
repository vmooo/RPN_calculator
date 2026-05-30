#ifndef PARSER_HPP
#define PARSER_HPP

#include <array>
#include <cstddef>
#include <string_view>

#include "Token.hpp"

namespace rpn {

    constexpr std::size_t max_literal_size = 256;

    /// Functional object that
    /// parse std::string_view with RPN
    /// into std::array of tokens
    class Parser {

        static constexpr bool is_integer(const std::string_view sv) noexcept {
            return !sv.empty() && sv.find_first_not_of("0123456789") == sv.npos;
        }

    public:
        constexpr auto operator() (const std::string_view input) const  {
            std::array<Token, max_literal_size> result{};
            std::size_t index_of_last_token = 0;
            std::size_t start = 0;
            for (std::size_t i = 0; i <= input.size(); ++i) {
                if (i == input.size() || input[i] == ' ' || input[i] == ',') {
                    if (i > start) {
                        std::string_view sv = input.substr(start, i - start);
                        Token token;
                        token.value = sv;
                        token.token_type = rpn::NULL_TOKEN;
                        if (sv[0] == '+' && sv.size() == 1) {
                            token.token_type = rpn::TokenType::OPERATOR_PLUS;
                        }
                        else if (sv[0] == '-' && sv.size() == 1) {
                            token.token_type = rpn::TokenType::OPERATOR_MINUS;
                        }
                        else if (sv[0] == '*' && sv.size() == 1) {
                            token.token_type = rpn::TokenType::OPERATOR_MUL;
                        }
                        else if (sv[0] == '/' && sv.size() == 1) {
                            token.token_type = rpn::TokenType::OPERATOR_DIV;
                        }
                        else if (sv[0] == '%' && sv.size() == 1) {
                            token.token_type = rpn::TokenType::OPERATOR_MOD;
                        }
                        else if (sv[0] == '^' && sv.size() == 1) {
                            token.token_type = rpn::TokenType::OPERATOR_POW;
                        }
                        else if (is_integer(sv)) {
                            token.token_type = rpn::TokenType::LITERAL_INTEGER;
                        }
                        result[index_of_last_token++] = token;
                    }
                    start = i + 1;
                }
            }
            return result;
        }

        constexpr Parser() = default;
    };
}


#endif // PARSER_HPP
