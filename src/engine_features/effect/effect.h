#pragma once
#include "sofheader.h"

void engine_effect_register(const char* effectName);
int engine_effect_calc_free_slots(void);
void engine_effect_list(const char* search, int* count, cvar_t** savecvar);
void engine_effect_endpos(const char* cvarName);
void engine_effect_start(const char* effectFileName, const char* cvarName);

