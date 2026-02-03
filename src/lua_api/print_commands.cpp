#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/print/print.h"
#include "engine_features/players/players.h"

int sf_sv_print_cprintf(lua_State* L) {
	unsigned int slot = lua_tointeger(L, 1);
	const char* text = lua_tostring(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (ent) {
		engine_print_cprintf(ent, text);
	}
	return 0;
}

int sf_sv_print_bprintf(lua_State* L) {
	const char* text = lua_tostring(L, 1);
	engine_print_bprintf(text);
	return 0;
}

int sf_sv_print_centerprint(lua_State* L) {
	unsigned int slot = lua_tointeger(L, 1);
	const char* text = lua_tostring(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (ent) {
		engine_print_centerprint(ent, text);
	}
	return 0;
}

int sf_sv_print_welcomeprint(lua_State* L) {
	unsigned int slot = lua_tointeger(L, 1);
	edict_t* ent = engine_player_get_ent(slot);
	if (ent) {
		engine_print_welcomeprint(ent);
	}
	return 0;
}

int sf_sv_print_cinprintf(lua_State* L) {
	unsigned int slot = lua_tointeger(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);
	int speed = lua_tointeger(L, 4);
	const char* text = lua_tostring(L, 5);
	edict_t* ent = engine_player_get_ent(slot);
	if (ent) {
		engine_print_cinprintf(ent, x, y, speed, text);
	}
	return 0;
}

