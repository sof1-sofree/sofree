#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/image/image.h"
#include "util_funcs.h"

int sf_sv_image_register(lua_State* L) {
	const char* imageName = lua_tostring(L, 1);
	char imageNameStr[128];
	strcpy(imageNameStr, imageName);
	replacechar(imageNameStr, '\\', '/');
	engine_image_register(imageNameStr);
	int freeslots = engine_image_calc_free_slots();
	cvar_t* thecvar = findCvar("_sf_sv_image_info_slots");
	setCvarUnsignedInt(thecvar, freeslots);
	return 0;
}

int sf_sv_image_list(lua_State* L) {
	const char* search = (lua_gettop(L) >= 1) ? lua_tostring(L, 1) : NULL;
	int count = 0;
	cvar_t* savecvar = NULL;
	engine_image_list(search, &count, &savecvar);
	lua_pushinteger(L, count);
	return 1;
}

