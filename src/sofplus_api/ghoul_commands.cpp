#include <windows.h>
#include "sofheader.h"
#include "engine_features/ghoul/ghoul.h"
#include "util_funcs.h"

void sf_sv_ghoul_register(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Registers a new ghoul file\n"
			"Must be in a sub-directory\n"
			"----------------------------\n"
			"arg1 -> name of ghoul\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_ghoul_register -h\n");
		return;
	}
	char ver1[128];
	strcpy(ver1, one);
	replacechar(ver1, '\\', '/');
	engine_ghoul_register(ver1);
	int freeslots = engine_ghoul_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_ghoul_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
}

void sf_sv_ghoul_translate(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Shifts the ghoul model's origin by vector\n"
			"Vector represents offset in each axis X Y Z\n"
			"NB. Order of ghoul editting matters. Scale affects translation units\n"
			"Translation affects point of rotation\n"
			"----------------------------\n"
			"arg1 -> entity handle\n"
			"arg2 -> invector cvarname\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_ghoul_translate -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	vec3_t translate_v;
	readCvarAsVector(orig_Cmd_Argv(2), translate_v);
	engine_ghoul_translate(ent, translate_v);
}

void sf_sv_ghoul_scale(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Scale the size of the entity model\n"
			"NB. Order of ghoul editting matters. Scale affects translation units\n"
			"Translation affects point of rotation\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> scale [float]\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_ghoul_scale -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	engine_ghoul_scale(ent, atof(orig_Cmd_Argv(2)));
}

void sf_sv_ghoul_list(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Lists all registered ghoul files\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_ghoul_X with the results\n"
		);
		return;
	}
	if (c > 1) {
		orig_Com_Printf("sf_sv_ghoul_list -h\n");
		return;
	}
	const char* search = (c == 1) ? orig_Cmd_Argv(1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_ghoul_list(search, &count, &savecvar);
}

