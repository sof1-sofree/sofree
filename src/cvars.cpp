#include <windows.h>
#include <stdio.h>
#include "sofheader.h"
#include "features.h"


cvar_t * _sf_sv_version = NULL;
cvar_t * _sf_sv_sofree_deathmatch = NULL;

cvar_t * _sf_sv_on_client_damage = NULL;
cvar_t * _sf_sv_on_flag_take = NULL;

cvar_t * _sf_sv_on_use_press = NULL;
cvar_t * _sf_sv_on_use_release= NULL;

cvar_t * _sf_sv_on_attack_press = NULL;
cvar_t * _sf_sv_on_attack_release = NULL;

cvar_t * _sf_sv_on_left_press = NULL;
cvar_t * _sf_sv_on_left_release = NULL;

cvar_t * _sf_sv_on_right_press = NULL;
cvar_t * _sf_sv_on_right_release = NULL;


cvar_t * _sf_sv_bot_focus = NULL;
cvar_t * _sf_sv_sofree_debug = NULL;
cvar_t * _sf_sv_debug_sounds = NULL;

cvar_t * _sf_sv_sound_info_slots = NULL;
cvar_t * _sf_sv_image_info_slots = NULL;
cvar_t * _sf_sv_ghoul_info_slots = NULL;
cvar_t * _sf_sv_effect_info_slots = NULL;



cvar_t * _sf_sv_debug_triggers = NULL;

cvar_t * testcvar = NULL;

cvar_t * _sf_sv_sofree_glmode[16];

cvar_t * g_movescale = NULL;
cvar_t * user = NULL;
cvar_t * maxclients = NULL;
cvar_t * qport = NULL;



void createCvars()
{
	_sf_sv_version = orig_Cvar_Get("_sf_sv_version","",0,NULL);
	
	_sf_sv_sound_info_slots = orig_Cvar_Get("_sf_sv_sound_info_slots","",0,NULL);
	_sf_sv_image_info_slots = orig_Cvar_Get("_sf_sv_image_info_slots","",0,NULL);
	_sf_sv_ghoul_info_slots = orig_Cvar_Get("_sf_sv_ghoul_info_slots","",0,NULL);
	_sf_sv_effect_info_slots = orig_Cvar_Get("_sf_sv_effect_info_slots","",0,NULL);

	qport = orig_Cvar_Get("qport","",0,NULL);
	maxclients = orig_Cvar_Get ("maxclients","",0,NULL);
	user =  orig_Cvar_Get ("user","",0,NULL);
	g_movescale = orig_Cvar_Get("g_movescale","0",0,NULL);
	_sf_sv_sofree_deathmatch = orig_Cvar_Get("_sf_sv_sofree_deathmatch","0",0,NULL);
	
	_sf_sv_sound_info_slots = orig_Cvar_Get("_sf_sv_sound_info_slots","0",0,NULL);
	_sf_sv_image_info_slots = orig_Cvar_Get("_sf_sv_image_info_slots","0",0,NULL);
	_sf_sv_ghoul_info_slots = orig_Cvar_Get("_sf_sv_ghoul_info_slots","0",0,NULL);

	_sf_sv_sofree_debug = orig_Cvar_Get("_sf_sv_sofree_debug","1.0",0,NULL);

	_sf_sv_on_client_damage = orig_Cvar_Get("_sf_sv_on_client_damage","",0,NULL);
	_sf_sv_on_flag_take = orig_Cvar_Get("_sf_sv_on_flag_take","",0,NULL);

	_sf_sv_on_use_press = orig_Cvar_Get("_sf_sv_on_use_press","",0,NULL);
	_sf_sv_on_use_release = orig_Cvar_Get("_sf_sv_on_use_release","",0,NULL);

	_sf_sv_on_attack_press = orig_Cvar_Get("_sf_sv_on_attack_press","",0,NULL);
	_sf_sv_on_attack_release = orig_Cvar_Get("_sf_sv_on_attack_release","",0,NULL);

	_sf_sv_on_left_press = orig_Cvar_Get("_sf_sv_on_left_press","",0,NULL);
	_sf_sv_on_left_release = orig_Cvar_Get("_sf_sv_on_left_release","",0,NULL);

	_sf_sv_on_right_press = orig_Cvar_Get("_sf_sv_on_right_press","",0,NULL);
	_sf_sv_on_right_release = orig_Cvar_Get("_sf_sv_on_right_release","",0,NULL);

	_sf_sv_debug_triggers = orig_Cvar_Get("_sf_sv_debug_triggers","0.0",0,NULL);
	
	_sf_sv_debug_sounds = orig_Cvar_Get("_sf_sv_debug_sounds","0.0",0,NULL);
		
	_sf_sv_bot_focus = orig_Cvar_Get("_sf_sv_bot_focus","-1.0",0,NULL);

	testcvar = orig_Cvar_Get("testcvar","0",0,NULL);

	create_movement_cvars();
	create_grenade_cvars();
	create_q2_mode_cvars();
	create_force_sky_cvars();
	create_ghoul_tint_cvars();
	create_fx_cvars();
	create_gravity_cvars();
	create_force_item_respawn_cvars();
}


