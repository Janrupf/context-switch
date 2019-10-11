#pragma once

#include <cstdint>
#include <cstdlib>

namespace context_switch {
    /**
     * \brief Helper class representing a stack instance
     */
    class stack {
    private:
        char *stack_pointer;
        size_t size;
        bool external;

        explicit stack(char *stack_pointer, size_t size, bool external);

    public:
        static stack allocate_stack(size_t size);
        static stack current();

        ~stack();

        stack(const stack &other) = delete;
        stack &operator =(const stack &other) = delete;

        stack(stack &&other) noexcept;
        stack &operator =(stack &&other) noexcept;

        uint64_t get_start_address();
    };
}