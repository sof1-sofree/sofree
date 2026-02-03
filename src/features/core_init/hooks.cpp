#include "../../../hdr/feature_config.h"

#if FEATURE_CORE_INIT

#include <windows.h>
#include "../../../hdr/sofheader.h"
#include "../../DetourXS/detourxs.h"

extern void * game_clients;
extern void my_SV_InitGameProgs(void);
extern void * my_Sys_GetGameApi(void * imports);
extern void * my_Sys_GetPlayerAPI(void * one, void * two, void * three, void * four, void * five);
extern void my_Qcommon_Init(void);
extern void detourSysShutDown(void);

void core_init_applyHooks(void) {
	//game.dll shutdown func - game.dll->GetGameAPI routed to pmy_GetGameAPI
	detourSysShutDown();

	/*
		-----------Sys_GetGameAPI---------------
		calls onMapInitiation();

		SV_InitGameProgs() -> Sys_GetGameApi()
	*/
	DetourRemove(orig_Sys_GetGameApi);
	orig_Sys_GetGameApi = (Sys_GetGameApi_type) DetourCreate((void*)0x20065F20,(void*)&my_Sys_GetGameApi,DETOUR_TYPE_JMP,5);
	
	/*
		-----------Sys_GetPlayerAPI---------------
		Used for detouring functions within player.dll, none active atm.
	*/
	DetourRemove(orig_Sys_GetPlayerAPI);
	orig_Sys_GetPlayerAPI = (Sys_GetPlayerAPI_type) DetourCreate((void*)0x20066100,(void*)&my_Sys_GetPlayerAPI,DETOUR_TYPE_JMP,6);

	/*
		-----------SV_InitGameProgs---------------
		- A brand new game has been started
		called by SV_Map() -> SV_InitGame() -> SV_InitGameProgs() 
		or SV_Loadgame_f() -> SV_InitGame() -> SV_InitGameProgs()
		We are just setting:
		game_clients = *(unsigned int*)0x20396EEC;
		for now.

		This is a function that _CALLS_ Sys_GetGameApi()
	*/
	DetourRemove(orig_SV_InitGameProgs);
	orig_SV_InitGameProgs = (SV_InitGameProgs_type) DetourCreate((void*)0x2005CDB0 , (void*)&my_SV_InitGameProgs,DETOUR_TYPE_JMP,5);

	/*
		-----------Qcommon_Init---------------
		After executable is initialised, program start-up.
		Used for print version.
	*/
	DetourRemove(orig_Qcommon_Init);
	orig_Qcommon_Init = (Qcommon_Init_type)DetourCreate((void*)0x2001F6F2 , (void*)&my_Qcommon_Init,DETOUR_TYPE_CALL,7);
}

#else

void core_init_applyHooks(void) {}

#endif

