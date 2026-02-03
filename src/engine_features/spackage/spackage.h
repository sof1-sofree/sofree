#pragma once
#include "sofheader.h"

void engine_spackage_register(const char* packageName);
void engine_spackage_list(const char* search, int* count, cvar_t** savecvar);
void engine_spackage_print_ref(edict_t* ent, const char* fileRef, const char* indexRef);
void engine_spackage_print_id(edict_t* ent, unsigned char fileId, unsigned char index);
void engine_spackage_print_obit(unsigned int slot, unsigned short id);
void engine_spackage_print_string(edict_t* ent, const char* msg, int len);

