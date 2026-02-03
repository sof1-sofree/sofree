#include <windows.h>
#include <shlwapi.h>
#include "sofheader.h"
#include "engine_features/image/image.h"
#include "util_funcs.h"

int engine_image_calc_free_slots(void) {
	int freeslots = 0;
	for (int i = 1; i < MAX_IMAGES; i++) {
		if (*(unsigned char*)(SV_CONFIGSTRINGS + (CS_IMAGES + i) * MAX_QPATH) == '\0') {
			freeslots++;
		}
	}
	return freeslots;
}

void engine_image_register(const char* imageName) {
	char ver1[128];
	strcpy(ver1, imageName);
	replacechar(ver1, '\\', '/');
	orig_SV_FindIndex(ver1, CS_IMAGES, MAX_IMAGES, 1, "image");
}

void engine_image_list(const char* search, int* count, cvar_t** savecvar) {
	*count = 0;
	if (!search) search = "";
	for (int i = 1; i < MAX_IMAGES; i++) {
		if (*(unsigned char*)(SV_CONFIGSTRINGS + (CS_IMAGES + i) * MAX_QPATH)) {
			char line[65];
			strcpy(line, SV_CONFIGSTRINGS + (CS_IMAGES + i) * MAX_QPATH);
			if (strlen(search) == 0 || StrStrI(line, search)) {
				(*count)++;
			}
		}
	}
}

void Cmd_CalcFreeImageSlots(void)
{
	int freeslots = engine_image_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_image_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
}

