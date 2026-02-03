#include <windows.h>
#include "sofheader.h"
#include "engine_features/image/image.h"
#include "util_funcs.h"

void sf_sv_image_register(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Registers a new image/m32 file\n"
			"----------------------------\n"
			"arg1 -> name of imagefile eg. pics/example.m32\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_image_register -h\n");
		return;
	}
	char ver1[128];
	strcpy(ver1, one);
	replacechar(ver1, '\\', '/');
	engine_image_register(ver1);
	int freeslots = engine_image_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_image_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
}

void sf_sv_image_list(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Lists all registered images\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_image_X with the results\n"
		);
		return;
	}
	if (c > 1) {
		orig_Com_Printf("sf_sv_image_list -h\n");
		return;
	}
	const char* search = (c == 1) ? orig_Cmd_Argv(1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_image_list(search, &count, &savecvar);
}

