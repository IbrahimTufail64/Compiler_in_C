#include "common.h"
#include "vm.h"
#include <stdio.h>
#include "debug.h"

Vm vm;

void initVM(){
    resetStack();
}

void freeVM(){
    resetStack();
}

static void resetStack(){
    vm.stackTop = vm.stack;
}

void push(Value value){
    *vm.stackTop = value;
     vm.stackTop++;
}

Value pop(){
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run(){
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    
    for(;;){
        #ifdef DEBUG_TRACE_EXECUTION
          for(Value* slot; slot < vm.stack; slot++){
            printf("[ ");
            printValue(*slot);
            printf(" ]");
          }
          printf("\n");
          disassembleInstruction(vm.chunk, (int)(vm.ip- vm.chunk->code));
        #endif
        uint8_t instruction = READ_BYTE();
        switch(instruction){
            case OP_RETURN: {
                return INTERPRET_OK;
            }
            case OP_CONSTANT: {
                Value constant  = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                return OP_CONSTANT;
            }
        }

    }
    #undef READ_BYTE
    #undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}