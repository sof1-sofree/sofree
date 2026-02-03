#include <windows.h>
#include "sofheader.h"
#include "engine_features/memory/memory.h"
#include "util_funcs.h"

void sf_sv_mem_read_int(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Read an integer in memory at offset\n"
			"----------------------------\n"
			"arg1 -> outcvar to store the integer\n"
			"arg2 -> memory offset to read from\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_read_int -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if (offset) {
		int value = engine_mem_read_int(offset);
		cvar_t* out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
		setCvarInt(out_cvar, value);
	}
}

void sf_sv_mem_read_short(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Read an short integer in memory at offset\n"
			"----------------------------\n"
			"arg1 -> outcvar to store the short integer\n"
			"arg2 -> memory offset to read from\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_read_short -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if (offset) {
		unsigned short value = engine_mem_read_short(offset);
		cvar_t* out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
		char shortstring[64];
		sprintf(shortstring, "%hd", value);
		setCvarString(out_cvar, shortstring);
	}
}

void sf_sv_mem_read_char(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Read a byte in memory at offset\n"
			"----------------------------\n"
			"arg1 -> outcvar to store the byte\n"
			"arg2 -> memory offset to read from\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_read_char -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if (offset) {
		unsigned char value = engine_mem_read_char(offset);
		cvar_t* out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
		char charstring[64];
		sprintf(charstring, "%c", value);
		setCvarString(out_cvar, charstring);
	}
}

void sf_sv_mem_read_float(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Read a float in memory at offset\n"
			"----------------------------\n"
			"arg1 -> outcvar to store the float\n"
			"arg2 -> memory offset to read from\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_read_float -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if (offset) {
		float value = engine_mem_read_float(offset);
		cvar_t* out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
		setCvarFloat(out_cvar, value);
	}
}

void sf_sv_mem_read_string(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Read a string in memory at offset\n"
			"----------------------------\n"
			"arg1 -> outcvar to store the string\n"
			"arg2 -> memory offset to read from\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_read_string -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(2));
	if (offset) {
		const char* value = engine_mem_read_string(offset);
		cvar_t* out_cvar = orig_Cvar_Get(orig_Cmd_Argv(1), "", 0, NULL);
		setCvarString(out_cvar, (char*)value);
	}
}

void sf_sv_mem_write_int(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Write an integer to memory at offset\n"
			"----------------------------\n"
			"arg1 -> memory offset to write to\n"
			"arg2 -> integer to write\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_write_int -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(1));
	if (offset) {
		engine_mem_write_int(offset, atoi(orig_Cmd_Argv(2)));
	}
}

void sf_sv_mem_write_short(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Write a short integer to memory at offset\n"
			"----------------------------\n"
			"arg1 -> memory offset to write to\n"
			"arg2 -> short integer to write\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_write_short -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(1));
	if (offset) {
		engine_mem_write_short(offset, atoi(orig_Cmd_Argv(2)));
	}
}

void sf_sv_mem_write_char(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Write a byte to memory at offset\n"
			"----------------------------\n"
			"arg1 -> memory offset to write to\n"
			"arg2 -> byte to write\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_write_char -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(1));
	if (offset) {
		engine_mem_write_char(offset, orig_Cmd_Argv(2)[0]);
	}
}

void sf_sv_mem_write_float(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Write a float to memory at offset\n"
			"----------------------------\n"
			"arg1 -> memory offset to write to\n"
			"arg2 -> float to write\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_write_float -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(1));
	if (offset) {
		engine_mem_write_float(offset, atof(orig_Cmd_Argv(2)));
	}
}

void sf_sv_mem_write_string(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Write a string to memory at offset\n"
			"----------------------------\n"
			"arg1 -> memory offset to write to\n"
			"arg2 -> string to write\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_mem_write_string -h\n");
		return;
	}
	unsigned int offset = atoi(orig_Cmd_Argv(1));
	if (offset) {
		engine_mem_write_string(offset, orig_Cmd_Argv(2));
	}
}

void sf_sv_jmp_at(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf(
			"Write a jmp instruction to memory at offset\n"
			"You have to do the relative math to make this work\n"
			"(to - from) - 5;\n"
			"----------------------------\n"
			"arg1 -> memory offset to write to , location of 0xe9\n"
			"arg2 -> jmp destination\n"
		);
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_jmp_at -h\n");
		return;
	}
	void* offset = (void*)atoi(orig_Cmd_Argv(1));
	if (offset) {
		unsigned int jmpTo_offset = atoi(orig_Cmd_Argv(2));
		DWORD dwProt = NULL;
		VirtualProtect(offset, 5, PAGE_READWRITE, &dwProt);
		*(unsigned char*)offset = 0xE9;
		*(unsigned int*)((char*)offset + 1) = jmpTo_offset;
		VirtualProtect(offset, 5, dwProt, &dwProt);
	}
}

void sf_sv_hook_at(void) {
	int c = orig_Cmd_Argc() - 1;
	if (!strcmp(orig_Cmd_Argv(1), "-h")) {
		orig_Com_Printf("This doesnt work , dont use this\n");
		return;
	}
	if (c != 2) {
		orig_Com_Printf("sf_sv_hook_at -h\n");
		return;
	}
}

void Cmd_SP_GetStringText(void) {
	int c = orig_Cmd_Argc() - 1;
	if (c != 1) {
		orig_Com_Printf("Cmd_SP_GetStringText -h\n");
		return;
	}
	unsigned short id = atoi(orig_Cmd_Argv(1));
	const char* text = orig_SP_GetStringText(id);
	if (text) {
		char out[2048] = "echo ";
		strcat(out, text);
		orig_Cbuf_AddText(out);
	}
}

