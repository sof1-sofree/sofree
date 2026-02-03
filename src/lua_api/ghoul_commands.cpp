#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/ghoul/ghoul.h"
#include "util_funcs.h"

int sf_sv_ghoul_register(lua_State* L) {
	const char* ghoulName = lua_tostring(L, 1);
	char ghoulNameStr[128];
	strcpy(ghoulNameStr, ghoulName);
	replacechar(ghoulNameStr, '\\', '/');
	engine_ghoul_register(ghoulNameStr);
	int freeslots = engine_ghoul_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_ghoul_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
	return 0;
}

int sf_sv_ghoul_translate(lua_State* L) {
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	vec3_t translate_v;
	luaReadTableAsVector(2, translate_v);
	engine_ghoul_translate(ent, translate_v);
	return 0;
}

int sf_sv_ghoul_scale(lua_State* L) {
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	float scale = lua_tonumber(L, 2);
	engine_ghoul_scale(ent, scale);
	return 0;
}

int sf_sv_ghoul_list(lua_State* L) {
	const char* search = (lua_gettop(L) >= 1) ? lua_tostring(L, 1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_ghoul_list(search, &count, &savecvar);
	lua_pushinteger(L, count);
	return 1;
}

