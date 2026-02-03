#include "../../../hdr/feature_config.h"

#if FEATURE_MOVEMENT

#include <windows.h>
#include "../../../hdr/sofheader.h"

extern cvar_t * _sf_sv_friction;
extern cvar_t * _sf_sv_accel;
extern cvar_t * _sf_sv_airaccel;
extern cvar_t * _sf_sv_crouchspeed;
extern cvar_t * _sf_sv_runspeed;
extern cvar_t * _sf_sv_rampslide_threshold;

void _sf_sv_friction_callback(cvar_t * thecvar) {
	float * friction = (float*)0x20137608;
	*friction = thecvar->value;
}

void _sf_sv_accel_callback(cvar_t * thecvar) {
	*pm_accelerate = thecvar->value;
}

void _sf_sv_airaccel_callback(cvar_t * thecvar) {
	float * airaccel = (float*)0x20137600;
	*airaccel = thecvar->value;
}

void _sf_sv_crouchspeed_callback(cvar_t * thecvar) {
	float * crouchspeed = (float*)0x201375F8;
	*crouchspeed = thecvar->value;
}

void _sf_sv_runspeed_callback(cvar_t * thecvar) {
	float * runspeed = (float*)0x201375F4;
	*runspeed = thecvar->value;
}

void _sf_sv_rampslide_threshold_callback(cvar_t * thecvar) {
	DWORD dwProt = NULL;
	void * addr = 0x201114C0;
	int count = 4;
	VirtualProtect(addr, count, PAGE_READWRITE, &dwProt);
	float * threshold = (float*)0x201114C0;
	*threshold = thecvar->value;
	VirtualProtect(addr, count, dwProt, new DWORD);
}

#endif

