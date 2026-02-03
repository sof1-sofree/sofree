#include <windows.h>
#include "sofheader.h"

#include <stdlib.h>
#include <string.h>

// StrStrI
#include <shlwapi.h>

#include <list>

#include "lua_api/generic.h"


//globals
void * gametype_self = 0x5015C4D8;

void * player_export = NULL;

short prev_sidemove[16];
byte prev_buttons[16];


// TODO USE THIS METHOD IN FUTURE.


/*
#define	FOFS(x) (int)&(((edict_t *)0)->x)
#define	STOFS(x) (int)&(((spawn_temp_t *)0)->x)
#define	LLOFS(x) (int)&(((level_locals_t *)0)->x)
#define	CLOFS(x) (int)&(((gclient_t *)0)->x)

*/

void InitFields(void);

void createCommands(void)
{
	InitFields();
	orig_Cmd_AddCommand("test",(void*)test);
	orig_Cmd_AddCommand("sf_sv_sofree_help",(void*)Cmd_SofreeHelp);

	//if sofplus
	// orig_Cmcomd_RemoveCommand("sf_sv_client_swap");
	// orig_Cmd_RemoveCommand("sf_sv_client_red");
	// orig_Cmd_RemoveCommand("sf_sv_client_blue");

	// orig_Cmd_AddCommand("sf_sv_client_blue",(void*)Cmd_Blue_f);
	// orig_Cmd_AddCommand("sf_sv_client_red",(void*)Cmd_Red_f);
	// orig_Cmd_AddCommand("sf_sv_client_swap",(void*)Cmd_Swap_f);

	// orig_Cmd_AddCommand("Cmd_TakePiss",(void*)Cmd_TakePiss);

	orig_Cmd_AddCommand("sf_sv_check_reso",(void*)sf_sv_check_reso);

	orig_Cmd_AddCommand("sf_sv_save_reso",(void*)sf_sv_save_reso);


	orig_Cmd_AddCommand("sf_sv_vector_grow",(void*)sf_sv_vector_grow);
	orig_Cmd_AddCommand("sf_sv_vector_copy",(void*)sf_sv_vector_copy);
	// orig_Cmd_AddCommand("sf_sv_vector_set",(void*)sf_sv_vector_set);
	orig_Cmd_AddCommand("sf_sv_vector_add",(void*)sf_sv_vector_add);
	orig_Cmd_AddCommand("sf_sv_vector_subtract",(void*)sf_sv_vector_subtract);
	orig_Cmd_AddCommand("sf_sv_vector_scale",(void*)sf_sv_vector_scale);
	orig_Cmd_AddCommand("sf_sv_vector_normalize",(void*)sf_sv_vector_normalize);
	orig_Cmd_AddCommand("sf_sv_vector_length",(void*)sf_sv_vector_length);
	orig_Cmd_AddCommand("sf_sv_vector_dotproduct",(void*)sf_sv_vector_dotproduct);

	orig_Cmd_AddCommand("sf_sv_print_cprintf",(void*)sf_sv_print_cprintf);
	orig_Cmd_AddCommand("sf_sv_print_bprintf",(void*)sf_sv_print_bprintf);
	orig_Cmd_AddCommand("sf_sv_print_centerprint",(void*)sf_sv_print_centerprint);
	// failure - does not work
	orig_Cmd_AddCommand("sf_sv_print_welcomeprint",(void*)sf_sv_print_welcomeprint);

	orig_Cmd_AddCommand("sf_sv_print_cinprintf",(void*)sf_sv_print_cinprintf);

	orig_Cmd_AddCommand("sf_sv_draw_string",(void*)sf_sv_draw_string);
	orig_Cmd_AddCommand("sf_sv_draw_string2",(void*)sf_sv_draw_string2);
	orig_Cmd_AddCommand("sf_sv_draw_altstring",(void*)sf_sv_draw_altstring);
	orig_Cmd_AddCommand("sf_sv_draw_clear",(void*)sf_sv_draw_clear);

	orig_Cmd_AddCommand("sf_sv_spackage_register",(void*)sf_sv_spackage_register);
	orig_Cmd_AddCommand("sf_sv_spackage_print_id",(void*)sf_sv_spackage_print_id);
	orig_Cmd_AddCommand("sf_sv_spackage_print_ref",(void*)sf_sv_spackage_print_ref);
	orig_Cmd_AddCommand("sf_sv_spackage_print_obit",(void*)sf_sv_spackage_print_obit);
	orig_Cmd_AddCommand("sf_sv_spackage_print_string",(void*)sf_sv_spackage_print_string);
	orig_Cmd_AddCommand("sf_sv_spackage_list",(void*)sf_sv_spackage_list);
	
	orig_Cmd_AddCommand("Cmd_SP_GetStringText",(void*)Cmd_SP_GetStringText);

	orig_Cmd_AddCommand("sf_sv_sound_remove",(void*)sf_sv_sound_remove);
	orig_Cmd_AddCommand("sf_sv_sound_register",(void*)sf_sv_sound_register);
	orig_Cmd_AddCommand("sf_sv_sound_play_origin",(void*)sf_sv_sound_play_origin);
	orig_Cmd_AddCommand("sf_sv_sound_play_ent",(void*)sf_sv_sound_play_ent);
	orig_Cmd_AddCommand("sf_sv_sound_override",(void*)sf_sv_sound_override);
	orig_Cmd_AddCommand("sf_sv_sound_list",(void*)sf_sv_sound_list);

	orig_Cmd_AddCommand("sf_sv_script_unload",(void*)sf_sv_script_unload);
	orig_Cmd_AddCommand("sf_sv_script_run",(void*)sf_sv_script_run);
	orig_Cmd_AddCommand("sf_sv_script_load",(void*)sf_sv_script_load);


	orig_Cmd_AddCommand("sf_sv_player_gravity",(void*)sf_sv_player_gravity);
	orig_Cmd_AddCommand("sf_sv_player_pos",(void*)sf_sv_player_pos);
	orig_Cmd_AddCommand("sf_sv_player_paint",(void*)sf_sv_player_paint);
	orig_Cmd_AddCommand("sf_sv_player_move",(void*)sf_sv_player_move);
	orig_Cmd_AddCommand("sf_sv_player_effect",(void*)sf_sv_player_effect);
	orig_Cmd_AddCommand("sf_sv_player_ent",(void*)sf_sv_player_ent);
	orig_Cmd_AddCommand("sf_sv_player_collision",(void*)sf_sv_player_collision);
	orig_Cmd_AddCommand("sf_sv_player_anim",(void*)sf_sv_player_anim);
	orig_Cmd_AddCommand("sf_sv_player_allow_attack",(void*)sf_sv_player_allow_attack);
	orig_Cmd_AddCommand("sf_sv_player_allow_altattack",(void*)sf_sv_player_allow_altattack);
	orig_Cmd_AddCommand("sf_sv_player_allow_walk",(void*)sf_sv_player_allow_walk);

	orig_Cmd_AddCommand("sf_sv_player_weap_lock",(void*)sf_sv_player_weap_lock);
	orig_Cmd_AddCommand("sf_sv_player_weap_switch",(void*)sf_sv_player_weap_switch);
	orig_Cmd_AddCommand("sf_sv_player_weap_paint",(void*)sf_sv_player_weap_paint);
	orig_Cmd_AddCommand("sf_sv_player_weap_current",(void*)sf_sv_player_weap_current);

	orig_Cmd_AddCommand("sf_sv_effect_endpos",(void*)sf_sv_effect_endpos);
	orig_Cmd_AddCommand("sf_sv_effect_start",(void*)sf_sv_effect_start);
	orig_Cmd_AddCommand("sf_sv_effect_list",(void*)sf_sv_effect_list);
	orig_Cmd_AddCommand("sf_sv_effect_register",(void*)sf_sv_effect_register);
	
	orig_Cmd_AddCommand("sf_sv_ent_paint",(void*)sf_sv_ent_paint);
	orig_Cmd_AddCommand("sf_sv_ent_vects",(void*)sf_sv_ent_vects);
	orig_Cmd_AddCommand("sf_sv_ent_spawn",(void*)sf_sv_ent_spawn);
	orig_Cmd_AddCommand("sf_sv_ent_remove",(void*)sf_sv_ent_remove);
	orig_Cmd_AddCommand("sf_sv_ent_find",(void*)sf_sv_ent_find);
	orig_Cmd_AddCommand("sf_sv_ent_create",(void*)sf_sv_ent_create);
	orig_Cmd_AddCommand("sf_sv_ent_use",(void*)sf_sv_ent_use);
	orig_Cmd_AddCommand("sf_sv_ent_anim",(void*)sf_sv_ent_anim);
	orig_Cmd_AddCommand("sf_sv_ent_relink",(void*)sf_sv_ent_relink);


	orig_Cmd_AddCommand("sf_sv_ent_model",(void*)sf_sv_ent_model);
	
	orig_Cmd_AddCommand("sf_sv_ent_bolt",(void*)sf_sv_ent_bolt);
	orig_Cmd_AddCommand("sf_sv_ent_tint",(void*)sf_sv_ent_tint);
	
	orig_Cmd_AddCommand("sf_sv_ent_callback",(void*)sf_sv_ent_callback);

	orig_Cmd_AddCommand("sf_sv_ent_field_get",(void*)sf_sv_ent_field_get);
	orig_Cmd_AddCommand("sf_sv_ent_field_set",(void*)sf_sv_ent_field_set);


	orig_Cmd_AddCommand("sf_sv_image_register",(void*)sf_sv_image_register);
	orig_Cmd_AddCommand("sf_sv_image_list",(void*)sf_sv_image_list);

	orig_Cmd_AddCommand("sf_sv_ghoul_scale",(void*)sf_sv_ghoul_scale);
	orig_Cmd_AddCommand("sf_sv_ghoul_translate",(void*)sf_sv_ghoul_translate);
	orig_Cmd_AddCommand("sf_sv_ghoul_register",(void*)sf_sv_ghoul_register);
	orig_Cmd_AddCommand("sf_sv_ghoul_list",(void*)sf_sv_ghoul_list);
	

	orig_Cmd_AddCommand("sf_sv_int_add",(void*)sf_sv_int_add);

	orig_Cmd_AddCommand("sf_sv_mem_read_string",(void*)sf_sv_mem_read_string);
	orig_Cmd_AddCommand("sf_sv_mem_read_short",(void*)sf_sv_mem_read_short);
	orig_Cmd_AddCommand("sf_sv_jmp_at",(void*)sf_sv_jmp_at);
	orig_Cmd_AddCommand("sf_sv_hook_at",(void*)sf_sv_hook_at);
	orig_Cmd_AddCommand("sf_sv_mem_read_int",(void*)sf_sv_mem_read_int);
	orig_Cmd_AddCommand("sf_sv_mem_read_float",(void*)sf_sv_mem_read_float);
	orig_Cmd_AddCommand("sf_sv_mem_read_char",(void*)sf_sv_mem_read_char);

	orig_Cmd_AddCommand("sf_sv_mem_write_char",(void*)sf_sv_mem_write_char);
	orig_Cmd_AddCommand("sf_sv_mem_write_short",(void*)sf_sv_mem_write_short);
	orig_Cmd_AddCommand("sf_sv_mem_write_float",(void*)sf_sv_mem_write_float);
	orig_Cmd_AddCommand("sf_sv_mem_write_int",(void*)sf_sv_mem_write_int);
	orig_Cmd_AddCommand("sf_sv_mem_write_string",(void*)sf_sv_mem_write_string);

	orig_Cmd_AddCommand("sf_sv_configstring_set",(void*)sf_sv_configstring_set);

	orig_Cmd_AddCommand("sf_sv_math_sin",(void*)sf_sv_math_sin);
	orig_Cmd_AddCommand("sf_sv_math_asin",(void*)sf_sv_math_asin);
	orig_Cmd_AddCommand("sf_sv_math_cos",(void*)sf_sv_math_cos);
	orig_Cmd_AddCommand("sf_sv_math_acos",(void*)sf_sv_math_acos);
	orig_Cmd_AddCommand("sf_sv_math_tan",(void*)sf_sv_math_tan);
	orig_Cmd_AddCommand("sf_sv_math_atan",(void*)sf_sv_math_atan);
	orig_Cmd_AddCommand("sf_sv_math_or",(void*)sf_sv_math_or);
	orig_Cmd_AddCommand("sf_sv_math_and",(void*)sf_sv_math_and);
	orig_Cmd_AddCommand("sf_sv_math_not",(void*)sf_sv_math_not);

	#ifdef LUA_ON
	orig_Cmd_AddCommand("sf_sv_lua_func_exec",(void*)sf_sv_lua_func_exec);
	#endif
}

#ifdef LUA_ON
/*
	This is not a LuA func!.
	input string of lua global func name to exec in lua
*/
void sf_sv_lua_func_exec(void)
{
	#ifdef SOFREE_DEBUG
	printf(__FUNCTION__);
	printf("\n");
	#endif
	int args = orig_Cmd_Argc() - 1;
	printf("%i\n",args);
	assert(args==1);
	
	lua_getglobal (L,orig_Cmd_Argv(1));
	if (lua_pcall(L, 0, LUA_MULTRET, 0) != LUA_OK)
		orig_Com_Error(ERR_FATAL,"%s\n",lua_tostring(L, -1));
	lua_settop(L,0);
}
#endif


int reso2d[16][2];
bool show_score[16];

//playerslot xvalue yvalue

//slot id cvar
//request cvar check to client before they have fully entered server

void sf_sv_cmd_list(void)
{
	cmd_function_t * cmd;

	for ( cmd = *(unsigned int*)0x20241840; cmd ; cmd=cmd->next)
		if (strstr (cmd->name,"sf_sv_") == cmd->name)
			orig_Com_Printf("%s\n",cmd->name);
}


void test(void)
{
	orig_Com_Printf(" intermission time is : %f\n",*level_intermissiontime);
}


void randomBoxCode(void)
{
	cvar_t * testbla = orig_Cvar_Get("testbla","",NULL,NULL);
	if ( strlen(testbla->string) ) {
		vec3_t start = {-741,229,136};
		vec3_t tmp;
		// VectorCopy(ent->s.origin,start);
		// orig_Com_Printf("your origin is :  %f %f %f\n",ent->s.origin[0],ent->s.origin[1],ent->s.origin[2]);
		
		int color = 0;
		vec3_t mins = {0,0,0};
		vec3_t maxs = {15,15,15};
		int iter = testbla->value;
		for ( int i = 0 ; i < iter; i++ ) {
			tmp[1] = start[1] + 50 * i;
			for ( int j = 0 ; j < iter; j++ ) {
				tmp[0] = start[0] + 50 * j;
				tmp[2] = start[2];
				// orig_Com_Printf("your origin is :  %f %f %f\n",tmp[0],tmp[1],tmp[2]);
				// orig_Com_Printf("Calling debug_drawbox %f\n",start);
				color = color % 12;
				debug_drawbox2(NULL, tmp ,mins,maxs, color );
				color++;
			}
		}

		start[2] = 200;
		// VectorCopy(ent->s.origin,start);
		// orig_Com_Printf("your origin is :  %f %f %f\n",ent->s.origin[0],ent->s.origin[1],ent->s.origin[2]);
		
		color = 0;
		iter = testbla->value;
		for ( int i = 0 ; i < iter; i++ ) {
			tmp[1] = start[1] + 50 * i;
			for ( int j = 0 ; j < iter; j++ ) {
				tmp[0] = start[0] + 50 * j;
				tmp[2] = start[2];
				// orig_Com_Printf("your origin is :  %f %f %f\n",tmp[0],tmp[1],tmp[2]);
				// orig_Com_Printf("Calling debug_drawbox %f\n",start);
				color = color % 12;
				debug_drawbox(NULL, tmp ,mins,maxs, color );
				color++;
			}
		}
	}
	// edict_t * ent  = get_ent_from_player_slot(0);
	// if ( ent && ent->inuse) {
		
	// }
}

#define HELP_TEXT "\001"
#define HELP_BOLD "\030"
void Cmd_SofreeHelp(void)
{
	orig_Com_Printf(HELP_TEXT
		"  SSSS          f f ff                    !! \n"
		" S       o     f          E E E  E E E    !! \n"
		"SS     o   o   f ff       E      E        !! \n"
		"  SS  o     o  f    r r r E E E  E E E    !! \n"
		"    S  o   o   f    r     E      E           \n"
		"SSSS     o     f    r     E E E  E E E    !! \n"
		"Type sf_sv_sofree_help to see this info again\n"
		"---------------------------------------------\n"

		"---------------------------------------------\n"
		"Use \"["HELP_BOLD"commandname"HELP_TEXT"] "HELP_BOLD"-h\""HELP_TEXT" to display information about a command\n"
		"---------------------------------------------\n"
		"Type sf_sv_sofree_help to see this again.\n"
	);
}

/*
#define	PRINT_LOW			0		// pickup messages
#define	PRINT_MEDIUM		1		// death messages
#define	PRINT_HIGH			2		// critical messages
#define	PRINT_CHAT			3		// chat messages
*/




// ent,x,y,speed,text


















enum FIELD_TYPES {
	TYPE_FLOAT,
	TYPE_INT,
	TYPE_VECTOR,
	TYPE_VECTOR_2D,
	TYPE_STRING,
	TYPE_POINTER,
	TYPE_SHORT,
	TYPE_BYTE,
	TYPE_SHORTVECTOR,
	TYPE_SHORTVECTOR_2D
};
struct A_FIELD {
	FIELD_TYPES type;
	char name[64];
	unsigned int offset;
	unsigned int relOffset; //for gclient pointer
	char info[256];
};

struct A_FIELD all_fields[256];
unsigned int numfields = 0;
void InitFields(void) {

	int index = 0;

	// e.entity_state_t.origin
	strcpy(all_fields[index].name,"origin");
	all_fields[index].type = TYPE_VECTOR;
	all_fields[index].offset = 4;
	strcpy(all_fields[index].info,"[VECTOR] origin is the 3 dimensional location of an entity. Use sf_sv_vector_set to understand this format.");
	index++;

	// e.entity_state_t.angles
	strcpy(all_fields[index].name,"angles");
	all_fields[index].type = TYPE_VECTOR;
	all_fields[index].offset = 16;;
	strcpy(all_fields[index].info,"[VECTOR] angles is the 3 dimensional orientation of an entity. Use sf_sv_vector_set to understand this format.");
	index++;

	// e.max_health
	strcpy(all_fields[index].name,"health_max");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 752;
	strcpy(all_fields[index].info,"[INT] health_max is the maximum health points of an entity.");
	index++;

	// e.health
	strcpy(all_fields[index].name,"health");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 748;
	strcpy(all_fields[index].info,"[INT] health is the current health points of an entity.");
	index++;

	// e.solid
	strcpy(all_fields[index].name,"solid");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 344;
	strcpy(all_fields[index].info,"[INT] solid is collision with other entities.");
	index++;

	// e.model
	strcpy(all_fields[index].name,"model");
	all_fields[index].type = TYPE_STRING;
	all_fields[index].offset = 420;
	strcpy(all_fields[index].info,"[INT] model is a hint to some entities for which ghoulmodel to load.");
	index++;

	// e.classname
	strcpy(all_fields[index].name,"classname");
	all_fields[index].type = TYPE_STRING;
	all_fields[index].offset = 436;
	strcpy(all_fields[index].info,"[STRING] classname determines which entity spawn function gets run, thus which type of ent this it.");
	index++;

	// e.targetname
	strcpy(all_fields[index].name,"targetname");
	all_fields[index].type = TYPE_STRING;
	all_fields[index].offset = 456;
	strcpy(all_fields[index].info,"[STRING] targetname is used as a label for triggers, so they can become targets of other triggers.");
	index++;

	// e.target
	strcpy(all_fields[index].name,"target");
	all_fields[index].type = TYPE_STRING;
	all_fields[index].offset = 452;
	strcpy(all_fields[index].info,"[STRING] target is used to set which entity/trigger you will activate/use.");
	index++;


	// e.Script [CScript*]
	strcpy(all_fields[index].name,"script");
	all_fields[index].type = TYPE_POINTER;
	all_fields[index].offset = 1108;
	strcpy(all_fields[index].info,"[MEMORY_HANDLE] script is an instance to ds script file object.");
	index++;

	// e.inuse
	strcpy(all_fields[index].name,"inuse");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 120;
	strcpy(all_fields[index].info,"[INT] inuse is whether an entity has been initiated and ready to use or not.");
	index++;


	// e.ghoulInst [IGhoulInst*]
	strcpy(all_fields[index].name,"ghoulinst");
	all_fields[index].type = TYPE_POINTER;
	all_fields[index].offset = 356;
	strcpy(all_fields[index].info,"[MEMORY_HANDLE] ghoulinst is a ghoul object pointer.");
	index++;

	
	// e.clipmask
	strcpy(all_fields[index].name,"clipmask");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 348;
	strcpy(all_fields[index].info,"[INT] clipmask determines which surfaces this ent should collide with. 0 dont collide with anything.\nLook in q_shared.h file for numbers to use.");
	index++;

	// e.mins
	strcpy(all_fields[index].name,"mins");
	all_fields[index].type = TYPE_VECTOR;
	all_fields[index].offset = 284;
	strcpy(all_fields[index].info,"[VECTOR] mins is used for collision bounding box creation. It represents the lowest corner of the 3d box.");
	index++;

	// e.maxs
	strcpy(all_fields[index].name,"maxs");
	all_fields[index].type = TYPE_VECTOR;
	all_fields[index].offset = 296;
	strcpy(all_fields[index].info,"[VECTOR] maxs is used for collision bounding box creation. It represents the highest corner of the 3d box.");
	index++;

	// e.movetype
	strcpy(all_fields[index].name,"movetype");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 412;
	strcpy(all_fields[index].info,"[INT] movetype is the mode in which the ent should interact with world and physics.");
	index++;

	//e.entity_state_t.skinnum;
	strcpy(all_fields[index].name,"skinnum");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 44;
	strcpy(all_fields[index].info,"[INT] skinnum is either the slot num if its a player or an alternative texture num for some entities.");
	index++;

	// e.enemy
	strcpy(all_fields[index].name,"enemy");
	all_fields[index].type = TYPE_POINTER;
	all_fields[index].offset = 804;
	strcpy(all_fields[index].info,"[MEMORY_HANDLE] enemy no idea what this is.");
	index++;

	// e.mass
	strcpy(all_fields[index].name,"mass");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 636;
	strcpy(all_fields[index].info,"[INT] mass some number used in physics calculations.");
	index++;

	// e.stopspeed
	strcpy(all_fields[index].name,"stopspeed");
	all_fields[index].type = TYPE_FLOAT;
	all_fields[index].offset = 640;
	strcpy(all_fields[index].info,"[FLOAT] stopspeed some number used in physics calculations.");
	index++;

	// e.friction
	strcpy(all_fields[index].name,"friction");
	all_fields[index].type = TYPE_FLOAT;
	all_fields[index].offset = 644;
	strcpy(all_fields[index].info,"[FLOAT] friction is some number used in physics calculations.");
	index++;

	// e.airresistance
	strcpy(all_fields[index].name,"airresistance");
	all_fields[index].type = TYPE_FLOAT;
	all_fields[index].offset = 652;
	strcpy(all_fields[index].info,"[FLOAT] airresistance is some number used in physics caluclations.");
	index++;

	// e.bouyancy
	strcpy(all_fields[index].name,"bouyancy");
	all_fields[index].type = TYPE_FLOAT;
	all_fields[index].offset = 656;
	strcpy(all_fields[index].info,"[FLOAT] buoyancy is some number used in physics calculations.");
	index++;

	// e.gravity
	strcpy(all_fields[index].name,"gravity");
	all_fields[index].type = TYPE_FLOAT;
	all_fields[index].offset = 648;
	strcpy(all_fields[index].info,"[FLOAT] gravity is how fast the entity falls downwards.");
	index++;

	// e.velocity
	strcpy(all_fields[index].name,"velocity");
	all_fields[index].type = TYPE_VECTOR;
	all_fields[index].offset = 588;
	strcpy(all_fields[index].info,"[VECTOR] velocity is the speed an entity is moving."); 
	index++;

	// e.flags
	strcpy(all_fields[index].name,"flags");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 416;
	strcpy(all_fields[index].info,"[INT] flags status information for this ent, not sure.");
	index++;

	// e.nextthink
	strcpy(all_fields[index].name,"next_think");
	all_fields[index].type = TYPE_FLOAT;
	all_fields[index].offset = 692;
	strcpy(all_fields[index].info,"[FLOAT] next_think when the entitys think function should run next.");
	index++;


	// e.soundName
	strcpy(all_fields[index].name,"soundname");
	all_fields[index].type = TYPE_STRING;
	all_fields[index].offset = 488;
	strcpy(all_fields[index].info,"[STRING] soundname a variable used for some events, not sure.");
	index++;

	// e.pos1
	strcpy(all_fields[index].name,"pos1");
	all_fields[index].type = TYPE_VECTOR;
	all_fields[index].offset = 564;
	strcpy(all_fields[index].info,"[VECTOR] pos1 is an extra paramter used for weird things, not sure.");
	index++;

	/*
	END OF BASIC ENT FIELDS
	*/

	//.gclient->player_state_t.gun
	strcpy(all_fields[index].name,"gunghoulinst");
	all_fields[index].type = TYPE_POINTER;
	all_fields[index].offset = 108;
	all_fields[index].relOffset = 116;
	strcpy(all_fields[index].info,"[MEMORY_HANDLE] gunghoulinst is the ghoul object pointer for the players gun.");
	index++;

	//.gclient->player_state_t.gun
	strcpy(all_fields[index].name,"viewangles");
	all_fields[index].type = TYPE_VECTOR_2D;
	all_fields[index].offset = 28;
	all_fields[index].relOffset = 116;
	strcpy(all_fields[index].info,"[VECTOR_2D] viewangles is the players viewing angle. Use sf_sv_vector_set to understand this format.");
	index++;

	// gclient_t->player_state_t.pmove_state_t.delta_angles[3]
	strcpy(all_fields[index].name,"delta_angles");
	all_fields[index].type = TYPE_SHORTVECTOR_2D;
	all_fields[index].offset = 20;
	all_fields[index].relOffset = 116;
	strcpy(all_fields[index].info,"[SHORTVECTOR_2D] delta_angles _1 _2 Vector-like but not float. These are relative to spawn angle.");
	index++;

	// gclient_t->player_state_t.pmove_state_t.gravity

	// REMOVED because complicated : Found other method with api.

	// strcpy(all_fields[index].name,"client_gravity");
	// all_fields[index].type = TYPE_SHORT;
	// all_fields[index].offset = 18;
	// all_fields[index].relOffset = 116;
	// strcpy(all_fields[index].info,"[SHORT] client_gravity is how fast the player falls to the ground.");
	// index++;

	// gclient_t->player_state_t.pmove_state_t.movescale
	strcpy(all_fields[index].name,"movescale");
	all_fields[index].type = TYPE_FLOAT;
	all_fields[index].offset = GCLIENT_MOVESCALE; //other movescale is 26
	all_fields[index].relOffset = 116;
	strcpy(all_fields[index].info,"[FLOAT] movescale is how fast a player moves. 0.0 -> 1.0");
	index++;

	// gclient_t->client_respawn_t.cmd_angles[3]
	strcpy(all_fields[index].name,"respawn_angles");
	all_fields[index].type = TYPE_VECTOR_2D;
	all_fields[index].offset = 780;
	all_fields[index].relOffset = 116;
	strcpy(all_fields[index].info,"[VECTOR_2D] respawn_angles are facing direction at spawn.");
	index++;

	// gclient_t->client_respawn_t.score
	strcpy(all_fields[index].name,"score");
	all_fields[index].type = TYPE_INT;
	all_fields[index].offset = 776;
	all_fields[index].relOffset = 116;
	strcpy(all_fields[index].info,"[INT] score is the points the player has.");
	index++;

	numfields = index;

}

// TODO: spawnflags
// scale ?
void sf_sv_ent_field_set(void)
{
	int i=0;
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Set a specific field for a specified entity\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> fieldname\n"
			"arg3 -> value\n"
		);


		for (i=0; i< numfields; i++ ) {
			orig_Com_Printf("%s ",all_fields[i].name);
			if ( !(i % 3 ) ) orig_Com_Printf("\n");
		}
		orig_Com_Printf("\n");
		orig_Com_Printf("Get help on specific field with sf_sv_ent_field_set fieldname\n");
		return;
	}
	if ( c == 1 ) {
		for ( i=0; i< numfields; i++ ) {
			if ( !strcmp(orig_Cmd_Argv(1),all_fields[i].name) ) {
				// match
				orig_Com_Printf("%s\n",all_fields[i].info);
				return;
			}
		}
		orig_Com_Printf("Not a known field\n");
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_ent_field_set -h\n");
		orig_Com_Printf("sf_sv_ent_field_set fieldname -h\n");
		return;
	}

	edict_t * ent = (edict_t*)atoi(orig_Cmd_Argv(1));
	char * field = orig_Cmd_Argv(2);
	char * value = orig_Cmd_Argv(3);
	void * real_field = NULL;

	for ( i = 0; i < numfields;i++ ) {
		if ( !strcmp(all_fields[i].name,field) ) {
			if ( all_fields[i].relOffset > 0 ) {
				real_field = *(unsigned int*)((unsigned int)ent + all_fields[i].relOffset);
				real_field = (void*)((unsigned int)real_field + all_fields[i].offset);
			} else {
				real_field = (void*)((unsigned int)ent + all_fields[i].offset);
			}
			char newname[64];
			cvar_t * one,*two,*three;
			vec3_t in_vect;
			switch( all_fields[i].type) {
				case TYPE_FLOAT:
					*(float*)real_field = atof(value);
				break;
				case TYPE_INT:
					*(int*)real_field = atoi(value);
				break;
				case TYPE_SHORT:
					*(short*)real_field = atoi(value);
				break;
				case TYPE_SHORTVECTOR:
					readCvarAsVector(value,in_vect);
					*(short*)(real_field)= in_vect[0];
					*(short*)(real_field + 2) = in_vect[1];
					*(short*)(real_field + 4)= in_vect[2];
				break;
				case TYPE_SHORTVECTOR_2D:
					readCvarAsVector(value,in_vect);
					*(short*)(real_field)= in_vect[0];
					*(short*)(real_field + 2) = in_vect[1];
				break;
				case TYPE_STRING:
					*(char**)real_field = orig_CopyString(value);
				break;
				case TYPE_POINTER:
					*(unsigned int*)real_field = atoi(value);
				break;
				case TYPE_BYTE:
					*(unsigned char*)real_field = atoi(value);
				break;
				case TYPE_VECTOR:
					readCvarAsVector(value,in_vect);
					*(float*)(real_field)=in_vect[0];
					*(float*)(real_field + 4)=in_vect[1];
					*(float*)(real_field + 8)=in_vect[2];
				break;
				case TYPE_VECTOR_2D:
					readCvarAsVector(value,in_vect);
					*(float*)(real_field)=in_vect[0];
					*(float*)(real_field + 4)=in_vect[1];
				break;
				default:
				break;
			}
			return;
		}
	}
	orig_Com_Printf("Not a known field\n");
	
}


void sf_sv_ent_field_get(void)
{
	int i = 0;
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Get a specific field for a specified entity\n"
			"----------------------------\n"
			"arg1 -> outcvar\n"
			"arg2 -> enthandle\n"
			"arg3 -> fieldname\n"
		);


		for (i=0; i< numfields; i++ ) {
			orig_Com_Printf("%s ",all_fields[i].name);
			if ( !(i % 3 ) ) orig_Com_Printf("\n");
		}
		orig_Com_Printf("\n");
		orig_Com_Printf("Get help on specific field with sf_sv_ent_field_get fieldname -h\n");
		return;
	}
	if ( c == 1 ) {
		for (i=0; i< numfields; i++ ) {
			if ( !strcmp(orig_Cmd_Argv(1),all_fields[i].name) ) {
				// match
				orig_Com_Printf("%s\n",all_fields[i].info);
				break;
			}
		}

		orig_Com_Printf("Not a known field\n");
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_ent_field_get -h\n");
		orig_Com_Printf("sf_sv_ent_field_get fieldname -h\n");
		return;
	}
	edict_t * ent = (edict_t*)atoi(orig_Cmd_Argv(2));
	char * field = orig_Cmd_Argv(3);
	char * outcvar = orig_Cmd_Argv(1);
	void * real_field = NULL;

	for ( i = 0; i < numfields;i++ ) {
		if ( !strcmp(all_fields[i].name,field) ) {
			if ( all_fields[i].relOffset > 0 ) {
				real_field = *(unsigned int*)((unsigned int)ent + all_fields[i].relOffset);
				real_field = (void*)((unsigned int)real_field + all_fields[i].offset);
			} else {
				real_field = (void*)((unsigned int)ent + all_fields[i].offset);
			}
			cvar_t * out_cvar = orig_Cvar_Get(outcvar,"",0,NULL);
			char newname[64];
			cvar_t * one,*two,*three;
			float * in_vec;
			switch( all_fields[i].type) {
				case TYPE_FLOAT:
					setCvarFloat(out_cvar,*(float*)real_field);
				break;
				case TYPE_INT:
					setCvarInt(out_cvar,*(int*)real_field);
				break;
				case TYPE_SHORT:
					setCvarInt(out_cvar,*(short*)real_field);
				break;
				case TYPE_SHORTVECTOR:
					
					sprintf(newname,"%s%s",outcvar,"_1");
					one = orig_Cvar_Get(newname,"",0,NULL);
					sprintf(newname,"%s%s",outcvar,"_2");
					two = orig_Cvar_Get(newname,"",0,NULL);
					sprintf(newname,"%s%s",outcvar,"_3");
					three = orig_Cvar_Get(newname,"",0,NULL);

					setCvarInt(one,*(short*)real_field);
					setCvarInt(two,*(short*)(real_field+2));
					setCvarInt(three,*(short*)(real_field+4));
				break;
				case TYPE_SHORTVECTOR_2D:
					
					sprintf(newname,"%s%s",outcvar,"_1");
					one = orig_Cvar_Get(newname,"",0,NULL);
					sprintf(newname,"%s%s",outcvar,"_2");
					two = orig_Cvar_Get(newname,"",0,NULL);

					setCvarInt(one,*(short*)real_field);
					setCvarInt(two,*(short*)(real_field+2));
				break;
				case TYPE_STRING:
					setCvarString(out_cvar,*(char**)real_field);
				break;
				case TYPE_POINTER:
					setCvarInt(out_cvar,*(int*)real_field);
				break;
				case TYPE_BYTE:
					setCvarByte(out_cvar,*(unsigned char*)real_field);
				break;
				case TYPE_VECTOR:
					// orig_Com_Printf("Do we reach here?\n");
					// assume its a cvar with _1 _2 _3
					in_vec = real_field;
					writeCvarAsVector(in_vec,outcvar);
				break;
				case TYPE_VECTOR_2D:
					sprintf(newname,"%s%s",outcvar,"_1");
					one = orig_Cvar_Get(newname,"",0,NULL);
					sprintf(newname,"%s%s",outcvar,"_2");
					two = orig_Cvar_Get(newname,"",0,NULL);

					setCvarFloat(one,*(float*)real_field);
					setCvarFloat(two,*(float*)real_field+4);
				break;
				// default:
				// break;
			}
			return;
		}
	}
	orig_Com_Printf("Not a known field\n");

}

// TODO : Convert fieldnames into offsets for people easier

/*
	AVOIDS USING FLOATS
*/

void sf_sv_int_add(void)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"A simple math addition function, strictly for integers\n"
			"eg. sofree_int_add ~meow 6\n"
			"----------------------------\n"
			"arg1 -> cvarname of cvar to do the addition on\n"
			"arg2 -> integer value to apply addition with\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_int_add -h\n");
		return;
	}

	//name of cvar to save output in
	// if does not exist error
	cvar_t * out_cvar = findCvar(orig_Cmd_Argv(1));
	if (!out_cvar) {
		orig_Com_Printf("Error in sf_sv_int_add, supplied cvar does not exist\n");
		return;
	}

	/*
		IMPORTANT: DONT USE FLOATS
		USE STRING OR DOUBLE
		BECAUSE OF PRECISION LOSS!!!
	*/
	unsigned int value = atoi(out_cvar->string) + atoi(orig_Cmd_Argv(2));
	setCvarUnsignedInt(out_cvar,value);
}

void Cmd_Swap_f(void)
{
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		if ( !strcmp(orig_Cmd_Argv(1),"*")) {
			for ( int i = 0; i < 16; i++ ) {
				unsigned int team = *(unsigned int*)(*(unsigned int*)GCLIENT_BASE + (i * SIZE_OF_GCLIENT) + GCLIENT_TEAM);
				if ( team == 2 ) {
					goBlue(i);
				} else if ( team == 1 ) {
					goRed(i);
				}
			}
		} else {
			int slot = atoi(orig_Cmd_Argv(1));

			if ( slot >=0 && slot < 16 )
			{
				unsigned int team = *(unsigned int*)(*(unsigned int*)GCLIENT_BASE + (slot * SIZE_OF_GCLIENT) + GCLIENT_TEAM);
				if ( team == 2 ) {
					goBlue(slot);
				} else if ( team == 1 ) {
					goRed(slot);
				}
			}
		}
	}
}

void Cmd_Blue_f(void)
{
	
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		if ( !strcmp(orig_Cmd_Argv(1),"*")) {
			for ( int i = 0; i < 16; i++ ) {
				goBlue(i);
			}
		} else {
			int slot = atoi(orig_Cmd_Argv(1));

			if ( slot >=0 && slot < 16 )
			{
				goBlue(slot);
			}
		}
		
	}
	
}

void Cmd_Red_f(void)
{
	
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		if ( !strcmp(orig_Cmd_Argv(1),"*")) {
			for ( int i = 0; i < 16; i++ ) {
				goRed(i);
			}
		} else {

			int slot = atoi(orig_Cmd_Argv(1));
			if ( slot >=0 && slot < 16 )
			{
				goRed(slot);
			}
		}
	}
	
	
}


void goRed(int who) {
	// orig_Com_Printf("yo momma's team is %i\n",*(unsigned int*)(*(unsigned int*)0x5015D6C4 + (slot * 0x600) + 0x324));
	// *(unsigned int*)(*(unsigned int*)0x5015D6C4 + (slot * 0x600) + 0x324) = 2;
	void * client_t = (void*)((*(unsigned int*)0x20396EEC) + ( who * 0xd2ac));
	char * cl_userinfo = (char*)((unsigned int)client_t + 0x4);
	orig_Info_SetValueForKey(cl_userinfo,"team_red_blue","1");
	orig_SV_UserinfoChanged(client_t);
	my_SV_UserinfoChanged(client_t);
}

void goBlue(int who) {
	void * client_t = (void*)((*(unsigned int*)0x20396EEC) + ( who * 0xd2ac));
	char * cl_userinfo = (char*)((unsigned int)client_t + 0x4);
	orig_Info_SetValueForKey(cl_userinfo,"team_red_blue","0");
	orig_SV_UserinfoChanged(client_t);
	my_SV_UserinfoChanged(client_t);
}

//mygimme [classname] [x] [y] [z] [pitch] [yaw]

/*
// Needs to be called any time an entity changes origin, mins, maxs,
// or solid.  Automatically unlinks if needed.
// sets ent->v.absmin and ent->v.absmax
// sets ent->leafnums[] for pvs determination even if the entity
// is not solid


G_TouchTriggers handles players triggering SOLID_TRIGGERS

import.BoxEdicts = SV_AreaEdicts;

This function is super important as it builds a list of entities who are likely to intersect
in a given area by using their (absmin absmax) compared to teh area.
area is absmin of the moving entity.. so it does compare absmin values after all..
*/

