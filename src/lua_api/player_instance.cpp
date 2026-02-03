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

/*
p.slot
p.score
p.respawn_angles
p.movescale
p.delta_angles
p.viewangles
p.gunghoulinst
???
*/

// Forward declaration
extern "C" int lua_player_anim(lua_State * L);

luaL_Reg player_inst_funcs[] = {
  {"anim", lua_player_anim},
  {NULL, NULL}
};

//Constructor for new instance, actually belongs to the 'Entities' table.
extern "C" int lua_player_grab(lua_State * L) {
  int slot = lua_tointeger(L,1);
  luaL_newlibtable(L,player_inst_funcs); //calls lua_createtable thus we have table on the stack.
  luaL_setfuncs(L,player_inst_funcs,0);

  // So we have a new player table !!! wow :)
  
  // Store anything inside the table?
  lua_pushinteger(L,slot); // value
  lua_setfield(L,-2,"slot");

  //returns the new 'table' aka ent
  return 1;
}

int lua_player_grab_ent(lua_State * L) {
  lua_getfield(L,1,"slot");
  int slot = lua_tointeger(L,-1);
  edict_t * ent = get_ent_from_player_slot(slot);

  ent_instance_prepare(ent);
  
  // returns an entity instance table
  return 1;
}

extern "C" int lua_player_anim(lua_State * L) {
	int args = lua_gettop(L);
	assert(args == 7 && "invalid arg count");
	lua_getfield(L,1,"slot");
	int slot = lua_tointeger(L,-1);
	edict_t* ent = get_ent_from_player_slot(slot);
	assert(ent && "invalid ent");
	char * animName = lua_tostring(L,2);
	float startPos = lua_tonumber(L,3);
	bool bRestart = lua_toboolean(L,4);
	int loop = lua_tointeger(L,5);
	int match = lua_tointeger(L,6);
	int reverse = lua_tointeger(L,7);
	clientinst = (unsigned int)(ent->ghoulInst);
	assert(clientinst && "invalid clientinst");
	GhoulGetObject();
	GhoulID seq = GhoulFindSequence(animName);
	assert(seq && "no sequence");
	GhoulPlay(seq,*(float*)0x5015CCDC,startPos,bRestart,loop,match,reverse);
	return 0;
}

#endif