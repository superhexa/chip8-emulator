#ifndef CONTEXT_H
#define CONTEXT_H
#include <stdint.h>
#include "defs.h"

typedef struct {
    uint8_t mem[MEM_SIZE];
    uint8_t reg[REG_COUNT];
    uint16_t addr;
    uint16_t pc;
    uint8_t delay;
    uint8_t sound;
    uint16_t stack[STACK_SIZE];
    uint8_t sp;
    uint8_t keys[KEY_COUNT];
    uint8_t gfx[GFX_WIDTH*GFX_HEIGHT];
    uint8_t draw;
    int wait;   
    int halt;   
} Context;

void init_ctx(Context* ctx);
void load_rom(Context* ctx,const char* path);

#endif
