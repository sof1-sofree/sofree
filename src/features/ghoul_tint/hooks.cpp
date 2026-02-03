#include "../../../hdr/feature_config.h"

#if FEATURE_GHOUL_TINT

#include <windows.h>
#include "../../../hdr/sofheader.h"

extern cvar_t * _sf_sv_ghl_tint_r;
extern cvar_t * _sf_sv_ghl_tint_g;
extern cvar_t * _sf_sv_ghl_tint_b;
extern cvar_t * _sf_sv_ghl_tint_a;

void ghoul_tint_applyTint(void) {
	GhoulSetTint(_sf_sv_ghl_tint_r->value,_sf_sv_ghl_tint_g->value,_sf_sv_ghl_tint_b->value,_sf_sv_ghl_tint_a->value);
}

#endif

