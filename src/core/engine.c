#include <SDL2/SDL.h>
#include "log.h"

static SDL_Window* s_window = NULL;
static SDL_Renderer* s_renderer = NULL;
static int s_running = 0;

int engine_init(void){
    LOG_INFO("Engine starting");
    // Init SDL - to move to Interface
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
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
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
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

void engine_run(void){
    // Main loop
    int running = 1;
    SDL_Event event;

    while (running) {
        // Event polling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

        // Clear screen (dark grey)
        SDL_SetRenderDrawColor(s_renderer, 30, 30, 30, 255);
        SDL_RenderClear(s_renderer);

        // Present
        SDL_RenderPresent(s_renderer);
    }
}

void engine_shutdown(void){
    // Shutdown - reverse order
    SDL_DestroyRenderer(s_renderer);
    SDL_DestroyWindow(s_window);
    SDL_Quit();
}