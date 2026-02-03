#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/console/console.h"

int sf_sv_console_write(lua_State* L) {
	const char* text = lua_tostring(L, 1);
	engine_console_write(text);
	return 0;
}

int sf_sv_configstring_set(lua_State* L) {
	int index = lua_tointeger(L, 1);
	const char* string = lua_tostring(L, 2);
	engine_configstring_set(index, string);
	return 0;
}

