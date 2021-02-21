// Use lua_topointer to do extra stuff to tables?

void entity_instance_init(void) {
	// create metatable here



}
// local fish = Ent('misc_generic_fish')
int lua_ent_birth(lua_State * L) {

	// we need a silly metatable for __call
	// set his meta-table here
	luaL_newlibtable(L,ent_funcs); //calls lua_createtable thus we have table on the stack.
	luaL_setfuncs(L,ent_funcs,0);

	//we don't want to just return handle.
	// we return entire ent api
	edict_t * ent = orig_G_Spawn();
	
	lua_pushstring(L,"handle"); // key
	lua_pushinteger(L,ent); // value
	lua_settable(L,-3); //attach to table

	//returns the new 'table' aka ent
	return 1;
}
int lua_ent_anim(lua_State * L) {
	int args = lua_gettop(L);
	assert(args == 7 && "invalid arg count");
	edict_t* ent = lua_tointeger(L,1);
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
	assert(clientinst && "no sequence");
	GhoulPlay(seq,*(float*)0x5015CCDC,startPos,bRestart,loop,match,reverse);
	return 0;
}
int lua_ent_model(lua_State *L) {
	edict_t* ent = lua_tointeger(L,1);
	assert(ent && "invalid ent");
	char * dir = lua_tostring(L,2);
	char * modelname = lua_tostring(L,3);
	modelSpawnData_t mdata =
	{
		.dir = dir,
		.file = modelname,
		.surfaceType = SURF_WOOD_DBROWN,
		.material = MAT_WOOD_DBROWN,
		.health = 500,
		.solid = SOLID_BBOX,
		.materialfile = NULL,
		.debrisCnt = 0,
		.debrisScale = DEBRIS_NONE,
		.objBreakData = NULL,
	};
	orig_SimpleModelInit2(ent,&mdata,NULL,NULL);
	return 0;
}
int lua_ent_paint(lua_State * L) {
	edict_t* ent = lua_tointeger(L,1);
	assert(ent && "invalid ent");
	float r = lua_tonumber(L,2);
	float g = lua_tonumber(L,3);
	float b = lua_tonumber(L,4);
	float a = lua_tonumber(L,5);
	clientinst=(unsigned int*)ent->ghoulInst;
	assert(clientinst && "invalid clientinst");
	GhoulSetTintOnAll(r,g,b,a);
	return 0;
}
int lua_ent_remove(lua_State * L) {

}
int lua_ent_spawn(lua_State * L) {

}
int lua_ent_tint(lua_State *L) {
	edict_t* ent = lua_tointeger(L,1);
	assert(ent && "invalid ent");
	vec3_t colors;
	luaReadTableAsVector(2,colors)
	assert(ent->ghoulInst && "invalid ghoulInst")
	clientinst = (unsigned int*)(ent->ghoulInst);
	GhoulSetTint(colors[0],colors[1],colors[2],lua_tonumber(L,3));
	return 0;
}
int lua_ent_use(lua_State *L) {
	edict_t* ent = lua_tointeger(L,1);
	assert(ent && "invalid ent");
	if ( ent->use ) {
		ent->use(ent,NULL,NULL);
	}
	return 0;
}
int lua_ent_vects(lua_State *L) {
	edict_t* ent = lua_tointeger(L,1);
	assert(ent && "invalid ent");

	vec3_t fwd_vec,side_vec,up_vec;
	orig_AngleVectors(ent->s.angles,fwd_vec,side_vec,up_vec);
	luaPushVectorAsTable(fwd_vec);
	luaPushVectorAsTable(side_vec);
	luaPushVectorAsTable(ip_vec);
	return 3;
}
luaL_Reg ent_funcs[] = {
  {"anim", lua_ent_anim},
  {"model",lua_ent_model},
  {"paint", lua_ent_paint},
  {"remove", lua_ent_remove},
  {"spawn", lua_ent_spawn},
  {"tint",lua_ent_tint},
  {"use",lua_ent_use},
  {"vects",lua_ent_vects}
};
