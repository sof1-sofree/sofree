#pragma once
#include "sofheader.h"

void engine_ghoul_register(const char* ghoulName);
void engine_ghoul_translate(edict_t* ent, vec3_t translate_v);
void engine_ghoul_scale(edict_t* ent, float scale);
int engine_ghoul_calc_free_slots(void);
void engine_ghoul_list(const char* search, int* count, cvar_t** savecvar);

