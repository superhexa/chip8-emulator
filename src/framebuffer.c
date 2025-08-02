#include <SDL2/SDL.h>
#include "framebuffer.h"
#include "context.h"

#define BASE_SCALE 10
#define MAX_SCALE 32
#define MIN_SCALE 2

static SDL_Window* win = NULL;
static SDL_Renderer* ren = NULL;
static SDL_Texture* texture = NULL;
static uint32_t* pixels = NULL;
static int scale = BASE_SCALE;

static void create_window() {
    int width = GFX_WIDTH * scale;
    int height = GFX_HEIGHT * scale;

    if (win) SDL_DestroyWindow(win);
    if (ren) SDL_DestroyRenderer(ren);
    if (texture) SDL_DestroyTexture(texture);

    win = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, GFX_WIDTH, GFX_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(ren, GFX_WIDTH, GFX_HEIGHT);

    if (!pixels) pixels = malloc(sizeof(uint32_t) * GFX_WIDTH * GFX_HEIGHT);
}

void init_fb() {
    SDL_Init(SDL_INIT_VIDEO);
    create_window();
}

void draw_fb(void* ctx) {
    uint8_t* gfx = ((Context*)ctx)->gfx;

    for (int i = 0; i < GFX_WIDTH * GFX_HEIGHT; i++) {
        pixels[i] = gfx[i] ? 0xFFFFFFFF : 0xFF000000;
    }

    SDL_UpdateTexture(texture, NULL, pixels, GFX_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, texture, NULL, NULL);
    SDL_RenderPresent(ren);
}

void resize_fb(int delta) {
    int new_scale = scale + delta;
    if (new_scale >= MIN_SCALE && new_scale <= MAX_SCALE) {
        scale = new_scale;
        create_window();
    }
}

void quit_fb() {
    if (texture) SDL_DestroyTexture(texture);
    if (ren) SDL_DestroyRenderer(ren);
    if (win) SDL_DestroyWindow(win);
    if (pixels) free(pixels);
    SDL_Quit();
}
