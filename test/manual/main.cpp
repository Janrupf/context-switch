#include "context_switch/context_switch.hpp"

#include <iostream>

extern "C" void test_entry() {
    std::cout << "Hello World" << std::endl;
}

int main(int argc, const char **argv) {
    context_switch::context current_context = context_switch::current_context();
    context_switch::context context = context_switch::new_context(8192*16, test_entry);
    context_switch::jump_context(&current_context, &context);
    return 0;
}