#include <SDL2/SDL.h>
#include <stdlib.h>
#include "keystate.h"
#include "framebuffer.h"
#include "context.h"

void process_input(Context* ctx) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) exit(0);
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_EQUALS || e.key.keysym.sym == SDLK_KP_PLUS) resize_fb(1);
            if (e.key.keysym.sym == SDLK_MINUS || e.key.keysym.sym == SDLK_KP_MINUS) resize_fb(-1);
        }
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            int v = (e.type == SDL_KEYDOWN) ? 1 : 0;
            SDL_Keycode k = e.key.keysym.sym;
            if (k == SDLK_1 || k == SDLK_KP_1) ctx->keys[0x1] = v;
            else if (k == SDLK_2 || k == SDLK_KP_2) ctx->keys[0x2] = v;
            else if (k == SDLK_3 || k == SDLK_KP_3) ctx->keys[0x3] = v;
            else if (k == SDLK_4 || k == SDLK_KP_4) ctx->keys[0xC] = v;
            else if (k == SDLK_q || k == SDLK_KP_7) ctx->keys[0x4] = v;
            else if (k == SDLK_w || k == SDLK_UP || k == SDLK_KP_8) ctx->keys[0x5] = v;
            else if (k == SDLK_e || k == SDLK_KP_9) ctx->keys[0x6] = v;
            else if (k == SDLK_r || k == SDLK_KP_DIVIDE) ctx->keys[0xD] = v;
            else if (k == SDLK_a || k == SDLK_LEFT || k == SDLK_KP_4) ctx->keys[0x7] = v;
            else if (k == SDLK_s || k == SDLK_DOWN || k == SDLK_KP_5) ctx->keys[0x8] = v;
            else if (k == SDLK_d || k == SDLK_RIGHT || k == SDLK_KP_6) ctx->keys[0x9] = v;
            else if (k == SDLK_f || k == SDLK_KP_MULTIPLY) ctx->keys[0xE] = v;
            else if (k == SDLK_z || k == SDLK_LCTRL || k == SDLK_KP_0) ctx->keys[0xA] = v;
            else if (k == SDLK_x || k == SDLK_RETURN || k == SDLK_KP_ENTER || k == SDLK_TAB) ctx->keys[0x0] = v;
            else if (k == SDLK_c || k == SDLK_ESCAPE || k == SDLK_BACKSPACE) ctx->keys[0xB] = v;
            else if (k == SDLK_v || k == SDLK_SPACE || k == SDLK_KP_PLUS) ctx->keys[0xF] = v;
        }
    }
}
