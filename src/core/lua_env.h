#ifndef EYE_LUA_ENV_H
#define EYE_LUA_ENV_H

int lua_env_init(void);
int lua_env_run(const char *path);
void lua_env_call_start(void);
void lua_env_shutdown(void);

#endif