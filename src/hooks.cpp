
#include <windows.h>
#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include "sofreeS.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

// #define SOFREE_DEBUG

// #define NETDEBUG


void * game_clients = NULL;
void my_SV_InitGameProgs(void)
{
	// this will call ctrls code
	orig_SV_InitGameProgs();


	// game.clients client_t array is set by InitGame in above function
	// lets get the value now
	game_clients = *(unsigned int*)0x20396EEC;

}

bool firstTime = true;

void * my_Sys_GetGameApi(void * imports)
{
	if ( firstTime == true ) {
		firstTime = false;
	} else {
		// like cleanup?
		onMapInitExceptFirstRun();
	}	

	onMapInitiation();

	void * pv_ret = 0;
	// calls LoadLibrary
	pv_ret = orig_Sys_GetGameApi(imports);




	//Apply Hooks the modules require
	Vaccine::applyHooks();
	applyClientHooks();
	applyDeathmatchHooks();


	DWORD dwProt = NULL;

	if ( _sf_sv_grenade_impact_explode->value == 0.0f ) {
		void * addr = 0x50101fb3;
		int count = 6;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		// its a force JMP
		*(unsigned int*)0x50101fB3 = 50153;
		*(unsigned char*)0x50101fB7 = 0x00;
		*(unsigned char*)0x50101fB8 = 0x90;
		VirtualProtect(addr, count, dwProt, new DWORD);
	} else {
		void * addr = 0x50101fb3;
		int count = 6;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		// its a force JMP
		*(unsigned int*)0x50101fB3 = 12747791;
		*(unsigned char*)0x50101fB7 = 0x00;	
		*(unsigned char*)0x50101fB8 = 0x00;	
		VirtualProtect(addr, count, dwProt, new DWORD);
	}

	// DISABLE GRAVITY SET FROM SV_GRAVITY CVAR
	// Gravity "mov     [ebx+12h], ax" DELETE
	void *addr = 0x500F5626;
	int count = 4;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);


	
	// Scoreboard dont clear CTF
	addr = 0x50071FAD;
	count = 6;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// Scoreboard dont clear only did DM
	addr = 0x5006C9B0;
	count = 6;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// its !(framecount & ONBITS)
	// faster scoreboard
	dwProt = NULL;
	char * blehpatch =0x500F9E2F;
	char * pc = blehpatch;
	VirtualProtect(blehpatch, 1, PAGE_READWRITE, &dwProt);
	*(unsigned char*)pc = 0x00;
	VirtualProtect(blehpatch, 1, dwProt, new DWORD);


	// SV_SendClientMessages Line 543 SV_DropClient DELETE
	// SV_SendClientMessages Line 542 SV_BroadcastPrintf(Client overflowed) DELETE 
	/*
		If the reliable buffer overflowed this frame Spam it to everyone
		Should unreliable and reliable buffers be cleared if relaible overflowed?
	*/
	addr = 0x20062603;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);


	// SV_SendClientMessages Line 542 SV_BroadcastPrintf(Client overflowed) DELETE 
	/*
		If the reliable buffer overflowed this frame Spam it to everyone
	*/
	addr = 0x200625F8;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);


	// SV_SendClientMessages Line 544 SV_RateDrop DELETE
	/*
		Means that clients with bad setup can get most smooth experience without frame skipping
	*/
	addr = 0x200626B9;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0xEB,1);
	VirtualProtect(addr, count, dwProt, new DWORD);


	// SV_SendClientDatagram Line 416 SZ_Write(msg,unreliablebuffer) ... DELETE
	/*
		Would usually copy the unreliable buffer into the msg buffer for sending out in netchan_transmit.
		But we handle this ourself, so no need to pass this data through.
		I think we only want frame data to be in there. So that the frame space is largest possible
	*/
	addr = 0x200624E2;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SV_SendClientDatagram Line 414 Com_Printf('datagram overflowed for client') DELETED
	/*
		This means that the unreliable buffer (client->datagram) overflowed this frame and will not be
		copied into msg, hence the final buffer... 0 unreliable data this frame.. sorry. OLDSTYLE.
	*/
	addr = 0x200624C5;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SV_SendClientDatagram Line 421 rename warning
	addr = 0x2013A30C;
	char lolmsg[64] = "Frame doesnt fit for %s\n";
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	strcpy(addr,lolmsg);
	VirtualProtect(addr, count, dwProt, new DWORD);


	// (to - from) - 5;
	// Netchan_Transmit Hook
	addr = 0x20062531;
	count = 4;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	// memset(addr,0x90,count);
	int newaddr = ((int)&my_Netchan_Transmit - ((int)addr-1)) - 5;
	memcpy(addr,&newaddr ,4);
	VirtualProtect(addr, count, dwProt, new DWORD);
	
	// SZ_GetSpace Line 901:common.c Com_Printf("SZ_GetSpace: overflow\n") DELETED
	addr = 0x2001E7F5;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);





	// // dont reject clients in atttractloop
	// addr = 0x2005E808;
	// VirtualProtect(addr, 1, PAGE_READWRITE, &dwProt);
	// memset(addr,0x75,1);
	// VirtualProtect(addr, 1, dwProt, new DWORD);


	// bbox offset fix sp_ammo_slug sp_ammo_shotgun
	addr = 0x50069AE4;
	count = 4;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	*(unsigned int*)0x50069AE4 = &ammofix;
	VirtualProtect(addr, count, dwProt, new DWORD);
	


	// Cmd_Score_f not called in player_die NOP!
	addr = 0x500F2C7E;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);



	/* NOT REQUIRED cos Wrote own PM_AirMove
	if ( _sf_sv_q2_mode->value ) {
		//!!!!! pitch should be 1/3 so this isn't needed??!
		#if 0
			pml.forward[2] = 0;
			pml.right[2] = 0;
			VectorNormalize (pml.forward);
			VectorNormalize (pml.right);
		#endif
		

		// PM_AirMove Q2/sof difference #if 0 code fix
		addr = 0x200531B9;
		count = 10;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		memset(addr,0x90,count);
		VirtualProtect(addr, count, dwProt, new DWORD);

		// PM_AirMove Q2/sof difference #if 0 code fix
		addr = 0x200531CB;
		count = 10;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		memset(addr,0x90,count);
		VirtualProtect(addr, count, dwProt, new DWORD);

		
		// PM_AirMove Q2/sof difference #if 0 code fix
		addr = 0x200531E1;
		count = 5;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		memset(addr,0x90,count);
		VirtualProtect(addr, count, dwProt, new DWORD);

		// PM_AirMove Q2/sof difference #if 0 code fix
		addr = 0x200531ED;
		count = 5;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		memset(addr,0x90,count);
		VirtualProtect(addr, count, dwProt, new DWORD);

	}
	*/


	// minecraft MOD is using omDamage
	//needed for on damage event
	//T_Damage
	DetourRemove(orig_T_Damage);
	orig_T_Damage = (T_Damage_type) DetourCreate((LPVOID)0x5008BB10 , (LPVOID)&T_Damage, DETOUR_TYPE_JMP,8);

	//necesarry for on flag grab
	//itemFlagTouch
	DetourRemove(orig_itemFlagTouch);
	orig_itemFlagTouch = (itemFlagTouch_type)DetourCreate((LPVOID)0x500A9AD0,(LPVOID)&my_itemFlagTouch,DETOUR_TYPE_JMP,5);

	// necessary for spawning custom ents
	//ED_CallSpawn
	DetourRemove(orig_ED_CallSpawn);
	orig_ED_CallSpawn = (ED_CallSpawn_type)DetourCreate((LPVOID)0x500BD570,(LPVOID)&my_ED_CallSpawn,DETOUR_TYPE_JMP,8);


	// necesary for overriding sound attenuation
	//PF_StartSound
	DetourRemove(orig_PF_StartSound);
	orig_PF_StartSound = (PF_StartSound_type)DetourCreate((LPVOID)0x2005CD30,(LPVOID)&my_PF_StartSound,DETOUR_TYPE_JMP,6);

	//needed for saving the cscript handle
	//new CScript
	DetourRemove(orig_CScript);
	orig_CScript = (CScript_type)DetourCreate((LPVOID)0x50079D60 , (LPVOID)&my_CScript,DETOUR_TYPE_JMP,7);

	//SP_script_runner
	DetourRemove(orig_SP_script_runner);
	orig_SP_script_runner = (SP_script_runner_type)DetourCreate((LPVOID)0x50076600,(LPVOID)my_SP_script_runner,DETOUR_TYPE_JMP,7);

	DetourRemove(det_PF_Configstring);
	det_PF_Configstring = (PF_Configstring_type) DetourCreate((LPVOID)0x2005CA40,(LPVOID)my_PF_Configstring,DETOUR_TYPE_JMP,6);

	//SV_SendClientDatagram
	DetourRemove(orig_SV_SendClientDatagram);
	orig_SV_SendClientDatagram = (SV_SendClientDatagram_type)DetourCreate((LPVOID)0x200622F0 ,(LPVOID)my_SV_SendClientDatagram,DETOUR_TYPE_JMP,5);

	DetourRemove(orig_SV_SendClientMessages);
	orig_SV_SendClientMessages = (SV_SendClientMessages_type)DetourCreate((LPVOID)0x20062560 , (LPVOID)my_SV_SendClientMessages,DETOUR_TYPE_JMP,5);
	

	//PF_Unicast
	DetourRemove(orig_PF_Unicast);
	orig_PF_Unicast = (PF_Unicast_type)DetourCreate((LPVOID)0x2005C210 , (LPVOID)my_PF_Unicast,DETOUR_TYPE_JMP,5);

	// SV_Multicast
	DetourRemove(orig_SV_Multicast);
	orig_SV_Multicast = (SV_Multicast_type)DetourCreate((LPVOID)0x20061A80,(LPVOID)my_SV_Multicast,DETOUR_TYPE_JMP,5);

	// SV_Multicast2
	DetourRemove(orig_SV_Multicast2);
	orig_SV_Multicast2 = (SV_Multicast_type)DetourCreate((LPVOID)0x20061CA0,(LPVOID)my_SV_Multicast2,DETOUR_TYPE_JMP,5);

	//necesary for sound overrides
	//SV_SoundIndex
	DetourRemove(orig_SV_SoundIndex);
	orig_SV_SoundIndex = (SV_SoundIndex_td)DetourCreate((LPVOID)0x2005D550,(LPVOID)my_SV_SoundIndex,DETOUR_TYPE_JMP,9);



	// SV_WriteFrameToClient NEED TO PACKET CONTROL THIS TOO hmm
	DetourRemove(orig_SV_WriteFrameToClient);
	orig_SV_WriteFrameToClient = (SV_WriteFrameToClient_type)DetourCreate((LPVOID)0x2005B970 , (LPVOID)my_SV_WriteFrameToClient,DETOUR_TYPE_JMP,6 );

	// MAX_SENT_ENTITIES_LIMITTING
	DetourRemove(orig_MSG_WriteDeltaEntity);
	orig_MSG_WriteDeltaEntity = (MSG_WriteDeltaEntity_type)DetourCreate((LPVOID)0x2001D4F0 , (LPVOID)my_MSG_WriteDeltaEntity,DETOUR_TYPE_JMP, 5);


	// DetourRemove(orig_MSG_WriteShort);
	// orig_MSG_WriteShort = (MSG_WriteShort_type)DetourCreate((LPVOID)0x2001CB70 , (LPVOID)my_MSG_WriteShort,DETOUR_TYPE_JMP, 5);

	// MAX_SENT_ENTITIES_LIMITTING
	DetourRemove(orig_SV_EmitPacketEntities);
	orig_SV_EmitPacketEntities = (SV_EmitPacketEntities_type) DetourCreate((LPVOID)0x2005AF90 , (LPVOID)my_SV_EmitPacketEntities,DETOUR_TYPE_JMP, 7);

	// MAX_SENT_ENTITIES_LIMITTING
	DetourRemove(orig_MSG_WriteUnknownDelta);
	orig_MSG_WriteUnknownDelta = (MSG_WriteUnknownDelta_type)DetourCreate((LPVOID)0x2001D210 , (LPVOID)my_MSG_WriteUnknownDelta,5);

	// Attempting to fix overflow issues allow more data to be sent
	DetourRemove(orig_SZ_Write);
	orig_SZ_Write = (SZ_Write_type)DetourCreate((LPVOID)0x2001E7B0,(LPVOID)my_SZ_Write,DETOUR_TYPE_JMP,5);

	// Inspecting single player ammo respawn problems
	// DetourRemove(orig_DoRespawn);
	// orig_DoRespawn = (DoRespawn_type)DetourCreate((LPVOID)0x5006B780 , (LPVOID) my_DoRespawn,5);


	// DetourRemove(orig_PutBits);
	// orig_PutBits = (PutBits_type)DetourCreate((LPVOID)0x200BDCA0 , (LPVOID) my_PutBits, 8);

	// get current client for debug checksums
	// DetourRemove(orig_SV_ExecuteClientMessage);
	// orig_SV_ExecuteClientMessage = (SV_ExecuteClientMessage_type)DetourCreate((LPVOID)0x200636C0 , (LPVOID)&my_SV_ExecuteClientMessage,DETOUR_TYPE_JMP,7);

	// debug checksums
	// DetourRemove(orig_COM_BlockSequenceCRCByte);
	// orig_COM_BlockSequenceCRCByte = (COM_BlockSequenceCRCByte_type)DetourCreate((LPVOID)0x2001F1B0,(LPVOID)&my_COM_BlockSequenceCRCByte,DETOUR_TYPE_JMP,6 );


	// DetourRemove(orig_COM_BlockChecksum);
	// orig_COM_BlockChecksum = (COM_BlockChecksum_type)DetourCreate((LPVOID)0x2004D150 ,(LPVOID) &my_COM_BlockChecksum,DETOUR_TYPE_JMP, 7);



	DetourRemove(orig_SP_vnsprintf);
	orig_SP_vnsprintf = (SP_vnsprintf_type)DetourCreate((LPVOID)0x20056B90,(LPVOID)&my_SP_vnsprintf,DETOUR_TYPE_JMP, 6);



	// To become likq Q2
	// CAUTION THIS DEPENDS ON THE orig_PM_StepSlideMove
	DetourRemove(orig_PM_AirMove);
	orig_PM_AirMove = (PM_AirMove_type)DetourCreate((LPVOID) 0x200531A0 ,(LPVOID)&my_PM_AirMove,DETOUR_TYPE_JMP,8);

	// To become like Q2
	DetourRemove(orig_PM_StepSlideMove);
	orig_PM_StepSlideMove = (PM_StepSlideMove_type)DetourCreate((LPVOID)0x20052A10 , (LPVOID)&my_PM_StepSlideMove,DETOUR_TYPE_JMP, 6);


	// // To become like Q2
	// DetourRemove(orig_PM_CatagorizePosition);
	// orig_PM_CatagorizePosition = (PM_CatagorizePosition_type)DetourCreate((LPVOID) 0x20053500 , (LPVOID) &my_PM_CatagorizePosition,DETOUR_TYPE_JMP,6);

	// // To become liek Q2
	// DetourRemove(orig_PM_InitialSnapPosition);
	// orig_PM_InitialSnapPosition = (PM_InitialSnapPosition_type)DetourCreate((LPVOID) 0x20054470,(LPVOID)&my_PM_InitialSnapPosition,DETOUR_TYPE_JMP,6);
	
	// DetourRemove(orig_PM_SnapPosition);
	// orig_PM_SnapPosition = (PM_SnapPosition_type)DetourCreate((LPVOID) 0x20054260 ,(LPVOID) &my_PM_SnapPosition,DETOUR_TYPE_JMP,6);

	// // To become like Q2
	// DetourRemove(orig_PM_StepSlideMove_);
	// orig_PM_StepSlideMove_ = (PM_StepSlideMove__type)DetourCreate((LPVOID)0x20052620 , (LPVOID)&my_PM_StepSlideMove_,DETOUR_TYPE_JMP, 6);



	


	// fix any broken sound configstrings
	for (int i=0 ; i<MAX_SOUNDS ; i++) {
		char * c = (char*)(SV_CONFIGSTRINGS+(CS_SOUNDS+i)*MAX_QPATH);
		if ( *c ) replacechar(c,'\\','/');
	}
	// Cmd_SofreeHelp(); 
	
	// orig_Com_Printf("SoFree build %hu%02hhu%02hhu.%hu loaded\n",(unsigned int)&_BUILD_YEAR,(unsigned int)((&_BUILD_MONTH)-16) & 0xF,(unsigned int)(&_BUILD_DAY)-64,(unsigned int)&_BUILD_NUMBER);
	return pv_ret;

	// orig_ctf_base_touch = (ctf_base_touch_type)DetourCreate((LPVOID)0x500725D0 ,(LPVOID)&my_ctf_base_touch,DETOUR_TYPE_JMP,5);


	//ent->solid is changed when spectator joins
	// DetourRemove(orig_spectator_respawn);
	// orig_spectator_respawn = (spectator_respawn_type) DetourCreate((LPVOID)0x500F35D0 ,(LPVOID)my_spectator_respawn,DETOUR_TYPE_JMP,6);
	
	// DetourRemove(orig_SV_GhoulIndex);
	// orig_SV_GhoulIndex = (SV_GhoulIndex_type)DetourCreate((LPVOID)0x2005D5B0,(LPVOID)&my_SV_GhoulIndex,DETOUR_TYPE_JMP, 9);
	// orig_SpawnEntities = (SpawnEntities_type)DetourCreate((LPVOID)0x500BDB50 ,(LPVOID)&my_SpawnEntities,DETOUR_TYPE_JMP,5);

	//orig_ctfClientScoreboardMessage = (ctfClientScoreboardMessage_type)DetourCreate((LPVOID)0x50071D70,(LPVOID)&my_ctfClientScoreboardMessage,DETOUR_TYPE_JMP,6);

	// orig_G_Find = (G_Find_type)DetourCreate((LPVOID)0x500C26A0 , (LPVOID)&my_G_Find,DETOUR_TYPE_JMP, 5);

	//gamex86.dll should be loaded now
	// PrintOut(PRINT_GOOD,true,"Hooking T_Damage as game.dll is loaded\n");


	// orig_script_use = (script_use_type)DetourCreate((LPVOID)0x50076570 , (LPVOID)&my_script_use,DETOUR_TYPE_JMP,9);

	// sp_det_CreateDetour("PutClientInServer", 1, 0x500F38A0, "cdecl", 6,false,0x12D3C);


	// orig_SimpleModelInit2 = (SimpleModelInit2_type) DetourCreate((LPVOID)0x500B3870 , (LPVOID)&my_SimpleModelInit2,DETOUR_TYPE_JMP,7);
	
	// seems to singleplayer related
	// orig_respawn = (respawn_type) DetourCreate((LPVOID)0x500F3550,(LPVOID)my_respawn,DETOUR_TYPE_JMP,6);

	//orig_AddObjectInstance = (AddObjectInstance_type)DetourCreate((LPVOID)0x500A5D10  ,(LPVOID)my_AddObjectInstance,DETOUR_TYPE_JMP,6);

	// orig_PB_AddFlag = (PB_AddFlag_type) DetourCreate((LPVOID)0x500A3F30, (LPVOID) my_PB_AddFlag,DETOUR_TYPE_JMP,6);
	
	// very important to paint a player
	// DetourRemove(orig_NewPlayerModelInfo);
	// orig_NewPlayerModelInfo = (NewPlayerModelInfo_type) DetourCreate((LPVOID) 0x200494C0 ,(LPVOID)my_NewPlayerModelInfo,DETOUR_TYPE_JMP,7);
	
	
	// orig_FX_HandleDMMuppleFlash = (FX_HandleDMMuppleFlash_type)DetourCreate((LPVOID)0x50084E60,(LPVOID)my_FX_HandleDMMuppleFlash,DETOUR_TYPE_JMP,8);

	// orig_TakePiss = (TakePiss_type)DetourCreate((LPVOID) 0x500273A0  ,(LPVOID)&my_TakePiss,DETOUR_TYPE_JMP,5);
	// orig_COM_BlockSequenceCRCByte = (COM_BlockSequenceCRCByte_type)DetourCreate((LPVOID)orig_COM_BlockSequenceCRCByte,(LPVOID)&my_COM_BlockSequenceCRCByte,DETOUR_TYPE_JMP,6);


	// COOPFIX DEATHMATCH RUN SCRIPTRUNNER WORLDSPAWN FOR CLEINTS
	// BLEH
	
	
	//DetourThis((void*)0x500AE340,(void*)&hook_G_RunFrame,6,(int*)&G_RunFrame);
	//DetourThis((void*)0x500AD490,(void*)&hook_CleanupGame,7,(int*)&CleanupGame);

	// cant detour this fuck cos he has relative call at start of func
	// orig_ShutdownGame = (ShutdownGame_type)DetourCreate((LPVOID)0x500AD5B0 , (LPVOID)&my_ShutdownGame,DETOUR_TYPE_JMP,5);	


	// direct patch of ge table, first check if ctrl doesnt patch it with that method.
	// 500ADA3A


	//special hook for script_use
	// // Enable writing to original
	// VirtualProtect(0x500767AD, 4, PAGE_READWRITE, &dwProt);
	// *(unsigned int*)(0x500767AD) = &my_script_use;
	// // Reset original mem flags
	// VirtualProtect(0x500767AD, 4, dwProt, new DWORD);

	// // allows send gun update to clients
	// dwProt = NULL;
	// // Enable writing to original
	// VirtualProtect(0x2005B150, 2, PAGE_READWRITE, &dwProt);
	// *(unsigned char*)(0x2005B150) = 0x90;
	// *(unsigned char*)(0x2005B151) = 0x90;
	// // Reset original mem flags
	// VirtualProtect(0x2005B150, 2, dwProt, new DWORD);

	orig_M_AddServerToList = (M_AddServerToList_type)DetourCreate((LPVOID)0x200C7F40,(LPVOID)&my_M_AddServerToList,DETOUR_TYPE_JMP,5);
	orig_PM_AirMove = (PM_AirMove_type)DetourCreate((LPVOID) 0x200531A0 ,(LPVOID)&my_PM_AirMove,DETOUR_TYPE_JMP,8);
}

game_export_t * my_GetGameAPI (game_import_t *import) {
	// orig_Com_Printf("overwriting SHUTDOWN in GetGameAPI!!\n");

	//special hook because relative call on first instruction
	// BLEH
	DWORD dwProt = NULL;
	// Enable writing to original
	VirtualProtect(0x500ADA3A, 4, PAGE_READWRITE, &dwProt);
	*(unsigned int*)(0x500ADA3A) = &my_ShutdownGame;
	// Reset original mem floatags
	VirtualProtect(0x500ADA3A, 4, dwProt, new DWORD);

	return orig_GetGameAPI(import);
}



char skysib[64] = "sib";
void my_PF_Configstring(int index,char * string)
{
	try{
	// if ( index == CS_CTF_BLUE_STAT || index == CS_CTF_RED_STAT ){
	// 	return;
	// 	//orig_Com_Printf("string is : %s\n",string);
	// }
	
	if ( strlen(_sf_sv_force_sky->string) && index == CS_SKY ) {
		string = _sf_sv_force_sky->string;
		orig_Com_Printf("setting sky to %s\n",string);
	}
	det_PF_Configstring(index,string);

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

void my_script_use(edict_t *ent, edict_t *other, edict_t *activator)
{
	try{
	orig_Com_Printf("calling Use!\n");
	orig_script_use(ent,other,activator);

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

edict_t * my_G_Find(edict_t *from, int fieldofs, char *match, int charsToCompare)
{
	try{
	orig_G_Find(from,fieldofs,match,charsToCompare);

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

void my_SpawnEntities (char *mapname, char *entities, char *spawnpoint)
{
	try{
	// edict_t * ent = orig_G_Spawn();
	// char * c = orig_p_TagMalloc(strlen("misc_generic_table_round") + 1,TAG_SOFREE);
	// strcpy(c,"misc_generic_table_round");
	// *(char**)(ent+EDICT_CLASSNAME) = c;

	// *(float*)(ent+EDICT_S_ORIGIN) = 266;
	// *(float*)(ent+EDICT_S_ORIGIN+4) = -431;
	// *(float*)(ent+EDICT_S_ORIGIN+8) = 30;

	// orig_ED_CallSpawn(ent);
	// orig_Com_Printf(mapname);
	// orig_Com_Printf(spawnpoint);


	orig_SpawnEntities(mapname,entities,spawnpoint);

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}

	// 		orig_SP_Register("hax");
}

void my_PF_StartSound(edict_t *entity, int channel, int sound_num, float volume,float attenuation, float timeofs,int localipe)
{
	try{
	float new_atn = attenuation;

	sound_overrides_t	*p, *next;
	for (p=sound_overrides.next ; p != &sound_overrides ; p=next)
	{
		next = p->next;
		if ( sound_num == p->index && p->atten_mod > -0.5f ) {
			new_atn = p->atten_mod;
			break;
		}
	}

	orig_PF_StartSound(entity,channel,sound_num,volume,new_atn,timeofs,localipe);
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


void my_itemFlagTouch(edict_t *theFlag, edict_t *flagToucher, cplane_t *plane, mtexinfo_t *surf)
{
	try{

	int oldFlagState = flagToucher->ctf_flags;

	//my flag value before?
	orig_itemFlagTouch(theFlag,flagToucher,plane,surf);

	if ( flagToucher ) {
		gclient_t * gc = flagToucher->client;
		if (gc) {
			int myTeam = gc->resp.team;
			int flagsTeam = theFlag->ctf_flags;
			//if its enemy flag?
			if ( !(flagsTeam & myTeam) ) {
				
				int newFlagState = flagToucher->ctf_flags;
				// if flag state has changed
				if ( newFlagState != oldFlagState ) {
					orig_Com_Printf("You grabbed the flag! %i  %i\n",newFlagState, myTeam);
					
					makeTheStringElips(" %i %s\n",_sf_sv_on_flag_take, get_player_slot_from_ent(flagToucher),newFlagState==2 ? "red" : (newFlagState==1 ? "blue" : "none"));
				}
			}		
		}
	}

	// if ( other ) {
	// 	unsigned int ghl = *(unsigned int*)(other+EDICT_GHOULINST);
	// 	if ( ghl ) {
	// 		unsigned int lol = orig_FindBoltInstance(ghl,);		
	// 	}
	// }

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

void my_ctf_base_touch(edict_t *self, edict_t *other, cplane_t *plane, mtexinfo_t *surf)
{
	try{
	orig_Com_Printf("You SOMETHING the flag!\n");
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


int my_SV_GhoulIndex(char *name)
{
	try{
	// orig_Com_Printf("lol : %s\n",name);
	return orig_SV_GhoulIndex(name);
	
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

/*
	G_Spawn has already been called prior.
*/
void my_ED_CallSpawn (edict_t *ent)
{
	try{
		// cvar_t * testbla = orig_Cvar_Get("testbla","",NULL,NULL);
		cvar_t * delaysec = orig_Cvar_Get("delaysec","0",NULL,NULL);
		cvar_t * counthsec = orig_Cvar_Get("counthsec","64",NULL,NULL);
		cvar_t * healthsize = orig_Cvar_Get("healthsize","12",NULL,NULL);
		/*
		// fix these buggy positions breaking effect spawning using PHS
		if ( ent->classname && (!strcmp(ent->classname,"item_ammo_sp_shotgun") || !strcmp(ent->classname,"item_ammo_sp_slug")) ) {
			ent->mins[2] -= testbla->value;
		}
		*/

		if ( ent->classname && !strcmp(ent->classname,"environ_fire") ) {
			// life of actual fire
			void * vent = ent;
			stset(vent,EDICT_DELAY,(int)delaysec->value);
			// orig_Com_Printf("delay : %X\n",FOFS(delay));
			// lifetime
			stset(vent,EDICT_COUNT,(int)counthsec->value);


			// orig_Com_Printf("count : %X\n",FOFS(count));

			stset(vent,EDICT_HEALTH,(int)healthsize->value);

			char text[256];
			sprintf(text,"say UNUSUAL\n");
			orig_Cbuf_AddText(text);
		}
		if ( ent->classname && !strcmp(ent->classname,"pacman") ) {
			SP_pacman(ent);
		} else {
			orig_ED_CallSpawn(ent);	
		}
		
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
	
}

void * my_Sys_GetPlayerAPI(void * one, void * two, void * three, void * four,void * five)
{
	try{
	// PrintOut(PRINT_GOOD,0,"Loaded Player.dll\n");
	void * ret = orig_Sys_GetPlayerAPI(one,two,three,four,five);
	player_export = ret;
	// orig_selectWeapon = (selectWeapon_type) DetourCreate((LPVOID)0x400024D0,(LPVOID)&my_selectWeapon,DETOUR_TYPE_JMP,8);
	// orig_initNewWeapon = (initNewWeapon_type)DetourCreate((LPVOID) 0x400020C0,(LPVOID)&my_initNewWeapon,DETOUR_TYPE_JMP,5);

	return ret;
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

void my_initNewWeapon(void * self)
{
	try{
	// orig_Com_Printf("NewWeapon hehe!\n");
	orig_initNewWeapon(self);
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

int my_selectWeapon(void * self,int weapon)
{
	try{
	orig_Com_Printf("SelectWeapon\n");
	int ret = orig_selectWeapon(self,weapon);
	return ret;

	unsigned int owner = *(unsigned int*)(self+0x1AC);
	unsigned int edict = *(unsigned int*)(owner+0x4);

	if (edict){
		unsigned int slot = get_player_slot_from_ent(edict);
		unsigned int gclient = *(unsigned int*)(edict + EDICT_GCLIENT);
		if (gclient) {
			clientinst = *(unsigned int*)(gclient + EDICT_PS_GUN);
			if ( clientinst ) {
				GhoulSetTintOnAll(player_wep_tint[slot][0],player_wep_tint[slot][1],player_wep_tint[slot][2],player_wep_tint[slot][3]);
			}
		}
	}
	// orig_getViewModel = (getViewModel_type)(*(unsigned int*)(*(unsigned int*)self+0x14C));
	// orig_Com_Printf("lol %08X\n",orig_getViewModel);
	// orig_Com_Printf("lol %08X\n",*(unsigned int*)self);
	// clientinst = (unsigned int*)orig_getViewModel(self);

	// GhoulSetTint(1.0,0.0,0.0,1.0);


	return ret;

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


/*
This is also called by SV_Map before SV_SpawnServer
So you can't use multicast or sv variables here cos they are all 0. cleared for mapchange.
*/
void my_SV_SendClientMessages(void)
{

	// sv.state == ss_game
	if ( stget(0x203A1F20,0) == 2 ){
		// 83 max boxes 83 * 12 = 996
		if( _sf_sv_debug_triggers->value ) {
			if ( _sf_sv_debug_triggers->value == 3.0f ) {
				randomBoxCode();
			} else  {
				if ( *level_framenum % 5 == 0 ) {
					drawBoxesOnEnts(1,_sf_sv_debug_triggers->value);
				} else
				if ( *level_framenum % 5 == 1 ) {
					drawBoxesOnEnts(2,_sf_sv_debug_triggers->value);
				} else
				if ( *level_framenum % 5 == 2 ) {
					drawBoxesOnEnts(3,_sf_sv_debug_triggers->value);
				} else
				if ( *level_framenum % 5 == 3 ) {
					drawBoxesOnEnts(4,_sf_sv_debug_triggers->value);
				} else
				if ( *level_framenum % 5 == 4 ) {
					drawBoxesOnEnts(5,_sf_sv_debug_triggers->value);
				}
			}
			
		}
		
	}
	orig_SV_SendClientMessages();

}


//called for every client
/*
Seperated reliable unreliable from SV_SendClientDatagram

qboolean SV_SendClientDatagram (client_t *client):
	SV_BuildClientFrame (client);
	SZ_Init (&msg, msg_buf, sizeof(msg_buf));
	msg.allowoverflow = true;
	SV_WriteFrameToClient (client, &msg);
	if (client->datagram.overflowed)
		Com_Printf ("WARNING: datagram overflowed for %s\n", client->name); DELETED
	else
		SZ_Write (&msg, client->datagram.data, client->datagram.cursize); DELETED
	SZ_Clear (&client->datagram);
	if (msg.overflowed)
	{	// must have room left for the packet header
		Com_Printf ("WARNING: msg overflowed for %s\n", client->name); RENAMED FRAME DOES NOT FIT
		SZ_Clear (&msg);
	}
	// msg will only contain frame data from sv_writeframetoclient
	// this is hooked
	Netchan_Transmit (&client->netchan, msg.cursize, msg.data);
	client->message_size[sv.framenum % RATE_MESSAGES] = msg.cursize;
	return true;
*/
qboolean my_SV_SendClientDatagram(client_t *client)
{
	edict_t * ent = stget(client,CLIENT_ENT);
	if ( !ent || !ent->inuse ) return orig_SV_SendClientDatagram(client);
	int j = get_player_slot_from_ent(ent);

	//paint it
	clientinst = (unsigned int)(ent->ghoulInst);
	if ( clientinst ) {
		GhoulSetTintOnAll(player_tint[j][0],player_tint[j][1],player_tint[j][2],player_tint[j][3]);	
		clientinst = stget((unsigned int)ent->client,GCLIENT_PS_BOD);
		if (clientinst)
		{
			GhoulSetTintOnAll(player_tint[j][0],player_tint[j][1],player_tint[j][2],player_tint[j][3]);
		}
	}

	//weapon paint it
	gclient_t * gclient = (unsigned int)(ent->client);

	if (gclient) {
		unsigned int ghosted = gclient->ghosted;
		// orig_Com_Printf("Ghosted is : %08X\n",ghosted);
		float alpha = player_wep_tint[j][3];
		//should be ghosted but isnt
		// if ( ghosted ) {
		// 	alpha = 0.5f;
		// }
		clientinst = (unsigned int)(gclient->ps.gun);
		if ( clientinst ) {
			GhoulSetTint(player_wep_tint[j][0],player_wep_tint[j][1],player_wep_tint[j][2],alpha);
		}
				
	}//gclient		

	// the original netchan_transmit will still send frame and then the reliable on 2 seperate packets
	qboolean ret = orig_SV_SendClientDatagram(client);
	// return orig_SV_SendClientDatagram(client);
	// return ret;


	void * client_t = game_clients + j * 0xd2ac;

	// headersize = 10
	int packets_sent = 0;
	int parsed = 0;
	int numcmds = num_net_cmds[j];
	int tmp_parse = 0;
	int len = 0;
	// orig_Com_Printf("This many commands : %i\n",numcmds);
	for ( int i = 0; i < numcmds; i++ ) {
		tmp_parse += net_commands[j][i].msgsize;
		if ( tmp_parse > 1384 ) {
			// orig_Com_Printf("Full Packet wtf\n");
			// i'th command does not fit
			// sendpacket (i-1)th commands
			len = tmp_parse - net_commands[j][i].msgsize;
			Netchan_Transmit_Unreliable(client_t + 0x526C, len , &unreliableData[j][parsed]);

			packets_sent++;
			parsed += len;
			tmp_parse = net_commands[j][i].msgsize;
		}
	}
	// 1 cmd 9 packetsize 0 start 1 packet
	// remaining
	if ( tmp_parse ) {
		// orig_Com_Printf("Sending Packet Length = %i, offsetFrom = %i\n",tmp_parse,parsed);

		Netchan_Transmit_Unreliable(client_t + 0x526C, tmp_parse , &unreliableData[j][parsed]);
		packets_sent++;
	}

	 // orig_Com_Printf("You Sent %i Packets HeHe\n",packets_sent);

	// reset for next frame
	num_net_cmds[j] = 0;

	#ifdef NETDEBUG
	orig_Com_Printf("unreli %i bytes : %i packets\n",unreliablePointer[j],packets_sent);
	#endif
	unreliablePointer[j] = 0;

	return ret;
}

void Netchan_Transmit_Unreliable(netchan_t *chan, int length, byte *data)
{
	byte		send_buf[1400];
	sizebuf_t	send;
	qboolean	send_reliable = false;
	unsigned	w1, w2;

	// write the packet header
	memset (&send, 0, sizeof(send));
	send.data = send_buf;
	send.maxsize = sizeof(send_buf);

	w1 = ( chan->outgoing_sequence & ~(1<<31) ) | (send_reliable<<31);
	w2 = ( chan->incoming_sequence & ~(1<<31) ) | (chan->incoming_reliable_sequence<<31);

	chan->outgoing_sequence++;
	chan->last_sent = *(int*)0x20390D38;

	orig_MSG_WriteLong (&send, w1);
	orig_MSG_WriteLong (&send, w2);

	// send the qport if we are a client
	if (chan->sock == NS_CLIENT)
		orig_MSG_WriteShort (&send, qport->value);

	
// add the unreliable part if space is available
	if (send.maxsize - send.cursize >= length)
		orig_SZ_Write (&send, data, length);
	else
		orig_Com_Printf ("Netchan_Transmit: dumped unreliable\n");

// send the datagram
	orig_NET_SendPacket (chan->sock, send.cursize, send.data, chan->remote_address);
}


void my_ShutdownGame(void)
{

	// orig_Com_Printf("CLEANUP FUNCTION GAME ENDDD\n");
	// cleanup my ds scripts here
	struct d_script_s * ds = NULL;
	for ( int i = 0 ; i < d_script_pointer; i++ ) {
		struct d_script_s ** ds = &(dende_scripts[i]);
		*ds = NULL;
	}
	d_script_pointer = 0;

	dm_always.removeHooks();


	orig_ShutdownGame();
	
}



bool my_PB_InitBody(edict_t *ent,char *userinfo)
{
	try{
	#ifdef SOFREE_DEBUG
		orig_Com_Printf("Calling %s\n",__FUNCTION__);
	#endif

	bool donut = orig_PB_InitBody(ent,userinfo);



	int slot = get_player_slot_from_ent(ent);
	if ( slot > -1 ) {
		clientinst = stget(ent,EDICT_GHOULINST);
		if ( clientinst ) {

			GhoulSetTintOnAll(player_tint[slot][0],player_tint[slot][1],player_tint[slot][2],player_tint[slot][3]);	
			clientinst = stget(stget(ent,EDICT_GCLIENT),GCLIENT_PS_BOD);
			if (clientinst)
			{
				GhoulSetTintOnAll(player_tint[slot][0],player_tint[slot][1],player_tint[slot][2],player_tint[slot][3]);	
			}
		}
	}
	return donut;

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

void my_PB_AddFlag(edict_t *ent, char *FlagSkinName, char* FlagGhoulFile)
{
	try{
	orig_PB_AddFlag(ent,FlagSkinName,FlagGhoulFile);
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


void my_SimpleModelInit2(edict_t *ent, modelSpawnData_t *modelData,char *skinname,char *partname)
{
	try{
	// if ( !strcmp(*(char**)(ent+EDICT_CLASSNAME),"misc_generic_table_round") )
	// {
	// 	orig_Com_Printf("cough_d : %s\ncough_f : %s\ncough_m : %s\ncough_s : %s\n",modelData->dir,modelData->file,modelData->materialfile,skinname);
		
	// }
	/*
	char * c;
	if (modelData->materialfile && !strcmp(modelData->materialfile,"box")) {
		c = orig_p_TagMalloc(4,TAG_SOFREE);
		strcpy(c,"123");
		modelData->materialfile = c;
		orig_Com_Printf("patched him1\n");

		
		skinname = c;
	}
	if (modelData->file && !strcmp(modelData->file,"box")) {
		orig_Com_Printf("cough_d : %s\ncough_f : %s\ncough_m : %s\ncough_s : %s\n",modelData->dir,modelData->file,modelData->materialfile,skinname);
		c = orig_p_TagMalloc(4,TAG_SOFREE);
		strcpy(c,"123");
		modelData->file = c;
		orig_Com_Printf("patched him2\n");
	}*/
	orig_SimpleModelInit2(ent,modelData,skinname,partname);
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

	
IPlayerModelInfoC	*my_NewPlayerModelInfo(char *modelname)
{
	try{
	IPlayerModelInfoC	* ret = orig_NewPlayerModelInfo(modelname);

	// edict_t * ent = get_ent_from_player_slot(0);
	// clientinst = stget(ent,EDICT_GHOULINST);
	// if ( clientinst ) {
	// 	GhoulSetTintOnAll(player_tint[slot][0],player_tint[slot][1],player_tint[slot][2],player_tint[slot][3]);	


	// char * (*getghbdir)(void) = (unsigned int)(ret+0x18);
	// char * (*getseqgsq)(void) = (unsigned int)(ret+0x24);
	// char * (*getgameghb)(void) = (unsigned int)(ret+0x20);
	

	// asm volatile("mov %%ecx, %0"::"m"(ret));
	// char * ggd = getghbdir();
	// asm volatile("mov %%ecx, %0"::"m"(ret));
	// char * gsg = getseqgsq();
	// asm volatile("mov %%ecx, %0"::"m"(ret));
	// char * ggg = getgameghb();
	// PrintOut(PRINT_GOOD,false,"%s\n%s\n%s\n",ggd,gsg,ggg);

	// void * myobj = GhoulFindObject(ggd,gsg,false,modelname,ggg);


	// map<IGhoulInst*,gg_inst_c_ptr>::iterator iteri




	return ret;

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


/*
if(deathmatch->value &&
   client->pers.spectator != client->resp.spectator &&
   (level.time - client->respawn_time) >= 5)
{
	spectator_respawn(ent);
	return;
}
*/
void my_spectator_respawn(edict_t * ent)
{
	try{
	// orig_Com_Printf("hehe\n");
		// unsigned int spec = *(unsigned int*)(*(unsigned int*)(ent + EDICT_GCLIENT) + GCLIENT_PERS_SPECTATOR);
		int slot = get_player_slot_from_ent(ent);

		// this badboy calls PutClientInServer ( which is ctrls client_spawn which is sofplus code )
		orig_spectator_respawn(ent);

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

int last_created_cscript;
int my_CScript(void * self,char *ScriptName, edict_t *new_owner)
{
	try{
	int ret;
	ret = orig_CScript(self,ScriptName,new_owner);
	last_created_cscript = ret;
	return ret;
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


int my_SV_SoundIndex(char *name)
{
	try{
	if ( _sf_sv_debug_sounds->value == 1.0f )	orig_Com_Printf("%s\n",name);
	replacechar(name,'\\','/');

	int ret = -1;


	sound_overrides_t	*p, *next;
	for (p=sound_overrides.next ; p != &sound_overrides ; p=next)
	{
		next = p->next;

		
		char * c;
		if ( (c=strchr(p->orig_sound,'*')) && *(c+1) == 0x00 ) {
			// no sound
			if ( !strlen(p->new_sound) ) return 0;

			// match just the stuff before the *
			if ( !strnicmp(p->orig_sound,name,c - p->orig_sound ) ) {
				ret = orig_SV_SoundIndex(p->new_sound);
				p->index = ret;
				return ret;
			}
		} else if ( !stricmp(name,p->orig_sound) ) {

			// no sound
			if ( !strlen(p->new_sound) ) return 0;

			ret = orig_SV_SoundIndex(p->new_sound);
			p->index = ret;
			return ret;
		}
	}
	
	return orig_SV_SoundIndex(name);

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}



ggOinstC * my_AddObjectInstance(ggObjC *curObject, edict_t *whose)
{
	try{
	//unsigned int esp;
	//save ecx here
	//asm volatile( "movl %%esp,%0;":"=m"(esp)::"%esp");
	/*

	unsigned int ret;
	
	asm volatile(	"push %3;" //whose
					"push %2;"//push curObject
					"movl %1,%%ecx;"//game_ghoul->ecx
					"call *%3;"//call orig_AddObjectInstance
					"movl %%eax,%0;"//eax->ret
					:"=m"(ret):"m"(ecx),"m"(curObject),"m"(whose) ,"m"(orig_AddObjectInstance):"%ecx");
	
	*/

	// ggOinstC * ret = orig_AddObjectInstance(curObject,whose);
	// if ( ret ) {
	// 	lastentnewghoul = whose;	
	// }

	//restore ecx
	//asm volatile( "movl %0, %%esp;"::"m"(esp):"%esp");
	// return ret;

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


void my_respawn (edict_t *self)
{
	try{

	// orig_Com_Printf("respawn\n");
	orig_respawn(self);

	
	// lastentnewghoul = NULL;
	int slot = get_player_slot_from_ent(self);
	if (slot > -1) {
		clientinst = *(unsigned int*)(*(unsigned int*)(self + EDICT_GCLIENT) + GCLIENT_PS_BOD);
		if ( clientinst ) {			
				GhoulSetTintOnAll(player_tint[slot][0],player_tint[slot][1],player_tint[slot][2],player_tint[slot][3]);	
				// *(unsigned int*)(self+0x15C) = MASK_SOLID;
		}
	}


	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}

client_t * SV_ExecuteClient = NULL;
bool usercmdCRC = false;
unsigned char my_COM_BlockSequenceCRCByte(unsigned char *base, int length, int sequence)
{
	try{
		usercmdCRC = true;
		unsigned char blossom = orig_COM_BlockSequenceCRCByte(base,length,sequence);
		edict_t * ent = stget(SV_ExecuteClient,CLIENT_ENT);
		int slot = get_player_slot_from_ent(ent);
		if ( slot == 1 ) {

			orig_Com_Printf("seq is %i,length is %i, first char is %02X, blossom is %02X\n",sequence,length,base[0], blossom);
		}
		usercmdCRC = false;
		return blossom;

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}






//3: 'h'
//2: "std_ilooking_n_a_a"
//1: 
//takepiss
void my_TakePiss(unsigned int arg1, char* arg2, int arg3)
{
	try{

	orig_Com_Printf("What %08X %08X %08X\n",arg1,arg2,arg3);
	orig_TakePiss(arg1,arg2,arg3);

	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}


// void		(*SP_Register)(const char *Package);
// void		(*SP_Print)(edict_t *ent, unsigned short ID, ...);
// void		(*SP_Print_Obit)(edict_t *ent, unsigned short ID, ...);
// int			(*SP_SPrint)(char *buffer, int buffer_size, unsigned short ID, ...);
// const char	*(*SP_GetStringText)(unsigned short ID);



void my_FX_HandleDMMuppleFlash(vec3_t start, vec3_t dir, edict_t *shooter, IGhoulInst *gun, int mupplefx)
{
	try{

	}
	// orig_FX_HandleDMMuppleFlash(start,dir,shooter,gun,mupplefx);


	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}




void my_SP_script_runner (edict_t *ent) {
	
	orig_Com_Printf(P_PINK"%s\n",*(char**)0x5015CC30);
	orig_SP_script_runner(ent);
}

// malloc
// realloc
// free
char * overflowed_data[16];
int data_len[16];
void my_SZ_Write(sizebuf_t * buf, void * data, int length)
{
	register int tt asm("ebp");
	unsigned int ret_address = *(unsigned int*)(tt + 4);
	if ( ret_address == 0x20062262 ) {
		// specific hook @ sv_startsound for client
		// unsigned char temp[256];
		// sprintf(temp,"say unreliable data written of length : %i\n",length);
		// orig_Cbuf_AddText(temp);
		for ( int i =0; i < maxclients->value; i++ ) {
			void * client_t = game_clients + i * 0xd2ac;
			sizebuf_t * dg = client_t + 0x2c4;
			int state = *(int*)(client_t);
			if ( state == cs_free || state == cs_zombie)
				continue;

			if ( buf == dg ) {
				edict_t * ent = get_ent_from_player_slot(i);
				sv_multicast->cursize = length;
				my_PF_Unicast(ent,0);
				return;
			}
		}

		
	} else {
		orig_SZ_Write(buf,data,length);
	}
	
}

int num_net_cmds[16];
networkCommand_t net_commands[16][MAX_NET_COMMANDS];
char unreliableData[16][TOTAL_PSIZE];//1390 * 1024
unsigned int unreliablePointer[16];

/*
MULTICAST_ALL,
MULTICAST_PHS,
MULTICAST_PVS,
MULTICAST_ALL_R,
MULTICAST_PHS_R,
MULTICAST_PVS_R
*/
sizebuf_t * sv_multicast = 0x203F6C34;
// sof Multicast has a third argument for some reason
// I THINK THIRD ARGUMENT IS SLOT NUMBER + 1 , EXCEPT HIM!
void my_SV_Multicast (vec3_t origin, multicast_t to, int unknown)
{
	// return orig_SV_Multicast(origin,to,unknown);
	// sv_multicast->overflowed = false;
	// sv_multicast->cursize = 0;
	// return;
	
	sizebuf_t * dg;
	int size_before = sv_multicast->cursize;
	int dg_before[16];
	for ( int i = 0 ; i < maxclients->value;i++ ) {
		void * client_t = game_clients + i * 0xd2ac;

		int state = *(int*)(client_t);
		if ( state == cs_free || state == cs_zombie)
			continue;
		// dont send unreliable to ppl who have not spawned
		if (state != cs_spawned )
			continue;
		dg = client_t + 0x2C4;
		dg_before[i] = dg->cursize;
	}

	// let it be called before
	// if this overflows writing to datagram, datagram will be cleared, cursize math corrupts
	// lets make sure the unreliable buffer does not overflow by clearing it often?
	orig_SV_Multicast(origin,to,unknown);

	// unreliable
	if ( to < 3 ) {
		int maxloop = maxclients->value;
		for ( int i=0; i < maxloop;i++) {
			void * client_t = game_clients + i * 0xd2ac;

			int state = *(int*)(client_t);
			if ( state == cs_free || state == cs_zombie)
				continue;
			// dont send unreliable to ppl who have not spawned
			if (state != cs_spawned )
				continue;

			// unreliable datagram
			dg = client_t + 0x2C4;
			int len = dg->cursize - dg_before[i];
			if ( dg->cursize >  dg_before[i]) {
				// orig_Com_Printf("unreli pointer = %i\n",unreliablePointer[i]);
				memcpy(&(unreliableData[i][unreliablePointer[i]]),dg->data + dg_before[i],len);

				unreliablePointer[i]+=len;
				// save cursize
				net_commands[i][num_net_cmds[i]].msgsize = len;
				num_net_cmds[i]++;
			}
			// clear datagram unreliable buffer
			dg->cursize = 0;
			dg->overflowed = false;
		}
	}
	
	/*
	Multicast will copy sv.multicast into ALL reliable or unreliable client buffers
	*/
	
}
// I THINK THIRD ARGUMENT IS SLOT NUMBER , EXCEPT HIM!
void my_SV_Multicast2 (vec3_t origin, multicast_t to,int unknown)
{
	// sv_multicast->overflowed = false;
	// sv_multicast->cursize = 0;
	// return;
	
	sizebuf_t * dg;
	int size_before = sv_multicast->cursize;
	int dg_before[16];
	void * client_t = NULL;
	int i = 0;
	for ( i = 0 ; i < maxclients->value;i++ ) {
		client_t = game_clients + i * 0xd2ac;

		int state = *(int*)(client_t);
		if ( state == cs_free || state == cs_zombie)
			continue;
		// dont send unreliable to ppl who have not spawned
		if (state != cs_spawned )
			continue;
		dg = client_t + 0x2C4;
		dg_before[i] = dg->cursize;
	}

	// let it be called before
	orig_SV_Multicast2(origin,to,unknown);

	// unreliable
	if ( to < 3) {
		int maxloop = maxclients->value;
		for ( i=0; i < maxloop;i++) {
			client_t = game_clients + i * 0xd2ac;

			int state = *(int*)(client_t);
			if ( state == cs_free || state == cs_zombie)
				continue;
			// dont send unreliable to ppl who have not spawned
			if (state != cs_spawned )
				continue;

			dg = client_t + 0x2C4;
			// sample how many bytes were written to the buffer
			int len = dg->cursize - dg_before[i];

			if ( dg->cursize >  dg_before[i]) {
				// orig_Com_Printf("Client %i ::  %i %i\n",i,len,unknown);

				// orig_Com_Printf("unreli pointer = %i\n",unreliablePointer[i]);
				memcpy(&(unreliableData[i][unreliablePointer[i]]),dg->data + dg_before[i],len);
				unreliablePointer[i]+=len;
				// save cursize
				net_commands[i][num_net_cmds[i]].msgsize = len;
				num_net_cmds[i]++;
			}
			// this is quite important to make sure the unreliable buffer never overflows
			dg->cursize = 0;
			dg->overflowed = false;
		}
	}
	
	/*
	Multicast will copy sv.multicast into ALL reliable or unreliable client buffers
	*/
}

void my_PF_Unicast (edict_t *ent, qboolean reliable)
{
	// sv_multicast->overflowed = false;
	// sv_multicast->cursize = 0;
	// return;

	if ( !reliable ) {
		// write directly into our buffer instead of using datagram unreliable buffer
		int slot =  get_player_slot_from_ent(ent);
		// if ( !_sf_sv_sofree_debug->value ) {
			num_net_cmds[slot]++;
			// save cursize
			net_commands[slot][num_net_cmds[slot]-1].msgsize = sv_multicast->cursize;
			// orig_Com_Printf("unreli pointer = %i\n",unreliablePointer[slot]);
			memcpy(&(unreliableData[slot][unreliablePointer[slot]]),sv_multicast->data,sv_multicast->cursize);
			unreliablePointer[slot]+=sv_multicast->cursize;
		// } else {
		// 	orig_PF_Unicast(ent,reliable);
		// }


		sv_multicast->overflowed = false;
		sv_multicast->cursize = 0;
		
	} else {
		orig_PF_Unicast(ent,reliable);
	}
	
	/*
	Unicast will copy sv.multicast into reliable or unreliable client buffer
	*/
	// orig_PF_Unicast(ent,reliable);
}


void my_SV_WriteFrameToClient (client_t *client, sizebuf_t *msg)
{
	// client->lastframe
	// this disables delta compression
	// *(int*)(client + 0x204) = -1;
	orig_SV_WriteFrameToClient(client,msg);
}


void my_MSG_WriteShort(sizebuf_t *sb, int c)
{
	orig_MSG_WriteShort(sb,c);
}
sizebuf_t * g_msg;
int sizeAtEmit;
void * savedTo;
int entcount;
int removeCmdCount;
bool inwritedelta;
/*

*/
void my_MSG_WriteDeltaEntity (struct entity_state_s *from, struct entity_state_s *to, sizebuf_t *msg, qboolean force, qboolean newentity)
{
	inwritedelta = true;
	orig_MSG_WriteDeltaEntity(from,to,msg,force,newentity);
	inwritedelta = false;
	// inside SV_EmitPacketEntities
	if ( g_msg ) {
		// g_msg->maxsize == 1400
		int cursize = g_msg->cursize - sizeAtEmit;
		
		// break if we run out of room
		// size of an entity and size of header
		if (  g_msg->cursize >= ( g_msg->maxsize - 40 - 16) ) {
			// break from SV_EmitPacketEntities loop please by faking to->num_entities
			*(int*)(savedTo + 0xEC) = 0;
			// orig_Com_Error(ERR_FATAL,"This map has too many entities, please ask map developer to fix it\n");
			// orig_Com_Printf("cursize = %i g_msg.cursize = %i g_msg.maxsize = %i\n",cursize,g_msg->cursize,g_msg->maxsize);
			orig_Cbuf_AddText("say overflowing entitiesDelta\n");
		}
		entcount++;
	}
}


/*
	entity upperlimit - refuse to send all ents
*/
void my_MSG_WriteUnknownDelta(sizebuf_t *sb, int c)
{
	orig_MSG_WriteUnknownDelta(sb,c);
	// inside SV_EmitPacketEntities
	if ( g_msg && !inwritedelta) {
		int cursize = g_msg->cursize - sizeAtEmit;
		// break if we run out of room
		if ( g_msg->cursize >= ( g_msg->maxsize - 40 - 16) ) {
			// break from SV_EmitPacketEntities loop please by faking to->num_entities
			*(int*)(savedTo + 0xEC) = 0;
			// orig_Com_Error(ERR_FATAL,"This map has too many entities, please ask map developer to fix it\n");
			// orig_Cbuf_AddText("say overflowing entitiesUnknown\n");
		}
		removeCmdCount++;
	}
}


/*
save msg here into global
dont allow to send too many entities to clients
entity upperlimit - refuse to send all ents
*/
void my_SV_EmitPacketEntities (void *from, void *to, sizebuf_t *msg)
{
	sizeAtEmit = msg->cursize;
	g_msg = msg;
	savedTo = to;
	entcount = 0;
	removeCmdCount = 0;
	int size_before = msg->cursize;

	// cap num_entities to 64...
	// save for restoration later
	int num_ents = *(int*)(to + 0xEC);

	
	// if ( num_ents > 64 ) {
	// 	*(int*)(to + 0xEC) = 64;
	// }

	// save and restore to->num_ents
	// orig_SV_EmitPacketEntities(from,to,msg);
	// PUT FROM As NULL to force retransmit instead of delta?? :P
	orig_SV_EmitPacketEntities(from,to,msg);

	// orig_Com_Printf("originally %i limited to %i numremoves %i\n",num_ents,entcount,removeCmdCount);

	// because i use a trick to end a loop inside emitpacketetieis whcih involve this var
	// restoration
	*(int*)(to + 0xEC) = num_ents;
	g_msg = NULL;
}

// this is not a detour, its a jmp overwrite
/*
SendClientDatagram
Builds the frame and the entities based on PHS etc.. then calls Netchan_Transmit..
*/
void my_Netchan_Transmit (netchan_t *chan, int length, byte *data)
{
	// orig_Netchan_Transmit(chan,length,data);
	// return;

	
	// sizebuf_t * reli_msg  = (sizebuf_t*)((unsigned int)chan + 0x48);
	sizebuf_t * reli_msg = &chan->message;
	// if ( reli_msg != &chan->message)
		// orig_Com_Printf("chan does not work\n");
	
	
	// send the frame !!!
	// works better when The frame is sent FIRST SHAKEY BUG.. otherwise.
	Netchan_Transmit_Unreliable(chan,length,data);

	qboolean	send_reliable;

// if the remote side dropped the last reliable message, resend it
	send_reliable = false;

	int len = chan->reliable_length;
	if (chan->incoming_acknowledged > chan->last_reliable_sequence
	&& chan->incoming_reliable_acknowledged != chan->reliable_sequence)
		send_reliable = true;

// if the reliable transmit buffer is empty, copy the current message out
	if (!chan->reliable_length && chan->message.cursize)
	{
		send_reliable = true;
		len = chan->message.cursize;
	}
	char extra[64];
	extra[0] = 0x00;
	if ( send_reliable ) {
		
		char emptybuffer;
		#ifdef NETDEBUG
		if ( reli_msg->cursize ) 
			sprintf(extra,"reli size = %i",len);
		#endif
		// send reliable!!
		orig_Netchan_Transmit(chan,0,&emptybuffer);
	}
	#ifdef NETDEBUG
	orig_Com_Printf("frame/ents = %i %s\n",length,extra);
	#endif
}

float ammofix = -1;
void my_DoRespawn(edict_t * ent)
{

	// char text[256];
	// sprintf(text,"say MINS IS %f MAXS IS %f\n",ent->mins[2],ent->maxs[2]);
	// orig_Cbuf_AddText(text);

	orig_DoRespawn(ent);

	ent->solid = SOLID_TRIGGER;
}


void my_SV_ExecuteClientMessage(client_t *cl)
{
	SV_ExecuteClient = cl;
	orig_SV_ExecuteClientMessage(cl);
}



void my_COM_BlockChecksum(void * buffer, int length)
{	
	if ( usercmdCRC ) {
		edict_t * ent = stget(SV_ExecuteClient,CLIENT_ENT);
		int slot = get_player_slot_from_ent(ent);
		if ( slot == 1 ) {
			orig_Com_Printf("internal chkb\n");
			for (int i= 0; i < length; i ++ ) {
				orig_Com_Printf("%02X ",*(unsigned char*)(buffer+i));
			}
			orig_Com_Printf("\n");
		}	
	}
	orig_COM_BlockChecksum(buffer,length);
}


void __thiscall my_PutBits(void * self,const void *x,int NumBits)
{
	orig_Com_Printf("my_PutBits!!!\n");
	orig_PutBits(self,x,NumBits);
}


void my_MSG_WriteDeltaUsercmd (sizebuf_t *sb, struct usercmd_s *from, struct usercmd_s *cmd)
{
	
}

void * generateFakeStack(char * instr) {
	// orig_Com_Printf("attempting to parse : %08X %s\n",instr,instr);
	// int c = orig_Cmd_Argc() - 1;
	void * membuff = NULL;
	void * mb;
	int count = 0;
	char * c = instr;
	while ( *c != 0x00 ) {
		if ( *c == '%') {
			char * nc = c+1;
			if ( *nc != 0x00 ) {
				if ( *nc == 'd' ) {
					c++;
					count++;
					membuff = my_realloc(membuff,count*4);
					*(int*)(membuff + (count-1)*4) = atoi(orig_Cmd_Argv(count + 3));
				} else if ( *nc == 'h' ) {
					c++;
					if ( *(nc+1) == 'd' ) {
						c++;
						count++;
						membuff = my_realloc(membuff,count*4);
						*(int*)(membuff + (count-1)*4) = atoi(orig_Cmd_Argv(count + 3)) & 0xFFFF;
					} else if ( *(nc+1) == 'u' ) {
						c++;
						count++;
						membuff = my_realloc(membuff,count*4);
						*(unsigned int*)(membuff + (count-1)*4) = atoi(orig_Cmd_Argv(count + 3)) & 0xFFFF;
					}
				} else if ( *nc == 's' ) {
					c++;
					count++;
					membuff = my_realloc(membuff,count*4);
					*(char**)(membuff + (count-1)*4) = orig_Cmd_Argv(count + 3);
				} else if ( *nc == 'p' ) {
					c++;
					count++;
					membuff = my_realloc(membuff,count*4);
					*(unsigned int*)(membuff + (count-1)*4) = atoi(orig_Cmd_Argv(count + 3)) & 0xFF;
				}
			}
			

		}
		c++;
	}
	return membuff;
}

unsigned int __thiscall my_SP_vnsprintf(void * self, char * writetome,int size,void * va_list)
{
	void * fakestack = NULL;
	if ( INSIDE_SPACKAGE_PRINT_ID ) {
		char * formatstring = *(char**)(self + 0xC);
		fakestack = generateFakeStack(formatstring);
		// orig_Com_Printf("fakestack is : %08X\n",fakestack);
		if ( fakestack != NULL ) 
			va_list = fakestack;
		INSIDE_SPACKAGE_PRINT_ID = false;
	}
	
	return orig_SP_vnsprintf(self,writetome,size,va_list);

	if ( fakestack ) {
		free(fakestack);
	}
}

/*
This function seems to have a lot of differences than q2.

eg. Velocity = 0 before accel.

int shittycounter = 0;
void my_PM_AirMove(void) {
	
	if ( shittycounter % 20 == 0 ) {
		float velX = *(float*)0x2039022C;
		float velY = *(float*)0x20390230;
		float modVel = velX * velX + velY * velY;
		modVel = sqrt(modVel);
		orig_Com_Printf("+++++++\nVelocity before = %f\n",modVel);
	}
	
	if ( shittycounter % 20 == 0 ) {
		float velX = *(float*)0x2039022C;
		float velY = *(float*)0x20390230;
		float modVel = velX * velX + velY * velY;
		modVel = sqrt(modVel);
		orig_Com_Printf("Velocity after = %f\n",modVel);
	}
	

	/*if ( shittycounter % 20 == 0 ) {
		unsigned int pmove = *(unsigned int*)0x20390290;
		unsigned int groundEnt = *(unsigned int*)(pmove+0xE4);
		orig_Com_Printf("groundEnt = %i groundSurf = %i\n",groundEnt,*(unsigned int*)0x20390260);
	}
	shittycounter++;
	*/

	

	// orig_PM_AirMove();
	/*
	if ( pml_velocity[2] != 0.0 )
	orig_Com_Printf("velocity at end of frame is %f\n",pml_velocity[2]);
	
}
*/

/*
==============
PM_Accelerate

Handles user intended acceleration
==============
*/
void PM_Accelerate (vec3_t wishdir, float wishspeed, float accel, float addspeed)
{
	int			i;
	float		accelspeed;

	// if  ( !(*pm)->groundentity ) return;
	float friction_loss = *(float*)0x2039028C;

	// orig_Com_Printf("Before addspeed\n");
	if (addspeed <= 0)
		return;

	// SOF DIFFERNCE - moved location
	// currentspeed = DotProduct (pml_velocity, wishdir);
	// addspeed = wishspd - currentspeed;
	// if (addspeed <= 0)
	// 	return;
	accelspeed = accel * wishspeed * *pml_frametime * friction_loss;
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	
	// orig_Com_Printf("Before vels\n");
	for (i=0 ; i<3 ; i++)
		pml_velocity[i] += accelspeed*wishdir[i];	

	// orig_Com_Printf("End of accel func\n");
	

	
}


/*
===================
PM_AirMove

===================
*/
void my_PM_AirMove (void)
{
	// orig_PM_AirMove();
	// return;
	int			i;
	vec3_t		wishvel;
	float		fmove, smove;
	vec3_t		wishdir;
	float		wishspeed;
	float		maxspeed;

	fmove = (*pm)->cmd.forwardmove;
	smove = (*pm)->cmd.sidemove;

	
//!!!!! pitch should be 1/3 so this isn't needed??!
// #if 0
	pml_forward[2] = 0;
	pml_right[2] = 0;
	VectorNormalize (pml_forward);
	VectorNormalize (pml_right);

	// orig_Com_Printf("%f %f\n",fmove,smove);
// #endif

	for (i=0 ; i<2 ; i++)
		wishvel[i] = pml_forward[i]*fmove + pml_right[i]*smove;
	wishvel[2] = 0;

	orig_PM_AddCurrents (wishvel);

	VectorCopy (wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	// wishspeed = magnitude of wishvel
	// wishdir = unit vector of wishvel

//
// clamp to server defined max speed
//
	// only duckspeed when grounded
	maxspeed = ((*pm)->s.pm_flags & PMF_DUCKED && (*pm)->s.pm_flags & PMF_ON_GROUND) ? *pm_duckspeed : *pm_runspeed;

	if (wishspeed > maxspeed)
	{
		// VectorScale (wishvel, maxspeed/wishspeed, wishvel);
		wishvel[2] *= maxspeed/wishspeed;
		wishspeed = maxspeed;
	}
	float addspeed,currentspeed;


	// project current speed vector onto the wish unit vector
	currentspeed = DotProduct (pml_velocity, wishdir);
	addspeed = wishspeed - currentspeed;
	
	if ( *pml_ladder )
	{
		
		PM_Accelerate (wishdir, wishspeed, *pm_accelerate,addspeed);
		if (!wishvel[2])
		{
			if (pml_velocity[2] > 0)
			{
				pml_velocity[2] -= (*pm)->s.gravity * *pml_frametime;
				if (pml_velocity[2] < 0)
					pml_velocity[2]  = 0;
			}
			else
			{
				pml_velocity[2] += (*pm)->s.gravity * *pml_frametime;
				if (pml_velocity[2] > 0)
					pml_velocity[2]  = 0;
			}
		}
		orig_PM_StepSlideMove (1);
	}
	else if ( (*pm)->groundentity )
	{	// walking on ground

		// orig_Com_Printf("GROUND!!\n");
		// SOF DIFFERENCE TO Q2 here!!
		// pml_velocity[2] = 0; //!!! this is before the accel
		PM_Accelerate (wishdir, wishspeed, *pm_accelerate,addspeed);

// PGM	-- fix for negative trigger_gravity fields
		pml_velocity[2]  = 0;

		// orig_Com_Printf("%f %f %f\n",pml_velocity[0],pml_velocity[1],pml_velocity[2]);

		// SOF DIFFERENCE TO Q2 HERE !!
		// if((*pm)->s.gravity > 0) 
		// 	pml_velocity[2] = 0;
		// else
		// 	pml_velocity[2] -= (*pm)->s.gravity * *pml_frametime;
// PGM

		if (!pml_velocity[0] && !pml_velocity[1])
			return;
		orig_PM_StepSlideMove (1);
	}
	else
	{	// not on ground, so little effect on velocity
		
		// orig_Com_Printf("AIR!!\n");
		PM_Accelerate (wishdir, wishspeed, 1.0f, addspeed);
		// orig_Com_Printf("Gravity!!\n");
		// add gravity
		pml_velocity[2] -= (*pm)->s.gravity * (*pml_frametime);
		// my_PM_StepSlideMove (1);
		orig_PM_StepSlideMove(1);

	}
	// orig_Com_Printf("EndAirmove!!\n");

}

void my_PM_CatagorizePosition(void)
{
	static edict_t * prevGround = NULL;
	vec3_t point;
	trace_t trace;
	float norm_before;
	// if (pml_velocity[2] > 100) {
	// 	//orig_Com_Printf("I am flying 100%% wooo\n");
	// }
	float vel_before = pml_velocity[2];


	// orig_Com_Printf("velocity is %f\n",vel_before);

	orig_PM_CatagorizePosition();
	//sof sets velocity to 0

	// fixes slide bug
	// if velocity was adjusted, undo the change
	if ( _sf_sv_q2_mode->value ) {
		if ( pml_velocity[2] != vel_before && _sf_sv_q2_slide_fix->value ) pml_velocity[2] = vel_before;
	}
/*
	//if ( prevGround && !((*pm)->groundentity) ) {
	// if ( (*pm)->s.pm_flags & PMF_DUCKED ) {
		// orig_Com_Printf("Flying now! %08X\n",__builtin_return_address(0));

		point[0] = pml_origin[0];
		point[1] = pml_origin[1];
		point[2] = pml_origin[2] - 0.25;
		
		trace = (*pm)->trace (pml_origin, (*pm)->mins, (*pm)->maxs, point);
		// if ( norm_before >= 0.7 && trace.plane.normal[2] < 0.7 ) {
		// 	orig_Com_Printf("normal BROKEN %08X\n",trace.ent);
		// }
		// if ( norm_before < 0.7 && trace.plane.normal[2] >= 0.7 ) {
		// 	orig_Com_Printf("normal FIXED %08X\n",trace.ent);
		// }
		// norm_before = trace.plane.normal[2];
		// orig_Com_Printf("origin = %f\n",pml_origin[2]);
	// }
	//if ( !prevGround && (*pm)->groundentity ) {
	// else {
		// orig_Com_Printf("Grounded now! %08X\n",__builtin_return_address(0));
		// point[0] = pml_origin[0];
		// point[1] = pml_origin[1];
		// point[2] = pml_origin[2] - 0.25;
		
		// trace = (*pm)->trace (pml_origin, (*pm)->mins, (*pm)->maxs, point);
		// if ( trace.fraction < 1.0 ) {
		// 	orig_Com_Printf("SSTrace fraction less than 1\n");
		// }
		// if ( trace.ent ) {
		// 	orig_Com_Printf("SSTrace ent!\n");
		// }
		// if ( vel_before < 0 ) {
		// 	orig_Com_Printf("SSnegative velo\n");
		// }
	// }
	
	//prevGround = (*pm)->groundentity;
	*/
	
}


qboolean	PM_GoodPosition (void)
{
	trace_t	trace;
	vec3_t	origin, end;
	int		i;

	if ((*pm)->s.pm_type == PM_SPECTATOR ||  (*pm)->s.pm_type == PM_NOCLIP)
		return true;

	for (i=0 ; i<3 ; i++)
		origin[i] = end[i] = (*pm)->s.origin[i]*0.125;
	trace = (*pm)->trace (origin, (*pm)->mins, (*pm)->maxs, end);

	return !trace.allsolid;
}
#define VectorCopyH(a,b)			(b[0]=a[0],b[1]=a[1],b[2]=a[2])
/*
This fixes slide bug... lol

Sof is using the other version that starts at 1 then goes to 0, then goes to -1
*/
void my_PM_InitialSnapPosition(void)
{
	if ( _sf_sv_q2_mode->value ) {
		int        x, y, z;
		short      base[3];
		static int offset[3] = { 0, -1, 1 };

		VectorCopyH ((*pm)->s.origin, base);

		for ( z = 0; z < 3; z++ ) {
			(*pm)->s.origin[2] = base[2] + offset[ z ];
			for ( y = 0; y < 3; y++ ) {
				(*pm)->s.origin[1] = base[1] + offset[ y ];
				for ( x = 0; x < 3; x++ ) {
					(*pm)->s.origin[0] = base[0] + offset[ x ];
					if (PM_GoodPosition ()) {
						pml_origin[0] = (*pm)->s.origin[0]*0.125;
						pml_origin[1] = (*pm)->s.origin[1]*0.125;
						pml_origin[2] = (*pm)->s.origin[2]*0.125;
						VectorCopyH ((*pm)->s.origin, pml_previous_origin);
						return;
					}
				}
			}
		}

		//Com_DPrintf ("Bad InitialSnapPosition\n");
	} else {
		orig_PM_InitialSnapPosition();
	}
	
}

void my_PM_SnapPosition(void)
{

	// orig_Com_Printf("lol inside the func\n");
	bool truncActive = false;

	int		sign[3];
	int		i, j, bits;
	short	base[3];
	// try all single bits first
	static int jitterbits[8] = {0,4,1,2,3,5,6,7};

	// snap velocity to eigths
	for ( i=0;i<3;i++)
		(*pm)->s.velocity[i] = (int)(pml_velocity[i]*8);


	for (i=0 ; i<3 ; i++)
	{
		if (pml_origin[i] >= 0)
		{
			/*if ( i == 2 )
				sign[i] = -1;
			else*/
			sign[i] = 1;
		}
		else
		{
			/*if ( i == 2 )
				sign[i] = 1;
			else*/
			sign[i] = -1;
				//Com_Printf("pml_origin is %f origin is %i\n",*pml_origin[i],*origin[i]);
			// orig_Com_Printf("Wohooo negative!\n");
		}
		
		(*pm)->s.origin[i] = (int)(pml_origin[i]*8);
		//if ( i == 2)
			//Com_Printf("%f * 8 = %i\n",*pml_origin[i],*origin[i]);
		if ((*pm)->s.origin[i]*0.125 == pml_origin[i])
		{
			//Com_Printf("sign is 0!\n");
			sign[i] = 0;
		}
		else {
			if ( i == 2  && sign[i] == -1) {
				truncActive = true;
			}
		}
	}

	// if ( truncActive) orig_Com_Printf("before origin_Z = %hu\n",(*pm)->s.origin[2]);
	
	//Com_Printf("signx is %i signz is %i signy is %i\n",sign[0],sign[1],sign[2]);
	VectorCopyH ((*pm)->s.origin, base);

	// try all combinations
	for (j=0 ; j<8 ; j++)
	{
		bits = jitterbits[j];
		VectorCopyH (base, (*pm)->s.origin);
		for (i=0 ; i<3 ; i++)
		{
			
			if (bits & (1<<i) )
			{
				//if ( i == 2 && sign[i] == -1)
					//Com_Printf("%i add with %i\n",*origin[i],sign[i]);
				/*if ( j == 0 && i == 2 )
					*origin[i] += -1;
				else*/
				(*pm)->s.origin[i] += sign[i];
			}
		}
		
		bool ret = PM_GoodPosition();
		if ( ret ) {
			// if ( truncActive) orig_Com_Printf("after origin_Z = %hu fixed with %i:%i,%i,%i\n",(*pm)->s.origin[2],bits,sign[0],sign[1],sign[2]);
			return;
		}
		
	}

	// go back to the last position
	//Com_Printf("SnapPosition : LAST POSITION TIME!\n");

	VectorCopyH (pml_previous_origin, (*pm)->s.origin);

	if ( truncActive) orig_Com_Printf("No change no good position %f\n",(*pm)->s.origin[2]);

}

#define	STEPSIZE	18
#define	MIN_STEP_NORMAL	0.7		// can't step up onto very steep slopes
#define	MAX_CLIP_PLANES	5
#define	STOP_EPSILON	0.1
void my_PM_StepSlideMove(int argument)
{
	// currently causes spec to crash when it touches things
	orig_PM_StepSlideMove(argument);
	return;
	vec3_t		start_o, start_v;
	vec3_t		down_o, down_v;
	trace_t		trace;
	float		down_dist, up_dist;
	vec3_t		delta;
	vec3_t		up, down;

	VectorCopyH (pml_origin, start_o);
	VectorCopyH (pml_velocity, start_v);

	my_PM_StepSlideMove_();

	VectorCopyH (pml_origin, down_o);
	VectorCopyH (pml_velocity, down_v);

	VectorCopyH (start_o, up);
	up[2] += STEPSIZE;

	trace = (*pm)->trace (up, (*pm)->mins, (*pm)->maxs, up);
	if (trace.allsolid)
		return;		// can't step up

	// try sliding above
	VectorCopyH (up, pml_origin);
	VectorCopyH (start_v, pml_velocity);

	my_PM_StepSlideMove_();

	// push down the final amount
	VectorCopyH (pml_origin, down);
	down[2] -= STEPSIZE;
	trace = (*pm)->trace (pml_origin, (*pm)->mins, (*pm)->maxs, down);
	if (!trace.allsolid)
	{
		VectorCopyH (trace.endpos, pml_origin);
	}

if ( !_sf_sv_q2_mode->value ) {
	// sof uses this ...
	VectorSubtract (pml_origin, up, delta);
	up_dist = DotProduct (delta, start_v);

	VectorSubtract (down_o, start_o, delta);
	down_dist = DotProduct (delta, start_v);
}
else {
	// quake uses this
	VectorCopyH(pml_origin, up);

	// decide which one went farther
    down_dist = (down_o[0] - start_o[0])*(down_o[0] - start_o[0])
        + (down_o[1] - start_o[1])*(down_o[1] - start_o[1]);
    up_dist = (up[0] - start_o[0])*(up[0] - start_o[0])
        + (up[1] - start_o[1])*(up[1] - start_o[1]);
}

	if (down_dist > up_dist || trace.plane.normal[2] < MIN_STEP_NORMAL)
	{
		VectorCopyH (down_o, pml_origin);
		VectorCopyH (down_v, pml_velocity);
		return;
	}

	// This is what causes q2 to not use TIME_JUMP lol
	//!! Special case
	// if we were walking along a plane, then we need to copy the Z over
	
	if ( _sf_sv_q2_style_jump->value || _sf_sv_q2_mode->value ) 
		pml_velocity[2] = down_v[2];
}

/*
==================
PM_StepSlideMove

Each intersection will try to step over the obstruction instead of
sliding along it.

Returns a new origin, velocity, and contact entity
Does not modify any world state?
==================
*/
#define	MIN_STEP_NORMAL	0.7		// can't step up onto very steep slopes
#define	MAX_CLIP_PLANES	5
void my_PM_StepSlideMove_ (void)
{
	int			bumpcount, numbumps;
	vec3_t		dir;
	float		d;
	int			numplanes;
	vec3_t		planes[MAX_CLIP_PLANES];
	vec3_t		primal_velocity;
	int			i, j;
	trace_t	trace;
	vec3_t		end;
	float		time_left;
	float rub;
	
	numbumps = 4;
	
	VectorCopyH (pml_velocity, primal_velocity);
	numplanes = 0;
	
	time_left = *pml_frametime;

	for (bumpcount=0 ; bumpcount<numbumps ; bumpcount++)
	{
		for (i=0 ; i<3 ; i++)
			end[i] = pml_origin[i] + time_left * pml_velocity[i];

		trace = (*pm)->trace (pml_origin, (*pm)->mins, (*pm)->maxs, end);

		if (trace.allsolid)
		{	// entity is trapped in another solid
			pml_velocity[2] = 0;	// don't build up falling damage
			return;
		}

		if (trace.fraction > 0)
		{	// actually covered some distance
			VectorCopyH (trace.endpos, pml_origin);
			numplanes = 0;
		}

		if (trace.fraction == 1)
			 break;		// moved the entire distance

		// save entity for contact
		if ((*pm)->numtouch < MAXTOUCH && trace.ent)
		{
			(*pm)->touchents[(*pm)->numtouch] = trace.ent;
			(*pm)->numtouch++;
		}
		
		time_left -= time_left * trace.fraction;

		// slide along this plane
		if (numplanes >= MAX_CLIP_PLANES)
		{	// this shouldn't really happen
			VectorCopyH (vec3_origin, pml_velocity);
			break;
		}

		VectorCopyH (trace.plane.normal, planes[numplanes]);
		numplanes++;

if (!_sf_sv_q2_mode->value) {
// sof uses this

		//
		// modify velocity so it parallels all of the clip planes
		//
		if (numplanes == 1)
		{	// go along this plane
			VectorCopy (pml_velocity, dir);
			VectorNormalize (dir);
			rub = 1.0 + 0.5 * DotProduct (dir, planes[0]);

			// slide along the plane
			my_PM_ClipVelocity (pml_velocity, planes[0], pml_velocity, 1.01);
			// rub some extra speed off on xy axis
			// not on Z, or you can scrub down walls
			pml_velocity[0] *= rub;
			pml_velocity[1] *= rub;
			pml_velocity[2] *= rub;
		}
		else if (numplanes == 2)
		{	// go along the crease
			VectorCopy (pml_velocity, dir);
			VectorNormalize (dir);
			rub = 1.0 + 0.5 * DotProduct (dir, planes[0]);

			// slide along the plane
			CrossProduct (planes[0], planes[1], dir);
			d = DotProduct (dir, pml_velocity);
			VectorScale (dir, d, pml_velocity);

			// rub some extra speed off
			VectorScale (pml_velocity, rub, pml_velocity);
		}
		else
		{
//			Con_Printf ("clip velocity, numplanes == %i\n",numplanes);
			VectorCopy (vec3_origin, pml_velocity);
			break;
		}
}
else {
// quake uses this
//
// modify original_velocity so it parallels all of the clip planes
//
		for (i=0 ; i<numplanes ; i++)
		{
			my_PM_ClipVelocity (pml_velocity, planes[i], pml_velocity, 1.01);
			for (j=0 ; j<numplanes ; j++)
				if (j != i)
				{
					if (DotProduct (pml_velocity, planes[j]) < 0)
						break;	// not ok
				}
			if (j == numplanes)
				break;
		}
		
		if (i != numplanes)
		{	// go along this plane
		}
		else
		{	// go along the crease
			if (numplanes != 2)
			{
//				Con_Printf ("clip velocity, numplanes == %i\n",numplanes);
				VectorCopyH (vec3_origin, pml_velocity);
				break;
			}
			CrossProduct (planes[0], planes[1], dir);
			d = DotProduct (dir, pml_velocity);
			VectorScale (dir, d, pml_velocity);
		}
}
// #endif
		//
		// if velocity is against the original velocity, stop dead
		// to avoid tiny occilations in sloping corners
		//
		if (DotProduct (pml_velocity, primal_velocity) <= 0)
		{
			VectorCopyH (vec3_origin, pml_velocity);
			break;
		}
	}

	if ((*pm)->s.pm_time)
	{
		VectorCopyH (primal_velocity, pml_velocity);
	}
}

/*
==================
PM_ClipVelocity

Slide off of the impacting object
returns the blocked flags (1 = floor, 2 = step / wall)
==================
*/
#define	STOP_EPSILON	0.1

void my_PM_ClipVelocity (vec3_t in, vec3_t normal, vec3_t out, float overbounce)
{
	float	backoff;
	float	change;
	int		i;
	
	backoff = DotProduct (in, normal) * overbounce;

	for (i=0 ; i<3 ; i++)
	{
		change = normal[i]*backoff;
		out[i] = in[i] - change;
		if (out[i] > -STOP_EPSILON && out[i] < STOP_EPSILON)
			out[i] = 0;
	}
}



void my_M_AddServerToList(netadr_t adr, char * serverdata)
{
	orig_Com_Printf("Calling M_AddServerToList!\n");
	orig_M_AddServerToList(adr, serverdata);
}