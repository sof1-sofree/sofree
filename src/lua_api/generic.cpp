#ifdef LUA_ON
#include <windows.h>
#include "sofheader.h"

#include "lua_api/entities.h"
#include "lua_api/players.h"

void LuaLoadFiles(void);
void LuaCreateTables(void);
lua_State * L;
void LuaInitalize(void) {
	L = luaL_newstate();
	luaL_openlibs(L);


	// Tables = API
	LuaCreateTables();
	// Files = users' scripts
	LuaLoadFiles();
}

void LuaCreateTables(void) {
	entities_init();
}

void LuaLoadFiles(void)
{
	char **file_list = NULL;
	int file_list_len;
	ListDirectoryContents("user-server\\sofplus\\addons\\lua",&file_list,&file_list_len);

	orig_Com_Printf("There are %i entries\n",file_list_len);

	/*
		Run all .lua scripts in lua directory.
	*/
	for ( int i=0; i < file_list_len;i++)
	{
		char * filepath = *(file_list+i);
		orig_Com_Printf("loading %s\n",filepath);

		// LUA_MULTRET
		if (luaL_loadfile(L, filepath) == LUA_OK) {
			// state,Nargs,Nrets,messageHandler
			if (lua_pcall(L, 0, LUA_MULTRET, 0) == LUA_OK) {
				// if it returned anything to us.
				lua_settop(L,0);
				// lua_pop(L, lua_gettop(L));
			}
		} else {
			orig_Com_Error(ERR_FATAL,"%s\n",lua_tostring(L, -1));
			lua_settop(L,0);
		}
	}
}

#endif