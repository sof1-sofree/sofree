#include "../../../hdr/feature_config.h"

#if FEATURE_GRAVITY

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_gravity_default = NULL;

void create_gravity_cvars(void) {
	_sf_sv_gravity_default = orig_Cvar_Get("_sf_sv_gravity_default","800",0,NULL);
}

#else

void create_gravity_cvars(void) {}

#endif

