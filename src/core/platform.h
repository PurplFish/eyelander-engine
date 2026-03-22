#pragma once

#if defined(_WIN32)
    #define EYE_PLATFORM_WINDOWS
    #define EYE_PLATFORM_DESKTOP

#elif defined(__linux__)
    #define EYE_PLATFORM_LINUX
    #define EYE_PLATFORM_DESKTOP

#elif defined(__APPLE__)
    #define EYE_PLATFORM_MAC
    #define EYE_PLATFORM_DESKTOP

#elif defined(HW_RVL)
    #define EYE_PLATFORM_WII
#else
    #error "Unknown platform"
#endif

int platform_init(void);
void platform_render_begin(void);
void platform_render_end(void);
int platform_shutdown_signal(void);
void platform_shutdown(void);