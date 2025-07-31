#include <windows.h>
#include "sofheader.h"

#include <stdio.h>
#include <stdlib.h>

/*
class TestCallback :public IGhoulCallBack
{
public:
	bool Execute(IGhoulInst *me,void *ent,float time,const void *matrix);
};


TestCallback theTestCallback;
bool TestCallback::Execute(IGhoulInst *me,edict_t *ent,float time,const void *matrix)
{
	static DWORD	last;

	
	//orig_Com_Printf("hello world\n");
	//orig_Com_Printf("Diff = %10.2f\n",*level_time);
	orig_Cbuf_AddText("say lol\n");
	last = timeGetTime();

	return true;
}
*/

void T_Damage_old(edict_t *targ, edict_t *inflictor, edict_t *attacker, 
vec3_t dir, vec3_t point, vec3_t origin, int damage, int knockback, int dflags, int mod, float penetrate, float absorb)
{
	try{
	// targ can be expected to be good value ( present )
	// but probably not attacker/inflictor

	//kill(suicide) : targ=worldspawn,attacker=player,inflictor=player
	//crater : targ=player,attacker=worldspawn,inflictor=worldspawn

	// PrintOut(PRINT_GOOD,"target classname = %s\n",*(unsigned int*)(targ + EDICT_CLASSNAME));
	// if (attacker)
	// 	PrintOut(PRINT_GOOD,"attacker classname = %s\n",*(unsigned int*)(attacker + EDICT_CLASSNAME));
	// else PrintOut(PRINT_BAD,"no attacker present\n");

	// if (inflictor)
	// 	PrintOut(PRINT_GOOD,"inflictor classname = %s\n",*(unsigned int*)(inflictor + EDICT_CLASSNAME));
	// else PrintOut(PRINT_BAD,"no inflictor present\n");
	
	// _sf_sv_on_client_damage trigger
	// only trigger if both targ and attacker are clients

	
	void * gclient_targ = *(int*)(targ + EDICT_GCLIENT);
	

	int health_before = *(int*)((int)targ+EDICT_HEALTH);

	orig_T_Damage(targ,inflictor,attacker,dir,point,origin,damage,knockback,dflags,mod,penetrate,absorb);

	char targ_classname[64];
	strcpy(targ_classname,*(unsigned int*)(targ + EDICT_CLASSNAME))	;
	
	

	// safe
	int targ_num = *(unsigned int*)targ;
	int attacker_num = -1, inflictor_num = -1;
	char attacker_classname[64] = "",inflictor_classname[64] = "";
	if ( attacker ) {
		void * gclient_attacker = *(int*)(attacker + EDICT_GCLIENT);
		attacker_num = *(unsigned int*)attacker;
		strcpy(attacker_classname,*(unsigned int*)(attacker + EDICT_CLASSNAME));
	}
	if ( inflictor ) {
		inflictor_num = *(unsigned int*)inflictor;
		strcpy(inflictor_classname,*(unsigned int*)(inflictor + EDICT_CLASSNAME));
	} 	

	// PrintOut(PRINT_GOOD,"victim is %i\nsuspect is %i\n",victim,suspect);
	int taken = 0;
	// health changed AND is 'alive'
	if ( health_before > *(int*)((int)targ+EDICT_HEALTH) && *(int*)((int)targ+EDICT_SOLID) ) {
		taken = health_before - *(int*)((int)targ+EDICT_HEALTH);
	}
		
	makeTheStringElips(" %s %s %s %i %i %i %i %i\n",_sf_sv_on_client_damage, targ_classname,attacker_classname,inflictor_classname,targ_num,attacker_num,inflictor_num,mod,taken);

	
	vec3_t vec3_up = {0,0,1};
	vec3_t mins = {-1,-1,-1};
	vec3_t maxs = {1,1,1};
	int slot = ((entity_state_t*)targ)->skinnum;
	switch ( (int)_sf_sv_fx_mode->value ) {
		case 0:
		break;
		case 1:
			//paletteRGBA_t p;
			//p.r=255;p.g=255;p.b=255;p.a=255;
			orig_debug_drawbox(targ,point,mins,maxs,0);
		break;
		case 2:
			orig_FX_Flashpack(point);
		break;
		case 3:
			orig_FX_NeuralPulse(point);
		break;
		case 4:
			orig_FX_MakeBloodSpray(point, dir, _sf_sv_fx_blood_speed->value, _sf_sv_fx_blood_amount->value, targ);
		break;
		case 5:
			orig_FX_C4Explosion(targ);
		break;
		case 6:
			orig_FX_MakeBarrelExplode(point,targ);
		break;
		case 7:
			//_sf_sv_fx_decal_type
			orig_FX_MakeDecalBelow(point,FXDECAL_BLOODPOOL,1);
		break;
		case 8:
			orig_FX_MakeGumballs(point,dir, 0);
		break;
		case 9:
			orig_FX_MakeDustPuff(point);
		break;
		case 10:
			//_sf_sv_fx_elec_len
			orig_FX_MakeElectricArc(point,60,dir);
		break;
		case 11:
			
			orig_FX_MakeBulletWhiz(targ,vec3_up,dir,100,220);
		break;
		case 12:
			trace_t tr;
			orig_SV_Trace(origin, NULL, NULL, point, attacker, MASK_SHOT| MASK_WATER, &tr);

			orig_FX_MakeWallDamage(tr, dir, 10, WMRK_NONE,false);
		break;
		case 13:
			orig_FX_MakeSkyLightning();
		break;
		//vec3_t	origin,vec3_t norm, byte numchunks, byte scale, byte skin,byte x_max,byte y_max,byte p_max, byte surfType
		case 14:
			orig_FX_ThrowDebris(point,vec3_up,1,DEBRIS_SM,MAT_GLASS,1,1,1,SURF_GLASS);
		break;
		case 15:
			orig_FX_StrikeWall(point,0);
		break;
		//crashes
		case 16:
			orig_FX_WallSparks(point,dir,3);
		break;
		case 17:
			
			//+0x164 .. to access the ghoulInst from the edict_t pointer ;) - enjoy - dendexxx
			
			
			clientinst = (unsigned int*)(*(unsigned int*)((unsigned int)targ+0x164));
			if ( clientinst != NULL )
			{
				
				if ( GhoulGetObject() )
				{	
					unsigned short partid = GhoulFindPart("abolt_head_t");
					if ( partid != 0 ) {			
						orig_FX_Bleed(targ,partid,50);
					}
				}
			}
			
			
		break;
		case 18:
			clientinst = (unsigned int*)(*(unsigned int*)((unsigned int)targ+0x164));
			if ( clientinst != NULL )
			{
				if ( GhoulGetObject() )
				{
					unsigned short partid = GhoulFindPart("abolt_head_t");
					if ( partid != 0 ) {
						orig_FX_BloodCloud(targ,partid,50);
					}
				}
			}
		break;
		case 19:

			
			clientinst = (unsigned int*)(*(unsigned int*)((unsigned int)targ+0x164));
			orig_Com_Printf("RayTrace is %08X\n",*(unsigned int*)0x201122A4);
			if ( clientinst != NULL )
			{
				if ( GhoulGetObject() )
				{
					GhoulID huh = GhoulFindNoteToken("jump");
					orig_Com_Printf("huh is %08X\n",huh);
					//GhoulAddNoteCallBack(&theTestCallback,huh);
				}
				/*if ( GhoulGetObject() )
				{
					unsigned short partid = GhoulFindPart("abolt_head_t");
					if ( partid != 0 ) {
						orig_FX_HeadExplosion(targ,partid);
						GhoulSetTint(_sf_sv_ghl_tint_r->value,_sf_sv_ghl_tint_g->value,_sf_sv_ghl_tint_b->value,_sf_sv_ghl_tint_a->value);
					}
				}*/
			}
		break;
		//ent, point, dir
		case 20:
			orig_FX_BloodJet(targ,point,dir);
		break;
		//point, size
		case 21:
			orig_FX_VehicleExplosion(point,255);
		break;
		//point,red,green,blue,alpha
		case 22:
			orig_FX_SmokePuff(point,255,255,255,255);
		break;
		//point, size, sound
		case 23:
			orig_FX_LittleExplosion(point, 100, 1);
		break;
		case 24:
			orig_FX_MediumExplosion(point,100,1);
		break;
		case 25:
			orig_FX_LargeExplosion(point,100,1);
		break;
		//point, size
		case 26:
			orig_FX_MakeRing(point,4);
		break;
		//point , count(0 generates random number)
		case 27:
			orig_FX_PaperCloud(point,0);
		break;
		//point, dir, speed, count ( 0 = random)
		case 28:
			orig_FX_SodaCans(point,dir,100,0);
		break;
		//point dir, type
		case 29:
			orig_FX_MakeCoins(point,dir,0);
		break;
		case 30:
			orig_FX_DropDustBits(point,50);
		break;
		case 31:
			orig_FX_MakeRicochet(point);
		break;
		case 32:
			orig_FX_PhoneHit(point);
		break;
		case 33:
			orig_FX_TrashcanHit(point);
		break;
		default:
		break;
	}
	}
	catch(...) {
		char temp[64];
		sprintf(temp,"ERROR IN %s",__FUNCTION__);
		MessageBox(NULL,temp,NULL,MB_OK);
	}
}
/*
T_Damage

targ		entity that is being damaged
inflictor	entity that is causing the damage
attacker	entity that caused the inflictor to damage targ
	example: targ=monster, inflictor=rocket, attacker=player

dir			direction of the attack
point		point at which the damage is being inflicted
normal		normal vector from that point
damage		amount of damage being inflicted
knockback	force to be applied against targ as a result of the damage

dflags		these flags are used to control how T_Damage works
	DAMAGE_RADIUS			damage was indirect (from a nearby explosion)
	DAMAGE_NO_ARMOR			armor does not protect from this damage
	DAMAGE_ENERGY			damage is from an energy based weapon
	DAMAGE_NO_KNOCKBACK		do not affect velocity, just view angles
	DAMAGE_BULLET			damage is from a bullet (used for ricochets)
	DAMAGE_NO_PROTECTION	kills godmode, armor, everything
*/
void T_Damage(edict_t *targ, edict_t *inflictor, edict_t *attacker, 
vec3_t dir, vec3_t point, vec3_t origin, int damage, int knockback, int dflags, int mod, float penetrate=0.0f, float absorb=0.0f)
{

	if ( _sf_sv_sofree_deathmatch->value == SOFREE_MINECRAFT) {
		// tell the minecraft module the ondamage data.
		Minecraft::onDamage(targ);
	}

	gclient_t * targ_cl = targ->client;
	int health_before = targ->health;

	orig_T_Damage(targ,inflictor,attacker,dir,point,origin,damage,knockback,dflags,mod,penetrate,absorb);

	char targ_classname[64];
	strcpy(targ_classname,targ->classname);
	
	// safe
	int targ_num = targ->s.number;
	int attacker_num = -1, inflictor_num = -1;
	char attacker_classname[64] = "",inflictor_classname[64] = "";
	if ( attacker ) {
		gclient_t * attacker_cl = attacker->client;
		attacker_num = attacker->s.number;
		strcpy(attacker_classname,attacker->classname);
	}
	if ( inflictor ) {
		inflictor_num = inflictor->s.number;
		strcpy(inflictor_classname,inflictor->classname);
	} 	

	// PrintOut(PRINT_GOOD,"victim is %i\nsuspect is %i\n",victim,suspect);
	int taken = 0;
	// health changed AND is 'alive'
	if ( health_before > targ->health && targ->solid ) {
		taken = health_before - targ->health;
	}

	makeTheStringElips(" %s %s %s %i %i %i %i %i\n",_sf_sv_on_client_damage, targ_classname,attacker_classname,inflictor_classname,targ_num,attacker_num,inflictor_num,mod,taken);
	
}