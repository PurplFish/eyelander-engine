#include "lua_env.h"
#include "log.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static lua_State *s_L = NULL;

static int l_eye_log(lua_State *L) {
    const char *msg = luaL_checkstring(L, 1);
    LOG_INFO("%s", msg);
    return 0;
}

static const luaL_Reg s_eye_lib[] = {
    { "log", l_eye_log },
    { NULL,  NULL      }
};

static int register_libs(void) {
    // Opens standard Lua libraries
    luaL_requiref(s_L, "_G",     luaopen_base,   1); lua_pop(s_L, 1);
    luaL_requiref(s_L, "string", luaopen_string, 1); lua_pop(s_L, 1);
    luaL_requiref(s_L, "math",   luaopen_math,   1); lua_pop(s_L, 1);
    luaL_requiref(s_L, "table",  luaopen_table,  1); lua_pop(s_L, 1);
    // Create the eye table from s_eye_lib
    luaL_newlib(s_L, s_eye_lib);
    lua_setglobal(s_L, "eye");
    return 1;
}


int lua_env_init(void){
    s_L = luaL_newstate();
    if (!s_L) {
        LOG_ERROR("Failed to create Lua state");
        return 0;
    }
    register_libs();
    return 1;
}
int lua_env_run(const char *path){
    if (luaL_dofile(s_L, path) != LUA_OK) {
        LOG_ERROR("%s",lua_tostring(s_L, -1));
        lua_pop(s_L, 1);
        return 0;
    }
    return 1;
}
void lua_env_call_start(void){
    lua_getglobal(s_L, "eye");      // stack: [eye table]
    if(!lua_istable(s_L, -1)){
        LOG_WARN("eye table missing");
        lua_pop(s_L, 1);
        return;
    }

    lua_getfield(s_L, -1, "start"); // stack: [eye table, eye.start fn]
    lua_remove(s_L, -2);            // stack: [eye.init fn]

    if(!lua_isfunction(s_L, -1)) {
        LOG_WARN("eye.start not defined");
        lua_pop(s_L, 1);
        return;
    }

    if (lua_pcall(s_L,0,0,0) != LUA_OK) {
        LOG_ERROR("%s",lua_tostring(s_L, -1));
        lua_pop(s_L, 1);
    }
}
void lua_env_shutdown(void){
    if (s_L) {
        lua_close(s_L);
        s_L= NULL;
    }
}


