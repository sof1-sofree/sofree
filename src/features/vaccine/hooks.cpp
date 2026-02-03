#include "../../../hdr/feature_config.h"

#if FEATURE_VACCINE

#include <windows.h>
#include "../../../hdr/sofheader.h"
#include "../../DetourXS/detourxs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void vaccine_SV_UserinfoChanged(void * cl);

void vaccine_applyHooks(void) {
	DetourRemove(orig_SV_UserinfoChanged);
	orig_SV_UserinfoChanged = (SV_UserinfoChanged_type)DetourCreate((LPVOID)0x2005F7D0,(LPVOID)&vaccine_SV_UserinfoChanged,DETOUR_TYPE_JMP,10);
}

void vaccine_SV_UserinfoChanged(void * cl)
{
	edict_t * ent  = stget(cl,CLIENT_ENT);
	gclient_t* gc = stget(ent,EDICT_GCLIENT);
	int slot = get_player_slot_from_ent(ent);
	
	char * cl_userinfo = (char*)((unsigned int)cl + CLIENT_USERINFO);
	int team = stget(gc,GCLIENT_TEAM);
	if ( team == 1 ) {
		if ( atoi(orig_Info_ValueForKey(cl_userinfo,"team_red_blue")) != 1 ) {
			orig_PF_WriteByte((unsigned char)STUFFTEXT);
			orig_PF_WriteString("team_red_blue 1\n");
			orig_PF_Unicast(ent,true);
		}
	} else if ( team == 2 ) {
		if ( atoi(orig_Info_ValueForKey(cl_userinfo,"team_red_blue")) != 0 ) {
			orig_PF_WriteByte((unsigned char)STUFFTEXT);
			orig_PF_WriteString("team_red_blue 0\n");
			orig_PF_Unicast(ent,true);
		}
	}
	orig_SV_UserinfoChanged(cl);
}

#else

void vaccine_applyHooks(void) {}

#endif

