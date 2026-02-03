#include <windows.h>
#include "sofheader.h"
#include "engine_features/print/print.h"
#include "engine_features/players/players.h"

void sf_sv_print_cprintf(void) {
	edict_t* ent = engine_player_get_ent(atoi(orig_Cmd_Argv(1)));
	if (ent) {
		engine_print_cprintf(ent, orig_Cmd_Argv(2));
	}
}

void sf_sv_print_bprintf(void) {
	engine_print_bprintf(orig_Cmd_Argv(1));
}

void sf_sv_print_centerprint(void) {
	edict_t* ent = engine_player_get_ent(atoi(orig_Cmd_Argv(1)));
	if (ent) {
		engine_print_centerprint(ent, orig_Cmd_Argv(2));
	}
}

void sf_sv_print_welcomeprint(void) {
	edict_t* ent = engine_player_get_ent(atoi(orig_Cmd_Argv(1)));
	if (ent) {
		engine_print_welcomeprint(ent);
	}
}

void sf_sv_print_cinprintf(void) {
	edict_t* ent = engine_player_get_ent(atoi(orig_Cmd_Argv(1)));
	if (ent) {
		engine_print_cinprintf(ent, atoi(orig_Cmd_Argv(2)), atoi(orig_Cmd_Argv(3)), atoi(orig_Cmd_Argv(4)), orig_Cmd_Argv(5));
	}
}

