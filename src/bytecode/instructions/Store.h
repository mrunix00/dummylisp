#ifndef YASI_STORE_H
#define YASI_STORE_H

#include "Instruction.h"
#include <string>
namespace Bytecode {
    class Store final : public Instruction {
        size_t reg;

    public:
        explicit Store(size_t rg) {
            reg = rg;
            type = InstructionType::Store;
        }

        bool operator==(const Instruction &instruction) const override {
            return getType() == type && ((Store *) &instruction)->reg == reg;
        }
    };
}// namespace Bytecode

#endif//YASI_STORE_H
