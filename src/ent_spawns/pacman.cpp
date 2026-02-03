#include <windows.h>
#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include <stdio.h>
#include <stdlib.h>

#include "sofreeS.h"

#include <string>
#include <map>

modelSpawnData_t pacmandata =
{
 .dir = "sofree",
 .file = "cube_medium",
 .surfaceType = SURF_WOOD_DBROWN,
 .material = MAT_WOOD_DBROWN,
 .health = 500,
 .solid = SOLID_BBOX,
 .materialfile = NULL,
 .debrisCnt = 0,
 .debrisScale = DEBRIS_NONE,
 .objBreakData = NULL,
};
void SP_pacman(edict_t *self)
{
	orig_Com_Printf("Spawning PACMAN\n");

	int real_size = 32;
	int size = real_size * 0.5;
	int neg_size = size*-1;
	VectorSet (self->maxs, size, size, size);
	VectorSet (self->mins,  neg_size,  neg_size,  neg_size);
	orig_SimpleModelInit2(self,&pacmandata,NULL,NULL);
	self->movetype = MOVETYPE_DAN;
	orig_linkentity (self);
}