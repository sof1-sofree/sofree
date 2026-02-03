#pragma once
#include "sofheader.h"

edict_t* engine_script_load(const char* scriptName, const char** params, int paramCount);
void engine_script_unload(edict_t* runner);
void engine_script_run(edict_t* runner);

