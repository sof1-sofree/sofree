#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/players/players.h"
#include "util_funcs.h"

int sf_sv_player_ent(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	edict_t* ent = engine_player_get_ent(slot);
	if (ent && ent->inuse) {
		lua_pushinteger(L, (int)ent);
	} else {
		lua_pushinteger(L, 0);
	}
	return 1;
}

int sf_sv_player_pos(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	vec3_t pos;
	engine_player_pos(ent, pos);
	luaPushVectorAsTable(pos);
	return 1;
}

int sf_sv_player_move(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	vec3_t pos;
	luaReadTableAsVector(2, pos);
	engine_player_move(ent, pos);
	return 0;
}

int sf_sv_player_gravity(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	short gravity = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_gravity(ent, slot, gravity);
	return 0;
}

int sf_sv_player_paint(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	float r = lua_tonumber(L, 2);
	float g = lua_tonumber(L, 3);
	float b = lua_tonumber(L, 4);
	float a = lua_tonumber(L, 5);
	engine_player_paint(slot, r, g, b, a);
	return 0;
}

int sf_sv_player_weap_paint(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	float r = lua_tonumber(L, 2);
	float g = lua_tonumber(L, 3);
	float b = lua_tonumber(L, 4);
	float a = lua_tonumber(L, 5);
	engine_player_weap_paint(slot, r, g, b, a);
	return 0;
}

int sf_sv_player_weap_current(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	int weapon = engine_player_weap_current(ent);
	lua_pushinteger(L, weapon);
	return 1;
}

int sf_sv_player_weap_switch(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	int weapon = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_weap_switch(ent, weapon);
	return 0;
}

int sf_sv_player_weap_lock(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	int lock = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_weap_lock(ent, lock);
	return 0;
}

int sf_sv_player_collision(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	int mode = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_collision(ent, slot, mode);
	return 0;
}

int sf_sv_player_allow_attack(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	int allow = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_allow_attack(ent, slot, allow);
	return 0;
}

int sf_sv_player_allow_altattack(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	int allow = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_allow_altattack(ent, slot, allow);
	return 0;
}

int sf_sv_player_allow_walk(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	int allow = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_allow_walk(ent, slot, allow);
	return 0;
}

int sf_sv_player_anim(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	const char* animName = lua_tostring(L, 2);
	float startPos = lua_tonumber(L, 3);
	int restart = lua_tointeger(L, 4);
	int loop = lua_tointeger(L, 5);
	int resume = lua_tointeger(L, 6);
	int reverse = lua_tointeger(L, 7);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_anim(ent, animName, startPos, restart, loop, resume, reverse);
	return 0;
}

int sf_sv_player_effect(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	unsigned int slot = lua_tointeger(L, 1);
	int effectID = lua_tointeger(L, 2);
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	engine_player_effect(ent, effectID);
	return 0;
}

