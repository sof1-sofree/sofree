#include "../../../hdr/feature_config.h"

#if FEATURE_FORCE_SKY

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_force_sky = NULL;

void create_force_sky_cvars(void) {
	_sf_sv_force_sky = orig_Cvar_Get("_sf_sv_force_sky","",0,NULL);
}

#else

void create_force_sky_cvars(void) {}

#endif

