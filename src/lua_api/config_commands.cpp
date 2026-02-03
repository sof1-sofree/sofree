#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "engine_features/config/config.h"

int sf_sv_save_reso(lua_State* L) {
	unsigned int slot = lua_tointeger(L, 1);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);
	engine_config_save_reso(slot, x, y);
	return 0;
}

int sf_sv_check_reso(lua_State* L) {
	const char* cmd = lua_tostring(L, 1);
	engine_config_check_reso(cmd);
	return 0;
}

