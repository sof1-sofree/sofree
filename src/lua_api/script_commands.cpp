#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/script/script.h"

int sf_sv_script_load(lua_State* L) {
	const char* scriptName = lua_tostring(L, 1);
	int paramCount = lua_gettop(L) - 1;
	const char* params[16] = { 0 };
	for (int i = 0; i < paramCount && i < 16; i++) {
		params[i] = lua_tostring(L, i + 2);
	}
	edict_t* runner = engine_script_load(scriptName, params, paramCount);
	lua_pushinteger(L, (int)runner);
	return 1;
}

int sf_sv_script_unload(lua_State* L) {
	edict_t* runner = (edict_t*)lua_tointeger(L, 1);
	engine_script_unload(runner);
	return 0;
}

int sf_sv_script_run(lua_State* L) {
	edict_t* runner = (edict_t*)lua_tointeger(L, 1);
	engine_script_run(runner);
	return 0;
}

