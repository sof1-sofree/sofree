#include <windows.h>
#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "sofreeS.h"


/*
	Ah callback events relating to individual clients instead of the server its self.
*/
void applyClientHooks(void)
{

	//ClientBegin
	// DetourRemove(orig_ClientBegin);
	// orig_ClientBegin = (ClientBegin_type) DetourCreate((void*)0x500F4070,(void*)&my_ClientBegin,DETOUR_TYPE_JMP, 8);
	// DetourRemove(orig_ClientConnect);
	// orig_ClientConnect = (ClientConnect_type) DetourCreate((void*)0x500F4DE0,(void*)&my_ClientConnect,DETOUR_TYPE_JMP, 8);
	DetourRemove(orig_PutClientInServer);
	orig_PutClientInServer = (PutClientInServer_type) DetourCreate((LPVOID)0x500F38A0,(LPVOID)my_PutClientInServer,DETOUR_TYPE_JMP,6);

	// DetourRemove(orig_SV_New_f);
	// orig_SV_New_f = (SV_New_f_type)DetourCreate((LPVOID)0x20062780 , (LPVOID)my_SV_New_f,DETOUR_TYPE_JMP, 5);

	// DetourRemove(orig_SV_Configstrings_f);
	// orig_SV_Configstrings_f = (SV_Configstrings_f_type) DetourCreate((LPVOID)0x200629E0 , (LPVOID) my_SV_Configstrings_f, DETOUR_TYPE_JMP , 5 );

	// DetourRemove(orig_SVC_DirectConnect);
	// orig_SVC_DirectConnect = (SVC_DirectConnect_type) DetourCreate((LPVOID)0x2005E5C0 , (LPVOID)my_SVC_DirectConnect,DETOUR_TYPE_JMP,5);

	
	// Used by minecraft scoreboardmenu
	DetourRemove(orig_ClientThink);
	orig_ClientThink = (ClientThink_type)DetourCreate((LPVOID)0x500F53A0,(LPVOID)&my_ClientThink,DETOUR_TYPE_JMP,6);
}



/*
ClientBegin
called by SoF.exe SV_Begin_f
-> gamex86.dll export ge->ClientBegin();
client is ready to join server fully
"cmd begin" sent from server to client
*/


/*
called by SoF.exe SVC_DirectConnect
-> gamex86.dll export ge->ClientConnect();
sets userinfo rejmsg, denies connections
*/
edict_t * saved_ent;
qboolean my_ClientConnect (edict_t *ent, char *userinfo)
{
	saved_ent = ent;
	int p = get_player_slot_from_ent(ent);
	/*
	char* http = orig_Info_ValueForKey(userinfo,"http");
	//they dont have http usrinfo valu
	if (strcmp(http,"true")) {
		orig_Info_SetValueForKey(userinfo, "rejmsg", "\x07" "Download my http hax.");
		return false;
	}*/
	int ret = orig_ClientConnect(ent,userinfo);

	//he is allowed to enter
	if ( ret ) {

	}
	return ret;
}

/*
if you call code AFTER This func is called, you have network init setup can call net funcs.
*/
void my_SVC_DirectConnect(void)
{
	saved_ent = NULL;
	orig_SVC_DirectConnect();
	if ( saved_ent ) {
		//we know that it was a new client accepted

		
	}
}


/*
WinMain
	Qcommon_Frame
		SV_Frame
			SV_RunGameFrame
				ge->G_RunFrame
				-Advances the world by 0.1 seconds
					ClientBeginServerFrame 
					-Called for each connected client, once per frame
					-Checks if player is dead
						respawn
							PutClientInServer
							-Also called by ClientBeginDeathmatch which is called by ClientBegin//SV_Begin_f

*/

/*
	Ctrl's client_spawn event is just _AFTER_ this Function
	PutClientInServer adjusts solid variable for entities based on whether they are spec or not
	It also sets clipmask and movetype : caution.
*/
void my_PutClientInServer(edict_t *ent)
{
	orig_PutClientInServer(ent);
}


/*
	ClientThink called by SV_ClientThink called by SV_ExecuteClientMessage in sv_user.c
	ClientThink Hook
	I want to intercept usercmd_t data to find out if client
	is pressing forward key or backward key.
*/
void my_ClientThink(edict_t *player_ent, usercmd_t *ucmd)
{
	int slot = get_player_slot_from_ent(player_ent);
	gclient_t * client = player_ent->client;

	// client->buttons = last frame
	// ucmd->buttons = this frame
	byte prevbuttons = prev_buttons[slot];

	// faster method TODO: replace ifs
	// byte TurnOffOnesWhichWEreOnPreviouslyLeavOnlyOnesWhichWereOffPreviouslyRemainThusNewlyPressedButtonsFilter = ucmd->buttons & (~prevbuttons)

	
	// release
	if (  (prevbuttons & BUTTON_USE)  && !(ucmd->buttons & BUTTON_USE) ) {
		if ( _sf_sv_on_use_release->string && _sf_sv_on_use_release->string[0])
			makeTheStringElips(" %i\n",_sf_sv_on_use_release, slot);
	}

	if ( (prevbuttons & BUTTON_ATTACK) && !(ucmd->buttons & BUTTON_ATTACK)  ) {
		if ( _sf_sv_on_attack_release->string && _sf_sv_on_attack_release->string[0] )
			makeTheStringElips(" %i\n",_sf_sv_on_attack_release, slot);

		if ( _sf_sv_debug_triggers->value ) {
			intersect(player_ent);
			// orig_Com_Printf("%f %f\n",player_ent->client->v_angle[0],player_ent->client->v_angle[1]);
		}
	}

	short prev = prev_sidemove[slot];
	if ( prev < 0 ) {
		if ( ucmd->sidemove >= 0 ) {
			if ( _sf_sv_on_left_release->string && _sf_sv_on_left_release->string[0] )
				makeTheStringElips(" %i\n",_sf_sv_on_left_release, slot);
		}
	}

	if ( prev > 0 ) {
		if ( ucmd->sidemove <= 0 ) {
			if ( _sf_sv_on_right_release->string && _sf_sv_on_right_release->string[0] )
				makeTheStringElips(" %i\n",_sf_sv_on_right_release, slot);
		}
	}

	// press
	if ( !(prevbuttons & BUTTON_USE) && (ucmd->buttons & BUTTON_USE) ) {
		if ( _sf_sv_on_use_press->string && _sf_sv_on_use_press->string[0] )
			makeTheStringElips(" %i\n",_sf_sv_on_use_press, slot);
	}

	if ( !(prevbuttons & BUTTON_ATTACK) && (ucmd->buttons & BUTTON_ATTACK) ) {
		if ( _sf_sv_on_attack_press->string && _sf_sv_on_attack_press->string[0] )
			makeTheStringElips(" %i\n",_sf_sv_on_attack_press, slot);
	}

	if ( prev >= 0 ) {
		if ( ucmd->sidemove < 0 ) {
			if ( _sf_sv_on_left_press->string && _sf_sv_on_left_press->string[0] )
				makeTheStringElips(" %i\n",_sf_sv_on_left_press, slot);
		}
	}

	if ( prev <= 0 ) {
		if ( ucmd->sidemove > 0 ) {
			if ( _sf_sv_on_right_press->string && _sf_sv_on_right_press->string[0] )
				makeTheStringElips(" %i\n",_sf_sv_on_right_press, slot);
		}
	}

	prev_buttons[slot] = ucmd->buttons;

	// force running
	if ( disable_walk[slot] ) ucmd->buttons |= BUTTON_RUN;

	// intermision
	if ( !(*(unsigned int*)0x5015D1C8) ) {
		if ( disable_attack[slot] ) {
			ucmd->buttons &= (~BUTTON_ATTACK);
			// orig_Com_Printf("Disabling attack for you mofo\n");
			ucmd->fireEvent = 0.0f;
		}
		if ( disable_altattack[slot] ) {
			ucmd->buttons &= (~BUTTON_ALTATTACK);
			ucmd->altfireEvent = 0.0f;
		}
	}
	
	prev_sidemove[slot] = ucmd->sidemove;
	
	// client->oldbuttons is set by clientThink so currently stores lastframe
	orig_ClientThink(player_ent,ucmd);
}


void my_SV_New_f(void)
{
	orig_SV_New_f();

	orig_Com_Printf("Telling him to disconnect\n");
	// attractloop is set here.
	orig_PF_WriteByte((unsigned char)STUFFTEXT);
	orig_PF_WriteString("echo Sofree CLient Control v30424542\ndisconnect\n");
	orig_PF_Unicast(saved_ent,true);
}

void my_SV_Configstrings_f(void)
{
	orig_SV_Configstrings_f();

	if ( atoi(orig_Cmd_Argv(2)) == 0 ) {
		client_t * cl = stget(SV_CLIENT,0);
		edict_t * ent = stget(cl,CLIENT_ENT);
		orig_Com_Printf("Telling him to disconnect\n");
		// attractloop is set here.
		orig_PF_WriteByte((unsigned char)STUFFTEXT);
		orig_PF_WriteString("connect 47.54.100.25:28910\n");
		orig_PF_Unicast(ent,true);
	}
	
}


/*
//Spawn cube here
edict_t * cube = orig_G_Spawn();

vec3_t fwd,vOut;
// orig_AngleVectors(player_ent->s.angles,fwd,NULL,NULL);
orig_AngleVectors(client->ps.viewangles,fwd,NULL,NULL);

vec3_t startorg = { player_ent->s.origin[0],player_ent->s.origin[1],player_ent->s.origin[2] + 30.0f};
//vecC = vecA + scale * vecB
VectorMA(startorg,256.0f,fwd,vOut);
trace_t tr;
// +30.0f - f_crouch

// vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, edict_t *passedict, int contentmask
orig_SV_Trace(startorg, NULL, NULL, vOut, player_ent, MASK_ALL, &tr);

// position it first
cube->s.origin[0] = tr.endpos[0];
cube->s.origin[1] = tr.endpos[1];
cube->s.origin[2] = tr.endpos[2];
SP_pacman(cube);
*/