#include "context_switch/context_switch.hpp"

#include <exception>
#include <utility>

extern "C" void __context_switch_save_registers(context_switch::register_save *output);
extern "C" void __context_switch_jump_context(
        context_switch::context *current_context,
        context_switch::context *new_context
);

extern "C" size_t __context_switch_jump_get_start_address(context_switch::context *context) {
    return context->stack_pointer.get_start_address();
}

namespace context_switch {
    context current_context() {
        register_save register_save{};
        __context_switch_save_registers(&register_save);

        return {0, register_save, stack::current()};
    }

    context new_context(size_t stack_size, context_switch_entry_function entry) {
        auto new_stack = stack::allocate_stack(stack_size);
        register_save save{};
        save.rbp = new_stack.get_start_address();

        return {reinterpret_cast<uint64_t>(entry), save, std::move(new_stack)};
    }

    void jump_context(context *current_context, context *new_context) {
        __context_switch_jump_context(current_context, new_context);
    }
}