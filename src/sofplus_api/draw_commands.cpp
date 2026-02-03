#include <windows.h>
#include "sofheader.h"
#include "engine_features/draw/draw.h"

void sf_sv_draw_clear(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Clears all interface text on screen\n"
		);
		return;
	}
	if (c != 0) {
		orig_Com_Printf("sf_sv_draw_clear -h\n");
		return;
	}
	engine_draw_clear();
}

void sf_sv_draw_string(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Draw a string at offset x y with message\n"
			"----------------------------\n"
			"arg1 -> offsetx\n"
			"arg2 -> offsety\n"
			"arg3 -> message\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_draw_string -h\n");
		return;
	}
	int offsetx = atoi(orig_Cmd_Argv(1));
	int offsety = atoi(orig_Cmd_Argv(2));
	char* message = orig_Cmd_Argv(3);
	engine_draw_string(offsetx, offsety, message);
}

void sf_sv_draw_string2(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Draw a string at offset x y with message\n"
			"----------------------------\n"
			"arg1 -> offsetx\n"
			"arg2 -> offsety\n"
			"arg3 -> message\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_draw_string2 -h\n");
		return;
	}
	int offsetx = atoi(orig_Cmd_Argv(1));
	int offsety = atoi(orig_Cmd_Argv(2));
	char* message = orig_Cmd_Argv(3);
	engine_draw_string2(offsetx, offsety, message);
}

void sf_sv_draw_altstring(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Draw a grey string at offset x y with message\n"
			"----------------------------\n"
			"arg1 -> offsetx\n"
			"arg2 -> offsety\n"
			"arg3 -> message\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_draw_altstring -h\n");
		return;
	}
	int offsetx = atoi(orig_Cmd_Argv(1));
	int offsety = atoi(orig_Cmd_Argv(2));
	char* message = orig_Cmd_Argv(3);
	engine_draw_altstring(offsetx, offsety, message);
}

