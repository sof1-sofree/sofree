#ifdef LUA_ON
#include <windows.h>
#include "sofheader.h"
#include "lua_api/generic.h"
// #include <stdlib.h>
// #include <string.h>

// // StrStrI
// #include <shlwapi.h>

// #include <list>

#include "lua_api/entity_instance.h"

void entities_init(void);
int lua_entities_find(lua_State *L);


luaL_Reg entities_funcs[] = {
  {"find", lua_entities_find},
  {"birth", lua_ent_birth},
  {NULL, NULL}
};


/*
Create a table... :) Thats all.
*/
void entities_init(void) {
	// pushes new table to stack
	luaL_newlibtable(L,entities_funcs);

	// set our funcs
	luaL_setfuncs(L,entities_funcs,0);

	// pops value from stack and sets as new global
	lua_setglobal(L,"Entities");
}
int lua_entities_find(lua_State *L) {
	char * cvarprefix = lua_tostring(L,1);
	char * compare_field_offset = lua_tointeger(L,2);
	char * val_to_find = lua_tostring(L,3);
	lua_newtable(L);
	int count = 0;
	//use count as index into table
	edict_t * entfound = orig_G_Find(0,compare_field_offset,val_to_find,0);
	while ( entfound ) {
		count++;
		lua_pushinteger(L,count); // key
		lua_pushinteger(L,entfound); // value
		lua_settable(L,-3); //attach to table
		entfound = orig_G_Find(entfound,compare_field_offset,val_to_find,0);
	} 
	// returns table full of ends found handles
	return 1;
}



/*
Account = {balance = 0}
    
function Account:new (o)
  o = o or {}
  setmetatable(o, self)
  self.__index = self
  return o
end

function Account:deposit (v)
  self.balance = self.balance + v
end

function Account:withdraw (v)
  if v > self.balance then error"insufficient funds" end
  self.balance = self.balance - v
end

*/

#endif