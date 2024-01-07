#ifndef YASI_LESSTHAN_FUNCTION_H
#define YASI_LESSTHAN_FUNCTION_H

#include "Function.h"
#include "bytecode/instructions/LessThan.h"
namespace Bytecode::BuiltinFunctions {
    class LessThan : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Bytecode::Compiler &compiler,
                std::vector<Bytecode::Instruction *> &result) override {
            compiler.compile(*args[0], result);
            compiler.compile(*args[1], result);
            result.push_back(new Bytecode::LessThan());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], result);
                result.push_back(new Bytecode::LessThan());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
#endif//YASI_LESSTHAN_FUNCTION_H
