# Function table
.global __context_switch_save_registers
.global __context_switch_get_stack_ptr
.global __context_switch_get_instruction_ptr
.global __context_switch_jump_context

.extern __context_switch_jump_get_start_address

# Function to save all registers except the stack and instruction pointer
# Param 0: context_switch::register_save *output
__context_switch_save_registers:
    mov %r15, 0x00(%rdi)
    mov %r14, 0x08(%rdi)
    mov %r13, 0x10(%rdi)
    mov %r12, 0x18(%rdi)
    mov %rbx, 0x20(%rdi)
    mov %rbp, 0x28(%rdi)
    ret

# Function to retrieve the stack pointer
__context_switch_get_stack_ptr:
    mov %rsp, %rax
    ret

# Function to really do the jump to a new context
# Param 0: context_switch::context *current_context
# Param 1: context_switch::context *new_context
__context_switch_jump_context:
    # Set the instruction pointer in the current context to the return address
    pop %rax
    mov %rax, 0x00(%rdi)
    push %rax

    # Get stack start from C++
    # Our second argument is the first argument to the call
    mov %rsi, %rdi
    call __context_switch_jump_get_start_address

    # Back up the current stack pointer into rax
    mov %rsp, %rcx

    # Restore the stack pointer
    mov %rax, %rsp

    # Save the current registers
    push %rcx # our stack pointer
    push %r15
    push %r14
    push %r13
    push %r12
    push %rbx
    push %rbp

    # Save MMX and x87
    sub $8, %rsp
    stmxcsr 0x00(%rsp)
    fnstcw 0x04(%rsp)

    # Begin restoring the new context
    mov 0x08(%rsi), %r15
    mov 0x10(%rsi), %r14
    mov 0x18(%rsi), %r13
    mov 0x20(%rsi), %r12
    mov 0x28(%rsi), %rbx
    mov 0x30(%rsi), %rbp

    # Mov 3rd argument to first

    # And finally, call the address
    call *0x00(%rsi)

    # Restore x87 and MMX
    ldmxcsr 0x00(%rsp)
    fldcw 0x04(%rsp)
    add $8, %rsp

    # Restore the original context
    pop %rbp
    pop %rbx
    pop %r12
    pop %r13
    pop %r14
    pop %r15

    # Restore the stack pointer
    pop %rsp

    ret