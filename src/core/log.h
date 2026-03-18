#pragma once
#include <stdio.h>

// ── Log levels ───────────────────────────────────────────
#define EYE_LOG_LEVEL_INFO   0
#define EYE_LOG_LEVEL_WARN   1
#define EYE_LOG_LEVEL_ERROR  2

// Default to INFO in debug, can be overridden by CMake
#ifndef EYE_LOG_LEVEL
    #define EYE_LOG_LEVEL EYE_LOG_LEVEL_INFO
#endif

// ── ANSI colors (desktop only) ───────────────────────────
#ifdef EYE_PLATFORM_DESKTOP
    #define LOG_COL_RESET   "\033[0m"
    #define LOG_COL_CYAN    "\033[36m"
    #define LOG_COL_YELLOW  "\033[33m"
    #define LOG_COL_RED     "\033[31m"
#else
    // Wii / PS2 — no terminal colors
    #define LOG_COL_RESET   ""
    #define LOG_COL_CYAN    ""
    #define LOG_COL_YELLOW  ""
    #define LOG_COL_RED     ""
#endif

// ── Macros ───────────────────────────────────────────────
#if EYE_LOG_LEVEL <= EYE_LOG_LEVEL_INFO
    #define LOG_INFO(msg, ...) \
        printf(LOG_COL_CYAN "[INFO]" LOG_COL_RESET " (%s:%d) " msg "\n", \
        __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define LOG_INFO(msg, ...)
#endif

#if EYE_LOG_LEVEL <= EYE_LOG_LEVEL_WARN
    #define LOG_WARN(msg, ...) \
        printf(LOG_COL_YELLOW "[WARN]" LOG_COL_RESET " (%s:%d) " msg "\n", \
        __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define LOG_WARN(msg, ...)
#endif

// errors always print
#define LOG_ERROR(msg, ...) \
    fprintf(stderr, LOG_COL_RED "[ERROR]" LOG_COL_RESET " (%s:%d) " msg "\n", \
    __FILE__, __LINE__, ##__VA_ARGS__)