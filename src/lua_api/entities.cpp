#include <windows.h>
#include "sofheader.h"

#include <stdlib.h>
#include <string.h>

// StrStrI
#include <shlwapi.h>

#include <list>





/*
I want format:
  local fish = Ents('classname')


So there must be a constructor, and it must return a Userdata.

I'm still not sure why I want to use Userdata

He has a struct.. which are just pointers...
then he fills the pointers...

with actual data...

then ... when the __gc hits, he can just free the pointers or close them....
Do i have something that i want to 'close' ???

on __gc??? Else use table???-
*/

/*
This is Ran on Server startup?? I guess. Store metatables(if any) in registry.
And. Prepare all tables for serving the API.
*/
void entities_init(void) {
	// create metatable here



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



luaL_Reg entities_funcs[] = {
  {"find", lua_entities_find},
  {"spawn", NULL},
  {"remove", NULL},
  {NULL, NULL}
};



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