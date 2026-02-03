#include <windows.h>
#include "sofheader.h"
#include "engine_features/script/script.h"
#include "util_funcs.h"

void sf_sv_script_load(void) {
	int n = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"DesignerScripts are .ds files compiled into .os files using sofds.exe from SoF SDK\n"
			"----------------------------\n"
			"Loads a DesignerScript file (.os), located in your %%User%%/ds/ directory\n"
			"----------------------------\n"
			"arg1 -> cvarname to store handle\n"
			"arg2 -> name of script\n"
			"args3+ -> optional parameters to pass\n"
		);
		return;
	}
	if (n < 2) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}
	cvar_t* out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
	const char* params[16] = { 0 };
	for (int i = 0; i < n - 2 && i < 16; i++) {
		params[i] = orig_Cmd_Argv(i + 3);
	}
	edict_t* runner = engine_script_load(orig_Cmd_Argv(2), params, n - 2);
	setCvarInt(out_cvar, (int)runner);
}

void sf_sv_script_unload(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"DesignerScripts are .ds files compiled into .os files using sofds.exe from SoF SDK\n"
			"----------------------------\n"
			"Stops execution to a previously loaded script file and unloads the script file\n"
			"Your script handle is no longer valid after calling this function\n"
			"You must pass in the handle you saved from sp_sv_script_load\n"
			"eg. \"sp_sv_script_unload $my_script\" , where myscript is the cvar storing the handle\n"
			"----------------------------\n"
			"arg1 -> handle to loaded script\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent || !ent->inuse) {
		orig_Com_Printf("Invalid script handle\n");
		return;
	}
	engine_script_unload(ent);
}

void sf_sv_script_run(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"DesignerScripts are .ds files compiled into .os files using sofds.exe from SoF SDK\n"
			"----------------------------\n"
			"Returns execution to a previously loaded script file\n"
			"You must pass in the handle you saved from sp_sv_script_load\n"
			"eg. \"sp_sv_script_run $my_script\" , where myscript is the cvar storing the handle\n"
			"----------------------------\n"
			"arg1 -> handle to loaded script\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent || !ent->inuse) {
		orig_Com_Printf("Invalid script handle\n");
		return;
	}
	engine_script_run(ent);
}

