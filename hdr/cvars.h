extern cvar_t * _sf_sv_version;
extern cvar_t * _sf_sv_sofree_deathmatch;
extern cvar_t * _sf_sv_on_client_damage;
extern cvar_t * _sf_sv_on_flag_take;

extern cvar_t * _sf_sv_on_use_press;
extern cvar_t * _sf_sv_on_use_release;

extern cvar_t * _sf_sv_on_attack_press;
extern cvar_t * _sf_sv_on_attack_release;

extern cvar_t * _sf_sv_on_left_press;
extern cvar_t * _sf_sv_on_left_release;

extern cvar_t * _sf_sv_on_right_press;
extern cvar_t * _sf_sv_on_right_release;

extern cvar_t * _sf_sv_gravity_default;

extern cvar_t * _sf_sv_force_sky;

extern cvar_t * _sf_sv_fx_blood_amount;
extern cvar_t * _sf_sv_fx_blood_speed;
extern cvar_t * _sf_sv_fx_mode;
extern cvar_t * _sf_sv_ghl_tint_r;
extern cvar_t * _sf_sv_ghl_tint_g;
extern cvar_t * _sf_sv_ghl_tint_b;
extern cvar_t * _sf_sv_ghl_tint_a;

extern cvar_t * _sf_sv_bot_focus;
extern cvar_t * _sf_sv_sofree_debug;
extern cvar_t * _sf_sv_debug_sounds;
extern cvar_t * _sf_sv_debug_triggers;

extern cvar_t * _sf_sv_sound_info_slots;
extern cvar_t * _sf_sv_ghoul_info_slots;
extern cvar_t * _sf_sv_images_info_slots;
extern cvar_t * _sf_sv_effect_info_slots;

extern cvar_t * _sf_sv_force_item_respawntime;
extern cvar_t * _sf_sv_airaccel;
extern cvar_t * _sf_sv_accel;
extern cvar_t * _sf_sv_friction;
extern cvar_t * _sf_sv_crouchspeed;
extern cvar_t * _sf_sv_runspeed;
extern cvar_t * _sf_sv_q2_mode;
extern cvar_t * _sf_sv_q2_slide_fix;
extern cvar_t * _sf_sv_q2_style_jump;
extern cvar_t * _sf_sv_rampslide_threshold;

extern  cvar_t * _sf_sv_grenade_impact_explode;

extern cvar_t * testcvar;

extern cvar_t * g_movescale;
extern cvar_t * user;
extern cvar_t * maxclients;
extern cvar_t * qport;

void createCvars(void);
void _sf_sv_accel_callback(cvar_t * thecvar);
void _sf_sv_airaccel_callback(cvar_t * thecvar);
void _sf_sv_crouchspeed_callback(cvar_t * thecvar);
void _sf_sv_runspeed_callback(cvar_t * thecvar);
void _sf_sv_friction_callback(cvar_t * thecvar);
void _sf_sv_rampslide_threshold_callback(cvar_t * thecvar);
void _sf_sv_grenade_impact_explode_callback(cvar_t * thecvar);


// #define LUA_USE_LINUX

extern "C" {
	// #include "lua/luaconf.h"
	#include "../src/lua/lua.h"
	#include "../src/lua/lualib.h"
	#include "../src/lua/lauxlib.h"
}

// #include "lua/lua.hpp"