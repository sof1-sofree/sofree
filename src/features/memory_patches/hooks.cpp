#include "../../../hdr/feature_config.h"

#if FEATURE_MEMORY_PATCHES

#include <windows.h>
#include "../../../hdr/sofheader.h"

extern float ammofix;

void memory_patches_applyPatches(void) {
	DWORD dwProt = NULL;
	void *addr = NULL;
	int count = 0;

	// DISABLE GRAVITY SET FROM SV_GRAVITY CVAR
	// Gravity "mov     [ebx+12h], ax" DELETE
	addr = 0x500F5626;
	count = 4;
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
	char * blehpatch = (char*)0x500F9E2F;
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
	addr = (void*)0x20062603;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SV_SendClientMessages Line 542 SV_BroadcastPrintf(Client overflowed) DELETE 
	/*
		If the reliable buffer overflowed this frame Spam it to everyone
	*/
	addr = (void*)0x200625F8;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SV_SendClientMessages Line 544 SV_RateDrop DELETE
	/*
		Means that clients with bad setup can get most smooth experience without frame skipping
	*/
	addr = (void*)0x200626B9;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0xEB,1);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SV_SendClientDatagram Line 416 SZ_Write(msg,unreliablebuffer) ... DELETE
	/*
		Would usually copy the unreliable buffer into the msg buffer for sending out in netchan_transmit.
		But we handle this ourself, so no need to pass this data through.
		I think we only want frame data to be in there. So that the frame space is largest possible
	*/
	addr = (void*)0x200624E2;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SV_SendClientDatagram Line 414 Com_Printf('datagram overflowed for client') DELETED
	/*
		This means that the unreliable buffer (client->datagram) overflowed this frame and will not be
		copied into msg, hence the final buffer... 0 unreliable data this frame.. sorry. OLDSTYLE.
	*/
	addr = (void*)0x200624C5;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SV_SendClientDatagram Line 421 rename warning
	addr = (void*)0x2013A30C;
	char lolmsg[64] = "Frame doesnt fit for %s\n";
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	strcpy((char*)addr,lolmsg);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// SZ_GetSpace Line 901:common.c Com_Printf("SZ_GetSpace: overflow\n") DELETED
	addr = (void*)0x2001E7F5;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);

	// bbox offset fix sp_ammo_slug sp_ammo_shotgun
	addr = (void*)0x50069AE4;
	count = 4;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	*(unsigned int*)0x50069AE4 = (unsigned int)&ammofix;
	VirtualProtect(addr, count, dwProt, new DWORD);

	// Cmd_Score_f not called in player_die NOP!
	addr = (void*)0x500F2C7E;
	count = 5;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);
}

#else

void memory_patches_applyPatches(void) {}

#endif

