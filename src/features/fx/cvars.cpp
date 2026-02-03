#include "../../../hdr/feature_config.h"

#if FEATURE_FX

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_fx_mode = NULL;
cvar_t * _sf_sv_fx_blood_amount = NULL;
cvar_t * _sf_sv_fx_blood_speed = NULL;

void create_fx_cvars(void) {
	_sf_sv_fx_mode = orig_Cvar_Get("_sf_sv_fx_mode","0",0,NULL);
	_sf_sv_fx_blood_speed = orig_Cvar_Get("_sf_sv_fx_blood_speed","200",0,NULL);
	_sf_sv_fx_blood_amount = orig_Cvar_Get("_sf_sv_fx_blood_amount","1",0,NULL);
}

#else

void create_fx_cvars(void) {}

#endif

