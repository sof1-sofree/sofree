#include <windows.h>
#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include <stdio.h>
#include <stdlib.h>

#include "sofreeS.h"

#include <string>
#include <map>
// minecraft should be a game mode of its own mb


/*
	Need on bullet hit callback
	Preferably able to get entity classname
	And thus face of impact.
*/
void Minecraft::applyHooks(void) {

}

void Minecraft::removeHooks(void) {
	
}
/*
targ		entity that is being damaged
inflictor	entity that is causing the damage
attacker	entity that caused the inflictor to damage targ
	example: targ=monster, inflictor=rocket, attacker=player
*/
void Minecraft::onDamage(edict_t *targ) {
	// something has been damaged.
	// what data do we need to verify we are interested in this damage event?

	// start with classname of damage entity?
	if ( targ->classname = "mc_block" ) {
		orig_Com_Printf("you hit the mc_block\n");
	}

}