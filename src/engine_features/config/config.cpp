#include <windows.h>
#include "sofheader.h"
#include <string.h>
#include "engine_features/config/config.h"
#include "util_funcs.h"

extern int reso2d[16][2];

void engine_config_save_reso(unsigned int slot, int x, int y) {
	reso2d[slot][0] = x;
	reso2d[slot][1] = y;
}

void engine_config_check_reso(const char* cmd) {
	char cmdstr[256];
	strcpy(cmdstr, cmd);
	strcat(cmdstr, "\n");
	orig_PF_WriteByte((unsigned char)STUFFTEXT);
	orig_PF_WriteString(cmdstr);
	edict_t* ent = get_ent_from_player_slot(0);
	orig_PF_Unicast(ent, true);
}

