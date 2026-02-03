#include <windows.h>
#include "sofheader.h"
#include "engine_features/players/players.h"
#include "util_funcs.h"

void sf_sv_player_ent(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Returns an entity from a player slot number\n"
			"Returned value is 0 for an ent that is not inuse\n"
			"----------------------------\n"
			"arg1 -> cvarname for resulting cvar\n"
			"arg2 -> slot number\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_ent -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(2));
	edict_t* ent = engine_player_get_ent(slot);
	cvar_t* out = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
	if (ent && ent->inuse) {
		setCvarUnsignedInt(out, (unsigned int)ent);
	} else {
		setCvarUnsignedInt(out, 0);
	}
}

void sf_sv_player_pos(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Gets the co-ordinates of the player and stores them in cvars\n"
			"3 cvars will be created based on the prefix you supply\n"
			"eg. sp_sv_player_pos ~org 5\n"
			"Will give me ~org_1 ~org_2 ~org_3 to use with data in them\n"
			"The 5 in the example represents player slot 5\n"
			"----------------------------\n"
			"arg1 -> cvarname you want to use for storing _1 _2 _3 , advisable to parse ~local varaible\n"
			"arg2 -> valid slot id\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_pos -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(2));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	char* storecvar = orig_Cmd_Argv(1);
	vec3_t pos;
	engine_player_pos(ent, pos);
	writeCvarAsVector(pos, storecvar);
}

void sf_sv_player_move(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Teleports a player to specified 1,2,3 co-ordinate\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> cvar prefix for input vector _1 _2 _3\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_move -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	char* prefix = orig_Cmd_Argv(2);
	vec3_t created_vect;
	readCvarAsVector(prefix, created_vect);
	engine_player_move(ent, created_vect);
}

void sf_sv_player_gravity(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Sets the gravity strength on the chosen player\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> gravity value\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_gravity -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	short grav = atoi(orig_Cmd_Argv(2));
	engine_player_gravity(ent, slot, grav);
}

void sf_sv_player_paint(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Applies a coloured tint on a specific player\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> red component between 0.0 and 1.0\n"
			"arg3 -> green component between 0.0 and 1.0\n"
			"arg4 -> blue component between 0.0 and 1.0\n"
			"arg5 -> opacity component between 0.0 and 1.0 , 1.0 being fully visible\n"
		);
		return;
	}
	if (c != 5) {
		orig_Com_Printf("sf_sv_player_paint -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	float r = atof(orig_Cmd_Argv(2));
	float g = atof(orig_Cmd_Argv(3));
	float b = atof(orig_Cmd_Argv(4));
	float a = atof(orig_Cmd_Argv(5));
	engine_player_paint(slot, r, g, b, a);
}

void sf_sv_player_weap_paint(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Applies a coloured tint on a specific player's weapon\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> red component between 0.0 and 1.0\n"
			"arg3 -> green component between 0.0 and 1.0\n"
			"arg4 -> blue component between 0.0 and 1.0\n"
			"arg5 -> opacity component between 0.0 and 1.0 , 1.0 being fully visible\n"
		);
		return;
	}
	if (c != 5) {
		orig_Com_Printf("sf_sv_player_weap_paint -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	float r = atof(orig_Cmd_Argv(2));
	float g = atof(orig_Cmd_Argv(3));
	float b = atof(orig_Cmd_Argv(4));
	float a = atof(orig_Cmd_Argv(5));
	engine_player_weap_paint(slot, r, g, b, a);
}

void sf_sv_player_weap_current(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Get currently held weapon of client\n"
			"----------------------------\n"
			"arg1 -> outcvar to store the weapon number\n"
			"arg2 -> playerslot\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_weap_current -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(2));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	cvar_t* out = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
	int weapon = engine_player_weap_current(ent);
	setCvarInt(out, weapon);
}

void sf_sv_player_weap_switch(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Switch a players weapon to this one\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> newweapon\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_weap_switch -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	int weapon = atoi(orig_Cmd_Argv(2));
	engine_player_weap_switch(ent, weapon);
}

void sf_sv_player_weap_lock(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Prevent a player from changing his weapon\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> Lockstate 1 or 0\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_weap_lock -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	int lockweap = atoi(orig_Cmd_Argv(2));
	engine_player_weap_lock(ent, lockweap);
}

void sf_sv_player_collision(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Makes it so this player can be passed through by all other players\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> 1 or 0 ... representing collision on or off\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_collision -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	int mode = atoi(orig_Cmd_Argv(2));
	engine_player_collision(ent, slot, mode);
}

void sf_sv_player_allow_attack(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Prevent a player from attacking\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> 1 or 0 ... representing allow or disallow\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_allow_attack -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	int allow = atoi(orig_Cmd_Argv(2));
	engine_player_allow_attack(ent, slot, allow);
}

void sf_sv_player_allow_altattack(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Prevent a player from alt attacking\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> 1 or 0 ... representing allow or disallow\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_allow_altattack -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	int allow = atoi(orig_Cmd_Argv(2));
	engine_player_allow_altattack(ent, slot, allow);
}

void sf_sv_player_allow_walk(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Prevent a player from walking\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> 1 or 0 ... representing allow or disallow\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_player_allow_walk -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	int allow = atoi(orig_Cmd_Argv(2));
	engine_player_allow_walk(ent, slot, allow);
}

void sf_sv_player_anim(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Play an animation for an entity\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> animation name\n"
			"arg3 -> startPosition [float]\n"
			"arg4 -> interrupt current [bool int]\n"
			"arg5 -> EndCondition [int]\n"
			"arg6 -> Resume?[bool int]\n"
			"arg7 -> reverse, play in reverse[bool int]\n"
		);
		return;
	}
	if (c != 7) {
		orig_Com_Printf("sf_sv_player_anim -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = engine_player_get_ent(slot);
	if (!ent) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	char* animName = orig_Cmd_Argv(2);
	float startPos = atof(orig_Cmd_Argv(3));
	int restart = atoi(orig_Cmd_Argv(4));
	int loop = atoi(orig_Cmd_Argv(5));
	int resume = atoi(orig_Cmd_Argv(6));
	int reverse = atoi(orig_Cmd_Argv(7));
	engine_player_anim(ent, animName, startPos, restart, loop, resume, reverse);
}

void sf_sv_player_effect(void) {
}

