#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <SDL2/SDL.h>
#include "context.h"

void init_fb();
void draw_fb(Context* ctx);
void quit_fb();
#endif
