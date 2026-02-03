#pragma once
#include "sofheader.h"

edict_t* engine_player_get_ent(unsigned int slot);
void engine_player_move(edict_t* ent, vec3_t pos);
void engine_player_gravity(edict_t* ent, unsigned int slot, short gravity);
void engine_player_paint(unsigned int slot, float r, float g, float b, float a);
void engine_player_weap_paint(unsigned int slot, float r, float g, float b, float a);
int engine_player_weap_current(edict_t* ent);
void engine_player_weap_switch(edict_t* ent, int weapon);
void engine_player_weap_lock(edict_t* ent, int lock);
void engine_player_collision(edict_t* ent, unsigned int slot, int mode);
void engine_player_allow_attack(edict_t* ent, unsigned int slot, int allow);
void engine_player_allow_altattack(edict_t* ent, unsigned int slot, int allow);
void engine_player_allow_walk(edict_t* ent, unsigned int slot, int allow);
void engine_player_anim(edict_t* ent, const char* animName, float startPos, int restart, int loop, int match, int reverse);
void engine_player_pos(edict_t* ent, vec3_t out);
void engine_player_effect(edict_t* ent, int effectID);

