#pragma once

#include "sofheader.h"
#include "feature_config.h"

void core_init_applyHooks(void);
void memory_patches_applyPatches(void);
void vaccine_applyHooks(void);

void create_movement_cvars(void);
void create_grenade_cvars(void);
void create_q2_mode_cvars(void);
void create_force_sky_cvars(void);
void create_ghoul_tint_cvars(void);
void create_fx_cvars(void);
void create_gravity_cvars(void);
void create_force_item_respawn_cvars(void);

void grenade_applyHooks(void);
void gravity_applyHooks(void);
char* force_sky_PF_Configstring(int index,char * string);
void ghoul_tint_applyTint(void);
void fx_handleDamage(vec3_t point, vec3_t dir, edict_t *targ);

extern cvar_t * _sf_sv_friction;
extern cvar_t * _sf_sv_accel;
extern cvar_t * _sf_sv_airaccel;
extern cvar_t * _sf_sv_crouchspeed;
extern cvar_t * _sf_sv_runspeed;
extern cvar_t * _sf_sv_rampslide_threshold;
extern cvar_t * _sf_sv_grenade_impact_explode;
extern cvar_t * _sf_sv_q2_slide_fix;
extern cvar_t * _sf_sv_q2_style_jump;
extern cvar_t * _sf_sv_q2_mode;
extern cvar_t * _sf_sv_force_sky;
extern cvar_t * _sf_sv_ghl_tint_r;
extern cvar_t * _sf_sv_ghl_tint_g;
extern cvar_t * _sf_sv_ghl_tint_b;
extern cvar_t * _sf_sv_ghl_tint_a;
extern cvar_t * _sf_sv_fx_mode;
extern cvar_t * _sf_sv_fx_blood_amount;
extern cvar_t * _sf_sv_fx_blood_speed;
extern cvar_t * _sf_sv_gravity_default;
extern cvar_t * _sf_sv_force_item_respawntime;

