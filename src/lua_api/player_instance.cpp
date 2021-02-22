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

luaL_Reg player_inst_funcs[] = {
  {"anim", lua_player_anim},
  {NULL, NULL}
};

//Constructor for new instance, actually belongs to the 'Entities' table.
int lua_player_grab(lua_State * L) {
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
