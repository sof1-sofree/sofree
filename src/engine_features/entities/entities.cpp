#include <windows.h>
#include "sofheader.h"
#include <stdlib.h>
#include <string.h>
#include "engine_features/entities/entities.h"

extern event_think_s think_events;
extern event_touch_s touch_events;
extern event_use_s use_events;
extern event_pluse_s pluse_events;
extern event_pain_s pain_events;
extern event_die_s die_events;
extern unsigned int* clientinst;

edict_t* engine_ent_create(void) {
	return orig_G_Spawn();
}

void engine_ent_spawn(edict_t* ent) {
	orig_ED_CallSpawn(ent);
}

void engine_ent_remove(edict_t* ent) {
	event_think_s* z, * next;
	for (z = think_events.next; z != &think_events; z = next) {
		next = z->next;
		if (z->ent == ent) {
			z->prev->next = z->next;
			z->next->prev = z->prev;
			ent->think = NULL;
			break;
		}
	}
	event_touch_s* z_touch, * next_touch;
	for (z_touch = touch_events.next; z_touch != &touch_events; z_touch = next_touch) {
		next_touch = z_touch->next;
		if (z_touch->ent == ent) {
			z_touch->prev->next = z_touch->next;
			z_touch->next->prev = z_touch->prev;
			ent->touch = NULL;
			break;
		}
	}
	event_die_s* z_die, * next_die;
	for (z_die = die_events.next; z_die != &die_events; z_die = next_die) {
		next_die = z_die->next;
		if (z_die->ent == ent) {
			z_die->prev->next = z_die->next;
			z_die->next->prev = z_die->prev;
			ent->die = NULL;
			break;
		}
	}
	event_use_s* z_use, * next_use;
	for (z_use = use_events.next; z_use != &use_events; z_use = next_use) {
		next_use = z_use->next;
		if (z_use->ent == ent) {
			z_use->prev->next = z_use->next;
			z_use->next->prev = z_use->prev;
			ent->use = NULL;
			break;
		}
	}
	event_pluse_s* z_pluse, * next_pluse;
	for (z_pluse = pluse_events.next; z_pluse != &pluse_events; z_pluse = next_pluse) {
		next_pluse = z_pluse->next;
		if (z_pluse->ent == ent) {
			z_pluse->prev->next = z_pluse->next;
			z_pluse->next->prev = z_pluse->prev;
			ent->plUse = NULL;
			break;
		}
	}
	event_pain_s* z_pain, * next_pain;
	for (z_pain = pain_events.next; z_pain != &pain_events; z_pain = next_pain) {
		next_pain = z_pain->next;
		if (z_pain->ent == ent) {
			z_pain->prev->next = z_pain->next;
			z_pain->next->prev = z_pain->prev;
			ent->pain = NULL;
			break;
		}
	}
	orig_G_FreeEdict(ent);
}

void engine_ent_relink(edict_t* ent) {
	orig_SV_LinkEdict(ent);
}

void engine_ent_use(edict_t* ent) {
	if (ent->use) {
		ent->use(ent, NULL, NULL);
	}
}

void engine_ent_vects(edict_t* ent, vec3_t fwd, vec3_t side, vec3_t up) {
	orig_AngleVectors(ent->s.angles, fwd, side, up);
}

void engine_ent_tint(edict_t* ent, vec3_t colors, float alpha) {
	if (ent->ghoulInst) {
		clientinst = (unsigned int*)(ent->ghoulInst);
		GhoulSetTint(colors[0], colors[1], colors[2], alpha);
	}
}

void engine_ent_anim(edict_t* ent, const char* animName, float startPos, int restart, int loop, int match, int reverse) {
	if (!ent) return;
	clientinst = (unsigned int*)(ent->ghoulInst);
	if (clientinst) {
		GhoulGetObject();
		GhoulID seq = GhoulFindSequence(animName);
		if (!seq) {
			orig_Com_Printf("Cant find sequence\n");
			return;
		}
		GhoulPlay(seq, *(float*)0x5015CCDC, startPos, restart, loop, match, reverse);
	}
}

void engine_ent_model(edict_t* ent, const char* dir, const char* modelname) {
	if (!ent) return;
	modelSpawnData_t mdata = {
		.dir = (char*)dir,
		.file = (char*)modelname,
		.surfaceType = SURF_WOOD_DBROWN,
		.material = MAT_WOOD_DBROWN,
		.health = 500,
		.solid = SOLID_BBOX,
		.materialfile = NULL,
		.debrisCnt = 0,
		.debrisScale = DEBRIS_NONE,
		.objBreakData = NULL,
	};
	orig_SimpleModelInit2(ent, &mdata, NULL, NULL);
}

void engine_ent_bolt(edict_t* ent, const char* dir, const char* file, const char* bolt_from, const char* bolt_to, float scale) {
	if (!ent) return;
	clientinst = (unsigned int*)(ent->ghoulInst);
	if (clientinst) {
		GhoulGetObject();
		ggObjC* MyGhoulObj = GhoulFindObjectSmall((IGhoulObj*)objinst);
		ggOinstC* myInstance = orig_FindOInst(MyGhoulObj, (IGhoulInst*)clientinst);
		orig_AddBoltedItem(ent->client->body, *ent, (char*)bolt_from, (char*)dir, (char*)file, (char*)bolt_to, myInstance, NULL, scale);
	}
}

void engine_ent_paint(edict_t* ent, float r, float g, float b, float a) {
	if (!ent) return;
	clientinst = (unsigned int*)ent->ghoulInst;
	if (!clientinst) {
		orig_Com_Printf("Ent doesn't have a ghoul model\n");
		return;
	}
	GhoulSetTintOnAll(r, g, b, a);
}

int engine_ent_find(int offset, const char* value, edict_t** results, int maxResults) {
	int count = 0;
	edict_t* entfound = orig_G_Find(0, offset, value, 0);
	while (entfound && count < maxResults) {
		if (results) {
			results[count] = entfound;
		}
		count++;
		entfound = orig_G_Find(entfound, offset, value, 0);
	}
	return count;
}

int engine_ent_callback(edict_t* ent, const char* type, const char* funcName) {
	char funcStr[128];
	sprintf(funcStr, "sp_sc_func_exec %s\n", funcName);
	if (!strcmp(type, "think")) {
		event_think_s* z = (event_think_s*)malloc(sizeof(event_think_s));
		z->next = think_events.next;
		z->prev = &think_events;
		think_events.next->prev = z;
		think_events.next = z;
		z->ent = ent;
		strcpy(z->sofplusfunc, funcStr);
		ent->think = &ThinkEventCallback;
		return 1;
	} else if (!strcmp(type, "touch")) {
		event_touch_s* z = (event_touch_s*)malloc(sizeof(event_touch_s));
		z->next = touch_events.next;
		z->prev = &touch_events;
		touch_events.next->prev = z;
		touch_events.next = z;
		z->ent = ent;
		strcpy(z->sofplusfunc, funcStr);
		ent->touch = &TouchEventCallback;
		return 1;
	} else if (!strcmp(type, "use")) {
		event_use_s* z = (event_use_s*)malloc(sizeof(event_use_s));
		z->next = use_events.next;
		z->prev = &use_events;
		use_events.next->prev = z;
		use_events.next = z;
		z->ent = ent;
		strcpy(z->sofplusfunc, funcStr);
		ent->use = &UseEventCallback;
		return 1;
	} else if (!strcmp(type, "pluse")) {
		event_pluse_s* z, * next;
		for (z = pluse_events.next; z != &pluse_events; z = next) {
			next = z->next;
			if (z->ent == ent) {
				z->ent = ent;
				strcpy(z->sofplusfunc, funcStr);
				ent->plUse = &PlUseEventCallback;
				return 1;
			}
		}
		z = (event_pluse_s*)malloc(sizeof(event_pluse_s));
		z->next = pluse_events.next;
		z->prev = &pluse_events;
		pluse_events.next->prev = z;
		pluse_events.next = z;
		z->ent = ent;
		strcpy(z->sofplusfunc, funcStr);
		ent->plUse = &PlUseEventCallback;
		return 1;
	} else if (!strcmp(type, "pain")) {
		event_pain_s* z = (event_pain_s*)malloc(sizeof(event_pain_s));
		z->next = pain_events.next;
		z->prev = &pain_events;
		pain_events.next->prev = z;
		pain_events.next = z;
		z->ent = ent;
		strcpy(z->sofplusfunc, funcStr);
		ent->pain = &PainEventCallback;
		return 1;
	} else if (!strcmp(type, "die")) {
		event_die_s* z = (event_die_s*)malloc(sizeof(event_die_s));
		z->next = die_events.next;
		z->prev = &die_events;
		die_events.next->prev = z;
		die_events.next = z;
		z->ent = ent;
		strcpy(z->sofplusfunc, funcStr);
		ent->die = &DieCallback;
		return 1;
	}
	return 0;
}

