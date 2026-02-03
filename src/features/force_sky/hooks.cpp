#include "../../../hdr/feature_config.h"

#if FEATURE_FORCE_SKY

#include <windows.h>
#include "../../../hdr/sofheader.h"

extern cvar_t * _sf_sv_force_sky;

char* force_sky_PF_Configstring(int index,char * string)
{
	if ( strlen(_sf_sv_force_sky->string) && index == CS_SKY ) {
		string = _sf_sv_force_sky->string;
		orig_Com_Printf("setting sky to %s\n",string);
	}
	return string;
}

#endif

