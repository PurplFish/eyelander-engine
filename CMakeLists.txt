cmake_minimum_required(VERSION 3.16)
project(eyelander_engine)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Build SDL2 from source ---
set(SDL_STATIC ON  CACHE BOOL "" FORCE)   # build static lib
set(SDL_SHARED OFF CACHE BOOL "" FORCE)   # no DLL/SO
set(SDL_TEST   OFF CACHE BOOL "" FORCE)   # skip SDL tests

add_subdirectory(libs/SDL2)

# --- Your game ---
add_executable(eyelander_engine src/main.c)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(EyeEngine PRIVATE EYE_LOG_LEVEL=2)
endif()

target_include_directories(eyelander_engine PRIVATE libs/SDL2/include)

target_link_libraries(eyelander_engine PRIVATE SDL2-static SDL2main)