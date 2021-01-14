#include <windows.h>
#include "sofheader.h"

#include <stdlib.h>
#include <string.h>

// StrStrI
#include <shlwapi.h>

#include <list>


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
/*
https://lucasklassmann.com/blog/2019-02-02-how-to-embeddeding-lua-in-c/

The loadfile returns a 'chunk' onto the stack.
You have to 'call' that chunk.. then all of the global names it defines will be created.
lua_pcall is popping its arguments off stack, if you eg pushed a function to it.
I'm clearing stack often with lua_settop(L,0).
You can find lua types in lua.h.  You can check for nil return, if the global name does not exist.
*/
void createCommands(void)
{

	L = luaL_newstate();
	luaL_openlibs(L);


	InitFields();

	lua_pushcfunction(L,sf_sv_console_write);
	lua_setglobal(L, "sf_sv_console_write");

	lua_pushcfunction(L,sf_sv_ent_create);
	lua_setglobal(L, "sf_sv_ent_create");

	lua_pushcfunction(L,sf_sv_ent_field_set);
	lua_setglobal(L, "sf_sv_ent_field_set");

	lua_pushcfunction(L,sf_sv_ent_field_get);
	lua_setglobal(L, "sf_sv_ent_field_get");

	lua_pushcfunction(L,sf_sv_ent_spawn);
	lua_setglobal(L, "sf_sv_ent_spawn");

	lua_pushcfunction(L,sf_sv_player_pos);
	lua_setglobal(L, "sf_sv_player_pos");

	// redundant cos of table copy of lua
	// lua_pushcfunction(L,sf_sv_vector_copy);
	// lua_setglobal(L, "sf_sv_vector_copy");

	lua_pushcfunction(L,sf_sv_vector_set);
	lua_setglobal(L,"sf_sv_vector_set");


	char **file_list = NULL;
	int file_list_len;
	ListDirectoryContents("user-server\\sofplus\\addons\\lua",&file_list,&file_list_len);

	orig_Com_Printf("There are %i entries\n",file_list_len);

	/*
		Run all .lua scripts in lua directory.
	*/
	for ( int i=0; i < file_list_len;i++)
	{
		char * filepath = *(file_list+i);
		orig_Com_Printf("loading %s\n",filepath);

		// LUA_MULTRET
		if (luaL_loadfile(L, filepath) == LUA_OK) {
			// state,Nargs,Nrets,messageHandler
			if (lua_pcall(L, 0, LUA_MULTRET, 0) == LUA_OK) {
				// if it returned anything to us.
				lua_settop(L,0);
				// lua_pop(L, lua_gettop(L));
			}
		} else {
			orig_Com_Error(ERR_FATAL,"%s\n",lua_tostring(L, -1));
			lua_settop(L,0);
		}
	}

	

	
	/*
	// lua_pop(LUASTATE,1);
	orig_Com_Printf("%i items on stack before getglobal\n",lua_gettop(L));
	orig_Com_Printf("type is %i\n",lua_getglobal (L,"hokuspokuss"));
	orig_Com_Printf("%i items on stack after getglobal\n",lua_gettop(L));
	if (lua_gettop(L) > 0 && lua_isfunction(L, -1)) {
		orig_Com_Printf("%i items on stack before call\n",lua_gettop(L));
		if (lua_pcall(L, 0, LUA_MULTRET, 0) == LUA_OK) {
			orig_Com_Printf("%i items on stack after call\n",lua_gettop(L));
			// clear returns
			lua_settop(L,0);
		}
	}
	
	*/
	

	// orig_Com_Printf("stack is after  : %i\n",lua_gettop(LUASTATE));


	orig_Cmd_AddCommand("sf_sv_sofree_help",(void*)Cmd_SofreeHelp);


	orig_Cmd_AddCommand("sf_sv_lua_func_exec",(void*)sf_sv_lua_func_exec);

	orig_Cmd_AddCommand("sf_sv_cmd_list",(void*)sf_sv_cmd_list);

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
	orig_Cmd_AddCommand("sf_sv_vector_set",(void*)sf_sv_vector_set);
	// orig_Cmd_AddCommand("sf_sv_vector_add",(void*)sf_sv_vector_add);
	// orig_Cmd_AddCommand("sf_sv_vector_subtract",(void*)sf_sv_vector_subtract);
	// orig_Cmd_AddCommand("sf_sv_vector_scale",(void*)sf_sv_vector_scale);
	// orig_Cmd_AddCommand("sf_sv_vector_normalize",(void*)sf_sv_vector_normalize);
	// orig_Cmd_AddCommand("sf_sv_vector_length",(void*)sf_sv_vector_length);
	// orig_Cmd_AddCommand("sf_sv_vector_dotproduct",(void*)sf_sv_vector_dotproduct);

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

}


void sf_sv_lua_func_exec(void)
{

	lua_getglobal (L,orig_Cmd_Argv(1));
	if (lua_gettop(L) > 0 && lua_isfunction(L, -1)) {
	 	if (lua_pcall(L, 0, LUA_MULTRET, 0) == LUA_OK) {
				// clear returns
			lua_settop(L,0);
		}
	}
	lua_settop(L,0);
}

__attribute__((always_inline))int LuaPopInt()
{
	return (int)round(lua_tonumber(L,-1));
}

int sf_sv_console_write(lua_State *L)
{
	int n = lua_gettop(L);
	char * str = lua_tostring(L,-1);
	orig_Cbuf_AddText(str);
}


int sf_sv_configstring_set(lua_State * L)
{
	int index = LuaPopInt();
		// index string
	orig_PF_Configstring(index,lua_tostring(L,-1));
}

int reso2d[16][2];
bool show_score[16];

//playerslot xvalue yvalue
int sf_sv_save_reso(lua_State * L)
{
	/*
		3 arguments
		playerslot Xreso Yreso
	*/
	
	int y = LuaPopInt();
	int x = LuaPopInt();
	int slot = LuaPopInt();

	reso2d[slot][1] = x;
	reso2d[slot][0] = y;
	
}

//slot id cvar
//request cvar check to client before they have fully entered server
int sf_sv_check_reso(lua_State * L)
{
	/*
		3 arguments
		playerslot Id cvarname
	*/

	char * cvar = lua_tostring(L,-1);
	char * cId= lua_tostring(L,-1);
	int slot = LuaPopInt();

	char mycvarcheck[256];
	//id cvar val
	sprintf(mycvarcheck,"cmd ,check %s %s #%s\n",cId,cvar,cvar);
	//cmd .check id cvar val
	orig_PF_WriteByte((unsigned char)STUFFTEXT);
	orig_PF_WriteString(mycvarcheck);
	edict_t * ent = get_ent_from_player_slot(slot);
	orig_PF_Unicast(ent,true);
}

int sf_sv_cmd_list(lua_State * L)
{
	cmd_function_t * cmd;

	for ( cmd = *(unsigned int*)0x20241840; cmd ; cmd=cmd->next)
		if (strstr (cmd->name,"sf_sv_") == cmd->name)
			orig_Com_Printf("%s\n",cmd->name);
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
int sf_sv_print_cprintf(lua_State * L)
{
	edict_t * ent = get_ent_from_player_slot(LuaPopInt());
	orig_cprintf(ent,PRINT_HIGH,lua_tostring(L,-1));
}

int sf_sv_print_bprintf(lua_State * L)
{
	orig_bprintf(PRINT_HIGH,lua_tostring(L,-1));
}

int sf_sv_print_centerprint(lua_State * L)
{
	edict_t * ent = get_ent_from_player_slot(LuaPopInt());
	orig_centerprintf(ent,lua_tostring(L,-1));
}

int sf_sv_print_welcomeprint(lua_State * L)
{
	edict_t * ent = get_ent_from_player_slot(LuaPopInt());
	orig_welcomeprint(ent);
}

// ent,x,y,speed,text
int sf_sv_print_cinprintf(lua_State * L)
{
	char * text = lua_tostring(L,-1);
	int speed = LuaPopInt();
	int y = LuaPopInt();
	int x = LuaPopInt();
	int slot = LuaPopInt();

	edict_t * ent = get_ent_from_player_slot(slot);
	orig_cinprintf(ent,x,y,speed,text);
}

//sf_sv_console_write

extern "C" void simpletest(lua_State * L) {
	orig_Com_Printf("There is %i args passed\n",lua_gettop(L));
	// char ** file_list;
	// int file_list_len;
	// ListDirectoryContents("user-server\\sofplus\\addons\\lua",file_list,&file_list_len);

	// orig_Com_Printf("There are %i entries\n",file_list_len);

	// for ( int i=0; i < file_list_len;i++)
	// {
	// 	char * filepath = *(file_list+i);
	// 	orig_Com_Printf("file path : %s\n",filepath);
	// }
}
extern "C" int sf_sv_player_ent(lua_State * L) {
	int c = lua_gettop(L);
	// if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Returns an entity from a player slot number\n"
	// 		"Returned value is 0 for an ent that is not inuse\n"
	// 		"----------------------------\n"
	// 		"arg1 -> cvarname for resulting cvar\n"
	// 		"arg2 -> slot number\n"
	// 	);
	// 	return;
	// }
	// if ( c != 2 ) {
	// 	orig_Com_Printf("sf_sv_player_ent -h\n");
	// 	return;
	// }
	
	int slot = LuaPopInt();
	edict_t * ent = get_ent_from_player_slot(slot);
	
	if ( ent && ent->inuse ) {
		char comp[32];
		_itoa((unsigned int)ent,comp,10);
		// setCvarUnsignedInt(out,ent);
		lua_pushstring(L,comp);

					
	} else {
		// setCvarUnsignedInt(out,0);
		lua_pushstring(L,"");
	}
	return 1;
}


int sf_sv_vector_set(lua_State * L) {
	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Create a vector\n"
	// 		"----------------------------\n"
	// 		"arg1 -> cvarname for output vector\n"
	// 		"arg2 -> first dimension value of vector to set\n"
	// 		"arg3 -> second dimension value of vector to set\n"
	// 		"arg4 -> third dimension value of vector to set\n"
	// 	);
	// 	return;
	// }
	// if ( c != 4 ) {
	// 	orig_Com_Printf("sf_sv_vector_set -h\n");
	// 	return;
	// }

	
	lua_newtable(L);

	lua_pushstring(L,"x");
	lua_pushnumber(L,lua_tonumber(L,1));
	lua_settable(L,-3);
	
	lua_pushstring(L,"z");
	lua_pushnumber(L,lua_tonumber(L,2));
	lua_settable(L,-3);
	
	lua_pushstring(L,"y");
	lua_pushnumber(L,lua_tonumber(L,3));
	lua_settable(L,-3);
	
	return 1;
}

int sf_sv_vector_copy(lua_State * L) {
	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Copy a vector\n"
	// 		"----------------------------\n"
	// 		"arg1 -> cvarname for output vector\n"
	// 		"arg2 -> cvarname vector to copy\n"
	// 	);
	// 	return;
	// }
	// if ( c != 2 ) {
	// 	orig_Com_Printf("sf_sv_vector_copy -h\n");
	// 	return;
	// }

	lua_Number z = lua_tonumber(L,3);
	lua_Number y = lua_tonumber(L,2);
	lua_Number x = lua_tonumber(L,1);

	lua_pushnumber(L,x);
	lua_pushnumber(L,y);
	lua_pushnumber(L,z);
	return 3;
}

int sf_sv_vector_add(lua_State * L) {
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Add 2 vectors: vectorA + vectorB\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname vectorA\n"
			"arg3 -> cvarname vectorB\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_vector_add -h\n");
		return;
	}
	char * outname = orig_Cmd_Argv(1);
	char * vec1name = orig_Cmd_Argv(2);
	char * vec2name = orig_Cmd_Argv(2);


	vec3_t vecA,vecB,vecC;
	// read the INCVAR and write to VECT
	readCvarAsVector(vec1name,vecA);
	readCvarAsVector(vec2name,vecB);

	VectorAdd(vecA,vecB,vecC);

	// read the VECT and write to CVAR
	writeCvarAsVector(vecC,outname);

}

int sf_sv_vector_subtract(lua_State * L) {
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Subtract 2 vectors: vectorA - vectorB\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname vectorA\n"
			"arg3 -> cvarname vectorB\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_vector_subtract -h\n");
		return;
	}
	char * outname = orig_Cmd_Argv(1);
	char * vec1name = orig_Cmd_Argv(2);
	char * vec2name = orig_Cmd_Argv(3);


	vec3_t vecA,vecB,vecC;
	// read the INCVAR and write to VECT
	readCvarAsVector(vec1name,vecA);
	readCvarAsVector(vec2name,vecB);

	VectorSubtract(vecA,vecB,vecC);

	// read the VECT and write to CVAR
	writeCvarAsVector(vecC,outname);
}

int sf_sv_vector_scale(lua_State * L) {
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Scale a vector by a number\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname for input vector\n"
			"arg3 -> scale Factor\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_vector_scale -h\n");
		return;
	}
	char * outname = orig_Cmd_Argv(1);
	char * vec1name = orig_Cmd_Argv(2);
	char * scalename = orig_Cmd_Argv(3);


	vec3_t vecA,vecC;
	// read the INCVAR and write to VECT
	readCvarAsVector(vec1name,vecA);
	float scale = atof(scalename);

	VectorScale(vecA,scale,vecC);

	// read the VECT and write to CVAR
	writeCvarAsVector(vecC,outname);

}

int sf_sv_vector_normalize(lua_State * L) {
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Normalize a vector\n"
			"Useful for making a vector become a directional vector\n"
			"Compresses values to be between 0.0 and 1.0\n"
			"----------------------------\n"
			"arg1 -> cvarname for output vector\n"
			"arg2 -> cvarname for input Vector\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_vector_normalize -h\n");
		return;
	}
	char * outname = orig_Cmd_Argv(1);
	char * vec1name = orig_Cmd_Argv(2);


	vec3_t vecA;
	// read the INCVAR and write to VECT
	readCvarAsVector(vec1name,vecA);

	VectorNormalize(vecA);

	// read the VECT and write to CVAR
	writeCvarAsVector(vecA,outname);

}

int sf_sv_vector_length(lua_State * L) {
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Get the length of a vector\n"
			"----------------------------\n"
			"arg1 -> cvarname for output length\n"
			"arg2 -> cvarname for input Vector\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_vector_length -h\n");
		return;
	}
	char * outname = orig_Cmd_Argv(1);
	char * vec1name = orig_Cmd_Argv(2);


	vec3_t vecA;

	float length;
	// read the INCVAR and write to VECT
	readCvarAsVector(vec1name,vecA);

	length = VectorLength(vecA);

	
	setCvarFloat(orig_Cvar_Get(outname,"",0,NULL),length);
}

int sf_sv_vector_dotproduct(lua_State * L) {
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Calculates the dot product of 2 vectors\n"
			"vectorA . vectorB\n"
			"----------------------------\n"
			"arg1 -> cvarname for output length\n"
			"arg2 -> cvarname for input vectorA\n"
			"arg3 -> cvarname for input vectorB\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_vector_dotproduct -h\n");
		return;
	}
	char * outname = orig_Cmd_Argv(1);
	char * vec1name = orig_Cmd_Argv(2);
	char * vec2name = orig_Cmd_Argv(3);

	vec3_t vecA,vecB;

	float length;
	// read the INCVAR and write to VECT
	readCvarAsVector(vec1name,vecA);
	readCvarAsVector(vec1name,vecB);

	length = DotProduct(vecA,vecB);

	setCvarFloat(orig_Cvar_Get(outname,"",0,NULL),length);
}





int sf_sv_vector_grow(lua_State * L) {
	int c = orig_Cmd_Argc() - 1;
	int n = lua_gettop(L);    /* number of arguments */
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Scales a vector with formula\n"
			"newVector = VectorA + Multiplier*VectorB"
			"----------------------------\n"
			"arg1 -> cvarname prefix for resulting cvar\n"
			"arg2 -> VectorA\n"
			"arg3 -> Multiplier\n"
			"arg4 -> VectorB\n"
		);
		return;
	}
	if ( c != 4 ) {
		orig_Com_Printf("sf_sv_vector_grow -h\n");
		return;
	}
	char * out = orig_Cmd_Argv(1);
	char * vectA = orig_Cmd_Argv(2);
	float multiplier = atof(orig_Cmd_Argv(3));
	char * vectB = orig_Cmd_Argv(4);

	cvar_t * out_cvar = orig_Cvar_Get(out,"",0,NULL);

	vec3_t in_vecA;
	readCvarAsVector(vectA,in_vecA);

	vec3_t in_vecB;
	readCvarAsVector(vectB,in_vecB);

	vec3_t vout;
	VectorMA(in_vecA,multiplier,in_vecB,vout);
	writeCvarAsVector(vout,out);
}

int sf_sv_ent_vects(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Grabs forward right up vectors of ent\n"
			"----------------------------\n"
			"arg1 -> cvarname prefix for resulting cvars\n"
			"arg2 -> ent\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}
	char * cvarprefix = orig_Cmd_Argv(1);
	edict_t * ent = (edict_t*)atoi(orig_Cmd_Argv(2));


	vec3_t fwd_vec,side_vec,up_vec;
	orig_AngleVectors(ent->s.angles,fwd_vec,side_vec,up_vec);
	char newname[64];
	sprintf(newname,"%s%s",cvarprefix,"_fwd");
	writeCvarAsVector(fwd_vec,newname);
	sprintf(newname,"%s%s",cvarprefix,"_side");
	writeCvarAsVector(side_vec,newname);
	sprintf(newname,"%s%s",cvarprefix,"_up");
	writeCvarAsVector(up_vec,newname);

}

int sf_sv_ent_use(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Execute the 'use' callback of an entity\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_ent_use -h\n");
		return;
	}
	edict_t * ent = (edict_t*)atoi(orig_Cmd_Argv(1));

	if ( ent->use ) {
		ent->use(ent,NULL,NULL);
	}
}

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
int sf_sv_ent_field_set(lua_State * L)
{
	int i=0;
	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Set a specific field for a specified entity\n"
	// 		"----------------------------\n"
	// 		"arg1 -> enthandle\n"
	// 		"arg2 -> fieldname\n"
	// 		"arg3 -> value\n"
	// 	);


	// 	for (i=0; i< numfields; i++ ) {
	// 		orig_Com_Printf("%s ",all_fields[i].name);
	// 		if ( !(i % 3 ) ) orig_Com_Printf("\n");
	// 	}
	// 	orig_Com_Printf("\n");
	// 	orig_Com_Printf("Get help on specific field with sf_sv_ent_field_set fieldname\n");
	// 	return;
	// }
	// if ( c == 1 ) {
	// 	for ( i=0; i< numfields; i++ ) {
	// 		if ( !strcmp(orig_Cmd_Argv(1),all_fields[i].name) ) {
	// 			// match
	// 			orig_Com_Printf("%s\n",all_fields[i].info);
	// 			return;
	// 		}
	// 	}
	// 	orig_Com_Printf("Not a known field\n");
	// 	return;
	// }
	// if ( c != 3 ) {
	// 	orig_Com_Printf("sf_sv_ent_field_set -h\n");
	// 	orig_Com_Printf("sf_sv_ent_field_set fieldname -h\n");
	// 	return;
	// }
	char * value;
	// if ( lua_isstring(L,3) )
	value = lua_tostring(L,3);	
	char * field = lua_tostring(L,2);
	edict_t * ent = lua_tointeger(L,1);

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
					lua_pushstring(L,"x");
					lua_gettable(L,3);
					*(float*)(real_field)=lua_tonumber(L,-1);
					lua_pop(L,1);
					
					lua_pushstring(L,"z");
					lua_gettable(L,3);
					*(float*)(real_field + 4)=lua_tonumber(L,-1);
					lua_pop(L,1);

					lua_pushstring(L,"y");
					lua_gettable(L,3);
					*(float*)(real_field + 8)=lua_tonumber(L,-1);
					lua_pop(L,1);
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


int sf_sv_ent_field_get(lua_State * L)
{
	int i = 0;
	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Set a specific field for a specified entity\n"
	// 		"----------------------------\n"
	// 		"arg1 -> outcvar\n"
	// 		"arg2 -> enthandle\n"
	// 		"arg3 -> fieldname\n"
	// 	);


	// 	for (i=0; i< numfields; i++ ) {
	// 		orig_Com_Printf("%s ",all_fields[i].name);
	// 		if ( !(i % 3 ) ) orig_Com_Printf("\n");
	// 	}
	// 	orig_Com_Printf("\n");
	// 	orig_Com_Printf("Get help on specific field with sf_sv_ent_field_get fieldname -h\n");
	// 	return;
	// }
	// if ( c == 1 ) {
	// 	for (i=0; i< numfields; i++ ) {
	// 		if ( !strcmp(orig_Cmd_Argv(1),all_fields[i].name) ) {
	// 			// match
	// 			orig_Com_Printf("%s\n",all_fields[i].info);
	// 			break;
	// 		}
	// 	}

	// 	orig_Com_Printf("Not a known field\n");
	// 	return;
	// }
	// if ( c != 3 ) {
	// 	orig_Com_Printf("sf_sv_ent_field_get -h\n");
	// 	orig_Com_Printf("sf_sv_ent_field_get fieldname -h\n");
	// 	return;
	// }



	
	char * field = lua_tostring(L,2);
	edict_t * ent = (edict_t*)lua_tointeger(L,1);
	char * outcvar = NULL;
	void * real_field = NULL;

	for ( i = 0; i < numfields;i++ ) {
		if ( !strcmp(all_fields[i].name,field) ) {
			if ( all_fields[i].relOffset > 0 ) {
				real_field = *(unsigned int*)((unsigned int)ent + all_fields[i].relOffset);
				real_field = (void*)((unsigned int)real_field + all_fields[i].offset);
			} else {
				real_field = (void*)((unsigned int)ent + all_fields[i].offset);
			}
			// cvar_t * out_cvar = orig_Cvar_Get(outcvar,"",0,NULL);
			char newname[64];
			cvar_t * one,*two,*three;
			switch( all_fields[i].type) {
				case TYPE_FLOAT:
					// setCvarFloat(out_cvar,*(float*)real_field);
				break;
				case TYPE_INT:
					// setCvarInt(out_cvar,*(int*)real_field);
				break;
				case TYPE_SHORT:
					// setCvarInt(out_cvar,*(short*)real_field);
				break;
				case TYPE_SHORTVECTOR:
					
					// sprintf(newname,"%s%s",outcvar,"_1");
					// one = orig_Cvar_Get(newname,"",0,NULL);
					// sprintf(newname,"%s%s",outcvar,"_2");
					// two = orig_Cvar_Get(newname,"",0,NULL);
					// sprintf(newname,"%s%s",outcvar,"_3");
					// three = orig_Cvar_Get(newname,"",0,NULL);

					// setCvarInt(one,*(short*)real_field);
					// setCvarInt(two,*(short*)(real_field+2));
					// setCvarInt(three,*(short*)(real_field+4));
				break;
				case TYPE_SHORTVECTOR_2D:
					
					// sprintf(newname,"%s%s",outcvar,"_1");
					// one = orig_Cvar_Get(newname,"",0,NULL);
					// sprintf(newname,"%s%s",outcvar,"_2");
					// two = orig_Cvar_Get(newname,"",0,NULL);

					// setCvarInt(one,*(short*)real_field);
					// setCvarInt(two,*(short*)(real_field+2));
				break;
				case TYPE_STRING:
					// setCvarString(out_cvar,*(char**)real_field);
				break;
				case TYPE_POINTER:
					// setCvarInt(out_cvar,*(int*)real_field);
				break;
				case TYPE_BYTE:
					// setCvarByte(out_cvar,*(unsigned char*)real_field);
				break;
				case TYPE_VECTOR:
					// orig_Com_Printf("Do we reach here?\n");
					// assume its a cvar with _1 _2 _3

					float * in_vec = real_field;
					
					lua_newtable(L);

					lua_pushstring(L,"x");
					lua_pushnumber(L,in_vec[0]);
					lua_settable(L,-3);
					
					lua_pushstring(L,"y");
					lua_pushnumber(L,in_vec[2]);
					lua_settable(L,-3);
					
					lua_pushstring(L,"z");
					lua_pushnumber(L,in_vec[1]);
					lua_settable(L,-3);

					return 1;
				break;
				case TYPE_VECTOR_2D:
					// sprintf(newname,"%s%s",outcvar,"_1");
					// one = orig_Cvar_Get(newname,"",0,NULL);
					// sprintf(newname,"%s%s",outcvar,"_2");
					// two = orig_Cvar_Get(newname,"",0,NULL);

					// setCvarFloat(one,*(float*)real_field);
					// setCvarFloat(two,*(float*)real_field+4);
				break;
				default:
				break;
			}
			return;
		}
	}
	orig_Com_Printf("Not a known field\n");

}

// TODO : Convert fieldnames into offsets for people easier
int sf_sv_ent_find(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
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
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_ent_find -h\n");
		return;
	}
	char * compare_field_offset = atoi(orig_Cmd_Argv(2));
	char * val_to_find = orig_Cmd_Argv(3);
	char * cvarprefix = orig_Cmd_Argv(1);

	char newname[64];
	int count = 0;
	sprintf(newname,"%s_%d",cvarprefix,count);
	cvar_t *howmany = orig_Cvar_Get(newname,"",0,NULL);

	
	edict_t * entfound = orig_G_Find(0,compare_field_offset,val_to_find,0);
	while ( entfound ) {
		count++;
		sprintf(newname,"%s_%d",cvarprefix,count);
		cvar_t *u = orig_Cvar_Get(newname,"",0,NULL);
		//set the cvar here?
		setCvarInt(u,entfound);
		entfound = orig_G_Find(entfound,compare_field_offset,val_to_find,0);
	} 

	setCvarInt(howmany,count);
}

/*
	AVOIDS USING FLOATS
*/

int sf_sv_int_add(lua_State * L)
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
int sf_sv_ent_create(lua_State * L)
{
	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Creates an entity from a classname\n"
	// 		"But doesn't spawn it into the world.\n"
	// 		"----------------------------\n"
	// 		"arg1 -> cvarname to store the entity handle\n"
	// 	);
	// 	return;
	// }
	// if ( c != 1 ) {
	// 	orig_Com_Printf("sf_sv_ent_create -h\n");
	// 	return;
	// }

	edict_t * ent = orig_G_Spawn();
	// char comp[32];
	// _itoa((unsigned int)ent,comp,10);
	lua_pushinteger(L,ent);
	return 1;
}

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
int sf_sv_ent_relink(lua_State * L)
{
	edict_t * ent = atoi(orig_Cmd_Argv(1));
	orig_SV_LinkEdict(ent);
}

int sf_sv_ent_spawn(lua_State * L)
{
	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Places an already created entity into the world.\n"
	// 		"----------------------------\n"
	// 		"arg1 -> immidiate value of entity handle\n"
	// 	);
	// 	return;
	// }
	// if ( c != 1 ) {
	// 	orig_Com_Printf("sf_sv_ent_spawn -h\n");
	// 	return;
	// }
	edict_t * ent = lua_tointeger(L,-1);
	orig_ED_CallSpawn(ent);
}

int sf_sv_ent_tint(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Tints an entity a certain color.\n"
			"----------------------------\n"
			"arg1 -> immidiate value of entity handle\n"
			"arg2 -> vector [floats] of r g b colors 0->1\n"
			"arg3 -> [float] alpha/transparency value 0->1\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_ent_tint -h\n");
		return;
	}
	edict_t * ent = atoi(orig_Cmd_Argv(1));
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}

	vec3_t colors;
	readCvarAsVector(orig_Cmd_Argv(2),colors);


	if ( ent->ghoulInst ) {
		clientinst = (unsigned int*)(ent->ghoulInst);
		GhoulSetTint(colors[0],colors[1],colors[2],atof(orig_Cmd_Argv(3)));
	}
}
int sf_sv_ent_remove(lua_State * L)
{	
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Deletes an edict\n"
			"Use this on ANY previously created entity\n"
			"Spawned or unspawned\n"
			"----------------------------\n"
			"arg1 -> immidiate value of entity handle\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_ent_remove -h\n");
		return;
	}
	edict_t * ent = atoi(orig_Cmd_Argv(1));
	event_think_s	*z, *next;
	for (z=think_events.next ; z != &think_events ; z=next)
	{
		next = z->next;		
		// if ( !strcmp(p->script_name,orig_Cmd_Argv(1)) ) {
		if ( z->ent == ent ) {
			z->prev->next = z->next;
			z->next->prev = z->prev;

			ent->think = NULL;
			break;
		}
	}
	event_touch_s	*z_touch, *next_touch;
	for (z_touch=touch_events.next ; z_touch != &touch_events ; z_touch=next_touch)
	{
		next_touch = z_touch->next;
		if ( z_touch->ent == ent ) {
			z_touch->prev->next = z_touch->next;
			z_touch->next->prev = z_touch->prev;

			ent->touch = NULL;
			break;
		}
	}
	event_die_s	*z_die, *next_die;
	for (z_die=die_events.next ; z_die != &die_events ; z_die=next_die)
	{
		next_die = z_die->next;
		if ( z_die->ent == ent ) {
			z_die->prev->next = z_die->next;
			z_die->next->prev = z_die->prev;

			ent->die = NULL;
			break;
		}
	}
	event_use_s	*z_use, *next_use;
	for (z_use=use_events.next ; z_use != &use_events ; z_use=next_use)
	{
		next_use = z_use->next;
		if ( z_use->ent == ent ) {
			z_use->prev->next = z_use->next;
			z_use->next->prev = z_use->prev;

			ent->use = NULL;
			break;
		}
	}
	event_pluse_s	*z_pluse, *next_pluse;
	for (z_pluse=pluse_events.next ; z_pluse != &pluse_events ; z_pluse=next_pluse)
	{
		next_pluse = z_pluse->next;
		if ( z_pluse->ent == ent ) {
			z_pluse->prev->next = z_pluse->next;
			z_pluse->next->prev = z_pluse->prev;

			ent->plUse = NULL;
			break;
		}
	}
	event_pain_s	*z_pain, *next_pain;
	for (z_pain=pain_events.next ; z_pain != &pain_events ; z_pain=next_pain)
	{
		next_pain = z_pain->next;
		if ( z_pain->ent == ent ) {
			z_pain->prev->next = z_pain->next;
			z_pain->next->prev = z_pain->prev;

			ent->pain = NULL;
			break;
		}
	}

	orig_G_FreeEdict(ent);
}

int sf_sv_ghoul_register(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one ,"-h" ) ) {
		orig_Com_Printf(
			"Registers a new ghoul file\n"
			"----------------------------\n"
			"arg1 -> name of ghoul\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_ghoul_register -h\n");
		return;
	}

	int i;
	// sv_soundindex(orig_Cmd_Argv(1));

	char ver1[128];
	strcpy(ver1,one);
	replacechar(ver1,'\\','/');
	orig_SV_FindIndex(ver1, CS_GHOULFILES, MAX_GHOULFILES, 1,"ghoulfile");
	Cmd_CalcFreeGhoulSlots();
}

/*
Order of matrix
Scale
Rotate
Translate
*/
int sf_sv_ghoul_translate(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one ,"-h" ) ) {
		orig_Com_Printf(
			"Shifts the ghoul model's origin by vector\n"
			"Vector represents offset in each axis X Y Z\n"
			"NB. Order of ghoul editting matters. Scale affects translation units\n"
			"Translation affects point of rotation\n"
			"----------------------------\n"
			"arg1 -> entity handle\n"
			"arg2 -> invector cvarname\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_ghoul_register -h\n");
		return;
	}
	edict_t * ent = atoi(orig_Cmd_Argv(1));
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	vec3_t translate_v;
	readCvarAsVector(orig_Cmd_Argv(2),translate_v);

	Matrix4 orig,trans,tmp;

	clientinst = (unsigned int*)ent->ghoulInst;
	GhoulGetXform(&orig);
	trans.Translate(translate_v[0],translate_v[1],translate_v[2]);
	tmp.Concat(trans,orig);
	GhoulSetXform(&tmp);
}

int sf_sv_effect_register(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one ,"-h" ) ) {
		orig_Com_Printf(
			"Registers a new effect file\n"
			"----------------------------\n"
			"arg1 -> name of effect\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_effect_register -h\n");
		return;
	}

	int i;
	// sv_soundindex(orig_Cmd_Argv(1));

	char ver1[128];
	strcpy(ver1,one);
	replacechar(ver1,'\\','/');
	orig_SV_FindIndex(ver1, CS_EFFECTS, MAX_EFPACKS, 1,"effect");
	Cmd_CalcFreeEffectSlots();
}
int sf_sv_image_register(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one ,"-h" ) ) {
		orig_Com_Printf(
			"Registers a new image/m32 file\n"
			"----------------------------\n"
			"arg1 -> name of imagefile eg. pics/example.m32\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_image_register -h\n");
		return;
	}

	int i;
	// sv_soundindex(orig_Cmd_Argv(1));

	char ver1[128];
	strcpy(ver1,one);
	replacechar(ver1,'\\','/');
	orig_SV_FindIndex(ver1, CS_IMAGES, MAX_IMAGES, 1,"image");
	Cmd_CalcFreeImageSlots();
}


int sf_sv_image_list(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Lists all registered images\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_image_X with the results\n"
		);
		return;
	}
	if ( c > 1 ) {
		orig_Com_Printf("sf_sv_image_list -h\n");
		return;
	}
	int i;
	cvar_t * savecvar = NULL;
	int count = 0;
	for (i=1 ; i<MAX_IMAGES ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_IMAGES+i)*MAX_QPATH) )
		{
			char line[65];
			// sprintf(line,"%s",(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH));
			strcpy(line,SV_CONFIGSTRINGS+(CS_IMAGES+i)*MAX_QPATH);
			
			if ( c ==  1 ) {
				if ( StrStrI(line,orig_Cmd_Argv(1)) ) {
					if ( _sf_sv_sofree_debug->value ) 
						orig_Com_Printf("%s\n",line);

					char tmpname[64];
					sprintf(tmpname,"%s%i","_sf_sv_image_",count+1);
					savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
					setCvarString(savecvar,line);
					count++;

				}
			} else {
				if ( _sf_sv_sofree_debug->value )
					orig_Com_Printf("%s\n",line);

				char tmpname[64];
				sprintf(tmpname,"%s%i","_sf_sv_image_",i);
				savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
				setCvarString(savecvar,line);
				count++;
			}
			
		}
	}
	cvar_t * finalcount = orig_Cvar_Get( "_sf_sv_image_0","",0,NULL);
	setCvarInt(finalcount,count);
	
	// Cmd_CalcFreeImageSlots();
}

void Cmd_CalcFreeImageSlots(void)
{
	int freeslots = 0;
	int i;
	for (i=1 ; i<MAX_IMAGES ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_IMAGES+i)*MAX_QPATH) == '\0' )
		{
			freeslots++;
		}
	}
	char num[8];
	cvar_t * thecvar = findCvar("_sf_sv_image_info_slots");
	setCvarUnsignedInt(thecvar,freeslots);
}



int sf_sv_effect_list(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Lists all registered effects\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_effect_X with the results\n"
		);
		return;
	}
	if ( c > 1 ) {
		orig_Com_Printf("sf_sv_effect_list -h\n");
		return;
	}
	cvar_t * savecvar = NULL;
	int count = 0;
	int i;
	for (i=1 ; i<MAX_EFPACKS ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_EFFECTS+i)*MAX_QPATH) )
		{
			char line[65];
			// sprintf(line,"%s",(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH));
			strcpy(line,SV_CONFIGSTRINGS+(CS_EFFECTS+i)*MAX_QPATH);
			
			if ( c ==  1 ) {
				if ( StrStrI(line,orig_Cmd_Argv(1)) ) {
					if ( _sf_sv_sofree_debug->value ) 
						orig_Com_Printf("%s\n",line);
					char tmpname[64];
					sprintf(tmpname,"%s%i","_sf_sv_effect_",count+1);
					savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
					setCvarString(savecvar,line);
					count++;
				}
			} else {
				if ( _sf_sv_sofree_debug->value ) 
					orig_Com_Printf("%s\n",line);

				char tmpname[64];
				sprintf(tmpname,"%s%i","_sf_sv_effect_",i);
				savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
				setCvarString(savecvar,line);
				count++;
			}
			
		}
	}
	cvar_t * finalcount = orig_Cvar_Get( "_sf_sv_effect_0","",0,NULL);
	setCvarInt(finalcount,count);
	// Cmd_CalcFreeEffectSlots();
}

void Cmd_CalcFreeEffectSlots(void)
{
	int freeslots = 0;
	int i;
	for (i=1 ; i<MAX_IMAGES ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_EFFECTS+i)*MAX_QPATH) == '\0' )
		{
			freeslots++;
		}
	}
	char num[8];
	cvar_t * thecvar = findCvar("_sf_sv_effect_info_slots");
	setCvarUnsignedInt(thecvar,freeslots);
}



int sf_sv_ghoul_list(lua_State *L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Lists all registered ghoul files\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_ghoul_X with the results\n"
		);
		return;
	}
	if ( c > 1 ) {
		orig_Com_Printf("sf_sv_ghoul_list -h\n");
		return;
	}
	cvar_t * savecvar = NULL;
	int count = 0;
	int i;
	for (i=1 ; i<MAX_GHOULFILES ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_GHOULFILES+i)*MAX_QPATH) )
		{
			char line[65];
			// sprintf(line,"%s",(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH));
			strcpy(line,SV_CONFIGSTRINGS+(CS_GHOULFILES+i)*MAX_QPATH);
			
			if ( c ==  1 ) {
				if ( StrStrI(line,orig_Cmd_Argv(1)) ) {
					if ( _sf_sv_sofree_debug->value )
						orig_Com_Printf("%s\n",line);
					char tmpname[64];
					sprintf(tmpname,"%s%i","_sf_sv_ghoul_",count+1);
					savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
					setCvarString(savecvar,line);
					count++;
				}
			} else {
				if ( _sf_sv_sofree_debug->value )
					orig_Com_Printf("%s\n",line);

				char tmpname[64];
				sprintf(tmpname,"%s%i","_sf_sv_ghoul_",i);
				savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
				setCvarString(savecvar,line);
				count++;
			}
			
		}
	}

	cvar_t * finalcount = orig_Cvar_Get( "_sf_sv_ghoul_0","",0,NULL);
	setCvarInt(finalcount,count);
	// Cmd_CalcFreeGhoulSlots();
}

void Cmd_CalcFreeGhoulSlots(void)
{
	int freeslots = 0;
	int i;
	for (i=1 ; i<MAX_GHOULFILES ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_GHOULFILES+i)*MAX_QPATH) == '\0' )
		{
			freeslots++;
		}
	}
	char num[8];
	cvar_t * thecvar = findCvar("_sf_sv_ghoul_info_slots");
	setCvarUnsignedInt(thecvar,freeslots);
}



int sf_sv_sound_list(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Lists all registered sounds\n"
			"See _sf_sv_sound_info_slots for how many sounds slots you have free\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_sound_X with the results\n"
		);
		return;
	}
	if ( c > 1 ) {
		orig_Com_Printf("sf_sv_sound_list -h\n");
		return;
	}
	cvar_t * savecvar = NULL;
	int count = 0;
	int i;
	for (i=1 ; i<MAX_SOUNDS ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH) )
		{
			char line[65];
			// sprintf(line,"%s",(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH));
			strcpy(line,SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH);
			
			if ( c ==  1 ) {
				if ( StrStrI(line,orig_Cmd_Argv(1)) ) {
					if ( _sf_sv_sofree_debug->value ) 
						orig_Com_Printf("%s\n",line);
					char tmpname[64];
					sprintf(tmpname,"%s%i","_sf_sv_sound_",count+1);
					savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
					setCvarString(savecvar,line);
					count++;
				}
			} else {
				if ( _sf_sv_sofree_debug->value ) 
					orig_Com_Printf("%s\n",line);

				char tmpname[64];
				sprintf(tmpname,"%s%i","_sf_sv_sound_",i);
				savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
				setCvarString(savecvar,line);
				count++;
			}
			
		}
	}
	cvar_t * finalcount = orig_Cvar_Get( "_sf_sv_sound_0","",0,NULL);
	setCvarInt(finalcount,count);
	// Cmd_CalcFreeSoundSlots();
}

void Cmd_CalcFreeSoundSlots(void)
{
	int freeslots = 0;
	int i;
	for (i=1 ; i<MAX_SOUNDS ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH) == '\0' )
		{
			freeslots++;
		}
	}
	char num[8];
	cvar_t * thecvar = findCvar("_sf_sv_sound_info_slots");
	setCvarUnsignedInt(thecvar,freeslots);
}
// configstrings is a giant array of 64 chars / MAX_QPATH

//1: name of sound
int sf_sv_sound_register(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one ,"-h" ) ) {
		orig_Com_Printf(
			"Registers a new soundfile\n"
			"Sound files live in your %%User%%/sound directory\n"
			"See _sf_sv_sound_info_slots for how many sounds slots you have free\n"
			"----------------------------\n"
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_sound_register -h\n");
		return;
	}

	int i;
	// sv_soundindex(orig_Cmd_Argv(1));

	char ver1[128];
	strcpy(ver1,one);
	replacechar(ver1,'\\','/');
	orig_SV_FindIndex(ver1, CS_SOUNDS, MAX_SOUNDS, 1,"sound");
	Cmd_CalcFreeSoundSlots();
}

int sf_sv_sound_remove(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Unregisters a soundfile that is already registered\n"
			"Sound files live in your %%User%%/sound directory\n"
			"See _sf_sv_sound_info_slots for how many sounds slots you have free\n"
			"----------------------------\n"
			
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_sound_remove -h\n");
		return;
	}
	char ver1[128];
	strcpy(ver1,one);
	replacechar(ver1,'\\','/');
	// sends a packet to cleints asking to remove sound configstrnig
	orig_SV_RemoveSound(ver1);
	Cmd_CalcFreeSoundSlots();
}

//(edict_t *entity, int channel, int sound_num, float volume, float attenuation, float timeofs)
//1: name of sound
//2:  
int sf_sv_sound_play_ent(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Plays a soundfile that has already been registered\n"
			"----------------------------\n"
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
			"arg2 -> ent to attach the sound to\n"
			"arg3 -> channel 0->6 to play the sound on, 0 = auto\n"
			"arg4 -> volume\n"
			"arg5 -> attenuation [0 full volume everywhere, 3-diminish volume rapidly with distance]\n"
			"arg6 -> client_only bool\n"
		);
		return;
	}
	if ( c != 6 ) {
		orig_Com_Printf("sf_sv_sound_play_ent -h\n");
		return;
	}
	edict_t * ent = atoi(orig_Cmd_Argv(2));
	int chan = atoi(orig_Cmd_Argv(3));
	float volume = atof(orig_Cmd_Argv(4));
	float atten = atof(orig_Cmd_Argv(5));
	int global = atoi(orig_Cmd_Argv(6));

	char ver1[128];
	strcpy(ver1,one);
	replacechar(ver1,'\\','/');

	// create bool is false
	int index = orig_SV_FindIndex(ver1, CS_SOUNDS, MAX_SOUNDS, 0,"sound");
	// only if its in our configstring
	if (index)
		orig_PF_StartSound(ent,chan, index ,volume,atten,0,global);
	else
		orig_Com_Printf("Sound is not registered.\n");
	
}
/*
(7:01:04 PM) Me: if all channels are full
(7:01:11 PM) Me: if will interrupt the one whcih is nearest to completion
(7:01:13 PM) Other: oh
(7:01:17 PM) Other: okk
(7:01:20 PM) Other: smart hen
(7:01:23 PM) Other: good soulution
(7:01:38 PM) Other: how come i manually
(7:01:46 PM) Other: set length of file as cvars
(7:01:53 PM) Other: if its built into sof1 the check of length
(7:02:00 PM) Other: lol
(7:02:28 PM) Other: for my queue script i set the ms time of each sound ifle
(7:03:27 PM) Me: and the algorithm suggests
(7:03:31 PM) Me: that all channels are auto
(7:03:40 PM) Other: lol yep
(7:03:43 PM) Me: its just that
(7:03:55 PM) Me: its not auto if its attached to same entity
(7:04:05 PM) Me: but that excludes channel 0
(7:04:09 PM) Me: thats where channel 0 differs from the others
(7:04:17 PM) Me: if will not override even if its attached to same entity
*/
// sv_startsound takes origin :P
int sf_sv_sound_play_origin(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Plays a soundfile that has already been registered\n"
			"----------------------------\n"
			"arg1 -> name of soundfile eg. misc/talk.wav\n"
			"arg2 -> name of cvar that holds origin vector\n"
			"arg3 -> channel 0->6 to play the sound on, 0 = auto\n"
			"arg4 -> volume\n"
			"arg5 -> attenuation\n"
			"arg6 -> client_only bool\n"
		);
		return;
	}
	if ( c != 6 ) {
		orig_Com_Printf("sf_sv_sound_play_origin -h\n");
		return;
	}
	char * origin = orig_Cmd_Argv(2);
	int chan = atoi(orig_Cmd_Argv(3));
	float volume = atof(orig_Cmd_Argv(4));
	float atten = atof(orig_Cmd_Argv(5));
	int global = atoi(orig_Cmd_Argv(6));

	vec3_t vorigin;
	readCvarAsVector(origin,vorigin);

	char ver1[128];
	strcpy(ver1,one);
	replacechar(ver1,'\\','/');

	// create bool is false
	int index = orig_SV_FindIndex(ver1, CS_SOUNDS, MAX_SOUNDS, 0,"sound");
	// only if its in our configstring
	if (index)
		orig_SV_StartSound(vorigin,*(unsigned int*)EDICT_BASE,chan, index ,volume,atten,0,global);
	else
		orig_Com_Printf("Sound is not registered.\n");
	
}
/*
#define SND_LOCALIZE_GLOBAL		0	// Default, means that the sound is projected into the world as normal.
#define SND_LOCALIZE_CLIENT		1	// Means to ONLY play the sound on the associated client.
*/

sound_overrides_t sound_overrides;

// sp_sv_sound_override "/enemy/dth/*" ""
// sp_sv_sound_override "/impact/gore/*" ""
// sp_sv_sound_override "/impact/player/*" ""
int sf_sv_sound_override(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Plays a specific sound in place of a previous one\n"
			"----------------------------\n"
			"arg1 -> the known original sound - can end with a * to target many sounds\n"
			"arg2 -> your new sound - can be empty then will play no sound\n"
			"arg3 -> altered attenuation value - "" empty string does not alter\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_sound_override -h\n");
		return;
	}

	char * name = orig_Cmd_Argv(1);
	
	sound_overrides_t	*z, *next;
	for (z=sound_overrides.next ; z != &sound_overrides ; z=next)
	{
		next = z->next;
		
		bool star_input = false,star_already = false;
		char * c,*d;
		c = strchr(name,'*');
		star_input = c && (c+1 == 0x00);
		d = strchr(z->orig_sound,'*');
		star_already = d && (d+1 == 0x00);
		if ( star_input || star_already ) {
			if ( star_already && star_input) {
				// both stars
				// check smaller length star
				if ( d - z->orig_sound < c - name ) {
					if ( !strnicmp(z->orig_sound,name,d - z->orig_sound )) {
						//they are equal and both stars
						orig_Com_Printf("This sound is already overriden, sorry\n");
						return;
					}		
				} else {
					if ( !strnicmp(z->orig_sound,name,c - name ) ) {
						//they are equal and both stars
						orig_Com_Printf("This sound is already overriden, sorry\n");
						return;
					}		
				}
				
			} else
			{
				// 1star name
				if ( star_already ) {
					//star already
					if ( !strnicmp(z->orig_sound,name,d - z->orig_sound ) ) {
						orig_Com_Printf("This sound is already overriden, sorry\n");
						return;
					}
				} else {
					//star input
					if ( !strnicmp(z->orig_sound,name,c - name ) ) {
						orig_Com_Printf("This sound is already overriden, sorry\n");
						return;
					}
				}
			}

			
		} else if ( !stricmp(name,z->orig_sound) ) {
			orig_Com_Printf("This sound is already overriden, sorry\n");
			return;
		}
	}
	
	// if we got here, assume the sound can be created


	z = malloc(sizeof(sound_overrides_t));

	z->next = sound_overrides.next;
	z->prev = &sound_overrides;
	sound_overrides.next->prev = z;
	sound_overrides.next = z;

	strcpy(z->orig_sound,orig_Cmd_Argv(1));
	strcpy(z->new_sound,orig_Cmd_Argv(2));
	z->index = 0;
	char * atn_str = orig_Cmd_Argv(3);
	if ( strlen(atn_str) ) {
		z->atten_mod = atof(orig_Cmd_Argv(3));
	} else z->atten_mod = -1.0f;
	
}


void Cmd_TakePiss(lua_State * L)
{	
	// orig_TakePiss(*(edict_t**)(cl + CLIENT_ENT))

}


char layoutstring[1024];
int layoutstring_len = 0;
int sf_sv_draw_clear(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Clears all interface text on screen\n"
		);
		return;
	}
	if ( c != 0 ) {
		orig_Com_Printf("sf_sv_draw_clear -h\n");
		return;
	}
	layoutstring_len = 0;
	layoutstring[0] = 0x00;
	sprintf(layoutstring,"xr %i yb -16 altstring \"%s\" ",0 - (sofreebuild_len*8+8),sofreebuildstring);
	// orig_Com_Printf("Layoutstring is : %s\n",layoutstring);
}
/*
yb yBottom 0 = bottom of screen, up=negative, down=positive
yt yTop 0 = top of screen, up=negative, down=positive
yv centered

xl xLeft
xr xRight
xv centered
*/
int sf_sv_draw_string(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Draw a string at offset x y with message\n"
			"----------------------------\n"
			"arg1 -> offsetx\n"
			"arg2 -> offsety\n"
			"arg3 -> message\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_draw_string -h\n");
		return;
	}
	int offsetx = atoi(orig_Cmd_Argv(1));
	int offsety = atoi(orig_Cmd_Argv(2));
	char * message = orig_Cmd_Argv(3);
	int len = strlen(message);

	if ( layoutstring_len + len <= 1024 ) {
		char newstring[256];
		sprintf(newstring,"xv %i yv %i string \"%s\" ",offsetx,offsety,message);
		int newlen = strlen(newstring);
		strcat(layoutstring, newstring);
		layoutstring_len+=newlen;
	} else {
		orig_Com_Printf("Cant draw this , run out of space\n");
	}
}

int sf_sv_draw_string2(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Draw a string at offset x y with message\n"
			"----------------------------\n"
			"arg1 -> offsetx\n"
			"arg2 -> offsety\n"
			"arg3 -> message\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_draw_string2 -h\n");
		return;
	}
	int offsetx = atoi(orig_Cmd_Argv(1));
	int offsety = atoi(orig_Cmd_Argv(2));
	char * message = orig_Cmd_Argv(3);
	int len = strlen(message);

	if ( layoutstring_len + len <= 1024 ) {
		char newstring[256];

		sprintf(newstring,"%s ",message);
		int newlen = strlen(newstring);
		strcat(layoutstring, newstring);
		layoutstring_len+=newlen;
	} else {
		orig_Com_Printf("Cant draw this , run out of space\n");
	}
}

int sf_sv_draw_altstring(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Draw a grey string at offset x y with message\n"
			"----------------------------\n"
			"arg1 -> offsetx\n"
			"arg2 -> offsety\n"
			"arg3 -> message\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_draw_altstring -h\n");
		return;
	}
	int offsetx = atoi(orig_Cmd_Argv(1));
	int offsety = atoi(orig_Cmd_Argv(2));
	char * message = orig_Cmd_Argv(3);
	int len = strlen(message);
	if ( layoutstring_len + len <= 1024 ) {
		for (int i = 0; i < len; i++ ) {
				*(message+i) = *(message+i) | 0x80;
		}

		char newstring[256];
		sprintf(newstring,"xv %i yv %i altstring \"%s\" ",offsetx,offsety,message);
		int newlen = strlen(newstring);
		strcat(layoutstring, newstring);
		layoutstring_len+=newlen;
	} else {
		orig_Com_Printf("Cant draw this , run out of space\n");
	}
}

// 32kb
// char floadfilebuffer[32768];
// sofplus uses 16,17,18
// i try to preserve sofreeS as using 7.. in a levelInit hook earlier than spawnentities after whcih sofplus uses on map_begin
int valid_ID[97] = {7,15,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,56,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,196,197,198,199,201,202,204,209,240,245,249,250,254,255};
int next_available_ID = 0;
int sf_sv_spackage_list(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1) ,"-h" ) ) {
		orig_Com_Printf(
			"Lists all registered string packages\n"
			"----------------------------\n"
			"takes optional argument as a search for substring\n"
			"fills _sf_sv_spackage_X with the results\n"
		);
		return;
	}
	if ( c > 1 ) {
		orig_Com_Printf("sf_sv_spackage_list -h\n");
		return;
	}
	int i;
	cvar_t * savecvar = NULL;
	int count = 0;
	char fileline[256];
	for (i=1 ; i<MAX_STRING_PACKAGES ; i++) {
		if ( *(unsigned char*)(SV_CONFIGSTRINGS+(CS_STRING_PACKAGES+i)*MAX_QPATH) )
		{
			char line[65];
			// sprintf(line,"%s",(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH));
			strcpy(line,SV_CONFIGSTRINGS+(CS_STRING_PACKAGES+i)*MAX_QPATH);
			
			if ( c ==  1 ) {
				if ( StrStrI(line,orig_Cmd_Argv(1)) ) {
					if ( _sf_sv_sofree_debug->value ) 
						orig_Com_Printf("%s\n",line);

					char tmpname[64];
					sprintf(tmpname,"%s%i","_sf_sv_spackage_",count+1);
					savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
					setCvarString(savecvar,line);
					count++;

				}
			} else {
				if ( _sf_sv_sofree_debug->value ) {
					
					char fname[64];
					sprintf(fname,"strip/%s.sp",line);
					unsigned char * filedata;
					int ret = orig_FS_LoadFile(fname,&filedata,false);
					// orig_Com_Printf("ret is %08X\n",ret);
					if ( ret != -1 ) {
						// fgets(fileline, sizeof(fileline), spfile);
						// fgets(fileline, sizeof(fileline), spfile);

						char * d = filedata;
						char * second_line = NULL;
						
						int count = 1;
						// it will break when d=='\n'
						while ( *d != '\n' &&  count < ret ) {
							d++;
							count++;
						}
						// d == '\n'
						if ( count < ret) {
							d++;
							count++;
							second_line = d;
						}
						while ( *d != '\n' && count < ret) {
							d++;
							count++;
						}
						*d=0x00;
						
						orig_Com_Printf("%s : %s\n",line,second_line);

						orig_Z_Free(filedata);
					}
					
				}

				char tmpname[64];
				sprintf(tmpname,"%s%i","_sf_sv_spackage_",i);
				savecvar = orig_Cvar_Get( tmpname,"",0,NULL);
				setCvarString(savecvar,line);
				count++;
			}
			
		}
	}
	cvar_t * finalcount = orig_Cvar_Get( "_sf_sv_spackage_0","",0,NULL);
	setCvarInt(finalcount,count);
	
	// Cmd_CalcFreeImageSlots();
}

// Register a string package
int sf_sv_spackage_register(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Register a .sp string package file that the client will download\n"
			"----------------------------\n"
			"arg1 -> name of file including .sp extension\n"
			"eg. sf_sv_spackage_register mystringpackage.sp\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_spackage_register -h\n");
		return;
	}

	char temp[128];
	sprintf(temp,"strip/%s",one);
	// z_malloc only called when 2nd arg is not NULL
	if ( orig_FS_LoadFile(temp,NULL,false) == -1 ) {
		orig_Com_Error(ERR_FATAL,"Error sf_sv_spackage_register: file %s cannot be found\n",temp);
		return;
	}
	
	sprintf(temp,"%s/strip/%s",user->string,one);

	// modify the file 
	FILE * thefile = fopen(temp,"r+");
	if ( !thefile ) {
		// assume its a standard strip in one of the .pak files
		// dont apply checksum to it or validate its ID
		// orig_Com_Printf("This SP is not in the user, assuming pakfile.\n");
		char * shorten= strchr(one,'.');
		if ( shorten ) {
			*shorten = 0x00;	
		}
		orig_SP_Register(one);

	} else {
		char line[512];
		char * mybuffer = NULL;
		char * newb;
		int line_count = 0;
		bool nowrite = false;

		// fgets = The result stored in str is appended with a null character.
		while ( fgets(line,512,thefile) ) {
			// there is a newline at the end of each string

			// change ID to safe value
			if ( line_count+1 == 2) {
				char * find = strstr(line,"ID ");
				if ( find ) {
					find += 3;
					char comp[16];
					_itoa(valid_ID[next_available_ID],comp,10);
					// you can be destructive to line buffer its overwritten after anyway
					find[strlen(find)-1] = 0x00;
					if ( !strncmp(find,comp,3) ) {
						// it already has this value no need to write
						nowrite = true;
						break;
					}
				}
				// adjust the ID
				sprintf(line,"ID %i\n",valid_ID[next_available_ID]);
			}
			mybuffer = my_realloc(mybuffer,512*(line_count+1));
			strcpy(mybuffer + (line_count*512),line);
			line_count++;
		}
		// nowrite=false
		if ( !nowrite ) {
			int totalbytes = 0;
			fseek(thefile,0,SEEK_SET);
			// orig_Com_Printf("Writing modified data\n");
			for ( int i=0;i<line_count; i++ ){
				totalbytes += strlen(mybuffer + (i*512));
				fputs(mybuffer + (i*512),thefile);
			}
			changesize(thefile,totalbytes);
		}
		char * newfile = orig_spfileChecksum("strip/",one);
		char * shorten= strchr(newfile,'.');
		if ( shorten ) {
			*shorten = 0x00;	
		}
		orig_SP_Register(newfile);

		next_available_ID++;
		free(mybuffer);
	}

	fclose(thefile);
	
}



int sf_sv_spackage_print_ref(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Register a .sp string package file that the client will download\n"
			"----------------------------\n"
			"arg1 -> ent handle or 0 for broadcast\n"
			"arg2 -> File reference string\n"
			"arg3 -> Index reference string\n"
			"arg4+ -> Extra strings for passing data into the output\n"
			"eg. sf_sv_spackage_print_id SOFREE CHEER ...\n"
			"NB. %d = integer %p = byte %s = string %hd = signed_short %hu = unsigned short\n"
		);
		return;
	}
	if ( c < 3 ) {
		orig_Com_Printf("sf_sv_spackage_print_ref -h\n");
		return;
	}

	edict_t * ent = atoi(orig_Cmd_Argv(1));

	char temp[64];
	sprintf(temp,"%s_%s",orig_Cmd_Argv(2),orig_Cmd_Argv(3));
	short final = SP_ReferenceToID(temp);

	if ( final != -1 ) {
		// orig_Com_Printf("Your id is %04X ENJOY!\n",final);
		// it can take extra params, hmm
		// it will read from Cmd_Argv(X) for how many % it finds in the string
		INSIDE_SPACKAGE_PRINT_ID = true;
		orig_SP_Print(ent,final);
	} else {
		orig_Com_Printf("Error sf_sv_spackage_print_ref : cant find the string refs %s %s\n",orig_Cmd_Argv(2),orig_Cmd_Argv(3));
	}
}

bool INSIDE_SPACKAGE_PRINT_ID = false;

//typedef void (*SP_Print)(edict_t *ent, unsigned short ID, ...);
// who,num
int sf_sv_spackage_print_id(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	char * one = orig_Cmd_Argv(1);
	if ( !strcmp(one,"-h" ) ) {
		orig_Com_Printf(
			"Print an entry from a .sp string package file\n"
			"----------------------------\n"
			"arg1 -> ent handle or 0 for broadcast\n"
			"arg2 -> ID of stringpackage file (found inside the file)\n"
			"arg3 -> Index number of the text you want to print\n"
			"arg4+ -> Extra strings for passing data into the output\n"
			"eg. sf_sv_spackage_print_id 18 25 ...\n"
			"NB. %d = integer %p = byte %s = string %hd = signed_short %hu = unsigned short\n"
		);
		return;
	}
	if ( c < 3 ) {
		orig_Com_Printf("sf_sv_spackage_print_id -h\n");
		return;
	}

	edict_t * ent = atoi(orig_Cmd_Argv(1));
	unsigned char file_id = atoi(orig_Cmd_Argv(2));
	unsigned char index = atoi(orig_Cmd_Argv(3));
	unsigned short final = file_id << 8;
	final |= index;
	INSIDE_SPACKAGE_PRINT_ID = true;
	// it can take extra params, hmm
	orig_SP_Print(ent,final);
}
// typedef void (*SP_Print_Obit)(edict_t *ent, unsigned short ID, ...);
// who,num
int sf_sv_spackage_print_obit(lua_State * L)
{
	unsigned int ed_base = *(unsigned int*)EDICT_BASE;
	orig_SP_Print(ed_base + (atoi(orig_Cmd_Argv(1))+1)*SIZE_OF_EDICT,atoi(orig_Cmd_Argv(2)));
}
// typedef int (*SP_SPrint)(char *buffer, int buffer_size, unsigned short ID, ...);

// who,msg,len
int sf_sv_spackage_print_string(lua_State * L)
{
	orig_SP_Print((edict_t*)orig_Cmd_Argv(2),(edict_t*)atoi(orig_Cmd_Argv(3)),(edict_t*)atoi(orig_Cmd_Argv(1)));
}
// typedef const char	*(*SP_GetStringText)(unsigned short ID);
int Cmd_SP_GetStringText(lua_State * L)
{
	char out[2048] = "echo ";
	strcat(out,orig_SP_GetStringText(atoi(orig_Cmd_Argv(1))));
	orig_Cbuf_AddText(out);	
}





int Cmd_New_Run_Script(lua_State * L)
{
	try {


	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"DesignerScripts are .ds files compiled into .os files using sofds.exe from SoF SDK\n"
			"----------------------------\n"
			"Returns execution to a previously loaded script file\n"
			"You must pass in the handle you saved from sp_sv_script_load\n"
			"eg. \"sp_sv_script_run $my_script\" , where myscript is the cvar storing the handle\n"
			"----------------------------\n"
			"arg1 -> handle to loaded script\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}

	edict_t * ent = atoi(orig_Cmd_Argv(1));
	if ( !ent->inuse ) {
		orig_Com_Printf("Invalid script handle\n");
		return;
	}
	//ent other activator
	orig_script_use(ent,ent,ent);
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
	
}

script_list_t the_scripts;

int sf_sv_script_load(lua_State * L)
{
	try {
	int n = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"DesignerScripts are .ds files compiled into .os files using sofds.exe from SoF SDK\n"
			"----------------------------\n"
			"Loads a DesignerScript file (.os), located in your %%User%%/ds/ directory\n"
			"----------------------------\n"
			"arg1 -> cvarname to store handle\n"
			"arg2 -> name of script\n"
			"args3+ -> optional parameters to pass\n"
			"...\n"
		);
		return;
	}
	if ( n < 2 ) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}

	// if ( !orig_FS_FileExists(orig_Cmd_Argv(2)) ) {
	// 	PrintOut(PRINT_BAD,false,"Cannot find a script named %s.os , make sure its compiled\n",orig_Cmd_Argv(1));
	// 	return;
	// }

	cvar_t * out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1),"",0,NULL);

	// script_list_t * s = getFreeLinkedListSlot_Scripts(&the_scripts,&num_scripts,sizeof(script_list_t));
	script_list_t	*z = malloc(sizeof(script_list_t));

	z->next = the_scripts.next;
	z->prev = &the_scripts;
	the_scripts.next->prev = z;
	the_scripts.next = z;

	char * blehparms[16] = {0};
	// move all arguments into parms
	for ( int i = 0 ; i < n-2 && i < 16; i++ ) {
		int len = strlen(orig_Cmd_Argv(i+1 + 2)) + 1;
		// orig_Com_Printf("A parm\n");
		// orig_Com_Printf(orig_Cmd_Argv(i+1 + 2));
		char * lul = malloc(len);
		strncpy(lul,orig_Cmd_Argv(i+1 + 2),len);
		lul[len-1] = 0x00;
		*(unsigned int*)(0x5015CC34+4*i) = lul;
		
		blehparms[i] = lul;
	}
	strcpy(z->script_name,orig_Cmd_Argv(2));

	edict_t * newrunner = orig_G_Spawn();
	newrunner->classname = "script_runner";

	*(unsigned int*)0x5015CC30 = &z->script_name;
	orig_SP_script_runner(newrunner);
	z->cscript = last_created_cscript;



	for (int j = 0; j < 16; j++ ) {
		if ( blehparms[j] )
			free(blehparms);
	}

	
	z->next = NULL;
	z->runner = newrunner;
	


	unsigned int value = newrunner;


	setCvarInt(out_cvar,value);


	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

/*
typedef struct zhead_s
{
	struct zhead_s	*prev, *next;
} zhead_t;
ONINIT
z_chain.next = z_chain.prev = &z_chain;
ONAPPEND
zhead_t	*z = malloc(sizeof(zhead_t));

z->next = z_chain.next;
z->prev = &z_chain;
z_chain.next->prev = z;
z_chain.next = z;
ONREMOVE
z->prev->next = z->next;
z->next->prev = z->prev;
ONSEARCH
zhead_t	*z, *next;
for (z=z_chain.next ; z != &z_chain ; z=next)
{
	next = z->next;
	if (matches) {
		//play with z here
	}
}
*/

int sf_sv_script_unload(lua_State * L)
{
	try{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"DesignerScripts are .ds files compiled into .os files using sofds.exe from SoF SDK\n"
			"----------------------------\n"
			"Stops execution to a previously loaded script file and unloads the script file\n"
			"Your script handle is no longer valid after calling this function\n"
			"You must pass in the handle you saved from sp_sv_script_load\n"
			"eg. \"sp_sv_script_unload $my_script\" , where myscript is the cvar storing the handle\n"
			"----------------------------\n"
			"arg1 -> handle to loaded script\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}

	edict_t * ent = atoi(orig_Cmd_Argv(1));
	if ( !ent->inuse ) {
		orig_Com_Printf("Invalid script handle\n");
		return;
	}

	script_list_t	*z, *next;
	for (z=the_scripts.next ; z != &the_scripts ; z=next)
	{
		next = z->next;		
		// if ( !strcmp(p->script_name,orig_Cmd_Argv(1)) ) {
		if ( z->runner == ent ) {
			z->prev->next = z->next;
			z->next->prev = z->prev;

			//would be nice to free CScript here, but oh well
			stset(z->cscript,CSCRIPT_SCRIPTCONDITION,COND_COMPLETED);
			orig_G_FreeEdict(z->runner);
			free(z);
			
			break;
		}
	}

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}



struct d_script_s
{
	char name[64];
	// CScript pointer self
	void * handle;
};


struct d_script_s * dende_scripts[MAX_D_SCRIPTS] = {NULL};
int d_script_pointer = 0;


// they must have moved script_use into the class...
// void script_use(edict_t *ent, edict_t *other, edict_t *activator)
int sf_sv_script_run(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Executes a DesignerScript file (.os), located in your %%User%%/ds/ directory\n"
			"DesignerScripts are .ds files compiled into .os files using sofds.exe\n"
			"eg. \"sp_sv_script_run elevator\" -notice no file extension\n"
			"----------------------------\n"
			"arg1 -> name of script\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}
	// void * cl = (void*)((*(unsigned int*)CLIENT_BASE) + ( (unsigned int)(atoi(orig_Cmd_Argv(1))) * SIZE_OF_CLIENT));
	// edict_t * entbleh = *(edict_t**)(cl + CLIENT_ENT);



	char scriptname[64];
	sprintf(scriptname,"ds/%s.os",orig_Cmd_Argv(1));
	if ( !orig_FS_FileExists(scriptname) ) {
		orig_Com_Printf("You are trying run a script that is unlikely to be loaded.\n");
		return;
	}

	unsigned int ed_base = stget(EDICT_BASE,0);

	//search for scriptname
	struct d_script_s * ds = NULL;
	
	for ( int i = 0 ; i < d_script_pointer; i++ ) {
		struct d_script_s * ds = dende_scripts[i];
		if ( !strcmp(scriptname,ds->name) ) {
			unsigned int  cond = stget(ds->handle,CSCRIPT_SCRIPTCONDITION);

			if ( cond != COND_COMPLETED && cond != COND_READY )
			{
				orig_Com_Printf("Seems like script %s is already running\n",scriptname);
				return;
			}

			// ParameterValues.push_back(new StringVar("parm",Value))

			// To allow many scripts to use one entity?
			//Link entity to script before run ?
			// *(unsigned int*)(ed_base+EDICT_SCRIPT) = ds->handle;

			orig_Com_Printf("Running script %s\n",scriptname);
			// *(unsigned int*)(ds->handle + CSCRIPT_SCRIPTCONDITION) = COND_READY;
			orig_script_use(ed_base,ed_base,ed_base);
			return;
		}
	}
	orig_Com_Printf("Script %s isn't loaded yet\n",scriptname);
	

/*
	asm volatile(	"push %1;"//push scriptname
					"push %2;"//push owner
					"push %3;"//push owner
					"movl %0,%%ecx;"//new_mem->ecx
					"call *%4;"//call orig_script_use
					::"m"(myscript),"m"(entbleh),"m"(entbleh),"m"(entbleh),"m"(orig_script_use):"%ecx");

*/
}




/*
d_script_pointer currently points to next element free
this doesnt expect gaps :/
*/
int Cmd_LoadScript(lua_State * L)
{	
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Loads a DesignerScript file (.os), located in your %%User%%/ds/ directory\n"
			"DesignerScripts are .ds files compiled into .os files using sofds.exe\n"
			"eg. \"sp_sv_script_load elevator\" -notice no file extension\n"
			"----------------------------\n"
			"arg1 -> name of script\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}

	if ( d_script_pointer == MAX_D_SCRIPTS ) {
		orig_Com_Printf("Sofree can't load that many scripts :~(\n");
		return;
	}
	void * newscript = orig_cplusplus_new(0x4b4);

	char scriptname[64];
	sprintf(scriptname,"ds/%s.os",orig_Cmd_Argv(1));

	if ( !orig_FS_FileExists(scriptname) ) {
		orig_Com_Printf("You are trying to load a non-existant file.\n");
		return;
	}

	struct d_script_s * ds = NULL;
	
	for ( int i = 0 ; i < d_script_pointer; i++ ) {
		struct d_script_s * ds = dende_scripts[i];
		if ( !strcmp(scriptname,ds->name) ) {
			orig_Com_Printf("Script %s is already loaded\n",scriptname);
			return;
		}
	}	


	orig_Com_Printf("Loading script %s\n",scriptname);

	// create the d_script
	ds = dende_scripts[d_script_pointer] = malloc(sizeof(struct d_script_s));
	d_script_pointer++;
	strcpy(ds->name,scriptname);
	ds->handle = newscript;



	//st.script = scriptname
	*(unsigned int*)0x5015CC30 = &(scriptname[0]);
	//orig_SP_script_runner(owner);
	
	unsigned int worldspawn = stget(EDICT_BASE,0);
	unsigned int p_to_string = &(scriptname[0]);


	asm volatile(	"push %1;"//push scriptname
					"push %2;"//push owner
					"movl %0,%%ecx;"//new_mem->ecx
					"call *%3;"//call orig_CScript
					::"m"(newscript),"m"(worldspawn),"m"(p_to_string),"m"(orig_CScript):"%ecx");

							   //nameofscript,ent
	//ent->Script = new CScript(temp, ent);
	// ent->script = newscript
	stset(worldspawn,EDICT_SCRIPT,newscript);

	// // append to list of scripts
	// //Scripts.push_back(ent->Script);
	void * newListItem = orig_cplusplus_new(0xC);

	// //no fucking idea what that does, i was insane copying it bit by bit from asm
	unsigned int esi = stget(0x5015c504,0);

	stset(newListItem,0,esi);

	unsigned int edi = stget(esi,4);

	stset(newListItem,4,edi);
	stset(esi,4,newListItem);


	stset(stget(newListItem,4),0,newListItem);
	stset(newListItem,8,stget(worldspawn,EDICT_SCRIPT));

	stset(0x5015C508,0,stget(0x5015C508,0) + 1);

}



int Cmd_StopScript(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Stops excution of a DesignerScript file (.os), located in your %%User%%/ds/ directory\n"
			"DesignerScripts are .ds files compiled into .os files using sofds.exe\n"
			"eg. \"sp_sv_script_stop elevator\" -notice no file extension\n"
			"----------------------------\n"
			"arg1 -> name of script\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("[commandname] -h\n");
		return;
	}
	char scriptname[64];
	sprintf(scriptname,"ds/%s.os",orig_Cmd_Argv(1));
	if ( !orig_FS_FileExists(scriptname) ) {
		orig_Com_Printf("You are trying stop a script that is unlikely to be loaded.\n");
		return;
	}

	struct d_script_s * ds = NULL;
	for ( int i = 0 ; i < d_script_pointer; i++ ) {
		struct d_script_s * ds = dende_scripts[i];
		if ( !strcmp(scriptname,ds->name) ) {
			orig_Com_Printf("Stopping script %s\n",scriptname);
			stset(ds->handle,CSCRIPT_SCRIPTCONDITION,COND_COMPLETED);
			return;
		}
	}

}


int sf_sv_player_move(lua_State * L)
{
	try{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Teleports a player to specified 1,2,3 co-ordinate\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> cvar prefix for input vector _1 _2 _3\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_move -h\n");
		return;
	}
	edict_t* ent = get_ent_from_player_slot(atoi(orig_Cmd_Argv(1)));
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	char * prefix = orig_Cmd_Argv(2);
	char newname[64];

	vec3_t created_vect;
	readCvarAsVector(prefix,created_vect);

	VectorCopy(created_vect, ent->s.origin );
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

int sf_sv_player_gravity(lua_State * L)
{
	try{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Sets the gravity strength on the chosen player\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> gravity value\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_gravity -h\n");
		return;
	}
	int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = get_ent_from_player_slot(slot);
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	
	short grav = atoi(orig_Cmd_Argv(2));
	ent->client->ps.pmove.gravity = grav;
	client_gravity[slot] = grav;
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}



float player_tint[32][4];
float player_wep_tint[32][4];
int sf_sv_player_paint(lua_State * L)
{
	try{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
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
	if ( c != 5 ) {
		orig_Com_Printf("sf_sv_player_paint -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = get_ent_from_player_slot(slot);
	//!stget(ent,EDICT_INUSE)
	if ( !ent ) {
		// PrintOut(PRINT_BAD,false,"Invalid Ent\n");
		return;
	}
	// PrintOut(PRINT_GOOD,false,"argc is : %i\n",orig_Cmd_Argc());

	float r = atof(orig_Cmd_Argv(2));
	float g = atof(orig_Cmd_Argv(3));
	float b = atof(orig_Cmd_Argv(4));
	float a = atof(orig_Cmd_Argv(5));
	player_tint[slot][0] = r;
	player_tint[slot][1] = g;
	player_tint[slot][2] = b;
	player_tint[slot][3] = a;
	
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
unsigned int was_ghosted[32];
int sf_sv_player_weap_paint(lua_State * L)
{
	try{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
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
	if ( c != 5 ) {
		orig_Com_Printf("sf_sv_player_weap_paint -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = get_ent_from_player_slot(slot);
	//!stget(ent,EDICT_INUSE)
	if ( !ent ) {
		// PrintOut(PRINT_BAD,false,"Invalid Ent\n");
		return;
	}
	// PrintOut(PRINT_GOOD,false,"argc is : %i\n",orig_Cmd_Argc());

	float r = atof(orig_Cmd_Argv(2));
	float g = atof(orig_Cmd_Argv(3));
	float b = atof(orig_Cmd_Argv(4));
	float a = atof(orig_Cmd_Argv(5));
	player_wep_tint[slot][0] = r;
	player_wep_tint[slot][1] = g;
	player_wep_tint[slot][2] = b;
	player_wep_tint[slot][3] = a;
	
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


int sf_sv_player_weap_current(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Get currently held weapon of client\n"
			"----------------------------\n"
			"arg1 -> outcvar to store the weapon number\n"
			"arg2 -> playerslot\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_weap_current -h\n");
		return;
	}
	//0x5c
	static int (__thiscall *getCurWeaponType)(void * self) = 0x40005A70;

	unsigned int slot = atoi(orig_Cmd_Argv(2));
	edict_t* ent = get_ent_from_player_slot(slot);

	cvar_t * out = orig_Cvar_Get(orig_Cmd_Argv(1),"",0,NULL);
	
	setCvarInt(out,getCurWeaponType(ent->client->inv));
	
	// orig_Com_Printf("Address : %08X\n",*(unsigned int*)(*(unsigned int*)(ent->client->inv)+0x5c));
}
int sf_sv_player_weap_switch(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Switch a players weapon to this one\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> newweapon\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_weap_switch -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = get_ent_from_player_slot(slot);

	sharedEdict_t	sh;
	sh.inv = (inven_c *)ent->client->inv;
	sh.edict = ent;
	
	orig_SetOwner(sh.inv,&sh);

	orig_selectWeapon(sh.inv,atoi(orig_Cmd_Argv(2)));
}


int sf_sv_player_weap_lock(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Prevent a player from changing his weapon\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> Lockstate 1 or 0\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_weap_lock -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = get_ent_from_player_slot(slot);

	sharedEdict_t	sh;
	sh.inv = (inven_c *)ent->client->inv;
	sh.edict = ent;
	
	orig_SetOwner(sh.inv,&sh);

	int lockweap = atoi(orig_Cmd_Argv(2));
	if ( lockweap == 1 ) {
		orig_rulesSetFreelySelectWeapon(sh.inv,0);
	} else
	if ( lockweap == 0 ) {
		orig_rulesSetFreelySelectWeapon(sh.inv,1);
	}
	
}

bool player_collision[32];
/*
SOLID CONTROLS ENTITY TO ENTITY COLLISION
*/
int sf_sv_player_collision(lua_State * L)
{
	try{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Makes it so this player can be passed through by all other players\n"
			"----------------------------\n"
			"arg1 -> valid slot id\n"
			"arg2 -> 1 or 0 ... representing collision on or off\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_collision -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = get_ent_from_player_slot(slot);
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	int mode = atoi(orig_Cmd_Argv(2));
	if ( mode != 0 and mode != 1 )
	{
		orig_Com_Printf("Collision must be 1 or 0\n");
	}

	// if he is IN game its fine to edit his solid now.
	if ( !ent->client->pers.spectator ) {
		if ( mode == 1 ) {
			ent->solid = SOLID_BBOX;
		} else {
			ent->solid = SOLID_TRIGGER;
		}
	}
	// the spec will solid change when he hops in because of client_spawn sofplus event is called AFTER PutClientInServer
	// specs and players alike shoudl ahve their setting cahnged
	if ( mode == 1 ) {
		player_collision[slot] = true;
	} else {
		player_collision[slot] = false;
	}
	

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}

}

bool disable_attack[32];
bool disable_altattack[32];
bool disable_walk[32];
int sf_sv_player_allow_attack(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Allow/disallow this player to use primary attack\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> 1 = allow , 0 = dont allow\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_allow_attack -h\n");
		return;
	}
	int who = atoi(orig_Cmd_Argv(1));
	int allow = atoi(orig_Cmd_Argv(2));
	if ( allow ) {
		disable_attack[who] = false;
	} else {
		disable_attack[who] = true;
	}
	
}

int sf_sv_player_allow_altattack(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Allow/disallow this player to use secondary attack\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> 1 = allow , 0 = dont allow\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_allow_altattack -h\n");
		return;
	}
	int who = atoi(orig_Cmd_Argv(1));
	int allow = atoi(orig_Cmd_Argv(2));
	if ( allow ) {
		disable_altattack[who] = false;
	} else {
		disable_altattack[who] = true;
	}
}

int sf_sv_player_allow_walk(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Allow/disallow a player to use walk\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> 1 = allow , 0 = dont allow\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_player_allow_walk -h\n");
		return;
	}
	int who = atoi(orig_Cmd_Argv(1));
	int allow = atoi(orig_Cmd_Argv(2));
	if ( allow ) {
		disable_walk[who] = false;
	} else {
		disable_walk[who] = true;
	}
}

/*
enum EndCondition
{
	Loop,
	Hold, // hold at end of seq
	BackAndForth,
	HoldFrame, // hold at PlayPos
	EndMarker //do not use
};

Restart - If animation is same as one playing, dont do anything.
EndCondition - Numbers higher than HoldFrame repeat but apply to skins forceful
*/
int sf_sv_player_anim(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
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
	if ( c != 7 ) {
		orig_Com_Printf("sf_sv_player_anim -h\n");
		return;
	}
	unsigned int slot = atoi(orig_Cmd_Argv(1));
	edict_t* ent = get_ent_from_player_slot(slot);
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}

	char * animName = orig_Cmd_Argv(2);
	float startPos = atof(orig_Cmd_Argv(3));
	int restart = atoi(orig_Cmd_Argv(4));
	int loop = atoi(orig_Cmd_Argv(5));
	int match = atoi(orig_Cmd_Argv(6));
	int reverse = atoi(orig_Cmd_Argv(7));
	clientinst = (unsigned int)(ent->ghoulInst);
	if ( clientinst ) {
		GhoulGetObject();
		GhoulID seq = GhoulFindSequence(animName);
		if ( !seq) {
			orig_Com_Printf("Cant find sequence\n");
			return;
		}
	 
		// GhoulID Seq,float Now,float PlayPos,bool Restart,IGhoulInst::EndCondition ec, bool MatchCurrentPos, bool reverseAnim
		GhoulPlay(seq,*(float*)0x5015CCDC,startPos,restart,loop,match,reverse);
	}
}


int sf_sv_ent_anim(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Play an animation for an entity\n"
			"----------------------------\n"
			"arg1 -> playerslot\n"
			"arg2 -> animation name\n"
			"arg3 -> startPosition [float]\n"
			"arg4 -> interrupt current [int]\n"
			"arg5 -> should it loop [int]\n"
			"arg6 -> match, no idea[int]\n"
			"arg7 -> reverse, play in reverse[int]\n"
		);
		return;
	}
	if ( c != 7 ) {
		orig_Com_Printf("sf_sv_ent_anim -h\n");
		return;
	}
	edict_t* ent = atoi(orig_Cmd_Argv(1));
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}

	char * animName = orig_Cmd_Argv(2);
	float startPos = atof(orig_Cmd_Argv(3));
	int restart = atoi(orig_Cmd_Argv(4));
	int loop = atoi(orig_Cmd_Argv(5));
	int match = atoi(orig_Cmd_Argv(6));
	int reverse = atoi(orig_Cmd_Argv(7));
	clientinst = (unsigned int)(ent->ghoulInst);
	if ( clientinst ) {
		GhoulGetObject();
		GhoulID seq = GhoulFindSequence(animName);
		if ( !seq) {
			orig_Com_Printf("Cant find sequence\n");
			return;
		}
		// IGhoulInst::EndCondition::Hold
		// GhoulID Seq,float Now,float PlayPos,bool Restart,IGhoulInst::EndCondition ec, bool MatchCurrentPos, bool reverseAnim
		GhoulPlay(seq,*(float*)0x5015CCDC,startPos,restart,loop,match,reverse);
	}
}



int sf_sv_ent_model(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Apply a model to an entity\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> dir\n"
			"arg3 -> modelname\n"
		);
		return;
	}
	if ( c != 3 ) {
		orig_Com_Printf("sf_sv_ent_model -h\n");
		return;
	}
	edict_t* ent = atoi(orig_Cmd_Argv(1));
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}

	char * dir = orig_Cmd_Argv(2);
	char * modelname = orig_Cmd_Argv(3);
	// void SimpleModelInit2(edict_t *ent, modelSpawnData_t *modelData,char *skinname,char *partname)

	// ghoul/sofree/cube_medium
	modelSpawnData_t mdata =
	{
		.dir = dir,//orig_CopyString(dir),
		.file = modelname,//orig_CopyString(modelname),
		.surfaceType = SURF_WOOD_DBROWN,
		.material = MAT_WOOD_DBROWN,
		.health = 500,
		.solid = SOLID_BBOX,
		.materialfile = NULL,
		.debrisCnt = 0,
		.debrisScale = DEBRIS_NONE,
		.objBreakData = NULL,
	};

	// modelSpawnData_t * mdata = malloc(sizeof(modelSpawnData_t));
	// mdata->dir = dir;//orig_CopyString(dir);
	// mdata->file = modelname;orig_CopyString(modelname);
	// mdata->surfaceType = SURF_WOOD_DBROWN;
	// mdata->material = MAT_WOOD_DBROWN;
	// mdata->health = 500;
	// mdata->solid = SOLID_TRIGGER;
	// mdata->materialfile = NULL;
	// mdata->debrisCnt = 0;
	// mdata->debrisScale = DEBRIS_NONE;
	// mdata->objBreakData = NULL;

	// sets movetype to MOVETYPE_DAN aka 10
	// sets ->movetype ->die ->touch ->clipmask ->takedamage ->mass
	orig_SimpleModelInit2(ent,&mdata,NULL,NULL);
}

/*
Order of matrix
Scale
Rotate
Translate
*/
int sf_sv_ghoul_scale(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Scale the size of the entity model\n"
			"NB. Order of ghoul editting matters. Scale affects translation units\n"
			"Translation affects point of rotation\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> scale [float]\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_ghoul_scale -h\n");
		return;
	}
	edict_t* ent = atoi(orig_Cmd_Argv(1));
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	orig_SimpleModelScale(ent,atof(orig_Cmd_Argv(2)));
}
int sf_sv_ent_bolt(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Bolt another ghoul model to the current ghoul\n"
			"----------------------------\n"
			"arg1 -> enthandle\n"
			"arg2 -> scale [float]\n"
		);
		return;
	}
	if ( c != 6 ) {
		orig_Com_Printf("sf_sv_ent_bolt -h\n");
		return;
	}
	edict_t* ent = atoi(orig_Cmd_Argv(1));
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}

	char * dir = orig_Cmd_Argv(2);
	char * file = orig_Cmd_Argv(3);
	char * bolt_from = orig_Cmd_Argv(4);
	char * bolt_to = orig_Cmd_Argv(5);
	float scale = atof(orig_Cmd_Argv(6));

	// set clientinst
	clientinst = (unsigned int)(ent->ghoulInst);
	if ( clientinst	)
	{
		GhoulGetObject();
		ggObjC * MyGhoulObj = GhoulFindObjectSmall((IGhoulObj*)objinst);
		ggOinstC* myInstance = orig_FindOInst(MyGhoulObj,(IGhoulInst*)clientinst);

		// edict_t &monster
		// char *myBolt -- where to bolt it
		// char *itemClass -- directory
		// char *itemSeq -- ghb file or ghl file
		// char *itemBolt -- its bolt location
		// ggOinstC *myInstance
		// char *itemSkinName=NULL -- if it has an alternate skin used
		// float scale = 1.0
		orig_AddBoltedItem(ent->client->body,*ent, bolt_from, dir, file, bolt_to, myInstance, NULL, scale);
	}
}
/*
	p_body.c
	/ add a flag to the main player - Jake
	void PB_AddFlag(edict_t *ent, char *FlagSkinName, char* FlagGhoulFile)
	{
		// now bolt on a Ghoul object of the flag to the player 
		ggOinstC* myInstance;
		ggObjC* MyGhoulObj = game_ghoul.FindObject(ent->ghoulInst->GetGhoulObject());
		body_c*	body = ent->client->body;
		// find the Game Ghoul Instance of the Ghoul object hanging off my player
		myInstance = MyGhoulObj->FindOInst(ent->ghoulInst);
		body->AddBoltedItem(*ent, "abolt_hip_r", "items/ctf_flag", FlagGhoulFile, "to_abolt_hip_r", myInstance, FlagSkinName, 1.0);
	}


	void PB_RemoveFlag(edict_t *ent)
	{
		ggOinstC	*MyGhoulInst=game_ghoul.FindOInst(ent->ghoulInst);
		GhoulID		theFlag;

		if (theFlag=ent->ghoulInst->GetGhoulObject()->FindPart("abolt_hip_r"))
		{
			MyGhoulInst->RemoveBolt(theFlag);
		}
	}
*/



int sf_sv_ent_paint(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
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
	if ( c != 5 ) {
		orig_Com_Printf("sf_sv_ent_paint -h\n");
		return;
	}
	edict_t* ent = atoi(orig_Cmd_Argv(1));

	float r = atof(orig_Cmd_Argv(2));
	float g = atof(orig_Cmd_Argv(3));
	float b = atof(orig_Cmd_Argv(4));
	float a = atof(orig_Cmd_Argv(5));
	
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}
	clientinst=(unsigned int*)ent->ghoulInst;
	if ( !clientinst ) {
		orig_Com_Printf("Ent doesn't have a ghoul model\n");
	}
	GhoulSetTintOnAll(r,g,b,a);
	
}


int sf_sv_player_pos(lua_State * L)
{
	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Gets the co-ordinates of the player and stores them in cvars\n"
	// 		"3 cvars will be created based on the prefix you supply\n"
	// 		"eg. sp_sv_player_pos ~org 5\n"
	// 		"Will give me ~org_1 ~org_2 ~org_3 to use with data in them\n"
	// 		"The 5 in the example represents player slot 5\n"
	// 		"----------------------------\n"
	// 		"arg1 -> cvarname you want to use for storing _1 _2 _3 , advisable to parse ~local varaible\n"
	// 		"arg2 -> valid slot id\n"
	// 	);
	// 	return;
	// }
	// if ( c != 2 ) {
	// 	orig_Com_Printf("sf_sv_player_pos -h\n");
	// 	return;
	// }
	unsigned int slot = lua_tointeger(L,-1);
	edict_t* ent = get_ent_from_player_slot(slot);
	if ( !ent ) {
		orig_Com_Printf("Invalid Ent\n");
		return;
	}

	lua_newtable(L);

	lua_pushstring(L,"x");
	lua_pushnumber(L,ent->s.origin[0]);
	lua_settable(L,-3);
	
	lua_pushstring(L,"y");
	lua_pushnumber(L,ent->s.origin[2]);
	lua_settable(L,-3);
	
	lua_pushstring(L,"z");
	lua_pushnumber(L,ent->s.origin[1]);
	lua_settable(L,-3);

	return 1;
}


int sf_sv_effect_endpos(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Call this just before you spawn or exec\n"
			"Set an end position for a line effect environ_effect entity\n"
			"eg. sp_sv_effect_endpos #~entval ~org\n"
			"Will give me ~org_1 ~org_2 ~org_3 to use with data in them\n"
			"----------------------------\n"
			"arg1 -> cvarname which holds endpos vector eg. v_1 v_2 v_3 cvar=v\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_effect_endpos -h\n");
		return;
	}
	char * origin = orig_Cmd_Argv(1);

	vec3_t vorigin;
	readCvarAsVector(origin,vorigin);

	// flags
	*(int*)0x5015C51C = *(int*)0x5015C51C | EFF_POS2;
	// set global pos2 values
	// call CFXSender:Exec
	*(float*)0x5015C524 = vorigin[0];
	*(float*)0x5015C528 = vorigin[1];
	*(float*)0x5015C52C = vorigin[2];

}


int sf_sv_effect_start(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Run an effect at pos\n"
			"eg. sp_sv_effect_start environ/tripbeam ~org\n"
			"----------------------------\n"\
			"arg1 -> path+filename of effect relative to effects dir\n"
			"arg2 -> cvarname which holds startpos vector eg. v_1 v_2 v_3 cvar=v\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_effect_start -h\n");
		return;
	}

	char * origin = orig_Cmd_Argv(2);

	vec3_t vorigin;
	readCvarAsVector(origin,vorigin);

	// fetching index from configstring.
	int index = orig_SV_FindIndex(orig_Cmd_Argv(1), CS_EFFECTS, MAX_EFPACKS, 0,"effect");
	if ( index == 0 ) {
		orig_Com_Error(ERR_FATAL,"sf_sv_effect_start: the effect file %s is not registered\n",orig_Cmd_Argv(1));
	}
	static (__thiscall *fxRunner_exec)(void* self,int effectID, vec3_t pos, multicast_t castType, edict_t *ignoreClient) = 0x500852E0;
	// fxRunner.exec(index, vorigin);
	fxRunner_exec((void*)0x5015C518,index,vorigin,MULTICAST_PHS,0);
}


int sf_sv_player_effect(lua_State * L)
{
	//orig_FX_HandleDMMuzzleFlash();
}

int sf_sv_mem_read_int(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Read an integer in memory at offset\n"
			"----------------------------\n"\
			"arg1 -> outcvar to store the integer\n"
			"arg2 -> memory offset to read from\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_mem_read_int -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if ( offset ){
		int value = stget(offset,0);

		edict_t * ent = (edict_t*)(offset - 120);
		cvar_t * out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1),"",0,NULL);
		setCvarInt(out_cvar,value);
	}
}
int sf_sv_mem_read_short(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Read an short integer in memory at offset\n"
				"----------------------------\n"\
				"arg1 -> outcvar to store the short integer\n"
				"arg2 -> memory offset to read from\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_read_short -h\n");
			return;
		}

	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if ( offset ){
		unsigned short value = stget(offset,0);

		cvar_t * out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1),"",0,NULL);

		out_cvar->modified = true;
		orig_Z_Free(out_cvar->string);
		char shortstring[64];
		
		sprintf(shortstring,"%hd",value);
		out_cvar->string = orig_CopyString(shortstring);

		out_cvar->value = (float)value;
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
int sf_sv_mem_read_char(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Read a byte in memory at offset\n"
				"----------------------------\n"\
				"arg1 -> outcvar to store the byte\n"
				"arg2 -> memory offset to read from\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_read_char -h\n");
			return;
		}
	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if ( offset ){
		unsigned char value = stget(offset,0);

		cvar_t * out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1),"",0,NULL);
		out_cvar->modified = true;
		orig_Z_Free(out_cvar->string);

		char charstring[64];
		sprintf(charstring,"%c",value);
		out_cvar->string = orig_CopyString(charstring);
		out_cvar->value = atof(out_cvar->string);
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

int sf_sv_mem_read_float(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Read a float in memory at offset\n"
				"----------------------------\n"\
				"arg1 -> outcvar to store the float\n"
				"arg2 -> memory offset to read from\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_read_float -h\n");
			return;
		}
	int offset = atoi(orig_Cmd_Argv(2));
	if ( offset ){
		cvar_t * out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1),"",0,NULL);
		setCvarFloat(out_cvar,*(float*)(offset));
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
int sf_sv_mem_read_string(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Read a string in memory at offset\n"
				"----------------------------\n"\
				"arg1 -> outcvar to store the string\n"
				"arg2 -> memory offset to read from\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_read_string -h\n");
			return;
		}
	char * offset = atoi(orig_Cmd_Argv(2));
	if ( offset ){
		cvar_t * out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1),"",0,NULL);
		out_cvar->modified = true;
		orig_Z_Free(out_cvar->string);

		
		out_cvar->string = orig_CopyString(offset);
		out_cvar->value = atof(offset);
	}

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}



int sf_sv_mem_write_int(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Write an integer to memory at offset\n"
				"----------------------------\n"\
				"arg1 -> memory offset to write to\n"
				"arg2 -> integer to write\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_write_int -h\n");
			return;
		}
	char * offset = atoi(orig_Cmd_Argv(1));
	if ( offset ){
		*(int*)offset = atoi(orig_Cmd_Argv(2));
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
int sf_sv_mem_write_short(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Write a short integer to memory at offset\n"
				"----------------------------\n"\
				"arg1 -> memory offset to write to\n"
				"arg2 -> short integer to write\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_write_short -h\n");
			return;
		}
	char * offset = atoi(orig_Cmd_Argv(1));
	if ( offset ){
		*(short int*)offset = atoi(orig_Cmd_Argv(2)) & 0xFFFF;
	}

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
int sf_sv_mem_write_char(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Write a byte to memory at offset\n"
				"----------------------------\n"\
				"arg1 -> memory offset to write to\n"
				"arg2 -> byte to write\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_write_char -h\n");
			return;
		}

	char * offset = atoi(orig_Cmd_Argv(1));
	if ( offset ){
		*(char*)offset = orig_Cmd_Argv(2)[0];
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
int sf_sv_mem_write_float(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Write a float to memory at offset\n"
				"----------------------------\n"\
				"arg1 -> memory offset to write to\n"
				"arg2 -> float to write\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_write_float -h\n");
			return;
		}
	char * offset = atoi(orig_Cmd_Argv(1));
	if ( offset ){
		*(float*)offset = atof(orig_Cmd_Argv(2));
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
int sf_sv_mem_write_string(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Write a string to memory at offset\n"
				"----------------------------\n"\
				"arg1 -> memory offset to write to\n"
				"arg2 -> string to write\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_mem_write_string -h\n");
			return;
		}

	char * offset = atoi(orig_Cmd_Argv(1));
	if ( offset ){
		*(char**)offset = orig_CopyString(orig_Cmd_Argv(2));
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

//Write_offset
//jmpTo_offset
int sf_sv_jmp_at(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"Write a jmp instruction to memory at offset\n"
				"You have to do the relative math to make this work\n"
				"(to - from) - 5;\n"
				"----------------------------\n"\
				"arg1 -> memory offset to write to , location of 0xe9\n"
				"arg2 -> jmp destination\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_jmp_at -h\n");
			return;
		}

	void * offset = atoi(orig_Cmd_Argv(1));
	if ( offset ){
		unsigned int jmpTo_offset = atoi(orig_Cmd_Argv(2));
		DWORD dwProt = NULL;
		// Enable writing to original
		VirtualProtect(offset, 5, PAGE_READWRITE, &dwProt);
		*(unsigned char *)offset = 0xE9;
		*(unsigned int*)(offset+1) = jmpTo_offset;

		// Reset original mem flags
		VirtualProtect(offset, 5, dwProt, new DWORD);
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


//func_offset
//sofplus_function name to call
//num_arguments
//calling_convention
int sf_sv_hook_at(lua_State * L)
{
	try{
		int c = orig_Cmd_Argc() - 1;
		if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
			orig_Com_Printf(
				"This doesnt work , dont use this\n"
			);
			return;
		}
		if ( c != 2 ) {
			orig_Com_Printf("sf_sv_hook_at -h\n");
			return;
		}
	void * offset = atoi(orig_Cmd_Argv(1));
	if ( offset ){
		char * cc = orig_Cmd_Argv(4);
		if ( !strcmp(cc,"cdecl") ) {

		}
		//orig_T_Damage = (T_Damage_type) DetourCreate(offset , (LPVOID)&T_Damage, DETOUR_TYPE_JMP,8);
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}



int sf_sv_ent_callback(lua_State * L)
{

	// int c = orig_Cmd_Argc() - 1;
	// if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
	// 	orig_Com_Printf(
	// 		"Attach a sof function to a touch event of an entity\n"
	// 		"Type can be : think/touch/use/pluse/pain/die\n"
	// 		"touch arguments: [2] touched toucher\n"
	// 		"think arguments: [1] thinker\n"
	// 		"use arguments: [2] ent_used activator\n"
	// 		"pluse (player_use) arguments: [2] ent_used activator\n"
	// 		"pain arguments: [2] inflicted inflictor\n"
	// 		"die arguments: [3] died inflictor attacker\n"
	// 		"----------------------------\n"
	// 		"arg1 -> entity handle\n"
	// 		"arg2 -> type of callback\n"
	// 		"arg3 -> sofplus function name\n"
	// 	);
	// 	return;
	// }
	// if ( c != 3 ) {
	// 	orig_Com_Printf("sf_sv_ent_callback -h\n");
	// 	return;
	// }

	
	
	char *f = lua_tostring(L,-1);
	char *a2 = lua_tostring(L,-1);
	edict_t * ent = atoi(lua_tostring(L,-1));
	if ( !strcmp(a2,"think") ) {
		event_think_s	*z = malloc(sizeof(event_think_s));

		z->next = think_events.next;
		z->prev = &think_events;
		think_events.next->prev = z;
		think_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->think = &ThinkEventCallback;
	} else if ( !strcmp(a2,"touch") ) {
		event_touch_s	*z = malloc(sizeof(event_touch_s));

		z->next = touch_events.next;
		z->prev = &touch_events;
		touch_events.next->prev = z;
		touch_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->touch = &TouchEventCallback;
	} else if ( !strcmp(a2,"use") ) {
		event_use_s	*z = malloc(sizeof(event_use_s));

		z->next = use_events.next;
		z->prev = &use_events;
		use_events.next->prev = z;
		use_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->use = &UseEventCallback;
	} else if ( !strcmp(a2,"pluse") ) {

		event_pluse_s	*z, *next;
		for (z=pluse_events.next ; z != &pluse_events ; z=next)
		{
			next = z->next;
			if (z->ent == ent) {
				z->ent = ent;
				sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
				ent->plUse = &PlUseEventCallback;
				return;
			}
		}

		z = malloc(sizeof(event_pluse_s));

		z->next = pluse_events.next;
		z->prev = &pluse_events;
		pluse_events.next->prev = z;
		pluse_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->plUse = &PlUseEventCallback;
	} else if ( !strcmp(a2,"pain") ) {
		orig_Com_Printf("registering paincallback!\n");
		event_pain_s	*z = malloc(sizeof(event_pain_s));

		z->next = pain_events.next;
		z->prev = &pain_events;
		pain_events.next->prev = z;
		pain_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->pain = &PainEventCallback;
	} else if ( !strcmp(a2,"die") ) {
		event_die_s	*z = malloc(sizeof(event_die_s));

		z->next = die_events.next;
		z->prev = &die_events;
		die_events.next->prev = z;
		die_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->die = &DieCallback;
	}


	
}
/*
void		(*think)(edict_t *self);
void		(*blocked)(edict_t *self, edict_t *other);	//move to moveinfo?
void		(*touch)(edict_t *self, edict_t *other, cplane_t *plane, struct mtexinfo_s *surf);
void		(*use)(edict_t *self, edict_t *other, edict_t *activator);
void		(*plUse)(edict_t *self, edict_t *other, edict_t *activator);
void		(*pain)(edict_t *self, edict_t *other, float kick, int damage, vec3_t wherehit);
void		(*die)(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point);
*/

event_think_s think_events;
void ThinkEventCallback(edict_t * thinker)
{
	try{
	event_think_s	*z, *next;
	for (z=think_events.next ; z != &think_events ; z=next)
	{
		next = z->next;
		if (z->ent == thinker) {
			char line[256];
			strcpy(line,z->sofplusfunc);
			//remove newline
			line[strlen(line)-1] = 0x00;
			sprintf(line,"%s %i\n",line,thinker);
			orig_Cbuf_AddText(line);
			// orig_Cmd_ExecuteString(line);
		}
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
event_touch_s touch_events;
void TouchEventCallback(edict_t *touched, edict_t *toucher, cplane_t *plane, struct mtexinfo_s *surf)
{
	// orig_Com_Printf("lol!\n");
	try{
	event_touch_s	*z, *next;
	for (z=touch_events.next ; z != &touch_events ; z=next)
	{
		next = z->next;
		if (z->ent == touched) {
			//play with z here
			char line[256];
			strcpy(line,z->sofplusfunc);
			//remove newline
			line[strlen(line)-1] = 0x00;
			sprintf(line,"%s %i %i\n",line,touched,toucher);
			orig_Cbuf_AddText(line);
			// orig_Cmd_ExecuteString("echo plowy dende 123 456\n");
		}
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
event_use_s use_events;
void UseEventCallback(edict_t *thing_used, edict_t *initiator, edict_t *activator)
{
	try{
	event_use_s	*z, *next;
	for (z=use_events.next ; z != &use_events ; z=next)
	{
		next = z->next;
		if (z->ent == thing_used) {
			char line[256];
			strcpy(line,z->sofplusfunc);
			//remove newline
			line[strlen(line)-1] = 0x00;
			sprintf(line,"%s %i %i\n",line,thing_used,initiator);
			orig_Cbuf_AddText(line);
			// orig_Cmd_ExecuteString(line);

		}
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
event_pluse_s pluse_events;
void PlUseEventCallback(edict_t *thing_used, edict_t *initiator, edict_t *activator)
{
	try{
	event_pluse_s	*z, *next;
	for (z=pluse_events.next ; z != &pluse_events ; z=next)
	{
		next = z->next;
		if (z->ent == thing_used) {
			char line[256];
			strcpy(line,z->sofplusfunc);
			//remove newline
			line[strlen(line)-1] = 0x00;
			sprintf(line,"%s %i %i\n",line,thing_used,initiator);
			orig_Cbuf_AddText(line);
			// orig_Cmd_ExecuteString(line);
		}
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
event_pain_s pain_events;
void PainEventCallback(edict_t *inflicted, edict_t *inflictor, float kick, int damage, vec3_t wherehit)
{
	try{
	// orig_Com_Printf("pain callback called\n");
	event_pain_s	*z, *next;
	for (z=pain_events.next ; z != &pain_events ; z=next)
	{
		next = z->next;
		if (z->ent == inflicted) {
			char line[256];
			strcpy(line,z->sofplusfunc);
			//remove newline
			line[strlen(line)-1] = 0x00;
			sprintf(line,"%s %i %i\n",line,inflicted,inflictor);
			orig_Cbuf_AddText(line);
			// orig_Cmd_ExecuteString(line);
		}
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
/*
inflictor	entity that is causing the damage, e.g. rocket.
attacker	entity that caused the inflictor to damage, e.g. player.
*/
event_die_s die_events;
void DieCallback(edict_t *killed, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	try{
	event_die_s	*z, *next;
	for (z=die_events.next ; z != &die_events ; z=next)
	{
		next = z->next;
		if (z->ent == killed) {
			char line[256];
			strcpy(line,z->sofplusfunc);
			//remove newline
			line[strlen(line)-1] = 0x00;
			sprintf(line,"%s %i %i %i\n",line,killed,inflictor,attacker);
			orig_Cbuf_AddText(line);
			// orig_Cmd_ExecuteString(line);
		}
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

int sf_sv_math_sin(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Your average math sin function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially angle, will sin the angle and store\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_math_sin -h\n");
		return;
	}
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		cvar_t * lol = orig_Cvar_Get(orig_Cmd_Argv(1),"0",0,NULL);
		setCvarFloat(lol,sinf(M_PI*lol->value/180.0f));
	}else
	{
		orig_Com_Printf(P_RED"Please supply 1 argument {cvar}\n");
	}
}
int sf_sv_math_asin(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Your average math asin function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially number, will inverse sin the number and store\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_math_asin -h\n");
		return;
	}
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		cvar_t * lol = orig_Cvar_Get(orig_Cmd_Argv(1),"0",0,NULL);
		setCvarFloat(lol,(180.0f/M_PI)*asinf(lol->value));
	}else
	{
		orig_Com_Printf(P_RED"Please supply 1 argument {cvar}\n");
	}
}
int sf_sv_math_cos(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Your average math cos function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially angle, will cos the angle and store\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_math_cos -h\n");
		return;
	}
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		cvar_t * lol = orig_Cvar_Get(orig_Cmd_Argv(1),"0",0,NULL);
		setCvarFloat(lol,cosf(M_PI*lol->value/180.0f));
	}else
	{
		orig_Com_Printf(P_RED"Please supply 1 argument {cvar}\n");
	}
}
int sf_sv_math_acos(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Your average math acos function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially number, will inverse cos the number and store\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_math_acos -h\n");
		return;
	}
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		cvar_t * lol = orig_Cvar_Get(orig_Cmd_Argv(1),"0",0,NULL);
		setCvarFloat(lol,(180.0f/M_PI)*acosf(lol->value));
	}else
	{
		orig_Com_Printf(P_RED"Please supply 1 argument {cvar}\n");
	}
}
int sf_sv_math_tan(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Your average math tan function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially angle, will tan the angle and store\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_math_tan -h\n");
		return;
	}
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		cvar_t * lol = orig_Cvar_Get(orig_Cmd_Argv(1),"0",0,NULL);
		setCvarFloat(lol,tanf(M_PI*lol->value/180.0f));
	}else
	{
		orig_Com_Printf(P_RED"Please supply 1 argument {cvar}\n");
	}
}
int sf_sv_math_atan(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Your average math atan function\n"
			"----------------------------\n"
			"arg1 -> cvarinout initially number, will inverse tan the number and store\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_math_atan -h\n");
		return;
	}
	int argc = orig_Cmd_Argc();
	if ( argc == 2 ) {
		cvar_t * lol = orig_Cvar_Get(orig_Cmd_Argv(1),"0",0,NULL);
		setCvarFloat(lol,(180.0f/M_PI)*atanf(lol->value));
	}else
	{
		orig_Com_Printf(P_RED"Please supply 1 argument {cvar}\n");
	}
}


int sf_sv_math_or(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Unsigned OR function\n"
			"----------------------------\n"
			"arg1 -> inoutcvar value of first number\n"
			"arg2 -> innumber OR with what?\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_math_or -h\n");
		return;
	}

	cvar_t * inout = findCvar(orig_Cmd_Argv(1));
	if (!inout) {
		orig_Com_Printf("error in sf_sv_math_or , supplied cvar does not exist\n");
		return;
	}

	unsigned int num1 = atoi(inout->string);
	unsigned int num2 = atoi(orig_Cmd_Argv(2));

	setCvarUnsignedInt(inout,num1 | num2);

}

int sf_sv_math_and(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Unsigned AND function\n"
			"----------------------------\n"
			"arg1 -> inoutcvar value of first number\n"
			"arg2 -> innumber AND with what?\n"
		);
		return;
	}
	if ( c != 2 ) {
		orig_Com_Printf("sf_sv_math_and -h\n");
		return;
	}

	cvar_t * inout = findCvar(orig_Cmd_Argv(1));
	if (!inout) {
		orig_Com_Printf("error in sf_sv_math_and , supplied cvar does not exist\n");
		return;
	}

	unsigned int num1 = atoi(inout->string);
	unsigned int num2 = atoi(orig_Cmd_Argv(2));

	setCvarUnsignedInt(inout,num1 & num2);

}

int sf_sv_math_not(lua_State * L)
{
	int c = orig_Cmd_Argc() - 1;
	if ( !strcmp(orig_Cmd_Argv(1),"-h" ) ) {
		orig_Com_Printf(
			"Unsigned NOT function\n"
			"----------------------------\n"
			"arg1 -> inoutcvar value of the number you want NOTTED\n"
		);
		return;
	}
	if ( c != 1 ) {
		orig_Com_Printf("sf_sv_math_not -h\n");
		return;
	}

	cvar_t * inout = findCvar(orig_Cmd_Argv(1));
	if (!inout) {
		orig_Com_Printf("error in sf_sv_math_not , supplied cvar does not exist\n");
		return;
	}

	unsigned int num1 = atoi(inout->string);

	setCvarUnsignedInt(inout,~num1);

}