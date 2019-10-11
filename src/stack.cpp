#include <stdexcept>
#include "context_switch/stack.hpp"

extern "C" uint64_t __context_switch_get_stack_ptr();

namespace context_switch {
    stack::stack(char *stack_pointer, size_t size, bool external) :
        stack_pointer(stack_pointer), size(size), external(external) {}

    stack stack::allocate_stack(size_t size) {
        if(size % 16 != 0) {
            throw std::invalid_argument("size has to be multiple of 16");
        }

        char *new_stack = (char *) std::aligned_alloc(16, size);
        return stack(new_stack, size, false);
    }

    stack stack::current() {
        return stack(reinterpret_cast<char *>(__context_switch_get_stack_ptr()), 0, true);
    }

    stack::~stack() {
        if(!external) {
            std::free(stack_pointer);
        }
    }

    stack::stack(stack &&other) noexcept :
        stack_pointer(other.stack_pointer), size(other.size), external(other.external) {
        other.external = true;
        other.stack_pointer = nullptr;
    }

    stack &stack::operator=(stack &&other) noexcept {
        external = other.external;
        size = other.size;
        stack_pointer = other.stack_pointer;
        other.external = true;
        other.size = 0;
        other.stack_pointer = nullptr;

        return *this;
    }

    uint64_t stack::get_start_address() {
        return reinterpret_cast<uint64_t>(stack_pointer) + size;
    }
}
