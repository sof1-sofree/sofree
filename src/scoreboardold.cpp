#include <windows.h>
#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include <stdio.h>
#include <stdlib.h>

#include "sofreeS.h"

#include <string>
#include <map>
using namespace std;

map<string,bool> Scoreboard::geoMap;


//globals
char countryCode[16][64];
const char * Scoreboard::geoSaveFile = "user-server/sofree/sofree_geo.txt";
bool Scoreboard::isMenuOn[16] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
//i wonder if we can get resolution at an earlier point ?


struct scoreSlot
{
	int score;
	int slot;
};

//5015C4D8
void Scoreboard::applyHooks(void) {
	orig_Cmd_Score_f = (Cmd_Score_f_type)DetourCreate((LPVOID)0x500F6710,(LPVOID)&my_Cmd_Score_f,DETOUR_TYPE_JMP,6);
	orig_Com_Printf("Calling scorevboard apply hooks\n");

	adjustPulseRate(1);
}

void Scoreboard::removeHooks(void) {
	orig_Com_Printf("removing previous hooks for scoreboard !!\n");
	DetourRemove(orig_Cmd_Score_f);
	adjustPulseRate(0x1F);
}


void Scoreboard::adjustPulseRate(unsigned char newpulse) {

	DWORD dwProt = NULL;
	char * blehpatch =0x500F9E2F;
	char * pc = blehpatch;
	VirtualProtect(blehpatch, 1, PAGE_READWRITE, &dwProt);
	*(unsigned char*)pc = newpulse;
	VirtualProtect(blehpatch, 1, dwProt, new DWORD);
	
}



int scoreCompare( const void * arg1, const void * arg2) {
	struct scoreSlot *A, *B;
	A = (struct scoreSlot*)arg1;
	B = (struct scoreSlot*)arg2;
	return (B->score - A->score);
}

/*
I want to use cvar checks to _sp_cl_info
and gl_mode
to find out the current resolution of my clients


#_spf_sv_check_slot #_spf_sv_check_id #_spf_sv_check_cvar

*/

/*
Deathmatch Class working
5015C4D8 - REFERENCE OBJECT
05000000 - OBJECT
501291E8 - FUNCTABLE/VTABLE

ECX = OBJECT
CALL FUNCTABLE+FUNCOFFSET

ECX+8 == RULES
*/

void my_Cmd_Score_f (edict_t *ent) {
	// orig_Cmd_Score_f(ent);
	//int player = get_player_slot_from_ent(ent);
	// show_score[player] = !show_score[player];

	//orig_Com_Printf("score toggle!\n");

	Scoreboard::toggleMenu(ent);
}

void Scoreboard::toggleMenu(edict_t * ent)
{
	int p = get_player_slot_from_ent(ent);
	isMenuOn[p] = !isMenuOn[p];
}


/*
	They've connected, show them the scoreboard
*/
void Scoreboard::clientConnect(edict_t *ent) {
	
	int p = get_player_slot_from_ent(ent);

	//initialise their scoreboard to be active and their reso to be empty
	for ( int j = 0; j < 2; j++ ) {
		show_score[p] = true;
		reso2d[p][j] = 0;
	}
	
	client_t * cl = stget(CLIENT_BASE,0) + p*SIZE_OF_CLIENT;
	unsigned int ip = sys_ntohl(stget(cl,CLIENT_NETCHAN_IP));
	char * cc = orig_GeoGetCC(ip);

	char gb[2] = "GB";
	//localhost
	if ( ip == 2130706433) {
		cc = gb;
	}

	
	sprintf(countryCode[p],"pics/sofree/geoflags/%c%c",tolower(cc[0]),tolower(cc[1]));
	char tmp[128];

	sprintf(tmp,"user-server/%s%s",countryCode[p],".m32");
	if( access( tmp, F_OK ) == -1 ) {
		orig_Com_Printf("that file does not exist!\n");
    	// file does NOT exist
		strcpy(countryCode[p],"");
	} else {
		orig_Com_Printf("the geo flag exists!\n");

		char c[3];
		c[2] = 0x00;
		c[0] = countryCode[p][strlen(countryCode[p])-2];
		c[1] = countryCode[p][strlen(countryCode[p])-1];

		if ( Scoreboard::isFlagNew(c) ) {
			orig_Com_Printf("New geoflag !\n");
			Scoreboard::saveNewFlagToFile(c);
		} else {
			//this file will be used to control which m32 files get registered
			orig_Com_Printf("Already discovered this geoflag!\n");
		}

	}

	

	ent->client->showscores = 1;
	Scoreboard::drawMe(ent,NULL,false);

}



//PutClientInServer clears client_t struct which contains showscores, so must hook inner func
//self = 5015c424
void Scoreboard::clientRespawn(edict_t *ent) {
	//force show score when client respawns
	ent->client->showscores = 1;
}

/*
	credit image
	xpos%,ypos%,duration,fadeintime,fadeouttime,red,green,blue,filepath

	//drawing crosshair
	sp_sv_print_sp_client $~slot 44 "50;50;1200;0;0;255;0;0;dmicons/destarget"
*/
void Scoreboard::drawCreditImage(edict_t * ent) {
	//only draw credit image if its 
	
		
	char out[256];
	sprintf(out,"50;50;1200;0;0;255;0;0;dmicons/destarget");
	orig_SP_Print(ent,0x122C,out);	
	
}

void Scoreboard::hideCreditImage(edict_t * ent) {
	
	char out[256];
	sprintf(out,"-50;-50;0.1;0;0;255;0;0;dmicons/destarget");
	orig_SP_Print(ent,0x122C,out);
}


/*-160 + somethingx

-120 + somethingy
*/

//(*SP_Print)(edict_t *ent, unsigned short ID, ...);
void Scoreboard::drawMe (edict_t *ent, edict_t *killer, qboolean log_file)
{

	//clear
	orig_SP_Print(ent,0x122B,"*");

	int sendToSlot = get_player_slot_from_ent(ent);
	int x = reso2d[sendToSlot][0];
	int y = reso2d[sendToSlot][1];
	if ( x == 0 || !show_score[sendToSlot] ) return;
	
	scoreSlot activeSlots[16];

	// sprintf(out,"xv %i yv %i picn %s",160 - x, 120 - y, "pics/console/l_animation ");

	unsigned char out[256];
	out[0] = 0x00;

	unsigned char final[1024];
	final[0] = 0x00;
	edict_t * e = NULL;
	gclient_t * gc = NULL;

	int active = 0;
	for ( int i=0;i<*maxclientss;i++ ) {
		e = get_ent_from_player_slot(i);
		gc = e->client;

		if(!e->inuse)
			continue;
		if (gc->resp.spectator)
			continue;

		//index wont be preserved! cos of sort!
		activeSlots[active].slot = i;

		activeSlots[active].score = gc->resp.score;
		active++;
	}

	qsort((void *)activeSlots, active, sizeof(scoreSlot), scoreCompare);

	int total = active;
	for ( int i=0;i<*maxclientss;i++ ) {
		e = get_ent_from_player_slot(i);
		gc = e->client;
		if(!e->inuse)
			continue;

		if (gc->resp.spectator)
			continue;

		unsigned char * name = gc->pers.netname;
		//orig_Com_Printf("edict is %08X\n name is %s\n",e,name);
		int score = gc->resp.score;
		int ping = gc->ping;

		//600 because seconds into minutes and 0.1's into 1's
		// /10 and /60 == /600
		int time = ((*level_framenum - gc->resp.enterframe)/600);

		int left = 160 - x*0.5;
		int right = 160 + x*0.5;
		int top = 120 - y*0.5;
		int bottom = 120 + y*0.5;
		int midheight = 120;
		int midwidth = 160;

		//search for i
		int j = 0;
		for (  j = 0 ; j < total; j++ ) {
			if ( activeSlots[j].slot == i ) {
				break;
			}
		}
		
		int outx = left;
		int outy = midheight-(total*32*0.5) + 32*(j);
		// orig_Com_Printf("%s ping equal to %i\n",name,ping);

		sprintf(out,"client_sb %d %d %u %d %u %u ",outx,outy,i,score,ping,time);
		strcat(final,out);
		/*
			ACCESS GEOIP PICTURE AND TELL CLIENT TO DRAW IT
			CAREFUL! MAKE SURE THE CLIENT HAS IT REGISTERED...
		*/
		//if the clients ip is recognised AND the current image is loaded.

		// for(map<string,bool>::iterator it = geoMap.begin(); it != geoMap.end(); ++it) {
		//   orig_Com_Printf("key is : %s\n",it->first.c_str());		  
		// }

		if ( strlen(countryCode[i]) ) {
			char cc[3];
			cc[2] = 0x00;
			cc[0] = countryCode[i][strlen(countryCode[i])-2];
			cc[1] = countryCode[i][strlen(countryCode[i])-1];

			map<string,bool>::iterator it = geoMap.find(cc);
			//attach their flag!
			if ( it != geoMap.end() ) {
				sprintf(out,"xv %d yv %d picn %s ",outx,outy+20,countryCode[i]);
				strcat(final,out);
			}
		}

		
		active--;

		// orig_Com_Printf("%s reso is : %i X %i Y\n",name,reso2d[i][0],reso2d[i][1]);
		
		
	}

	int p = get_player_slot_from_ent(ent);
	if ( isMenuOn[p] ) {
		Scoreboard::hideCreditImage(ent);
		Menu::drawMenu(final,ent);
	} else {
		Scoreboard::drawCreditImage(ent);
	}
	if (final[0]) {
		// orig_Com_Printf("%s\n",final);
		// %s string package
		orig_SP_Print(ent,0x122B,final);
	}
		
	
}
void Scoreboard::onMapBegin(void) {

	//read the flags to register
	FILE * f;
	char line[64];
	f = fopen(Scoreboard::geoSaveFile,"r");
	if (f) {
		while (fgets(line, sizeof(line), f)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
	 		line[strlen(line)-1] = 0x00;
	 		char registerLine[64];
	 		sprintf(registerLine,"pics/sofree/geoflags/%s.m32",line);
	 		orig_SV_FindIndex(registerLine, CS_GHOULFILES, MAX_GHOULFILES, 1,"ghoulfile");

	 		geoMap[line] = true;
	 		// orig_Com_Printf("This doesnt make sense : %s\n",line);

	    }
		fclose(f);
	}
}



void Scoreboard::saveNewFlagToFile(char * newflag){
	if (CreateDirectory("user-server/sofree", NULL) ||
    ERROR_ALREADY_EXISTS == GetLastError())
	{
		FILE * f;
		f = fopen(Scoreboard::geoSaveFile,"a+");
		if (f) {
			fprintf(f,"%s\n",newflag);
			fclose(f);
		}
	}
}


bool Scoreboard::isFlagNew(char * c) {
	FILE * f;
	char line[64];
	f = fopen(Scoreboard::geoSaveFile,"r");
	if (f) {
		while (fgets(line, sizeof(line), f)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
	        if ( strstr(line,c) == line ) {
	        	//found it
	        	fclose(f);
	        	return false;
	        }
	    }
		fclose(f);
	}
	return true;
}