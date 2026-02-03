#include <windows.h>
#include "sofheader.h"
#include "engine_features/spackage/spackage.h"

void sf_sv_spackage_register(void) {
	int c = orig_Cmd_Argc() - 1;
	char* one = orig_Cmd_Argv(1);
	if (!strcmp(one, "-h")) {
		orig_Com_Printf(
			"Register a .sp string package file that the client will download\n"
			"----------------------------\n"
			"arg1 -> name of file including .sp extension\n"
			"eg. sf_sv_spackage_register mystringpackage.sp\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_spackage_register -h\n");
		return;
	}
	engine_spackage_register(one);
}

void sf_sv_spackage_list(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Lists all registered string packages\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_spackage_X with the results\n"
		);
		return;
	}
	if (c > 1) {
		orig_Com_Printf("sf_sv_spackage_list -h\n");
		return;
	}
	const char* search = (c == 1) ? orig_Cmd_Argv(1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_spackage_list(search, &count, &savecvar);
}

void sf_sv_spackage_print_ref(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Register a .sp string package file that the client will download\n"
			"----------------------------\n"
			"arg1 -> ent handle or 0 for broadcast\n"
			"arg2 -> File reference string\n"
			"arg3 -> Index reference string\n"
			"arg4+ -> Extra strings for passing data into the output\n"
			"eg. sf_sv_spackage_print_id SOFREE CHEER ...\n"
			"NB. %d = integer %p = byte %s = string %hd = signed_short %hu = unsigned short\n"
		);
		return;
	}
	if (c < 3) {
		orig_Com_Printf("sf_sv_spackage_print_ref -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	engine_spackage_print_ref(ent, orig_Cmd_Argv(2), orig_Cmd_Argv(3));
}

void sf_sv_spackage_print_id(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Print an entry from a .sp string package file\n"
			"----------------------------\n"
			"arg1 -> ent handle or 0 for broadcast\n"
			"arg2 -> ID of stringpackage file (found inside the file)\n"
			"arg3 -> Index number of the text you want to print\n"
			"arg4+ -> Extra strings for passing data into the output\n"
			"eg. sf_sv_spackage_print_id 18 25 ...\n"
			"NB. %d = integer %p = byte %s = string %hd = signed_short %hu = unsigned short\n"
		);
		return;
	}
	if (c < 3) {
		orig_Com_Printf("sf_sv_spackage_print_id -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	unsigned char fileId = atoi(orig_Cmd_Argv(2));
	unsigned char index = atoi(orig_Cmd_Argv(3));
	engine_spackage_print_id(ent, fileId, index);
}

void sf_sv_spackage_print_obit(void) {
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	unsigned short id = atoi(orig_Cmd_Argv(2));
	engine_spackage_print_obit(slot, id);
}

void sf_sv_spackage_print_string(void) {
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	const char* msg = orig_Cmd_Argv(2);
	int len = atoi(orig_Cmd_Argv(3));
	engine_spackage_print_string(ent, msg, len);
}

