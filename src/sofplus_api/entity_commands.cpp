#include <windows.h>
#include "sofheader.h"
#include "engine_features/entities/entities.h"
#include "util_funcs.h"

void sf_sv_ent_create(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Creates an entity from a classname\n"
			"But doesn't spawn it into the world.\n"
			"----------------------------\n"
			"arg1 -> cvarname to store the entity handle\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_ent_create -h\n");
		return;
	}
	cvar_t* out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
	edict_t* ent = engine_ent_create();
	unsigned int value = (unsigned int)ent;
	setCvarInt(out_cvar, value);
}

void sf_sv_ent_spawn(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Places an already created entity into the world.\n"
			"----------------------------\n"
			"arg1 -> immidiate value of entity handle\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_ent_spawn -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	engine_ent_spawn(ent);
}

void sf_sv_ent_relink(void) {
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	engine_ent_relink(ent);
}

void sf_sv_ent_remove(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Deletes an edict\n"
			"Use this on ANY previously created entity\n"
			"Spawned or unspawned\n"
			"----------------------------\n"
			"arg1 -> immidiate value of entity handle\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_ent_remove -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	engine_ent_remove(ent);
}

void sf_sv_ent_use(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Execute the 'use' callback of an entity\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
		);
		return;
	}
	if (c != 1) {
		orig_Com_Printf("sf_sv_ent_use -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	engine_ent_use(ent);
}

void sf_sv_ent_vects(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Grabs forward right up vectors of ent\n"
			"----------------------------\n"
			"arg1 -> cvarname prefix for resulting cvars\n"
			"arg2 -> ent\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}
	char* cvarprefix = orig_Cmd_Argv(1);
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(2));
	vec3_t fwd_vec, side_vec, up_vec;
	engine_ent_vects(ent, fwd_vec, side_vec, up_vec);
	char newname[64];
	sprintf(newname, "%s%s", cvarprefix, "_fwd");
	writeCvarAsVector(fwd_vec, newname);
	sprintf(newname, "%s%s", cvarprefix, "_side");
	writeCvarAsVector(side_vec, newname);
	sprintf(newname, "%s%s", cvarprefix, "_up");
	writeCvarAsVector(up_vec, newname);
}

void sf_sv_ent_find(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Finds entities based on matching string using offset\n"
			"Will not return entities if inuse = false\n"
			"eg. sp_sv_ent_find ~answer 436 m_x_bull\n"
			"is equivalent to sp_sv_ent_find ~answer $EDICT_CLASSNAME m_x_bull\n"
			"cvarname_0 is the number of entities found\n"
			"cvarname_[1->N] is the id of each ent found\n"
			"----------------------------\n"
			"arg1 -> cvarname prefix for resulting cvar\n"
			"arg2 -> integer offset for which ent field to compare\n"
			"arg3 -> value for which it must match\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_ent_find -h\n");
		return;
	}
	char* cvarprefix = orig_Cmd_Argv(1);
	int offset = atoi(orig_Cmd_Argv(2));
	char* val_to_find = orig_Cmd_Argv(3);
	edict_t* results[256];
	int count = engine_ent_find(offset, val_to_find, results, 256);
	char newname[64];
	for (int i = 0; i < count; i++) {
		sprintf(newname, "%s_%d", cvarprefix, i + 1);
		cvar_t* u = orig_Cvar_Get(newname, "", 0, NULL);
		setCvarInt(u, (int)results[i]);
	}
	sprintf(newname, "%s_%d", cvarprefix, 0);
	cvar_t* howmany = orig_Cvar_Get(newname, "", 0, NULL);
	setCvarInt(howmany, count);
}

void sf_sv_ent_tint(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Tints an entity a certain color.\n"
			"----------------------------\n"
			"arg1 -> immidiate value of entity handle\n"
			"arg2 -> vector [floats] of r g b colors 0->1\n"
			"arg3 -> [float] alpha/transparency value 0->1\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_ent_tint -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	vec3_t colors;
	readCvarAsVector(orig_Cmd_Argv(2), colors);
	float alpha = atof(orig_Cmd_Argv(3));
	engine_ent_tint(ent, colors, alpha);
}

void sf_sv_ent_anim(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Play an animation for an entity\n"
			"----------------------------\n"
			"arg1 -> entId\n"
			"arg2 -> animation name\n"
			"arg3 -> startPosition [float]\n"
			"arg4 -> interrupt current [int]\n"
			"arg5 -> should it loop [int]\n"
			"arg6 -> match, no idea[int]\n"
			"arg7 -> reverse, play in reverse[int]\n"
		);
		return;
	}
	if (c != 7) {
		orig_Com_Printf("sf_sv_ent_anim -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	char* animName = orig_Cmd_Argv(2);
	float startPos = atof(orig_Cmd_Argv(3));
	int restart = atoi(orig_Cmd_Argv(4));
	int loop = atoi(orig_Cmd_Argv(5));
	int match = atoi(orig_Cmd_Argv(6));
	int reverse = atoi(orig_Cmd_Argv(7));
	engine_ent_anim(ent, animName, startPos, restart, loop, match, reverse);
}

void sf_sv_ent_model(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Apply a model to an entity\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> dir\n"
			"arg3 -> modelname\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_ent_model -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	char* dir = orig_Cmd_Argv(2);
	char* modelname = orig_Cmd_Argv(3);
	engine_ent_model(ent, dir, modelname);
}

void sf_sv_ent_bolt(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Bolt another ghoul model to the current ghoul\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> scale [float]\n"
		);
		return;
	}
	if (c != 6) {
		orig_Com_Printf("sf_sv_ent_bolt -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	char* dir = orig_Cmd_Argv(2);
	char* file = orig_Cmd_Argv(3);
	char* bolt_from = orig_Cmd_Argv(4);
	char* bolt_to = orig_Cmd_Argv(5);
	float scale = atof(orig_Cmd_Argv(6));
	engine_ent_bolt(ent, dir, file, bolt_from, bolt_to, scale);
}

void sf_sv_ent_paint(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Color an entity\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> red float 0.0 -> 1.0\n"
			"arg3 -> green float 0.0 -> 1.0\n"
			"arg4 -> blue float 0.0 -> 1.0\n"
			"arg5 -> alpha float 0.0 -> 1.0\n"
		);
		return;
	}
	if (c != 5) {
		orig_Com_Printf("sf_sv_ent_paint -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	float r = atof(orig_Cmd_Argv(2));
	float g = atof(orig_Cmd_Argv(3));
	float b = atof(orig_Cmd_Argv(4));
	float a = atof(orig_Cmd_Argv(5));
	engine_ent_paint(ent, r, g, b, a);
}

void sf_sv_ent_callback(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Attach a sof function to a touch event of an entity\n"
			"Type can be : think/touch/use/pluse/pain/die\n"
			"touch arguments: [2] touched toucher\n"
			"think arguments: [1] thinker\n"
			"use arguments: [2] ent_used activator\n"
			"pluse (player_use) arguments: [2] ent_used activator\n"
			"pain arguments: [2] inflicted inflictor\n"
			"die arguments: [3] died inflictor attacker\n"
			"----------------------------\n"
			"arg1 -> entity handle\n"
			"arg2 -> type of callback\n"
			"arg3 -> sofplus function name\n"
		);
		return;
	}
	if (c != 3) {
		orig_Com_Printf("sf_sv_ent_callback -h\n");
		return;
	}
	edict_t* ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	char* type = orig_Cmd_Argv(2);
	char* funcName = orig_Cmd_Argv(3);
	if (!engine_ent_callback(ent, type, funcName)) {
		orig_Com_Printf("Invalid callback type\n");
	}
}

