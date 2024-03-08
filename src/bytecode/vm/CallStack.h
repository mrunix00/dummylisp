#pragma once

#include "Stack.h"
#include "bytecode/objects/StackObject.h"
#include <cstdint>
#include <cstdlib>
#include <vector>

namespace Bytecode {
    struct StackFrame {
        uint32_t segment;
        uint32_t current_line;
    };

    class CallStack {
        StackFrame *stack;
        size_t stackframe_capacity;
        size_t stackframe_used;

        StackObject **local_registers;
        size_t local_registers_capacity;
        size_t local_registers_used;

    public:
        StackFrame *stackTop;

        CallStack() {
            stackframe_capacity = 512;
            local_registers_capacity = 512;
            local_registers_used = 0;
            local_registers = (StackObject **) malloc(local_registers_capacity *
                                                      sizeof(StackObject *));
            stack = (StackFrame *) malloc(stackframe_capacity * sizeof(StackFrame));
            stackTop = stack;
            stackframe_used = 0;
            newStackFrame(0, 0);
            stackTop->current_line++;
        }

        ~CallStack() {
            free(stack);
        }

        void newStackFrame(uint32_t segment, uint32_t args) {
            newStackFrame(segment, args, nullptr);
        }

        void newStackFrame(uint32_t segment, uint32_t args, Stack *program_stack) {
            if (stackframe_used + 1 > stackframe_capacity) {
                stackframe_capacity *= 2;
                stack = (StackFrame *) realloc(stack, stackframe_capacity);
            }
            stackTop = stack + stackframe_used;
            stack[stackframe_used++] = StackFrame{segment, static_cast<uint32_t>(-1)};

            if (local_registers_used + 1 > local_registers_capacity) {
                local_registers_capacity *= 2;
                local_registers = (StackObject **)
                        realloc(local_registers, local_registers_capacity *
                                                         sizeof(StackObject *));
            }
            local_registers[local_registers_used++] = (StackObject *) malloc(
                    args * sizeof(StackObject));

            for (auto i = args - 1; i + 1 != 0; i--)
                setLocal(i, program_stack->pop());
        }

        void popStackFrame() {
            if (stackframe_used != 0)
                stackframe_used--;
            if (local_registers_used != 0)
                local_registers_used--;
            stackTop = stack + stackframe_used - 1;
        }

        void jump(size_t line) {
            stack[stackframe_used - 1].current_line = line - 1;
        }

        StackObject getLocal(size_t reg) {
            return local_registers[local_registers_used - 1][reg];
        }

        void setLocal(size_t reg, StackObject sObject);
    };
}// namespace Bytecode