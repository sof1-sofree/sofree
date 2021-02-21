/*
This is a metatable.
Useful when creating type 'userdata'
Or want to override some behavior using meta-methods.

Metatables are stored in registry
use
luaL_setmetatable(L,name)
to apply a metatable to a 'table' or 'userdata'
*/
void createmeta (lua_State *L,char * tname,luaL_Reg * meta_funcs,luaL_Reg * extended_funcs) {
  luaL_newmetatable(L, tname);  /* metatable for file handles */
  luaL_setfuncs(L, meta_funcs, 0);  /* add metamethods to new metatable */
  luaL_newlibtable(L, extended_funcs);  /* create method table */
  luaL_setfuncs(L, extended_funcs, 0);  /* add file methods to method table */
  lua_setfield(L, -2, "__index");  /* metatable.__index = method table */
  lua_pop(L, 1);  /* pop metatable */
}


//EG. EXAMPLES:
/*
** methods for file handles
*/
luaL_Reg extended_funcs[] = {
  {"read", NULL},
  {"write", NULL},
  {"lines", NULL},
  {NULL, NULL}
};

/*
** metamethods for file handles
*/
luaL_Reg meta_funcs[] = {
  {"__index", NULL},  /* place holder */
  {"__gc", NULL},
  {"__close", NULL},
  {"__tostring", NULL},
  {NULL, NULL}
};

/*
** functions for 'io' library
*/
luaL_Reg iolib[] = {
  {"close", NULL},
  {"flush", NULL},
  {"input", NULL},
  {NULL, NULL}
};

/*
luaL_newlibtable(L,iolib);
luaL_setfuncs(L,iolib,0);
*/
