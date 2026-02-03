#pragma once
#include "sofheader.h"

int engine_sound_calc_free_slots(void);
void engine_sound_register(const char* soundName);
void engine_sound_remove(const char* soundName);
int engine_sound_list(const char* search, int* results, int maxResults);
int engine_sound_play_ent(const char* soundName, edict_t* ent, int chan, float volume, float atten, int global);
int engine_sound_play_origin(const char* soundName, vec3_t origin, int chan, float volume, float atten, int global);
int engine_sound_override(const char* origSound, const char* newSound, const char* attenStr);

