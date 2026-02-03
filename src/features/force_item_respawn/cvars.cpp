#include "../../../hdr/feature_config.h"

#if FEATURE_FORCE_ITEM_RESPAWN

#include <windows.h>
#include "../../../hdr/sofheader.h"

cvar_t * _sf_sv_force_item_respawntime = NULL;

void create_force_item_respawn_cvars(void) {
	_sf_sv_force_item_respawntime = orig_Cvar_Get("_sf_sv_force_item_respawntime","0",0,NULL);
}

#else

void create_force_item_respawn_cvars(void) {}

#endif

