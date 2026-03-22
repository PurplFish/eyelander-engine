#include "engine.h"
#include "log.h"
#include "platform.h"
static int s_running = 0;

int engine_init(void){
    return platform_init();
}
void engine_run(void){
    // Main loop
    int running = 1;

    while (running) {
        if(platform_shutdown_signal()){
            engine_shutdown();
            return;
        }

        platform_render_begin();
        platform_render_end();
    }
}

void engine_shutdown(void){
    platform_shutdown();
}