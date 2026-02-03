#include "../../../hdr/feature_config.h"

#if FEATURE_GRENADE

#include <windows.h>
#include "../../../hdr/sofheader.h"
#include "../../DetourXS/detourxs.h"

extern cvar_t * _sf_sv_grenade_impact_explode;

void grenade_applyHooks(void) {
	DWORD dwProt = NULL;
	if ( _sf_sv_grenade_impact_explode->value == 0.0f ) {
		void * addr = 0x50101fb3;
		int count = 6;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		*(unsigned int*)0x50101fB3 = 50153;
		*(unsigned char*)0x50101fB7 = 0x00;
		*(unsigned char*)0x50101fB8 = 0x90;
		VirtualProtect(addr, count, dwProt, new DWORD);
	} else {
		void * addr = 0x50101fb3;
		int count = 6;
		VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
		*(unsigned int*)0x50101fB3 = 12747791;
		*(unsigned char*)0x50101fB7 = 0x00;	
		*(unsigned char*)0x50101fB8 = 0x00;	
		VirtualProtect(addr, count, dwProt, new DWORD);
	}
}

#else

void grenade_applyHooks(void) {}

#endif

