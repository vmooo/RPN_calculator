#ifndef RPN_CALCULATOR_COMPILE_TIME_STACK_H
#define RPN_CALCULATOR_COMPILE_TIME_STACK_H

#include <cstddef>
#include <array>
#include <cassert>

namespace rpn {
    constexpr std::size_t max_stack_size = 256;

    template<typename T, std::size_t size>
    struct Stack {
        std::array<T, size> data{};
        std::size_t capacity{0};

        constexpr Stack() {
            assert(size <= max_stack_size);
        }

        [[nodiscard]] constexpr bool is_empty() const {
            return capacity == 0;
        }

        constexpr void throw_if_empty() const {
            if (is_empty()) throw std::runtime_error("stack is empty");
        }

        constexpr void push(T value) {
            if (capacity >= size) {
                throw std::runtime_error("stack overflow");
            }
            assert(capacity < size);
            data[capacity] = value;
            ++capacity;
        }

        [[nodiscard]] constexpr T top() const {
            throw_if_empty();

            assert(capacity <= size && capacity > 0);
            return data[capacity - 1];
        }

        constexpr T pop() {
            throw_if_empty();

            assert(capacity <= size && capacity > 0);
            return data[--capacity];
        }
    };
};

#endif //RPN_CALCULATOR_COMPILE_TIME_STACK_H