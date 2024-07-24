#include "lua.h"
#include "lualib.h"
#include "lua_sdl.h"
#include <string>
#include <vector>
#include <iostream>
#include <SDL.h>
using namespace std;

static int lualib_getWindowSize(lua_State* L)
{
	Uint32 tics = SDL_GetTicks64();
	lua_pushinteger(L, tics);
	return 0;
}

static const luaL_Reg enginesdl_funcs[] = {
	{"getWindowSize", lualib_getWindowSize},
	{NULL, NULL},
};

int enginelua_sdl(lua_State* L)
{
	luaL_register(L, LUA_ENGINESDL, enginesdl_funcs);
	return 1;
}
