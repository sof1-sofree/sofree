#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/draw/draw.h"

int sf_sv_draw_clear(lua_State* L) {
	engine_draw_clear();
	return 0;
}

int sf_sv_draw_string(lua_State* L) {
	int offsetx = lua_tointeger(L, 1);
	int offsety = lua_tointeger(L, 2);
	const char* message = lua_tostring(L, 3);
	engine_draw_string(offsetx, offsety, message);
	return 0;
}

int sf_sv_draw_string2(lua_State* L) {
	int offsetx = lua_tointeger(L, 1);
	int offsety = lua_tointeger(L, 2);
	const char* message = lua_tostring(L, 3);
	engine_draw_string2(offsetx, offsety, message);
	return 0;
}

int sf_sv_draw_altstring(lua_State* L) {
	int offsetx = lua_tointeger(L, 1);
	int offsety = lua_tointeger(L, 2);
	const char* message = lua_tostring(L, 3);
	engine_draw_altstring(offsetx, offsety, message);
	return 0;
}

