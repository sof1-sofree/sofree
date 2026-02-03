#include "../../../hdr/feature_config.h"

#if FEATURE_GRAVITY

#include <windows.h>
#include "../../../hdr/sofheader.h"

extern cvar_t * _sf_sv_gravity_default;

void gravity_applyHooks(void) {
	DWORD dwProt = NULL;
	void *addr = 0x500F5626;
	int count = 4;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	memset(addr,0x90,count);
	VirtualProtect(addr, count, dwProt, new DWORD);
}

#else

void gravity_applyHooks(void) {}

#endif

