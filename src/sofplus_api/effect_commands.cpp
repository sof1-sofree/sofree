#include <windows.h>
#include "sofheader.h"
#include "engine_features/effect/effect.h"
#include "util_funcs.h"

void sf_sv_effect_register(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Registers a new effect file\n"
			"----------------------------\n"
			"arg1 -> name of effect\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_effect_register -h\n");
		return;
	}
	char ver1[128];
	strcpy(ver1, one);
	replacechar(ver1, '\\', '/');
	engine_effect_register(ver1);
	int freeslots = engine_effect_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_effect_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
}

void sf_sv_effect_list(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Lists all registered effects\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_effect_X with the results\n"
		);
		return;
	}
	if (c > 1) {
		orig_Com_Printf("sf_sv_effect_list -h\n");
		return;
	}
	const char* search = (c == 1) ? orig_Cmd_Argv(1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_effect_list(search, &count, &savecvar);
}

void sf_sv_effect_endpos(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Call this just before you spawn or exec\n"
			"Set an end position for a line effect environ_effect entity\n"
			"----------------------------\n"
			"arg1 -> cvar name for origin vector\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_effect_endpos -h\n");
		return;
	}
	engine_effect_endpos(orig_Cmd_Argv(1));
}

void sf_sv_effect_start(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Start an effect\n"
			"----------------------------\n"
			"arg1 -> effect filename\n"
			"arg2 -> cvar name for origin vector\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_effect_start -h\n");
		return;
	}
	engine_effect_start(orig_Cmd_Argv(1), orig_Cmd_Argv(2));
}

