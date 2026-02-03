#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/sound/sound.h"

extern sound_overrides_t sound_overrides;

int sf_sv_sound_register(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	int args = lua_gettop(L);
	assert(args == 1 && "invalid arg count");
	const char* soundName = luaL_checkstring(L, 1);
	char soundNameStr[128];
	strcpy(soundNameStr, soundName);
	replacechar(soundNameStr, '\\', '/');
	engine_sound_register(soundNameStr);
	int freeslots = engine_sound_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_sound_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
	lua_pushinteger(L, 0);
	return 1;
}

int sf_sv_sound_remove(lua_State* L) {
	int args = lua_gettop(L);
	assert(args == 1 && "invalid arg count");
	const char* soundName = lua_tostring(L, 1);
	char soundNameStr[128];
	strcpy(soundNameStr, soundName);
	replacechar(soundNameStr, '\\', '/');
	engine_sound_remove(soundNameStr);
	int freeslots = engine_sound_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_sound_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
	return 0;
}

int sf_sv_sound_list(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	int argc = lua_gettop(L);
	if (argc > 1) {
		orig_Com_Printf("sf_sv_sound_list -h\n");
		return 0;
	}
	if (argc == 1 && !lua_isstring(L, 1)) {
		return luaL_error(L, "invalid argument type, expected string");
	}
	const char* search = (argc == 1) ? lua_tostring(L, 1) : NULL;
	int count = 0;
	for (int i = 1; i < MAX_SOUNDS; i++) {
		const char* sound = (const char*)(SV_CONFIGSTRINGS + (CS_SOUNDS + i) * MAX_QPATH);
		if (*sound) {
			if (search != NULL && strstr(sound, search) == NULL) {
				continue;
			}
			if (_sf_sv_sofree_debug->value) {
				orig_Com_Printf("%s\n", sound);
			}
			char tmpname[64];
			sprintf(tmpname, "%s%i", "_sf_sv_sound_", count + 1);
			lua_pushstring(L, sound);
			lua_setglobal(L, tmpname);
			count++;
		}
	}
	lua_pushinteger(L, MAX_SOUNDS - count);
	lua_setglobal(L, "_sf_sv_sound_info_slots");
	return 1;
}

int sf_sv_sound_play_ent(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	edict_t* ent = (edict_t*)lua_tointeger(L, 2);
	int chan = lua_tointeger(L, 3);
	float volume = lua_tonumber(L, 4);
	float atten = lua_tonumber(L, 5);
	int global = lua_tointeger(L, 6);
	const char* soundName = lua_tostring(L, 1);
	if (!engine_sound_play_ent(soundName, ent, chan, volume, atten, global)) {
		orig_Com_Printf("Sound is not registered.\n");
	}
	return 0;
}

int sf_sv_sound_play_origin(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	int chan = lua_tointeger(L, 3);
	float volume = lua_tonumber(L, 4);
	float atten = lua_tonumber(L, 5);
	int global = lua_tointeger(L, 6);
	vec3_t vorigin;
	luaReadTableAsVector(2, vorigin);
	const char* soundName = lua_tostring(L, 1);
	if (!engine_sound_play_origin(soundName, vorigin, chan, volume, atten, global)) {
		orig_Com_Printf("Sound is not registered.\n");
	}
	return 0;
}

int sf_sv_sound_override(lua_State* L) {
#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
#endif
	int c = lua_gettop(L);
	char* one = (char*)lua_tostring(L, 1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Plays a specific sound in place of a previous one\n"
			"----------------------------\n"
			"arg1 -> the known original sound - can end with a * to target many sounds\n"
			"arg2 -> your new sound - can be empty then will play no sound\n"
			"arg3 -> altered attenuation value - \"\" empty string does not alter\n"
		);
		return 0;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_sound_override -h\n");
		return 0;
	}
	const char* origSound = lua_tostring(L, 1);
	const char* newSound = lua_tostring(L, 2);
	const char* attenStr = lua_tostring(L, 3);
	if (!engine_sound_override(origSound, newSound, attenStr)) {
		orig_Com_Printf("This sound is already overriden, sorry\n");
	}
	return 0;
}

