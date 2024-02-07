#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            const auto result = new StackObject(
                    new Literal(object1->literal->int_literal +
                                object2->literal->int_literal));
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "Add"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
