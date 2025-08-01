#include "timerunit.h"

void tick(Context* ctx){
    if(ctx->delay)ctx->delay--;
    if(ctx->sound)ctx->sound--;
}
