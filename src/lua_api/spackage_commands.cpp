#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/spackage/spackage.h"

int sf_sv_spackage_register(lua_State* L) {
	const char* packageName = lua_tostring(L, 1);
	engine_spackage_register(packageName);
	return 0;
}

int sf_sv_spackage_list(lua_State* L) {
	const char* search = (lua_gettop(L) >= 1) ? lua_tostring(L, 1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_spackage_list(search, &count, &savecvar);
	lua_pushinteger(L, count);
	return 1;
}

int sf_sv_spackage_print_ref(lua_State* L) {
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	const char* fileRef = lua_tostring(L, 2);
	const char* indexRef = lua_tostring(L, 3);
	engine_spackage_print_ref(ent, fileRef, indexRef);
	return 0;
}

int sf_sv_spackage_print_id(lua_State* L) {
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	unsigned char fileId = lua_tointeger(L, 2);
	unsigned char index = lua_tointeger(L, 3);
	engine_spackage_print_id(ent, fileId, index);
	return 0;
}

int sf_sv_spackage_print_obit(lua_State* L) {
	unsigned int slot = lua_tointeger(L, 1);
	unsigned short id = lua_tointeger(L, 2);
	engine_spackage_print_obit(slot, id);
	return 0;
}

int sf_sv_spackage_print_string(lua_State* L) {
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	const char* msg = lua_tostring(L, 2);
	int len = lua_tointeger(L, 3);
	engine_spackage_print_string(ent, msg, len);
	return 0;
}

