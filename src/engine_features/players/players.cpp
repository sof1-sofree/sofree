#include <windows.h>
#include "sofheader.h"
#include "engine_features/players/players.h"
#include "util_funcs.h"

extern float player_tint[32][4];
extern float player_wep_tint[32][4];
extern short client_gravity[32];
extern bool player_collision[32];
extern bool disable_attack[32];
extern bool disable_altattack[32];
extern bool disable_walk[32];
extern unsigned int* clientinst;

edict_t* engine_player_get_ent(unsigned int slot) {
	return get_ent_from_player_slot(slot);
}

void engine_player_move(edict_t* ent, vec3_t pos) {
	VectorCopy(pos, ent->s.origin);
}

void engine_player_gravity(edict_t* ent, unsigned int slot, short gravity) {
	ent->client->ps.pmove.gravity = gravity;
	client_gravity[slot] = gravity;
}

void engine_player_paint(unsigned int slot, float r, float g, float b, float a) {
	player_tint[slot][0] = r;
	player_tint[slot][1] = g;
	player_tint[slot][2] = b;
	player_tint[slot][3] = a;
}

void engine_player_weap_paint(unsigned int slot, float r, float g, float b, float a) {
	player_wep_tint[slot][0] = r;
	player_wep_tint[slot][1] = g;
	player_wep_tint[slot][2] = b;
	player_wep_tint[slot][3] = a;
}

int engine_player_weap_current(edict_t* ent) {
	static int(__thiscall * getCurWeaponType)(void* self) = 0x40005A70;
	return getCurWeaponType(ent->client->inv);
}

void engine_player_weap_switch(edict_t* ent, int weapon) {
	sharedEdict_t sh;
	sh.inv = (inven_c*)ent->client->inv;
	sh.edict = ent;
	orig_SetOwner(sh.inv, &sh);
	orig_selectWeapon(sh.inv, weapon);
}

void engine_player_weap_lock(edict_t* ent, int lock) {
	sharedEdict_t sh;
	sh.inv = (inven_c*)ent->client->inv;
	sh.edict = ent;
	orig_SetOwner(sh.inv, &sh);
	if (lock == 1) {
		orig_rulesSetFreelySelectWeapon(sh.inv, 0);
	} else if (lock == 0) {
		orig_rulesSetFreelySelectWeapon(sh.inv, 1);
	}
}

void engine_player_collision(edict_t* ent, unsigned int slot, int mode) {
	if (mode != 0 && mode != 1) {
		return;
	}
	player_collision[slot] = (mode == 1);
	if (mode == 1) {
		ent->solid = SOLID_BBOX;
	} else {
		ent->solid = SOLID_NOT;
	}
	orig_SV_LinkEdict(ent);
}

void engine_player_allow_attack(edict_t* ent, unsigned int slot, int allow) {
	disable_attack[slot] = (allow == 0);
}

void engine_player_allow_altattack(edict_t* ent, unsigned int slot, int allow) {
	disable_altattack[slot] = (allow == 0);
}

void engine_player_allow_walk(edict_t* ent, unsigned int slot, int allow) {
	disable_walk[slot] = (allow == 0);
}

void engine_player_anim(edict_t* ent, const char* animName, float startPos, int restart, int loop, int match, int reverse) {
	if (!ent) return;
	clientinst = (unsigned int*)(ent->ghoulInst);
	if (clientinst) {
		GhoulGetObject();
		GhoulID seq = GhoulFindSequence(animName);
		if (!seq) {
			orig_Com_Printf("Cant find sequence\n");
			return;
		}
		GhoulPlay(seq, *(float*)0x5015CCDC, startPos, restart, loop, match, reverse);
	}
}

void engine_player_pos(edict_t* ent, vec3_t out) {
	VectorCopy(ent->s.origin, out);
}

void engine_player_effect(edict_t* ent, int effectID) {
}

