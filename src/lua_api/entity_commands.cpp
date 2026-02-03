#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/entities/entities.h"
#include "util_funcs.h"

int sf_sv_ent_create(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = engine_ent_create();
	lua_pushinteger(L, (int)ent);
	return 1;
}

int sf_sv_ent_spawn(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)lua_tointeger(L, -1);
	engine_ent_spawn(ent);
	return 0;
}

int sf_sv_ent_remove(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	int args = lua_gettop(L);
	assert(args == 1 && "invalid arg count");
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	engine_ent_remove(ent);
	return 0;
}

int sf_sv_ent_relink(lua_State* L) {
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	engine_ent_relink(ent);
	return 0;
}

int sf_sv_ent_use(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	engine_ent_use(ent);
	return 0;
}

int sf_sv_ent_vects(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	const char* cvarprefix = lua_tostring(L, 1);
	edict_t* ent = (edict_t*)lua_tointeger(L, 2);
	vec3_t fwd_vec, side_vec, up_vec;
	engine_ent_vects(ent, fwd_vec, side_vec, up_vec);
	char newname[64];
	sprintf(newname, "%s%s", cvarprefix, "_fwd");
	writeCvarAsVector(fwd_vec, (char*)newname);
	sprintf(newname, "%s%s", cvarprefix, "_side");
	writeCvarAsVector(side_vec, (char*)newname);
	sprintf(newname, "%s%s", cvarprefix, "_up");
	writeCvarAsVector(up_vec, (char*)newname);
	return 0;
}

int sf_sv_ent_find(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	const char* cvarprefix = lua_tostring(L, 1);
	int offset = lua_tointeger(L, 2);
	const char* val_to_find = lua_tostring(L, 3);
	edict_t* results[256];
	int count = engine_ent_find(offset, val_to_find, results, 256);
	lua_newtable(L);
	for (int i = 0; i < count; i++) {
		lua_pushinteger(L, i + 1);
		lua_pushinteger(L, (int)results[i]);
		lua_settable(L, -3);
	}
	return 1;
}

int sf_sv_ent_tint(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	int c = lua_gettop(L);
	if (c == 0) {
		orig_Com_Printf("sf_sv_ent_tint -h\n");
		return 0;
	}
	if (lua_isstring(L, 1) && strcmp(lua_tostring(L, 1), "-h") == 0) {
		orig_Com_Printf(
			"Tints an entity a certain color.\n"
			"----------------------------\n"
			"arg1 -> immidiate value of entity handle\n"
			"arg2 -> table of r g b colors {r=float, g=float, b=float} 0->1\n"
			"arg3 -> [float] alpha/transparency value 0->1\n"
		);
		return 0;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_ent_tint -h\n");
		return 0;
	}
	edict_t* ent = (edict_t*)atoi(lua_tostring(L, 1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return 0;
	}
	vec3_t colors;
	luaReadTableAsVector(2, colors);
	float alpha = (float)lua_tonumber(L, 3);
	engine_ent_tint(ent, colors, alpha);
	return 0;
}

int sf_sv_ent_anim(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	const char* animName = lua_tostring(L, 2);
	float startPos = lua_tonumber(L, 3);
	int restart = lua_tointeger(L, 4);
	int loop = lua_tointeger(L, 5);
	int match = lua_tointeger(L, 6);
	int reverse = lua_tointeger(L, 7);
	engine_ent_anim(ent, animName, startPos, restart, loop, match, reverse);
	return 0;
}

int sf_sv_ent_model(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	const char* dir = lua_tostring(L, 2);
	const char* modelname = lua_tostring(L, 3);
	engine_ent_model(ent, dir, modelname);
	return 0;
}

int sf_sv_ent_bolt(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	const char* dir = lua_tostring(L, 2);
	const char* file = lua_tostring(L, 3);
	const char* bolt_from = lua_tostring(L, 4);
	const char* bolt_to = lua_tostring(L, 5);
	float scale = lua_tonumber(L, 6);
	engine_ent_bolt(ent, dir, file, bolt_from, bolt_to, scale);
	return 0;
}

int sf_sv_ent_paint(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)lua_tointeger(L, 1);
	float r = lua_tonumber(L, 2);
	float g = lua_tonumber(L, 3);
	float b = lua_tonumber(L, 4);
	float a = lua_tonumber(L, 5);
	engine_ent_paint(ent, r, g, b, a);
	return 0;
}

int sf_sv_ent_callback(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)atoi(lua_tostring(L, 1));
	const char* type = lua_tostring(L, 2);
	const char* funcName = lua_tostring(L, 3);
	if (!engine_ent_callback(ent, type, funcName)) {
		orig_Com_Printf("Invalid callback type\n");
	}
	return 0;
}

