#include <windows.h>
#include "sofheader.h"
#include <string.h>
#include "engine_features/config/config.h"

void sf_sv_save_reso(void) {
	int slot = atoi(orig_Cmd_Argv(1));
	int x = atoi(orig_Cmd_Argv(2));
	int y = atoi(orig_Cmd_Argv(3));
	engine_config_save_reso(slot, x, y);
}

void sf_sv_check_reso(void) {
	char cmd[256];
	cmd[0] = 0x00;
	for (int i = 1; i < orig_Cmd_Argc(); i++) {
		strcat(cmd, orig_Cmd_Argv(i));
		strcat(cmd, " ");
	}
	if (strlen(cmd) > 0) {
		cmd[strlen(cmd) - 1] = 0x00;
	}
	engine_config_check_reso(cmd);
}

