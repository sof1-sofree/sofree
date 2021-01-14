#include <windows.h>
#include <stdio.h> //NULL lol
#include "sofheader.h"


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

cvar_t * _sf_sv_gravity_default = NULL;




cvar_t * _sf_sv_force_sky = NULL;

cvar_t * _sf_sv_fx_blood_amount = NULL;
cvar_t * _sf_sv_fx_blood_speed = NULL;

cvar_t * _sf_sv_fx_mode = NULL;
cvar_t * _sf_sv_ghl_tint_r = NULL;
cvar_t * _sf_sv_ghl_tint_g = NULL; 
cvar_t * _sf_sv_ghl_tint_b = NULL;
cvar_t * _sf_sv_ghl_tint_a = NULL;

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

cvar_t * _sf_sv_force_item_respawntime = NULL;
cvar_t * _sf_sv_airaccel = NULL;
cvar_t * _sf_sv_accel = NULL;
cvar_t * _sf_sv_friction = NULL;
cvar_t * _sf_sv_crouchspeed = NULL;
cvar_t * _sf_sv_runspeed = NULL;
cvar_t * _sf_sv_rampslide_threshold = NULL;

cvar_t * _sf_sv_grenade_impact_explode = NULL;

cvar_t * _sf_sv_q2_slide_fix = NULL;
cvar_t * _sf_sv_q2_style_jump = NULL;
cvar_t * _sf_sv_q2_mode = NULL;


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
	
	_sf_sv_force_sky = orig_Cvar_Get("_sf_sv_force_sky","",0,NULL);

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


	_sf_sv_ghl_tint_a = orig_Cvar_Get("_sf_sv_ghl_tint_a","1.0",0,NULL);
	_sf_sv_ghl_tint_b = orig_Cvar_Get("_sf_sv_ghl_tint_b","1.0",0,NULL);
	_sf_sv_ghl_tint_g = orig_Cvar_Get("_sf_sv_ghl_tint_g","1.0",0,NULL);
	_sf_sv_ghl_tint_r = orig_Cvar_Get("_sf_sv_ghl_tint_r","1.0",0,NULL);

	_sf_sv_fx_mode = orig_Cvar_Get("_sf_sv_fx_mode","0",0,NULL);

	_sf_sv_fx_blood_speed = orig_Cvar_Get("_sf_sv_fx_blood_speed","200",0,NULL);
	_sf_sv_fx_blood_amount = orig_Cvar_Get("_sf_sv_fx_blood_amount","1",0,NULL);
	

	_sf_sv_debug_triggers = orig_Cvar_Get("_sf_sv_debug_triggers","0.0",0,NULL);
	
	_sf_sv_debug_sounds = orig_Cvar_Get("_sf_sv_debug_sounds","0.0",0,NULL);
		
	_sf_sv_bot_focus = orig_Cvar_Get("_sf_sv_bot_focus","-1.0",0,NULL);

	_sf_sv_force_item_respawntime = orig_Cvar_Get("_sf_sv_force_item_respawntime","0",0,NULL);
	
	_sf_sv_accel = orig_Cvar_Get("_sf_sv_accel","10",0,_sf_sv_accel_callback);
	_sf_sv_airaccel = orig_Cvar_Get("_sf_sv_airaccel","1",0,_sf_sv_airaccel_callback);
	_sf_sv_friction = orig_Cvar_Get("_sf_sv_friction","6",0,_sf_sv_friction_callback);
	testcvar = orig_Cvar_Get("testcvar","0",0,NULL);

	_sf_sv_crouchspeed = orig_Cvar_Get("_sf_sv_crouchspeed","75",0,_sf_sv_crouchspeed_callback);
	_sf_sv_runspeed = orig_Cvar_Get("_sf_sv_runspeed","300",0,_sf_sv_runspeed_callback);
	_sf_sv_q2_slide_fix = orig_Cvar_Get("_sf_sv_q2_slide_fix","0",0,NULL);
	_sf_sv_q2_style_jump = orig_Cvar_Get("_sf_sv_q2_style_jump","0",0,NULL);
	_sf_sv_rampslide_threshold = orig_Cvar_Get("_sf_sv_rampslide_threshold","100",0,_sf_sv_rampslide_threshold_callback);

	_sf_sv_grenade_impact_explode = orig_Cvar_Get("_sf_sv_grenade_impact_explode","1",CVAR_LATCH,NULL);
	_sf_sv_q2_mode = orig_Cvar_Get("_sf_sv_q2_mode","0",CVAR_LATCH,NULL);

	_sf_sv_gravity_default = orig_Cvar_Get("_sf_sv_gravity_default","800",0,NULL);
}


void _sf_sv_friction_callback(cvar_t * thecvar) {
	// orig_Com_Printf("You changed me new value is : %f!\n",thecvar->value);

	float * friction = (float*)0x20137608;
	*friction = thecvar->value;
}

void _sf_sv_accel_callback(cvar_t * thecvar) {
	// orig_Com_Printf("You changed me new value is : %f!\n",thecvar->value);

	*pm_accelerate = thecvar->value;
}

void _sf_sv_airaccel_callback(cvar_t * thecvar) {
	// orig_Com_Printf("You changed me new value is : %f!\n",thecvar->value);

	float * airaccel = (float*)0x20137600;

	*airaccel = thecvar->value;
}

void _sf_sv_crouchspeed_callback(cvar_t * thecvar) {
	float * crouchspeed = (float*)0x201375F8;
	*crouchspeed = thecvar->value;
}
void _sf_sv_runspeed_callback(cvar_t * thecvar) {
	float * runspeed = (float*)0x201375F4;
	*runspeed = thecvar->value;
}

void _sf_sv_rampslide_threshold_callback(cvar_t * thecvar) {
	DWORD dwProt = NULL;
	void * addr = 0x201114C0;
	int count = 4;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	float * threshold = (float*)0x201114C0;
	*threshold = thecvar->value;
	VirtualProtect(addr, count, dwProt, new DWORD);
	
}
