cmake_minimum_required(VERSION 3.16)
project(MyGame)

set(CMAKE_CXX_STANDARD 17)

# --- Build SDL2 from source ---
set(SDL_STATIC ON  CACHE BOOL "" FORCE)   # build static lib
set(SDL_SHARED OFF CACHE BOOL "" FORCE)   # no DLL/SO
set(SDL_TEST   OFF CACHE BOOL "" FORCE)   # skip SDL tests

add_subdirectory(libs/SDL2)

# --- Your game ---
add_executable(MyGame src/main.cpp)

target_include_directories(MyGame PRIVATE libs/SDL2/include)

target_link_libraries(MyGame PRIVATE SDL2-static SDL2main)