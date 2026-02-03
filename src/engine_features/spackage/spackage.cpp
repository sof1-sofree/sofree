#include <windows.h>
#include <shlwapi.h>
#include "sofheader.h"
#include <string.h>
#include "engine_features/spackage/spackage.h"

extern bool INSIDE_SPACKAGE_PRINT_ID;

void engine_spackage_register(const char* packageName) {
	char temp[128];
	sprintf(temp, "strip/%s", packageName);
	if (orig_FS_LoadFile(temp, NULL, false) == -1) {
		orig_Com_Error(ERR_FATAL, "Error sf_sv_spackage_register: file %s cannot be found\n", temp);
		return;
	}
	char* shorten = strchr((char*)packageName, '.');
	if (shorten) {
		char temp2[128];
		strncpy(temp2, packageName, shorten - packageName);
		temp2[shorten - packageName] = 0x00;
		orig_SP_Register(temp2);
	} else {
		orig_SP_Register((char*)packageName);
	}
}

void engine_spackage_list(const char* search, int* count, cvar_t** savecvar) {
	*count = 0;
	if (!search) search = "";
	for (int i = 1; i < MAX_STRING_PACKAGES; i++) {
		if (*(unsigned char*)(SV_CONFIGSTRINGS + (CS_STRING_PACKAGES + i) * MAX_QPATH)) {
			char line[65];
			strcpy(line, SV_CONFIGSTRINGS + (CS_STRING_PACKAGES + i) * MAX_QPATH);
			if (strlen(search) == 0 || StrStrI(line, search)) {
				(*count)++;
			}
		}
	}
}

void engine_spackage_print_ref(edict_t* ent, const char* fileRef, const char* indexRef) {
	char temp[64];
	sprintf(temp, "%s_%s", fileRef, indexRef);
	short final = SP_ReferenceToID(temp);
	if (final != -1) {
		INSIDE_SPACKAGE_PRINT_ID = true;
		orig_SP_Print(ent, final);
	} else {
		orig_Com_Printf("Error sf_sv_spackage_print_ref : cant find the string refs %s %s\n", fileRef, indexRef);
	}
}

void engine_spackage_print_id(edict_t* ent, unsigned char fileId, unsigned char index) {
	unsigned short final = fileId << 8;
	final |= index;
	INSIDE_SPACKAGE_PRINT_ID = true;
	orig_SP_Print(ent, final);
}

void engine_spackage_print_obit(unsigned int slot, unsigned short id) {
	unsigned int ed_base = *(unsigned int*)EDICT_BASE;
	orig_SP_Print((edict_t*)(ed_base + (slot + 1) * SIZE_OF_EDICT), id);
}

void engine_spackage_print_string(edict_t* ent, const char* msg, int len) {
	orig_SP_Print(ent, (unsigned short)len);
}

