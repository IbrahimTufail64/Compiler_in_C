#include "common.h"
#include "vm.h"
#include <stdio.h>
#include "debug.h"

Vm vm;

initVM(){
    
}

freeVM(){

}



static InterpretResult run(){
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    
    for(;;){
        #ifdef DEBUG_TRACE_EXECUTION
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