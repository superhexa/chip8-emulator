#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include "defs.h"

void init_fb();
void draw_fb(void* ctx);
void quit_fb();
void resize_fb(int delta);

#endif
