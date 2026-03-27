#include "engine.h"
#include "log.h"
#include "platform.h"
#include "lua_env.h"
static int s_running = 0;

// WORKAROUND BECAUSE NO VFS, TO REMOVE LATER
#ifndef EYE_SCRIPTS_PATH
#define EYE_SCRIPTS_PATH "./"
#endif

int engine_init(void){
    LOG_INFO("Engine starting");

    if (platform_init() != 1)              return 0;
    if (lua_env_init()  != 1)              return 0;
    if (lua_env_run(EYE_SCRIPTS_PATH "src/boot/main.lua") != 1) return 0;

    lua_env_call_start();
    return 1;
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