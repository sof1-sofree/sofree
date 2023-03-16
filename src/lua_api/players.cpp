#ifdef LUA_ON

#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
#include "lua_api/player_instance.h"

luaL_Reg players_funcs[] = {
  {"grab", lua_players_grab},
  {NULL, NULL}		
};
/*
Create a table... :) Thats all.
*/
void players_init(void) {
	// pushes new table to stack
	luaL_newlibtable(L,players_funcs);

	// set our funcs
	luaL_setfuncs(L,players_funcs,0);

	// pops value from stack and sets as new global
	lua_setglobal(L,"Players");
}

#endif