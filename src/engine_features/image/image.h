#pragma once
#include "sofheader.h"

void engine_image_register(const char* imageName);
int engine_image_calc_free_slots(void);
void engine_image_list(const char* search, int* count, cvar_t** savecvar);

