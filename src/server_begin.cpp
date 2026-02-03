#include <windows.h>
#include "sofheader.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "DetourXS/detourxs.h"

#include "lua_api/generic.h"
#include "features.h"



void detourSysShutDown(void);
void myCheck_f(void);


int sofreebuild_len;
char sofreebuildstring[128];
float newrampslide = 180.0f;
double groundDist = 0.375;

/*
Called by WSA_Startup WSOCK init.
Entry point.

sof.exe -> sofree.dll -> sofplus.dll

This is called before sofplus's initialization.

Qcommon_Init
	NET_Init
		WSA_Startup
*/
void onServerInitiation(void)
{
	// // Force Attrack Loop SV_Map
	// DWORD dwProt = NULL;
	// void *addr = NULL;
	// addr = 0x20061623;
	// VirtualProtect(addr, 1, PAGE_READWRITE, &dwProt);
	// memset(addr,0x01,1);
	// VirtualProtect(addr, 1, dwProt, new DWORD);

	// // Force Attrack Loop SV_Map gamemap
	// addr = 0x20061439;
	// VirtualProtect(addr, 1, PAGE_READWRITE, &dwProt);
	// memset(addr,0x01,1);
	// VirtualProtect(addr, 1, dwProt, new DWORD);	

	// orig_Com_Printf("HMMM YEAR = %u\n",(unsigned int)&_BUILD_YEAR);
	// orig_Com_Printf("HMMM MONTH = %u\n",(unsigned int)((&_BUILD_MONTH)-16) & 0xF);
	// orig_Com_Printf("HMMM DAY = %u\n",(unsigned int)(&_BUILD_DAY)-64);
	// orig_Com_Printf("HMMM NUMBER = %u\n",(unsigned int)&_BUILD_NUMBER);
	
	

	//game.dll shutdown func - game.dll->GetGameAPI routed to pmy_GetGameAPI
	detourSysShutDown();

	// Apply core initialization hooks
	core_init_applyHooks();

	// orig_Com_Printf("%02X\n",*(unsigned char*)0x2001F6F2);
	// orig_Com_Printf("%02X\n",*(unsigned char*)0x2001F6F3);
	// orig_Com_Printf("%02X\n",*(unsigned char*)0x2001F6F4);
	// orig_Com_Printf("%02X\n",*(unsigned char*)0x2001F6F5);
	// orig_Com_Printf("Created the QCOMMOON DETOUR???\n");

	createCvars();
	createCommands();
	#ifdef LUA_ON
		LuaInitalize();
	#endif

	sprintf(sofreebuildstring,"SoFree build %hu%02hhu%02hhu.%hu ",(unsigned int)&_BUILD_YEAR,(unsigned int)((&_BUILD_MONTH)-16) & 0xF,(unsigned int)(&_BUILD_DAY)-64,(unsigned int)&_BUILD_NUMBER);
	sofreebuild_len = strlen(sofreebuildstring);
	// turn it grey
	for (int i = 0; i < sofreebuild_len; i++ ) {
		*(sofreebuildstring+i) = *(sofreebuildstring+i) | 0x80;
	}

	char tmp_chr[256];
	sprintf(tmp_chr,"%hu%02hhu%02hhu.%hu",(unsigned int)&_BUILD_YEAR,(unsigned int)((&_BUILD_MONTH)-16) & 0xF,(unsigned int)(&_BUILD_DAY)-64,(unsigned int)&_BUILD_NUMBER);
	setCvarString(_sf_sv_version,tmp_chr);
	// orig_Com_Printf("Welcome to Sofree %s Lua edition\n",tmp_chr);

	/*
		Heavily uses linked list as in Q2.
		Initialises all linked lists.
	*/
	sound_overrides.next = sound_overrides.prev = &sound_overrides;
	the_scripts.next = the_scripts.prev = &the_scripts;

	detours_one.next = detours_one.prev = &detours_one;
	detours_two.next = detours_two.prev = &detours_two;
	detours_three.next = detours_three.prev = &detours_three;
	detours_four.next = detours_four.prev = &detours_four;
	detours_five.next = detours_five.prev = &detours_five;
	detours_six.next = detours_six.prev = &detours_six;
	detours_seven.next = detours_seven.prev = &detours_seven;
	detours_eight.next = detours_eight.prev = &detours_eight;
	detours_nine.next = detours_nine.prev = &detours_nine;
	detours_ten.next = detours_ten.prev = &detours_ten;

	think_events.next = think_events.prev = &think_events;
	touch_events.next = touch_events.prev = &touch_events;
	use_events.next = use_events.prev = &use_events;
	pluse_events.next = pluse_events.prev = &pluse_events;
	pain_events.next = pain_events.prev = &pain_events;
	die_events.next = die_events.prev = &die_events;

	//function in sofplus
	orig_GeoGetCC = (unsigned int)o_sofplus + 0x0014440;
	orig_spfileChecksum = (unsigned int)o_sofplus + 0x000F2D0;

	// orig_SP_Register = (unsigned int)o_sofplus + 0x13710;


	//0x501291E8 gamemode_cDM


	// enable ZOID Rampsliding 180 degrees normal
	
	DWORD dwProt = NULL;
	void *addr = NULL;
	// addr = 0x20053533;
	// VirtualProtect(addr, 4, PAGE_READWRITE, &dwProt);
	// *(unsigned int*)addr = (unsigned int)(&newrampslide); 
	// VirtualProtect(addr, 4, dwProt, new DWORD);

	// addr = 0x2005350E;
	// VirtualProtect(addr, 4, PAGE_READWRITE, &dwProt);
	// *(unsigned int*)addr = (unsigned int)(&groundDist); 
	// VirtualProtect(addr, 4, dwProt, new DWORD);



	// addr = 0x2005350E;
	// VirtualProtect(addr, 4, PAGE_READWRITE, &dwProt);
	// *(unsigned int*)addr = (unsigned int)(&groundDist); 
	// VirtualProtect(addr, 4, dwProt, new DWORD);

}

/*
	Handy for print messages at end of startup??
*/
void my_Qcommon_Init (void)
{
	// orig_Qcommon_Init();
	// int zero = 0;
	// asm volatile("movl %%ecx, %%fs:0;":::"%ecx");

	char tmp_chr[256];
	sprintf(tmp_chr,"%hu%02hhu%02hhu.%hu",(unsigned int)&_BUILD_YEAR,(unsigned int)((&_BUILD_MONTH)-16) & 0xF,(unsigned int)(&_BUILD_DAY)-64,(unsigned int)&_BUILD_NUMBER);
	#ifdef LUA_ON
		orig_Com_Printf("\n\a====== Sofree Lua Edition %s Initialized, Lua Version %.2f ======\n\n",tmp_chr,lua_version (L)/100);
	#else
		orig_Com_Printf("\n\a====== Sofree Lua-disabled Edition %s Initialized ======\n\n",tmp_chr);
	#endif
}	

void onMapInitiation(void)
{
	// orig_Com_Printf("onMapInitiation\n");
	for ( int i = 0; i < 16; i++ ) {
		for ( int j = 0; j < 2; j++ ) {
			reso2d[i][j] = 0;
		}
		show_score[i] = false;
	}

	// reset tints
	// default tint values
	for (int j = 0; j < 32; j++ ) {
		new_client[j] = false;
		client_gravity[j] = _sf_sv_gravity_default->value;

		player_tint[j][0] = 1.0f;	
		player_tint[j][1] = 1.0f;
		player_tint[j][2] = 1.0f;
		player_tint[j][3] = 1.0f;

		player_wep_tint[j][0] = 1.0f;	
		player_wep_tint[j][1] = 1.0f;
		player_wep_tint[j][2] = 1.0f;
		player_wep_tint[j][3] = 1.0f;

		player_collision[j] = true;
		disable_attack[j] = false;
		disable_altattack[j] = false;
		disable_walk[j] = false;
		was_ghosted[j] = false;
	}

	Cmd_CalcFreeImageSlots();
	Cmd_CalcFreeSoundSlots();
	Cmd_CalcFreeGhoulSlots();



	// ListDirectoryContents

}

/*
this function seems kinda silly, is it really just so that we don't free empy variables?
i don't get it lol.
*/
void onMapInitExceptFirstRun(void)
{
	// clear sound overrides?
	sound_overrides_t	*p, *nextp;
	for (p=sound_overrides.next ; p != &sound_overrides ; p=nextp)
	{
		nextp = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
	}
	// clear scripts?
	script_list_t	*y, *nexty;
	for (y=the_scripts.next ; y != &the_scripts ; y=nexty)
	{
		nexty = y->next;
		y->prev->next = y->next;
		y->next->prev = y->prev;
		free(y);
	}
	event_think_t	*x, *nextx;
	for (x=think_events.next ; x != &think_events ; x=nextx)
	{
		nextx = x->next;
		x->prev->next = x->next;
		x->next->prev = x->prev;
		free(x);
	}
	event_touch_t	*t, *nextt;
	for (t=touch_events.next ; t != &touch_events ; t=nextt)
	{
		nextt = t->next;
		t->prev->next = t->next;
		t->next->prev = t->prev;
		free(t);
	}
	event_use_t	*j, *nextj;
	for (j=use_events.next ; j != &use_events ; j=nextj)
	{
		nextj = j->next;
		j->prev->next = j->next;
		j->next->prev = j->prev;
		free(j);
	}
	event_pluse_t	*k, *nextk;
	for (k=pluse_events.next ; k != &pluse_events ; k=nextk)
	{
		nextk = k->next;
		k->prev->next = k->next;
		k->next->prev = k->prev;
		free(k);
	}
	event_pain_t	*u, *nextu;
	for (u=pain_events.next ; u != &pain_events ; u=nextu)
	{
		nextu = u->next;
		u->prev->next = u->next;
		u->next->prev = u->prev;
		free(u);
	}
	event_die_t	*q, *nextq;
	for (q=die_events.next ; q != &die_events ; q=nextq)
	{
		nextq = q->next;
		q->prev->next = q->next;
		q->next->prev = q->prev;
		free(q);
	}
}

/*
	In Sys_GetGameApi
	Instead of calling GetProcAddress("GetGameAPI")
	We just set eax to my_GetGameAPI

	When hooking GetGameAPI , special hook because relative call on first instruction
	We just hook Sys_Shutdown in pmy_GetGameAPI
*/
void detourSysShutDown(void) {
	/*
	Detouring
	*/
	DWORD dwProt = NULL;
	char * blehpatch = 0x20066021;
	char * pc = blehpatch;
	VirtualProtect(blehpatch, 5, PAGE_READWRITE, &dwProt);
	// ADD ESP, 4 ? ( I guess this balances the stack, we could had just NOPPED the push eax.)
	*(unsigned char*)pc = 0x83;
	pc++;
	*(unsigned char*)pc = 0xC4;
	pc++;
	*(unsigned char*)pc = 0x04;
	pc++;
	*(unsigned char*)pc = 0x90;
	pc++;
	*(unsigned char*)pc = 0x90;
	VirtualProtect(blehpatch, 5, dwProt, new DWORD);

	/*
		Instead of calling GetProcAddress("GetGameAPI")
		We just set eax to my_GetGameAPI
	*/
	dwProt = NULL;
	blehpatch = 0x20066027;
	pc = blehpatch;
	// Enable writing to original
	VirtualProtect(blehpatch, 6, PAGE_READWRITE, &dwProt);

	// MOV EAX, [address]
	*(unsigned char*)pc = 0xA1;
	pc++;
	*(unsigned int*)pc = &pmy_GetGameAPI;
	pc+=4;
	*(unsigned char*)pc = 0x90;
	//0x2005F8A0

	// Reset original mem flags
	VirtualProtect(blehpatch, 6, dwProt, new DWORD);
}

typedef struct
{
	char	*name;
	void	(*func) (void);
} ucmd_t;

ucmd_t myucmds[] =
{
	// auto issued
	{"new", 0x20062780},
	{"configstrings", (unsigned int)o_sofplus + 0x174E0},
	{"baselines", (unsigned int)o_sofplus + 0x17530},
	{"begin", (unsigned int)o_sofplus + 0x17570},
	{"nextserver", 0x20063530},
	{"disconnect", 0x20063450},
	{"download", (unsigned int)o_sofplus + 0x175E0},
	{"nextdl", 0x20063040}, //
	{"ghoulstrings", (unsigned int)o_sofplus + 0x17660},
	{"sv_precache",0x20062F20},
	// deleted by ctrl
	//{"info", SV_ShowServerinfo_f},//0x20063470
	/*
	ctrl has shifted sv_precache up and wants info to not exist
	*/
	{",check",myCheck_f},
	{NULL, NULL}
};

//cmd ,check id cvar val
//sofplus func : ,check slot id cvar val
void myCheck_f(void) {
	/*
		PROCESSES THE CHECK FROM TEH CLIENT
	*/
	client_t * cl = stget(SV_CLIENT,0);
	edict_t * ent = stget(cl,CLIENT_ENT);
	int pnum = get_player_slot_from_ent(ent);
	unsigned int id = atoi(orig_Cmd_Argv(1));
	char * cvar = orig_Cmd_Argv(2);
	char * val = orig_Cmd_Argv(3);

	char checkString[128];
	// sprintf(checkString,"sp_sc_func_exec ,check %i %i %s %s\n",pnum,id,cvar,val);
	// orig_Cbuf_AddText(checkString);
	
	cvar_t * c = findCvar(cvar);
	orig_Com_Printf("cvar name %s : val : %s\n",cvar,c->string);
}

/*
enables us to implement our own remote server commands
*/
void patchUserCmds(void)
{
	//patching the ucmd_t command table
	DWORD dwProt = NULL;
	char * blehpatch = 0x20063977;
	char * pc = blehpatch;
	VirtualProtect(blehpatch, 4, PAGE_READWRITE, &dwProt);
	*(unsigned int*)pc = &myucmds;
	VirtualProtect(blehpatch, 4, dwProt, new DWORD);

	dwProt = NULL;
	blehpatch = 0x2006397F;
	pc = blehpatch;
	VirtualProtect(blehpatch, 4, PAGE_READWRITE, &dwProt);
	*(unsigned int*)pc = &myucmds;
	VirtualProtect(blehpatch, 4, dwProt, new DWORD);
}