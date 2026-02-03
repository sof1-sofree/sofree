#pragma once
#include "sofheader.h"

void engine_print_cprintf(edict_t* ent, const char* text);
void engine_print_bprintf(const char* text);
void engine_print_centerprint(edict_t* ent, const char* text);
void engine_print_welcomeprint(edict_t* ent);
void engine_print_cinprintf(edict_t* ent, int x, int y, int speed, const char* text);

