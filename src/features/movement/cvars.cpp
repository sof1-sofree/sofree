#include "../../../hdr/feature_config.h"

#if FEATURE_MOVEMENT

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_friction = NULL;
cvar_t * _sf_sv_accel = NULL;
cvar_t * _sf_sv_airaccel = NULL;
cvar_t * _sf_sv_crouchspeed = NULL;
cvar_t * _sf_sv_runspeed = NULL;
cvar_t * _sf_sv_rampslide_threshold = NULL;

extern void _sf_sv_friction_callback(cvar_t * thecvar);
extern void _sf_sv_accel_callback(cvar_t * thecvar);
extern void _sf_sv_airaccel_callback(cvar_t * thecvar);
extern void _sf_sv_crouchspeed_callback(cvar_t * thecvar);
extern void _sf_sv_runspeed_callback(cvar_t * thecvar);
extern void _sf_sv_rampslide_threshold_callback(cvar_t * thecvar);

void create_movement_cvars(void) {
	_sf_sv_accel = orig_Cvar_Get("_sf_sv_accel","10",0,_sf_sv_accel_callback);
	_sf_sv_airaccel = orig_Cvar_Get("_sf_sv_airaccel","1",0,_sf_sv_airaccel_callback);
	_sf_sv_friction = orig_Cvar_Get("_sf_sv_friction","6",0,_sf_sv_friction_callback);
	_sf_sv_crouchspeed = orig_Cvar_Get("_sf_sv_crouchspeed","75",0,_sf_sv_crouchspeed_callback);
	_sf_sv_runspeed = orig_Cvar_Get("_sf_sv_runspeed","300",0,_sf_sv_runspeed_callback);
	_sf_sv_rampslide_threshold = orig_Cvar_Get("_sf_sv_rampslide_threshold","100",0,_sf_sv_rampslide_threshold_callback);
}

#else

void create_movement_cvars(void) {}

#endif

