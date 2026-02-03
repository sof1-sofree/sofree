#include <windows.h>
#include "sofheader.h"
#include <stdlib.h>
#include <string.h>
#include <shlwapi.h>
#include "engine_features/sound/sound.h"

extern sound_overrides_t sound_overrides;

int engine_sound_calc_free_slots(void) {
	int freeslots = 0;
	for (int i = 1; i < MAX_SOUNDS; i++) {
		if (*(unsigned char*)(SV_CONFIGSTRINGS + (CS_SOUNDS + i) * MAX_QPATH) == '\0') {
			freeslots++;
		}
	}
	return freeslots;
}

void engine_sound_register(const char* soundName) {
	char ver1[128];
	strcpy(ver1, soundName);
	replacechar(ver1, '\\', '/');
	orig_SV_FindIndex(ver1, CS_SOUNDS, MAX_SOUNDS, 1, "sound");
}

void engine_sound_remove(const char* soundName) {
	char ver1[128];
	strcpy(ver1, soundName);
	replacechar(ver1, '\\', '/');
	orig_SV_RemoveSound(ver1);
}

int engine_sound_list(const char* search, int* results, int maxResults) {
	int count = 0;
	for (int i = 1; i < MAX_SOUNDS && count < maxResults; i++) {
		if (*(unsigned char*)(SV_CONFIGSTRINGS + (CS_SOUNDS + i) * MAX_QPATH)) {
			char line[65];
			strcpy(line, SV_CONFIGSTRINGS + (CS_SOUNDS + i) * MAX_QPATH);
			if (!search || StrStrI(line, search)) {
				if (results) {
					strcpy((char*)results + count * 65, line);
				}
				count++;
			}
		}
	}
	return count;
}

int engine_sound_play_ent(const char* soundName, edict_t* ent, int chan, float volume, float atten, int global) {
	char ver1[128];
	strcpy(ver1, soundName);
	replacechar(ver1, '\\', '/');
	int index = orig_SV_FindIndex(ver1, CS_SOUNDS, MAX_SOUNDS, 0, "sound");
	if (index) {
		orig_PF_StartSound(ent, chan, index, volume, atten, 0, global);
		return 1;
	}
	return 0;
}

int engine_sound_play_origin(const char* soundName, vec3_t origin, int chan, float volume, float atten, int global) {
	char ver1[128];
	strcpy(ver1, soundName);
	replacechar(ver1, '\\', '/');
	int index = orig_SV_FindIndex(ver1, CS_SOUNDS, MAX_SOUNDS, 0, "sound");
	if (index) {
		orig_SV_StartSound(origin, *(unsigned int*)EDICT_BASE, chan, index, volume, atten, 0, global);
		return 1;
	}
	return 0;
}

int engine_sound_override(const char* origSound, const char* newSound, const char* attenStr) {
	char* name = (char*)origSound;
	sound_overrides_t* z, * next;
	for (z = sound_overrides.next; z != &sound_overrides; z = next) {
		next = z->next;
		bool star_input = false, star_already = false;
		char* c, * d;
		c = strchr(name, '*');
		star_input = c && (c + 1 == 0x00);
		d = strchr(z->orig_sound, '*');
		star_already = d && (d + 1 == 0x00);
		if (star_input || star_already) {
			if (star_already && star_input) {
				if (d - z->orig_sound < c - name) {
					if (!strnicmp(z->orig_sound, name, d - z->orig_sound)) {
						return 0;
					}
				} else {
					if (!strnicmp(z->orig_sound, name, c - name)) {
						return 0;
					}
				}
			} else {
				if (star_already) {
					if (!strnicmp(z->orig_sound, name, d - z->orig_sound)) {
						return 0;
					}
				} else {
					if (!strnicmp(z->orig_sound, name, c - name)) {
						return 0;
					}
				}
			}
		} else if (!stricmp(name, z->orig_sound)) {
			return 0;
		}
	}
	z = (sound_overrides_t*)malloc(sizeof(sound_overrides_t));
	z->next = sound_overrides.next;
	z->prev = &sound_overrides;
	sound_overrides.next->prev = z;
	sound_overrides.next = z;
	strcpy(z->orig_sound, origSound);
	strcpy(z->new_sound, newSound);
	z->index = 0;
	if (attenStr && strlen(attenStr)) {
		z->atten_mod = atof(attenStr);
	} else {
		z->atten_mod = -1.0f;
	}
	return 1;
}

