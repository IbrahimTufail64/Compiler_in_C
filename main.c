#include "lib/common.h"
#include "lib/chunk.h" 
#include "lib/debug.h"
#include "lib/vm.h"

int main(int argc, const char* argv[]){
  
  initVM();
  
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk,1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk,"test chunk");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
    
    return 0;
}

