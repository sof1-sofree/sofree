#include "../../../hdr/feature_config.h"

#if FEATURE_GRENADE

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_grenade_impact_explode = NULL;

void create_grenade_cvars(void) {
	_sf_sv_grenade_impact_explode = orig_Cvar_Get("_sf_sv_grenade_impact_explode","1",CVAR_LATCH,NULL);
}

#else

void create_grenade_cvars(void) {}

#endif

