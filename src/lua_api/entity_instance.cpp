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

e.soundname
e.next_think
e.flags
e.velocity
e.gravity
e.bouyancy
e.airresistance
e.friction
e.stopspeed
e.mass
e.enemy
e.skinnum
e.movetype
e.maxs
e.mins
e.clipmask
e.ghoulinst
e.inuse
e.script
e.target
e.targetname
e.classname
e.model
e.solid
e.health
e.health_max
e.angles
e.origin

???
*/

luaL_Reg ent_inst_funcs[] = {
  {"anim", lua_ent_anim},
  {"model",lua_ent_model},
  {"paint", lua_ent_paint},
  {"remove", lua_ent_remove},
  {"spawn", lua_ent_spawn},
  {"tint",lua_ent_tint},
  {"use",lua_ent_use},
  {"vects",lua_ent_vects},
  {"relink",lua_ent_relink},
  {"bolt",lua_ent_bolt},
  {"callback",lua_ent_callback},
  {NULL, NULL}
};

// Use lua_topointer to do extra stuff to tables?

// local fish = Ent('misc_generic_fish')
//Constructor for new instance, actually belongs to the 'Entities' table.
int lua_ent_birth(lua_State * L) {

	// we need a silly metatable for __call
	// set his meta-table here
	luaL_newlibtable(L,ent_inst_funcs); //calls lua_createtable thus we have table on the stack.
	luaL_setfuncs(L,ent_inst_funcs,0);

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
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
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
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
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
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
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
	int args = lua_gettop(L);
	assert(args == 1 && "invalid arg count");
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	event_think_s	*z, *next;
	for (z=think_events.next ; z != &think_events ; z=next)
	{
		next = z->next;		
		// if ( !strcmp(p->script_name,orig_Cmd_Argv(1)) ) {
		if ( z->ent == ent ) {
			z->prev->next = z->next;
			z->next->prev = z->prev;

			ent->think = NULL;
			break;
		}
	}
	event_touch_s	*z_touch, *next_touch;
	for (z_touch=touch_events.next ; z_touch != &touch_events ; z_touch=next_touch)
	{
		next_touch = z_touch->next;
		if ( z_touch->ent == ent ) {
			z_touch->prev->next = z_touch->next;
			z_touch->next->prev = z_touch->prev;

			ent->touch = NULL;
			break;
		}
	}
	event_die_s	*z_die, *next_die;
	for (z_die=die_events.next ; z_die != &die_events ; z_die=next_die)
	{
		next_die = z_die->next;
		if ( z_die->ent == ent ) {
			z_die->prev->next = z_die->next;
			z_die->next->prev = z_die->prev;

			ent->die = NULL;
			break;
		}
	}
	event_use_s	*z_use, *next_use;
	for (z_use=use_events.next ; z_use != &use_events ; z_use=next_use)
	{
		next_use = z_use->next;
		if ( z_use->ent == ent ) {
			z_use->prev->next = z_use->next;
			z_use->next->prev = z_use->prev;

			ent->use = NULL;
			break;
		}
	}
	event_pluse_s	*z_pluse, *next_pluse;
	for (z_pluse=pluse_events.next ; z_pluse != &pluse_events ; z_pluse=next_pluse)
	{
		next_pluse = z_pluse->next;
		if ( z_pluse->ent == ent ) {
			z_pluse->prev->next = z_pluse->next;
			z_pluse->next->prev = z_pluse->prev;

			ent->plUse = NULL;
			break;
		}
	}
	event_pain_s	*z_pain, *next_pain;
	for (z_pain=pain_events.next ; z_pain != &pain_events ; z_pain=next_pain)
	{
		next_pain = z_pain->next;
		if ( z_pain->ent == ent ) {
			z_pain->prev->next = z_pain->next;
			z_pain->next->prev = z_pain->prev;

			ent->pain = NULL;
			break;
		}
	}
	orig_G_FreeEdict(ent);
}
int lua_ent_spawn(lua_State * L) {
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	orig_ED_CallSpawn(ent);
	return 0;
}
int lua_ent_tint(lua_State *L) {
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	assert(ent && "invalid ent");
	vec3_t colors;
	luaReadTableAsVector(2,colors);
	assert(ent->ghoulInst && "invalid ghoulInst");
	clientinst = (unsigned int*)(ent->ghoulInst);
	GhoulSetTint(colors[0],colors[1],colors[2],lua_tonumber(L,3));
	return 0;
}
int lua_ent_use(lua_State *L) {
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	assert(ent && "invalid ent");
	if ( ent->use ) {
		ent->use(ent,NULL,NULL);
	}
	return 0;
}
int lua_ent_vects(lua_State *L) {
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	assert(ent && "invalid ent");

	vec3_t fwd_vec,side_vec,up_vec;
	orig_AngleVectors(ent->s.angles,fwd_vec,side_vec,up_vec);
	luaPushVectorAsTable(fwd_vec);
	luaPushVectorAsTable(side_vec);
	luaPushVectorAsTable(up_vec);
	return 3;
}
int lua_ent_relink(lua_State * L)
{
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	orig_SV_LinkEdict(ent);
	return 0;
}
int lua_ent_bolt(lua_State * L)
{
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	assert(ent && "invalid ent");
	char * dir = lua_tostring(L,2);
	char * file = lua_tostring(L,3);
	char * bolt_from = lua_tostring(L,4);
	char * bolt_to = lua_tostring(L,5);
	float scale = lua_tonumber(L,6);
	clientinst = (unsigned int)(ent->ghoulInst);
	assert(clientinst && "invalid clientinst");
	GhoulGetObject();
	ggObjC * MyGhoulObj = GhoulFindObjectSmall((IGhoulObj*)objinst);
	ggOinstC* myInstance = orig_FindOInst(MyGhoulObj,(IGhoulInst*)clientinst);
	orig_AddBoltedItem(ent->client->body,*ent, bolt_from, dir, file, bolt_to, myInstance, NULL, scale);
}
int lua_ent_callback(lua_State * L)
{
	lua_getfield(L,1,"handle");
	edict_t* ent = lua_tointeger(L,-1);
	char *a2 = lua_tostring(L,2);
	char *f = lua_tostring(L,3);
	if ( !strcmp(a2,"think") ) {
		event_think_s	*z = malloc(sizeof(event_think_s));

		z->next = think_events.next;
		z->prev = &think_events;
		think_events.next->prev = z;
		think_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->think = &ThinkEventCallback;
	} else if ( !strcmp(a2,"touch") ) {
		event_touch_s	*z = malloc(sizeof(event_touch_s));

		z->next = touch_events.next;
		z->prev = &touch_events;
		touch_events.next->prev = z;
		touch_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->touch = &TouchEventCallback;
	} else if ( !strcmp(a2,"use") ) {
		event_use_s	*z = malloc(sizeof(event_use_s));

		z->next = use_events.next;
		z->prev = &use_events;
		use_events.next->prev = z;
		use_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->use = &UseEventCallback;
	} else if ( !strcmp(a2,"pluse") ) {

		event_pluse_s	*z, *next;
		for (z=pluse_events.next ; z != &pluse_events ; z=next)
		{
			next = z->next;
			if (z->ent == ent) {
				z->ent = ent;
				sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
				ent->plUse = &PlUseEventCallback;
				return;
			}
		}

		z = malloc(sizeof(event_pluse_s));

		z->next = pluse_events.next;
		z->prev = &pluse_events;
		pluse_events.next->prev = z;
		pluse_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->plUse = &PlUseEventCallback;
	} else if ( !strcmp(a2,"pain") ) {
		orig_Com_Printf("registering paincallback!\n");
		event_pain_s	*z = malloc(sizeof(event_pain_s));

		z->next = pain_events.next;
		z->prev = &pain_events;
		pain_events.next->prev = z;
		pain_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->pain = &PainEventCallback;
	} else if ( !strcmp(a2,"die") ) {
		event_die_s	*z = malloc(sizeof(event_die_s));

		z->next = die_events.next;
		z->prev = &die_events;
		die_events.next->prev = z;
		die_events.next = z;

		z->ent = ent;
		sprintf(z->sofplusfunc,"sp_sc_func_exec %s\n",f);
		ent->die = &DieCallback;
	}
}

