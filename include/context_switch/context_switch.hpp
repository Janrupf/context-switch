#pragma once

#include "stack.hpp"
#include <cstdint>

namespace context_switch {
    using context_switch_entry_function = void(*)();

    struct register_save {
        uint64_t r15;
        uint64_t r14;
        uint64_t r13;
        uint64_t r12;
        uint64_t rbx;
        uint64_t rbp;
    };

    struct context {
        uint64_t instruction_pointer;
        register_save registers;
        stack stack_pointer;
    };

    context current_context();
    context new_context(uint64_t stack_size, context_switch_entry_function entry);
    void jump_context(context *current_context, context *new_context);
}