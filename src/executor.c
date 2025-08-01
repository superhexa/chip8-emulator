#include <stdlib.h>
#include "executor.h"

void step(Context* ctx){
    uint16_t op=(ctx->mem[ctx->pc]<<8)|ctx->mem[ctx->pc+1];
    ctx->pc+=2;
    switch(op&0xF000){
        case 0x0000:
            if((op&0x0FFF)==0x00E0){
                for(int i=0;i<GFX_WIDTH*GFX_HEIGHT;i++) ctx->gfx[i]=0;
                ctx->draw=1;
            }else if((op&0x0FFF)==0x00EE){
                ctx->sp--;
                ctx->pc=ctx->stack[ctx->sp];
            }
            break;
        case 0x1000: ctx->pc=op&0x0FFF; break;
        case 0x2000:
            ctx->stack[ctx->sp]=ctx->pc;
            ctx->sp++;
            ctx->pc=op&0x0FFF;
            break;
        case 0x3000:
            if(ctx->reg[(op>>8)&0xF]==(op&0xFF)) ctx->pc+=2;
            break;
        case 0x4000:
            if(ctx->reg[(op>>8)&0xF]!=(op&0xFF)) ctx->pc+=2;
            break;
        case 0x5000:
            if(ctx->reg[(op>>8)&0xF]==ctx->reg[(op>>4)&0xF]) ctx->pc+=2;
            break;
        case 0x6000: ctx->reg[(op>>8)&0xF]=op&0xFF; break;
        case 0x7000: ctx->reg[(op>>8)&0xF]+=op&0xFF; break;
        case 0x8000:
            switch(op&0xF){
                case 0x0: ctx->reg[(op>>8)&0xF]=ctx->reg[(op>>4)&0xF]; break;
                case 0x1: ctx->reg[(op>>8)&0xF]|=ctx->reg[(op>>4)&0xF]; break;
                case 0x2: ctx->reg[(op>>8)&0xF]&=ctx->reg[(op>>4)&0xF]; break;
                case 0x3: ctx->reg[(op>>8)&0xF]^=ctx->reg[(op>>4)&0xF]; break;
                case 0x4: {
                    uint16_t sum=ctx->reg[(op>>8)&0xF]+ctx->reg[(op>>4)&0xF];
                    ctx->reg[0xF]=sum>0xFF;
                    ctx->reg[(op>>8)&0xF]=sum&0xFF;
                } break;
                case 0x5: {
                    ctx->reg[0xF]=ctx->reg[(op>>8)&0xF]>=ctx->reg[(op>>4)&0xF];
                    ctx->reg[(op>>8)&0xF]-=ctx->reg[(op>>4)&0xF];
                } break;
                case 0x6:
                    ctx->reg[0xF]=ctx->reg[(op>>8)&0xF]&1;
                    ctx->reg[(op>>8)&0xF]>>=1;
                    break;
                case 0x7:
                    ctx->reg[0xF]=ctx->reg[(op>>4)&0xF]>=ctx->reg[(op>>8)&0xF];
                    ctx->reg[(op>>8)&0xF]=ctx->reg[(op>>4)&0xF]-ctx->reg[(op>>8)&0xF];
                    break;
                case 0xE:
                    ctx->reg[0xF]=(ctx->reg[(op>>8)&0xF]>>7)&1;
                    ctx->reg[(op>>8)&0xF]<<=1;
                    break;
            }
            break;
        case 0x9000:
            if(ctx->reg[(op>>8)&0xF]!=ctx->reg[(op>>4)&0xF]) ctx->pc+=2;
            break;
        case 0xA000: ctx->addr=op&0x0FFF; break;
        case 0xB000: ctx->pc=(op&0x0FFF)+ctx->reg[0]; break;
        case 0xC000: ctx->reg[(op>>8)&0xF]=(rand()%256)&(op&0xFF); break;
        case 0xD000: {
            uint8_t x=ctx->reg[(op>>8)&0xF];
            uint8_t y=ctx->reg[(op>>4)&0xF];
            uint8_t h=op&0xF;
            ctx->reg[0xF]=0;
            for(int row=0;row<h;row++){
                uint8_t sprite=ctx->mem[ctx->addr+row];
                for(int col=0;col<8;col++){
                    if((sprite&(0x80>>col))!=0){
                        int px=((x+col)%GFX_WIDTH)+((y+row)%GFX_HEIGHT)*GFX_WIDTH;
                        if(ctx->gfx[px]==1) ctx->reg[0xF]=1;
                        ctx->gfx[px]^=1;
                    }
                }
            }
            ctx->draw=1;
        } break;
        case 0xE000:
            switch(op&0xFF){
                case 0x9E:
                    if(ctx->keys[ctx->reg[(op>>8)&0xF]]!=0) ctx->pc+=2;
                    break;
                case 0xA1:
                    if(ctx->keys[ctx->reg[(op>>8)&0xF]]==0) ctx->pc+=2;
                    break;
            }
            break;
        case 0xF000:
            switch(op&0xFF){
                case 0x07: ctx->reg[(op>>8)&0xF]=ctx->delay; break;
                case 0x0A: {
                    int pressed=-1;
                    for(int i=0;i<KEY_COUNT;i++){
                        if(ctx->keys[i]!=0){
                            pressed=i;
                            break;
                        }
                    }
                    if(pressed==-1){
                        ctx->pc-=2;
                    }else{
                        ctx->reg[(op>>8)&0xF]=pressed;
                    }
                } break;
                case 0x15: ctx->delay=ctx->reg[(op>>8)&0xF]; break;
                case 0x18: ctx->sound=ctx->reg[(op>>8)&0xF]; break;
                case 0x1E: ctx->addr+=ctx->reg[(op>>8)&0xF]; break;
                case 0x29: ctx->addr=FONT_START+ctx->reg[(op>>8)&0xF]*5; break;
                case 0x33: {
                    uint8_t val=ctx->reg[(op>>8)&0xF];
                    ctx->mem[ctx->addr]=val/100;
                    ctx->mem[ctx->addr+1]=(val/10)%10;
                    ctx->mem[ctx->addr+2]=val%10;
                } break;
                case 0x55:
                    for(int i=0;i<=((op>>8)&0xF);i++)
                        ctx->mem[ctx->addr+i]=ctx->reg[i];
                    break;
                case 0x65:
                    for(int i=0;i<=((op>>8)&0xF);i++)
                        ctx->reg[i]=ctx->mem[ctx->addr+i];
                    break;
            }
            break;
    }
}
