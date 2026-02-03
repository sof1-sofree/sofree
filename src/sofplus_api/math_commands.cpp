#include <windows.h>
#include "sofheader.h"
#include "engine_features/math/math.h"
#include "util_funcs.h"

void sf_sv_math_sin(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Your average math sin function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially angle, will sin the angle and store\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_math_sin -h\n");
		return;
	}
	cvar_t* lol = orig_Cvar_Get(orig_Cmd_Argv(1), "0", 0, NULL);
	setCvarFloat(lol, engine_math_sin(lol->value));
}

void sf_sv_math_asin(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Your average math asin function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially number, will inverse sin the number and store\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_math_asin -h\n");
		return;
	}
	cvar_t* lol = orig_Cvar_Get(orig_Cmd_Argv(1), "0", 0, NULL);
	setCvarFloat(lol, engine_math_asin(lol->value));
}

void sf_sv_math_cos(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Your average math cos function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially angle, will cos the angle and store\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_math_cos -h\n");
		return;
	}
	cvar_t* lol = orig_Cvar_Get(orig_Cmd_Argv(1), "0", 0, NULL);
	setCvarFloat(lol, engine_math_cos(lol->value));
}

void sf_sv_math_acos(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Your average math acos function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially number, will inverse cos the number and store\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_math_acos -h\n");
		return;
	}
	cvar_t* lol = orig_Cvar_Get(orig_Cmd_Argv(1), "0", 0, NULL);
	setCvarFloat(lol, engine_math_acos(lol->value));
}

void sf_sv_math_tan(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Your average math tan function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially angle, will tan the angle and store\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_math_tan -h\n");
		return;
	}
	cvar_t* lol = orig_Cvar_Get(orig_Cmd_Argv(1), "0", 0, NULL);
	setCvarFloat(lol, engine_math_tan(lol->value));
}

void sf_sv_math_atan(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Your average math atan function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially number, will inverse tan the number and store\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_math_atan -h\n");
		return;
	}
	cvar_t* lol = orig_Cvar_Get(orig_Cmd_Argv(1), "0", 0, NULL);
	setCvarFloat(lol, engine_math_atan(lol->value));
}

void sf_sv_math_or(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Unsigned OR function\n"
			"----------------------------\n"
			"arg1 -> inoutcvar value of first number\n"
			"arg2 -> innumber OR with what?\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_math_or -h\n");
		return;
	}
	cvar_t* inout = findCvar(orig_Cmd_Argv(1));
	if (!inout) {
		orig_Com_Printf("error in sf_sv_math_or , supplied cvar does not exist\n");
		return;
	}
	unsigned int num1 = atoi(inout->string);
	unsigned int num2 = atoi(orig_Cmd_Argv(2));
	setCvarUnsignedInt(inout, engine_math_or(num1, num2));
}

void sf_sv_math_and(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Unsigned AND function\n"
			"----------------------------\n"
			"arg1 -> inoutcvar value of first number\n"
			"arg2 -> innumber AND with what?\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_math_and -h\n");
		return;
	}
	cvar_t* inout = findCvar(orig_Cmd_Argv(1));
	if (!inout) {
		orig_Com_Printf("error in sf_sv_math_and , supplied cvar does not exist\n");
		return;
	}
	unsigned int num1 = atoi(inout->string);
	unsigned int num2 = atoi(orig_Cmd_Argv(2));
	setCvarUnsignedInt(inout, engine_math_and(num1, num2));
}

void sf_sv_math_not(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Unsigned NOT function\n"
			"----------------------------\n"
			"arg1 -> inoutcvar value of the number you want NOTTED\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_math_not -h\n");
		return;
	}
	cvar_t* inout = findCvar(orig_Cmd_Argv(1));
	if (!inout) {
		orig_Com_Printf("error in sf_sv_math_not , supplied cvar does not exist\n");
		return;
	}
	unsigned int num1 = atoi(inout->string);
	setCvarUnsignedInt(inout, engine_math_not(num1));
}

