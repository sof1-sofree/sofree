#include <windows.h>
#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

void Vaccine::applyHooks(void) {

	// DetourRemove(orig_SV_UserinfoChanged);
	// orig_SV_UserinfoChanged = (SV_UserinfoChanged_type)DetourCreate((LPVOID)0x2005F7D0,(LPVOID)&my_SV_UserinfoChanged,DETOUR_TYPE_JMP,10);
}

void my_SV_UserinfoChanged(void * cl)
{

	edict_t * ent  = stget(cl,CLIENT_ENT);
	gclient_t* gc = stget(ent,EDICT_GCLIENT);
	int slot = get_player_slot_from_ent(ent);
	
	char * cl_userinfo = (char*)((unsigned int)cl + CLIENT_USERINFO);
	int team = stget(gc,GCLIENT_TEAM);
	//blue
	if ( team == 1 ) {
		//they trying to change team
		if ( atoi(orig_Info_ValueForKey(cl_userinfo,"team_red_blue")) != 1 ) {
			//client control t_r_b to 1

			//remind them that they cannot change team
			orig_PF_WriteByte((unsigned char)STUFFTEXT);
			orig_PF_WriteString("team_red_blue 1\n");
			orig_PF_Unicast(ent,true);
		}
		
	//red
	} else if ( team == 2 ) {
		//they trying to change team
		if ( atoi(orig_Info_ValueForKey(cl_userinfo,"team_red_blue")) != 0 ) {

			//remind them that they cannot change team

			//client control t_r_b to 0
			orig_PF_WriteByte((unsigned char)STUFFTEXT);
			orig_PF_WriteString("team_red_blue 0\n");
			orig_PF_Unicast(ent,true);
		}
	}
	

	//WHY????
	/*
	//undo their attempt to change team

	//override change // force
	char forceTeam[2];
	_itoa(team-1,forceTeam,10);
	orig_Info_SetValueForKey(cl_userinfo,"team_red_blue",forceTeam);	
	
	// orig_Com_Printf("User changed his userinfo\n");
	*/
	orig_SV_UserinfoChanged(cl);

}