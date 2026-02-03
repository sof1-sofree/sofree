#include "../../../hdr/feature_config.h"

#if FEATURE_GHOUL_TINT

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_ghl_tint_r = NULL;
cvar_t * _sf_sv_ghl_tint_g = NULL; 
cvar_t * _sf_sv_ghl_tint_b = NULL;
cvar_t * _sf_sv_ghl_tint_a = NULL;

void create_ghoul_tint_cvars(void) {
	_sf_sv_ghl_tint_a = orig_Cvar_Get("_sf_sv_ghl_tint_a","1.0",0,NULL);
	_sf_sv_ghl_tint_b = orig_Cvar_Get("_sf_sv_ghl_tint_b","1.0",0,NULL);
	_sf_sv_ghl_tint_g = orig_Cvar_Get("_sf_sv_ghl_tint_g","1.0",0,NULL);
	_sf_sv_ghl_tint_r = orig_Cvar_Get("_sf_sv_ghl_tint_r","1.0",0,NULL);
}

#else

void create_ghoul_tint_cvars(void) {}

#endif

