#include "chunk.h"
#include <stdlib.h>
#include "memory.h"

void initChunk(Chunk *chunk){
    chunk ->count = 0;
    chunk ->capacity = 0;
    chunk ->code = NULL;
}

void writeChunk(Chunk *chunk,uint8_t byte){
    if(chunk->capacity <= chunk->count){
        int old_capacity = chunk -> capacity;
        chunk -> capacity = GROW_CAPACITY(old_capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
            old_capacity, chunk->capacity);
    }
    chunk ->code[chunk->count+1] = byte;
    chunk ->count ++;
}

void freeChunk(Chunk* chunk){
    FREE_ARRAY(uint8_t,chunk->code,chunk->count);
    initChunk(chunk);
}