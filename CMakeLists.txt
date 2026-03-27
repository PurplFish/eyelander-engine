cmake_minimum_required(VERSION 3.16)
project(eyelander_engine)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Build SDL2 from source ---
set(SDL_STATIC ON  CACHE BOOL "" FORCE)   # build static lib
set(SDL_SHARED OFF CACHE BOOL "" FORCE)   # no DLL/SO
set(SDL_TEST   OFF CACHE BOOL "" FORCE)   # skip SDL tests
add_subdirectory(libs/SDL2)

# --- Build Lua from source ---
file(GLOB LUA_SOURCES "libs/lua/*.c")
list(FILTER LUA_SOURCES EXCLUDE REGEX ".*(lua|luac)\\.c$")  # strip standalone entry points

add_library(lua STATIC ${LUA_SOURCES})
target_include_directories(lua PUBLIC libs/lua)

if(WIN32)
    target_compile_definitions(lua PRIVATE LUA_USE_WINDOWS)
elseif(UNIX)
    target_compile_definitions(lua PRIVATE LUA_USE_POSIX)
    target_link_libraries(lua PRIVATE m)  # Lua needs libm on Linux
endif()

# --- Engine ---
file(GLOB_RECURSE ENGINE_SOURCES "src/*.c")
add_executable(eyelander_engine ${ENGINE_SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(eyelander_engine PRIVATE EYE_LOG_LEVEL=2)
endif()


# TEMPORARY WORKAROUND BECAUSE NO VFS, TO REMOVE LATER
target_compile_definitions(eyelander_engine PRIVATE
    EYE_SCRIPTS_PATH="${CMAKE_SOURCE_DIR}/"
)


target_include_directories(eyelander_engine PRIVATE 
    libs/SDL2/include
    libs/lua
)

target_link_libraries(eyelander_engine PRIVATE 
    SDL2-static 
    SDL2main
    lua
)