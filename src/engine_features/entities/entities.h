#pragma once
#include "sofheader.h"

edict_t* engine_ent_create(void);
void engine_ent_spawn(edict_t* ent);
void engine_ent_remove(edict_t* ent);
void engine_ent_relink(edict_t* ent);
void engine_ent_use(edict_t* ent);
void engine_ent_vects(edict_t* ent, vec3_t fwd, vec3_t side, vec3_t up);
int engine_ent_find(int offset, const char* value, edict_t** results, int maxResults);
void engine_ent_tint(edict_t* ent, vec3_t colors, float alpha);
void engine_ent_anim(edict_t* ent, const char* animName, float startPos, int restart, int loop, int match, int reverse);
void engine_ent_model(edict_t* ent, const char* dir, const char* modelname);
void engine_ent_bolt(edict_t* ent, const char* dir, const char* file, const char* bolt_from, const char* bolt_to, float scale);
void engine_ent_paint(edict_t* ent, float r, float g, float b, float a);
int engine_ent_callback(edict_t* ent, const char* type, const char* funcName);

