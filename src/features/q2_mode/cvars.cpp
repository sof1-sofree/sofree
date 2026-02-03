#include "../../../hdr/feature_config.h"

#if FEATURE_Q2_MODE

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_q2_slide_fix = NULL;
cvar_t * _sf_sv_q2_style_jump = NULL;
cvar_t * _sf_sv_q2_mode = NULL;

void create_q2_mode_cvars(void) {
	_sf_sv_q2_slide_fix = orig_Cvar_Get("_sf_sv_q2_slide_fix","0",0,NULL);
	_sf_sv_q2_style_jump = orig_Cvar_Get("_sf_sv_q2_style_jump","0",0,NULL);
	_sf_sv_q2_mode = orig_Cvar_Get("_sf_sv_q2_mode","0",CVAR_LATCH,NULL);
}

#else

void create_q2_mode_cvars(void) {}

#endif

