#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/effect/effect.h"
#include "util_funcs.h"

int sf_sv_effect_register(lua_State* L) {
	const char* effectName = lua_tostring(L, 1);
	char effectNameStr[128];
	strcpy(effectNameStr, effectName);
	replacechar(effectNameStr, '\\', '/');
	engine_effect_register(effectNameStr);
	int freeslots = engine_effect_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_effect_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
	return 0;
}

int sf_sv_effect_list(lua_State* L) {
	const char* search = (lua_gettop(L) >= 1) ? lua_tostring(L, 1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_effect_list(search, &count, &savecvar);
	lua_pushinteger(L, count);
	return 1;
}

int sf_sv_effect_endpos(lua_State* L) {
	const char* cvarName = lua_tostring(L, 1);
	engine_effect_endpos(cvarName);
	return 0;
}

int sf_sv_effect_start(lua_State* L) {
	const char* effectFileName = lua_tostring(L, 1);
	const char* cvarName = lua_tostring(L, 2);
	engine_effect_start(effectFileName, cvarName);
	return 0;
}

