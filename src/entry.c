#include <unistd.h>
#include "context.h"
#include "executor.h"
#include "framebuffer.h"
#include "keystate.h"
#include "timerunit.h"
#include "defs.h"

int main(int c,char** v){
    Context ctx;
    init_ctx(&ctx);
    load_rom(&ctx,v[1]);
    init_fb();

    while (1) {
        process_input(&ctx);
        for (int i = 0; i < CYCLE_PER_FRAME; i++) step(&ctx);
        tick(&ctx);
        draw_fb(&ctx);
        usleep(1000);
    }

    quit_fb();
    return 0;
}
