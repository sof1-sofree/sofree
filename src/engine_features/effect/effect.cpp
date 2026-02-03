#include <windows.h>
#include <shlwapi.h>
#include "sofheader.h"
#include "engine_features/effect/effect.h"
#include "util_funcs.h"

int engine_effect_calc_free_slots(void) {
	int freeslots = 0;
	for (int i = 1; i < MAX_EFPACKS; i++) {
		if (*(unsigned char*)(SV_CONFIGSTRINGS + (CS_EFFECTS + i) * MAX_QPATH) == '\0') {
			freeslots++;
		}
	}
	return freeslots;
}

void engine_effect_register(const char* effectName) {
	char ver1[128];
	strcpy(ver1, effectName);
	replacechar(ver1, '\\', '/');
	orig_SV_FindIndex(ver1, CS_EFFECTS, MAX_EFPACKS, 1, "effect");
}

void engine_effect_list(const char* search, int* count, cvar_t** savecvar) {
	*count = 0;
	if (!search) search = "";
	for (int i = 1; i < MAX_EFPACKS; i++) {
		if (*(unsigned char*)(SV_CONFIGSTRINGS + (CS_EFFECTS + i) * MAX_QPATH)) {
			char line[65];
			strcpy(line, SV_CONFIGSTRINGS + (CS_EFFECTS + i) * MAX_QPATH);
			if (strlen(search) == 0 || StrStrI(line, search)) {
				(*count)++;
			}
		}
	}
}

void engine_effect_endpos(const char* cvarName) {
	vec3_t vorigin;
	readCvarAsVector((char*)cvarName, vorigin);
	*(int*)0x5015C51C = *(int*)0x5015C51C | EFF_POS2;
	*(float*)0x5015C524 = vorigin[0];
	*(float*)0x5015C528 = vorigin[1];
	*(float*)0x5015C52C = vorigin[2];
}

void engine_effect_start(const char* effectFileName, const char* cvarName) {
	vec3_t vorigin;
	readCvarAsVector((char*)cvarName, vorigin);
	int index = orig_SV_FindIndex(effectFileName, CS_EFFECTS, MAX_EFPACKS, 0, "effect");
	if (index == 0) {
		orig_Com_Error(ERR_FATAL, "engine_effect_start: the effect file %s is not registered\n", effectFileName);
	}
	static (__thiscall *fxRunner_exec)(void* self, int effectID, vec3_t pos, multicast_t castType, edict_t *ignoreClient) = 0x500852E0;
	fxRunner_exec((void*)0x5015C518, index, vorigin, MULTICAST_PHS, 0);
}

