#include <unistd.h>
#include "context.h"
#include "executor.h"
#include "framebuffer.h"
#include "keystate.h"
#include "timerunit.h"

int main(int argc, char** argv) {
    if (argc != 2) return 1;

    Context ctx;
    init_ctx(&ctx);
    load_rom(&ctx, argv[1]);
    init_fb();

    while (!ctx.halt) {
        update_keys(&ctx);       
        if (!ctx.wait) step(&ctx); 
        tick(&ctx);              
        draw_fb(&ctx);           
        usleep(1000 * CYCLE_DELAY); 
    }

    quit_fb();
    return 0;
}
