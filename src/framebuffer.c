#include "framebuffer.h"
#include <SDL2/SDL.h>

SDL_Window* win;
SDL_Renderer* ren;

void init_fb(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(GFX_WIDTH*10,GFX_HEIGHT*10,0,&win,&ren);
}

void draw_fb(Context* ctx){
    if(!ctx->draw)return;
    ctx->draw=0;
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren,255,255,255,255);
    for(int y=0;y<GFX_HEIGHT;y++){
    for(int x=0;x<GFX_WIDTH;x++){
    if(ctx->gfx[y*GFX_WIDTH+x]){
    SDL_Rect r={x*10,y*10,10,10};
    SDL_RenderFillRect(ren,&r);
    }}}
    SDL_RenderPresent(ren);
}

void quit_fb(){
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
