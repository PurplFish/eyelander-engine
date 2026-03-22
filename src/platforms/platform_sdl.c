// Cmake will only compile the specific platform .c file
// This will only compile when using sdl
// Other script will include platform.h to make use of the script here

#include "../core/log.h"
#include <SDL2/SDL.h>

static SDL_Window* s_window = NULL;
static SDL_Renderer* s_renderer = NULL;

int platform_init(void){
    LOG_INFO("Engine starting");
    // Init SDL - to move to Interface
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_ERROR("SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }
    s_window = SDL_CreateWindow(
        "Eyelander Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );
    if (s_window == NULL) {
        LOG_ERROR("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }
    s_renderer = SDL_CreateRenderer(
        s_window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    return 1;
}

void platform_render_begin(void){
    // Clear screen (dark grey)
    SDL_SetRenderDrawColor(s_renderer, 30, 30, 30, 255);
    SDL_RenderClear(s_renderer);
}
void platform_render_end(void){
    SDL_RenderPresent(s_renderer);
}

int platform_shutdown_signal(void){
    SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
               return 1;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return 1;
                }
            }
        }
    return 0;
}

void platform_shutdown(void){
    SDL_DestroyRenderer(s_renderer);
    SDL_DestroyWindow(s_window);
    SDL_Quit();
}