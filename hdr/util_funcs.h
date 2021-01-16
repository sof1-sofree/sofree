// #include "sp_detours.h"
extern HMODULE o_sofplus;
extern bool ListDirectoryContents(const char *sDir, char *** out_list,int *out_length);
extern int SP_ReferenceToID(const char * ref_string);
extern void writeCvarAsVector(vec3_t inarray,char * outcvar);
extern void readCvarAsVector(char *vectorname, vec3_t outarray);
extern edict_t *get_ent_from_player_slot(unsigned int slot);
extern int get_player_slot_from_ent(edict_t * ent);
extern int replacechar(char *str, char orig, char rep);
extern cvar_t * findCvar(char * cvarname);
extern void makeTheStringVaList(char * fmt,char * readstring, va_list vaGList);
extern void makeTheStringElips(char * fmt,cvar_t * readcvar, ...);
extern void debug_drawbox(edict_t* self,float *vOrigin, float *vMins, float *vMaxs, int nColor, int exceptWho=0);
extern void debug_drawbox2(edict_t* self,float *vOrigin, float *vMins, float *vMaxs, int nColor, int exceptWho=0);
extern void debug_drawbox3(edict_t* self,float *vOrigin, float *vMins, float *vMaxs, int nColor , int exceptWho=0);

extern void setCvarInt(cvar_t * which,int val);
extern void setCvarFloat(cvar_t * which, float val);
extern void setCvarUnsignedInt(cvar_t * which,unsigned int val);
extern void setCvarByte(cvar_t * which, unsigned char val);
extern void setCvarString(cvar_t * which, char * newstr);

extern detour_list_t * getFreeLinkedListSlot_Detours(detour_list_t ** linkedList, int * num,int itemSize);
extern sound_overrides_t * getFreeLinkedListSlot_Overrides( sound_overrides_t ** linkedList, int * num,int itemSize);
extern script_list_t * getFreeLinkedListSlot_Scripts(script_list_t ** linkedList, int * num,int itemSize);

extern void drawBoxesOnEnts(int round, int mode);
extern void intersect(edict_t * fromPlayer);
extern void *my_realloc(void * buffer,int size);
extern int changesize(FILE *fp, __int64 size);


void luaPushVectorAsTable(vec3_t inVec);
void luaReadTableAsVector(int tableStackPos, float* vecOut);