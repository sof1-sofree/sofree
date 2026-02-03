#include "../../../hdr/feature_config.h"

#if FEATURE_FX

#include <windows.h>
#include "../../../hdr/sofheader.h"

extern cvar_t * _sf_sv_fx_mode;
extern cvar_t * _sf_sv_fx_blood_amount;
extern cvar_t * _sf_sv_fx_blood_speed;

void fx_handleDamage(vec3_t point, vec3_t dir, edict_t *targ) {
	switch ( (int)_sf_sv_fx_mode->value ) {
		case 0:
			break;
		case 1:
			orig_FX_MakeBloodSpray(point, dir, _sf_sv_fx_blood_speed->value, _sf_sv_fx_blood_amount->value, targ);
			break;
	}
}

#endif

