typedef void (*PM_AddCurrents_type) (vec3_t	wishvel);
extern PM_AddCurrents_type orig_PM_AddCurrents;

extern void my_PM_ClipVelocity (vec3_t in, vec3_t normal, vec3_t out, float overbounce);

typedef void (*PM_ClipVelocity_type) (vec3_t in, vec3_t normal, vec3_t out, float overbounce);
extern PM_ClipVelocity_type orig_PM_ClipVelocity;

typedef void (*PM_StepSlideMove__type)(void);
extern PM_StepSlideMove__type orig_PM_StepSlideMove_;
extern void my_PM_StepSlideMove_ (void);

typedef void (*PM_StepSlideMove_type)(int argument);
extern PM_StepSlideMove_type orig_PM_StepSlideMove;
extern void my_PM_StepSlideMove(int argument);

typedef void (*PM_SnapPosition_type)(void);
extern PM_SnapPosition_type orig_PM_SnapPosition;
extern void my_PM_SnapPosition(void);

typedef void (*PM_InitialSnapPosition_type)(void);
extern PM_InitialSnapPosition_type orig_PM_InitialSnapPosition;
extern void my_PM_InitialSnapPosition(void);

typedef void (*PM_CatagorizePosition_type)(void);
extern PM_CatagorizePosition_type orig_PM_CatagorizePosition;
extern void my_PM_CatagorizePosition(void);

typedef void (*PM_AirMove_type)(void);
extern PM_AirMove_type orig_PM_AirMove;
extern void my_PM_AirMove(void);

typedef int (__thiscall * SPSP_FindStringID_type)(void * self,char * stringref);
extern SPSP_FindStringID_type orig_SPSP_FindStringID;

typedef void * (__thiscall *SP_ListByIDNextEnd_type)(void * self);
extern SP_ListByIDNextEnd_type orig_SP_ListByIDNextEnd;

typedef const char *(*SP_GetStringTextString_type)(const char *Reference);
extern SP_GetStringTextString_type orig_SP_GetStringTextString;

typedef int		(*FS_LoadFile_type) (char *name, void **buf, bool OverridePak = false);
extern FS_LoadFile_type orig_FS_LoadFile;

typedef unsigned int (__thiscall *SP_vnsprintf_type)(void * self, char * writetome,int size,void * va_list);
extern SP_vnsprintf_type orig_SP_vnsprintf;
extern unsigned int __thiscall my_SP_vnsprintf(void * self, char * writetome,int size,void * va_list);


typedef void (__thiscall *SetMyBolt_type)(void * self,char * boltname);
extern SetMyBolt_type orig_SetMyBolt;

typedef ggBinstC	*(__thiscall *AddBoltedItem_type)(void * self,edict_t &monster, char *myBolt, char *itemClass, char *itemSeq, char *itemBolt, ggOinstC *myInstance, char *itemSkinName=NULL, float scale = 1.0);
extern AddBoltedItem_type orig_AddBoltedItem;

typedef ggOinstC	*(__thiscall *FindOInst_type)(void * self,IGhoulInst *findme);
extern FindOInst_type orig_FindOInst;

typedef void (*SimpleModelScale_type)(edict_t *ent,float objscale);
extern SimpleModelScale_type orig_SimpleModelScale;

typedef void (__thiscall *PutBits_type)(void * self,const void *x,int NumBits);
extern PutBits_type orig_PutBits;
extern void __thiscall my_PutBits(void * self,const void *x,int NumBits);

typedef unsigned (*COM_BlockChecksum_type)(void *buffer, int length);
extern COM_BlockChecksum_type orig_COM_BlockChecksum;
extern void my_COM_BlockChecksum(void * buffer, int length);

typedef void (*SV_ExecuteClientMessage_type) (client_t *cl);
extern SV_ExecuteClientMessage_type orig_SV_ExecuteClientMessage;
extern void my_SV_ExecuteClientMessage(client_t *cl);

typedef unsigned char (*COM_BlockSequenceCRCByte_type)(unsigned char *base, int length, int sequence);
extern COM_BlockSequenceCRCByte_type orig_COM_BlockSequenceCRCByte;
extern unsigned char my_COM_BlockSequenceCRCByte(unsigned char *base, int length, int sequence);


typedef void (*DoRespawn_type)(edict_t * ent);
extern DoRespawn_type orig_DoRespawn;
void my_DoRespawn(edict_t * ent);

typedef void (*SV_Configstrings_f_type)(void);
extern SV_Configstrings_f_type orig_SV_Configstrings_f;
void my_SV_Configstrings_f(void);

typedef void (*SV_New_f_type)(void);
extern SV_New_f_type orig_SV_New_f;
void my_SV_New_f(void);

typedef void ( *MSG_WriteUnknownDelta_type ) (sizebuf_t *sb, int c);
extern MSG_WriteUnknownDelta_type orig_MSG_WriteUnknownDelta;
void my_MSG_WriteUnknownDelta(sizebuf_t *sb, int c);


typedef void (*SV_EmitPacketEntities_type)(void *from, void *to, sizebuf_t *msg);
extern SV_EmitPacketEntities_type orig_SV_EmitPacketEntities;
void my_SV_EmitPacketEntities (void *from, void *to, sizebuf_t *msg);

typedef void (*MSG_WriteDeltaEntity_type) (struct entity_state_s *from, struct entity_state_s *to, sizebuf_t *msg, qboolean force, qboolean newentity);
extern MSG_WriteDeltaEntity_type orig_MSG_WriteDeltaEntity;
void my_MSG_WriteDeltaEntity (struct entity_state_s *from, struct entity_state_s *to, sizebuf_t *msg, qboolean force, qboolean newentity);

typedef void (*SV_WriteFrameToClient_type) (client_t *client, sizebuf_t *msg);
extern SV_WriteFrameToClient_type orig_SV_WriteFrameToClient;
void my_SV_WriteFrameToClient (client_t *client, sizebuf_t *msg);

typedef void (*NET_SendPacket_type) (netsrc_t sock, int length, void *data, netadr_t to);
extern NET_SendPacket_type orig_NET_SendPacket;
// void my_NET_SendPacket(netsrc_t sock, int length, void *data, netadr_t to);

typedef void (*SV_Multicast_type) (vec3_t origin, multicast_t to,int thirdunknown);
extern SV_Multicast_type orig_SV_Multicast;
extern SV_Multicast_type orig_SV_Multicast2;
void my_SV_Multicast (vec3_t origin, multicast_t to,int size);
void my_SV_Multicast2 (vec3_t origin, multicast_t to,int size);

typedef void (*SZ_Write_type) (sizebuf_t *buf, void *data, int length);
extern SZ_Write_type orig_SZ_Write;
void my_SZ_Write(sizebuf_t * buf, void * data, int length);

typedef void  (*Com_Error_type) (int code, char *fmt, ...);
extern Com_Error_type orig_Com_Error;


typedef void (*SV_InitGameProgs_type)(void);
extern SV_InitGameProgs_type orig_SV_InitGameProgs;
void my_SV_InitGameProgs(void);

// Inventory funcs
typedef void ( __thiscall *SetOwner_type)(void * self,void *own);
extern SetOwner_type orig_SetOwner;

typedef int (__thiscall *selectWeapon_type)(void * self,int weapon);
extern selectWeapon_type orig_selectWeapon;

typedef void (__thiscall *rulesSetFreelySelectWeapon_type)(void * self,int toggle);
extern rulesSetFreelySelectWeapon_type orig_rulesSetFreelySelectWeapon;

typedef void (__thiscall *becomeDisguised_type)(void* self);
extern becomeDisguised_type orig_becomeDisguised;


typedef void (*ClientThink_type) (edict_t *ent, usercmd_t *ucmd);
extern ClientThink_type orig_ClientThink;
void my_ClientThink(edict_t *ent, usercmd_t *ucmd);

typedef void (*SVC_DirectConnect_type)(void);
extern SVC_DirectConnect_type orig_SVC_DirectConnect;
void my_SVC_DirectConnect(void); 


typedef game_export_t *(*GetGameAPI_type) (game_import_t *import);
extern GetGameAPI_type orig_GetGameAPI;
extern GetGameAPI_type pmy_GetGameAPI;
game_export_t * my_GetGameAPI (game_import_t *import);


typedef Pickup * (__thiscall *GetPickupFromType_type)(PickupList *self,pickup_t type, int spawnParm);
extern GetPickupFromType_type orig_GetPickupFromType;

typedef void (*I_Spawn_type)(edict_t *ent, Pickup *pickup);
extern I_Spawn_type orig_I_Spawn;

typedef void (*AddWeaponTypeForPrecache_type)(int type);
extern AddWeaponTypeForPrecache_type orig_AddWeaponTypeForPrecache;

typedef void (*SV_Init_type)(void);
extern SV_Init_type orig_SV_Init;
void my_SV_Init(void);


typedef char* (*spfileChecksum_type)( char * dir, char * file);
extern spfileChecksum_type orig_spfileChecksum;

typedef char * (*GeoGetCC_type)(unsigned int ip);
extern GeoGetCC_type orig_GeoGetCC;

typedef void (*Cmd_Score_f_type)(edict_t *ent);
extern Cmd_Score_f_type orig_Cmd_Score_f;
void my_Cmd_Score_f(edict_t *ent);


typedef void (__thiscall * setDMMode_type)(void * self,int newtype);
extern setDMMode_type orig_setDMMode;
void __thiscall my_setDMMode(void * self,int dmmode);

typedef void (__thiscall *dmClientRespawn_type)(void * self,edict_t *ent);
extern dmClientRespawn_type orig_dmClientRespawn;
void __thiscall my_dmClientRespawn(void * self,edict_t *ent);

typedef void (__thiscall *dmClientScoreboardMessage_type) (void * self,edict_t *ent, edict_t *killer, qboolean log_file);
extern dmClientScoreboardMessage_type orig_dmClientScoreboardMessage;
void __thiscall my_dmClientScoreboardMessage(void * self,edict_t *ent, edict_t *killer, qboolean log_file);

typedef void (*Qcommon_Init_type) (void);
extern Qcommon_Init_type orig_Qcommon_Init;
void my_Qcommon_Init (void);

typedef void	(*linkentity_type) (edict_t *ent);
extern linkentity_type orig_linkentity;



// void *ggOinstC (__thiscall *FindBoltInstance_type)(void * self,IGhoulInst * boltInst);
// extern FindBoltInstance_type orig_FindBoltInstance;



/*GetFrameOverride_type orig_GetFrameOverride = (GetFrameOverride_type)NULL;
typedef GhoulID (*GetFrameOverride_type)(GhoulID Mat,GhoulID Part=0,TexChannel Channel=Diffuse);
extern GetFrameOverride_type orig_GetFrameOverride;
*/


typedef void (*ctf_base_touch_type) (edict_t *self, edict_t *other, cplane_t *plane, mtexinfo_t *surf);
extern ctf_base_touch_type orig_ctf_base_touch;
extern void my_ctf_base_touch(edict_t *self, edict_t *other, cplane_t *plane, mtexinfo_t *surf);

typedef void (*itemFlagTouch_type)(edict_t *self, edict_t *other, cplane_t *plane, mtexinfo_t *surf);
extern itemFlagTouch_type orig_itemFlagTouch;
extern void my_itemFlagTouch(edict_t *self, edict_t *other, cplane_t *plane, mtexinfo_t *surf);

typedef void (*Netchan_Transmit_type) (netchan_t *chan, int length, byte *data);
extern Netchan_Transmit_type orig_Netchan_Transmit;
void my_Netchan_Transmit (netchan_t *chan, int length, byte *data);

typedef void (*SV_StartSound_type)(vec3_t origin,edict_t *entity, int channel, int sound_num, float volume,float attenuation, float timeofs,int localize);
extern SV_StartSound_type orig_SV_StartSound;

typedef void (*AngleVectors_type) (vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
extern AngleVectors_type orig_AngleVectors;

typedef int (*SV_GhoulIndex_type)(char *name);
extern SV_GhoulIndex_type orig_SV_GhoulIndex;
extern int my_SV_GhoulIndex(char *name);

typedef void (*Z_FreeTags_type) (int tag);
extern Z_FreeTags_type orig_Z_FreeTags;

typedef void *(*Z_TagMalloc_type) (int size, int tag);
extern Z_TagMalloc_type orig_Z_TagMalloc;
//extern void *Z_TagMalloc (int size, int tag);

typedef char *(*CopyString_type) (char *in);
extern CopyString_type orig_CopyString;


typedef void (*Z_Free_type) (void *ptr);
extern Z_Free_type orig_Z_Free;


typedef void (*SpawnEntities_type) (char *mapname, char *entities, char *spawnpoint);
extern SpawnEntities_type orig_SpawnEntities;
extern void my_SpawnEntities (char *mapname, char *entities, char *spawnpoint);



typedef void (__thiscall *ctfClientScoreboardMessage_type)(void * self,edict_t *ent, edict_t *killer, qboolean log_file);
extern ctfClientScoreboardMessage_type orig_ctfClientScoreboardMessagee;
extern void __thiscall my_ctfClientScoreboardMessage(void * self,edict_t *ent, edict_t *killer, qboolean log_file);



typedef void (*SV_LinkEdict_type)(edict_t * ent);
extern SV_LinkEdict_type orig_SV_LinkEdict;
extern void my_SV_LinkEdict (edict_t *ent);

typedef edict_t * (*G_Find_type) (edict_t *from, int fieldofs, char *match, int charsToCompare);
extern G_Find_type orig_G_Find;
extern edict_t * my_G_Find(edict_t *from, int fieldofs, char *match, int charsToCompare = 0);

typedef void (*spectator_respawn_type)(edict_t * ent);
extern spectator_respawn_type orig_spectator_respawn;
extern void my_spectator_respawn(edict_t * ent);

typedef void (__thiscall *NetWrite_type)(void * self,int clientnum);
extern NetWrite_type orig_NetWrite;

typedef void	(*ReliableWriteByteToClient_type)(byte b,int clientNum);
extern ReliableWriteByteToClient_type orig_ReliableWriteByteToClient;

typedef void (*sendRestartPrediction_type)(edict_t *ent);
extern sendRestartPrediction_type orig_sendRestartPrediction;
// extern void my_sendRestartPrediction(edict_t *ent);

typedef void (*SV_SendClientMessages_type) (void);
extern SV_SendClientMessages_type orig_SV_SendClientMessages;
extern void my_SV_SendClientMessages(void);


typedef qboolean (*SV_SendClientDatagram_type)(client_t *client);
extern SV_SendClientDatagram_type orig_SV_SendClientDatagram;
extern qboolean my_SV_SendClientDatagram(client_t *client);

typedef IGhoulInst	*(__thiscall *getViewModel_type)(unsigned int self);
extern getViewModel_type orig_getViewModel;

typedef int (__thiscall *getCurWeapon_type)(void *self);
extern getCurWeapon_type orig_getCurWeapon;



typedef void (__thiscall *initNewWeapon_type)(void * self);
extern initNewWeapon_type orig_initNewWeapon;
extern void __thiscall my_initNewWeapon(void * self);

typedef int (__thiscall *selectWeapon_type)(void* self,int weapon);
extern selectWeapon_type orig_selectWeapon;
extern int __thiscall my_selectWeapon(void* self,int weapon);

typedef void ( __thiscall * takeOutWeapon_type)(void * self,int weapon);
extern takeOutWeapon_type orig_takeOutWeapon;
extern void __thiscall my_takeOutWeapon(void * self, int weapon);


typedef void (*ShutdownGame_type)(void);
extern ShutdownGame_type orig_ShutdownGame;
extern void my_ShutdownGame(void);


typedef int	(*FS_FileExists_type) (char *path);
extern FS_FileExists_type orig_FS_FileExists;


typedef void (*script_use_type)(edict_t *ent, edict_t *other, edict_t *activator);
extern void my_script_use(edict_t *ent, edict_t *other, edict_t *activator);
extern script_use_type orig_script_use;

typedef int (__thiscall *CScript_type)(void * self,char *ScriptName, edict_t *new_owner);
extern CScript_type orig_CScript;
extern int __thiscall my_CScript(void * self,char *ScriptName, edict_t *new_owner);

typedef int (__thiscall *StringVar_type)(char * stringname, char *stringvalue);
extern StringVar_type orig_StringVar;

typedef void * (*cplusplus_new_type)(unsigned int size);
extern cplusplus_new_type orig_cplusplus_new;


typedef void (*SP_script_runner_type) (edict_t *ent);
extern SP_script_runner_type orig_SP_script_runner;


//LINUX FUNCTIONS
//dlsym
/*
typedef void * (dlsym_real_type)( void * handle, const char * symbol );
extern dlsym_real pr_real_dlsym;

//fopen
typedef FILE *(fopen_type)(const char *path, const char *mode);
extern fopen pr_real_fopen;

//glXGetProcAddressARB
typedef __GLXextFuncPtr (glXGetProcAddressARB_type) (const GLubyte*);
extern glXGetProcAddressARB pr_real_glXGetProcAddressARB;
__GLXextFuncPtr     pr_my_glXGetProcAddressARB (const GLubyte* procName);

//glXSwapBuffers
typedef __GLXextFuncPtr (glXSwapBuffers_type)(Display* dpy, GLXDrawable drawable); // pointer to function type SwapBuffers
extern glXSwapBuffers pr_real_glXSwapBuffers;
void                pr_my_glXSwapBuffers       (Display* dpy, GLXDrawable drawable);
*/



//OPENGL FUNCTIONS
/*
typedef void (glColor4f_type)( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern glColor4f pr_real_glColor4f;

typedef void (glColor3b_type)( GLbyte red, GLbyte green, GLbyte blue);
extern glColor3b pr_real_glColor3b;

typedef void (glColor3d_type)( GLdouble red, GLdouble green, GLdouble blue);
extern glColor3d pr_real_glColor3d;

typedef void (glColor3f_type)( GLfloat red, GLfloat green, GLfloat blue);
extern glColor3f pr_real_glColor3f;

typedef void (glColor3fv_type)( const GLfloat *v );
extern glColor3fv pr_real_glColor3fv;

typedef void (glColor4fv_type)( const GLfloat *v );
extern glColor4fv pr_real_glColor4fv;

typedef void (glColor4ub_type)( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha );
extern glColor4ub pr_real_glColor4ub;

typedef void (glVertex3fv_type)( const GLfloat *v );
extern glVertex3fv pr_real_glVertex3fv;

typedef void (glTexImage2D_type)( GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data );
extern glTexImage2D pr_real_glTexImage2D;

typedef void (glBindTexture_type)( GLenum target, GLuint texture );
extern glBindTexture pr_real_glBindTexture;
*/
//SOF-INBUILT-FUNCTIONS

//DrawChar
/*
typedef void ( DrawChar _type)(int f3,int f2,char* c,int i,int f);
void pr_my_DrawChar(int f3,int f2,char* c,int i,int f);
DrawChar DrawChar = (DrawChar)NULL;
*/
/*
//DrawFlag
typedef void ( * DrawFlag _type)(int i1,int i2, int i3,int i4, int i5, char * i6,int i7);
void pr_my_DrawFlag(int i1,int i2, int i3,int i4, int i5, char * i6,int i7);
DrawFlag DrawFlag = (DrawFlag)NULL;
*/
/*
//C_Parse
typedef char * ( * Com_Parse_type)(char **data_p);
char * pr_my_Com_Parse (char **data_p);
Com_Parse Com_Parse = (Com_Parse) 0x20055470;
*/
/*
//vSprintf
typedef char * ( * vSprintf_type)(const char * format, ...);
char * pr_my_vSprintf(const char * format, ...);
vSprintf vSprintf = (vSprintf) 0x20055450;
*/
/*
// SCR_UpdateScreen
typedef void ( * SCR_UpdateScreen_type)(BYTE arg00, BYTE arg01, BYTE arg02, BYTE arg03);
void pr_my_SCR_UpdateScreen(BYTE arg00, BYTE arg01, BYTE arg02, BYTE arg03);
SCR_UpdateScreen pr_real_SCR_UpdateScreen = (SCR_UpdateScreen)NULL;
*/


/*
//SV_Frame
typedef void (__attribute__((fastcall)) * SV_Frame_type) (int msec);
void __attribute__((fastcall)) pr_my_SV_Frame (int msec);
SV_Frame SV_Frame = (SV_Frame)NULL;
*/
/*
// SCR_ExecuteLayoutString
typedef void ( * SCR_ExecuteLayoutString_type)(char *s);
void pr_my_SCR_ExecuteLayoutString (char *s);
SCR_ExecuteLayoutString SCR_ExecuteLayoutString = (SCR_ExecuteLayoutString)NULL;
*/
/*
// opengldraw
typedef void (  * opengldraw_type)(int arg1, int arg2, char * arg3, int arg4, int arg5);
void pr_my_opengldraw(int arg1, int arg2, char *  arg3, int arg4, int arg5);
void pr_my_opengldraw2(int arg1, int arg2, char *  arg3, int arg4, int arg5);
opengldraw opengldraw = (opengldraw)NULL;
*/
/*
// opengldrawpic
typedef void ( * opengldrawpic_type)(int x, int y, char * iconname,int arg4);
void pr_my_opengldrawpic(int x, int y, char * iconname,int arg4);
opengldrawpic opengldrawpic = (opengldrawpic)NULL;
*/

// Cbuf_AddText
typedef void ( * Cbuf_AddText_type)(char * text);

/*
// SZ_Write
typedef void ( * SZ_Write_type)(sizebuf_t *buf, void *data, int length);
void pr_my_SZ_Write(sizebuf_t *buf, void *data, int length);
SZ_Write SZ_Write = (SZ_Write)NULL;
*/
/*
// Tokenize
typedef void ( * Tokenize_type)(char * text, int macroexpand);
void pr_my_Tokenize(char *text, int macroexpand);
Tokenize Tokenize = (Tokenize)NULL;
*/


//Com_Printf
typedef void ( *Com_Printf_type)(char * msg, ...);


//Cmd_Args
/*
typedef char * ( Cmd_Args ) ( void );
Cmd_Args Cmd_Args = (Cmd_Args) 0x20018D50;
*/
//Cvar_Get
typedef cvar_t *(*Cvar_Get_type)(const char * name, const char * value, int flags, cvarcommand_t command = NULL);


typedef cvar_t  *(*Cvar_Set_type)(const char *name, const char *value );

//recv
/*
typedef ssize_t (recv_type)(int sockfd, void *buf, size_t len, int flags);
recv pr_real_recv = (recv) NULL;
*/
//recvfrom
/*
typedef ssize_t ( recvfrom_type)(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
recvfrom pr_real_recvfrom = (recvfrom) NULL;
*/

typedef void (*SZ_Init_type)(sizebuf_t *buf, byte *data, int length);
extern SZ_Init_type orig_SZ_Init;

typedef void (*MSG_WriteShort_type)(sizebuf_t *sb, int c);
extern MSG_WriteShort_type orig_MSG_WriteShort;
void my_MSG_WriteShort(sizebuf_t *sb, int c);

typedef void (*MSG_WriteLong_type) (sizebuf_t *sb, int c);
extern MSG_WriteLong_type orig_MSG_WriteLong;

typedef void (*MSG_WritePos_type) (sizebuf_t *sb, vec3_t pos);
extern MSG_WritePos_type orig_MSG_WritePos;

//MSG_WriteByte
typedef void ( *MSG_WriteByte_type ) (sizebuf_t *sb, int c);
extern MSG_WriteByte_type orig_MSG_WriteByte;

//MSG_WriteString
typedef void ( *MSG_WriteString_type ) (sizebuf_t *sb, char * string);
extern MSG_WriteString_type orig_MSG_WriteString;
// extern void my_MSG_WriteString(sizebuf_t *sb, char * string);

//PF_WriteString
typedef void ( *PF_WriteString_type ) (char * string);
extern PF_WriteString_type orig_PF_WriteString;

typedef void (*PF_WriteByte_type) (int c);
extern PF_WriteByte_type orig_PF_WriteByte;


typedef void (*SV_RemoveSound_type)(char *name);
typedef int (*SV_SoundIndex_td)(char *name);
extern int my_SV_SoundIndex(char *name);

typedef int (*SV_FindIndex_type) (char *name, int start, int max, qboolean create, char * type);

typedef void (*SP_Register_type)(char *Package);
typedef void (*SP_Print_type)(edict_t *ent, unsigned short ID, ...);
typedef void (*SP_Print_Obit_type)(edict_t *ent, unsigned short ID, ...);
typedef int (*SP_SPrint_type)(char *buffer, int buffer_size, unsigned short ID, ...);
typedef const char	*(*SP_GetStringText_type)(unsigned short ID);

typedef void	(*cprintf_type) (edict_t *ent, int printlevel, char *fmt, ...);
typedef void	(*bprintf_type) (int printlevel, char *fmt, ...);
typedef void	(*centerprintf_type) (edict_t *ent, char *fmt, ...);
typedef void	(*welcomeprint_type) (edict_t *ent);
typedef void	(*cinprintf_type) (edict_t *ent,int x, int y, int textspeed, char *text);


typedef void (*SP_script_runner_type) (edict_t *ent);
extern void my_SP_script_runner (edict_t *ent);


//PF_Unicode
typedef void (*PF_Unicast_type) (edict_t *ent, qboolean reliable);
void my_PF_Unicast (edict_t *ent, qboolean reliable);
extern PF_Unicast_type orig_PF_Unicast;

typedef void (*PF_StartSound_type)(edict_t *entity, int channel, int sound_num, float volume,float attenuation, float timeofs,int localize);
extern PF_StartSound_type orig_PF_StartSound;
extern void my_PF_StartSound(edict_t *entity, int channel, int sound_num, float volume,float attenuation, float timeofs,int localize);
/*
//MSG_ReadString
typedef const char * (MSG_ReadString_type)(sizebuf_t * sb);
extern MSG_ReadString_type pr_real_MSG_ReadString;
const char * my_MSG_ReadString(sizebuf_t * sb);
*/
//Cmd_AddCommand
typedef void (*Cmd_AddCommand_type)(const char * cmd_name, const void * function);
//Cmd_RemoveCommand
typedef void (*Cmd_RemoveCommand_type)(const char * cmd_name);
//Cmd_ExecuteString
typedef void (*Cmd_ExecuteString_type)(const char * string);
//Cmd_Argc
typedef int (*Cmd_Argc_type)(void);
//Cmd_Argv
typedef char * (*Cmd_Argv_type)(int arg);
//Cmd_Args
typedef char * (*Cmd_Args_type)(void);



typedef void (*Info_SetValueForKey_type) (char *s, char *key, char *value);
typedef char *(*Info_ValueForKey_type) (char *s, char *key);

typedef void (*SV_UserinfoChanged_type) (void *cl);
extern void my_SV_UserinfoChanged(void * cl);


typedef unsigned char (*COM_BlockSequenceCRCByte_type)(unsigned char *base, int length, int sequence);
extern unsigned char my_COM_BlockSequenceCRCByte(unsigned char *base, int length, int sequence);


typedef void (*ClientBegin_type) (edict_t *ent);
extern void my_ClientBegin(edict_t *ent);


typedef qboolean (*ClientConnect_type) (edict_t *ent, char *userinfo);
extern qboolean my_ClientConnect(edict_t *ent, char *userinfo);


typedef void (*TakePiss_type)(unsigned int arg1, char* arg2, int arg3);
extern void my_TakePiss(unsigned int arg1, char* arg2, int arg3);


/*
//Cvar_VariableString
typedef const char	*(Cvar_VariableString_type) (const char *var_name);
extern Cvar_VariableString_type pr_real_Cvar_VariableString;
const char * my_Cvar_VariableString(const char *var_name);

*/
//Trace
/*typedef qboolean ( * trace_type) (trace_t * tr, vec3_t start,vec3_t end, vec3_t mins, vec3_t maxs, int headnode , int brushmark*//*, int eight, int nine*//*);
extern trace_type pr_real_trace;

// CL_DeltaEntity
typedef void (* CL_DeltaEntity_type)(frame_t *frame, int newnum, entity_state_t *old, int bits);
extern CL_DeltaEntity_type pr_real_CL_DeltaEntity;
extern void my_CL_DeltaEntity(frame_t *frame, int newnum, entity_state_t *old, int bits);


//CL_CalcViewValues
typedef void (* CL_CalcViewValues_type)(void);
extern CL_CalcViewValues_type pr_real_CL_CalcViewValues;
extern void my_CL_CalcViewValues(void);

//CL_SendCmd
typedef void (* MSG_WriteDeltaCmd_type)(char * buf, usercmd_t * oldcmd,usercmd_t * cmd);
extern MSG_WriteDeltaCmd_type pr_real_MSG_WriteDeltaCmd;
extern void my_MSG_WriteDeltaCmd(char * buf, usercmd_t * oldcmd,usercmd_t * cmd);

//SP_Print
typedef void ( * SP_Print_type)(int id, char * data);
extern SP_Print_type pr_real_SP_Print;
extern void my_SP_Print(int id, char * data);

//KeyUp
typedef void (* KeyUp_type)(void * kbutton);
extern KeyUp_type pr_real_KeyUp;
//KeyDown
typedef void (* KeyDown_type)(void * kbutton);
extern KeyDown_type pr_real_KeyDown;

typedef void ( GhoulWindowBox_type)(char * str);
extern GhoulWindowBox_type pr_real_GhoulWindowBox;
extern void my_GhoulWindowBox(char * str);

//REF_GL FUNCTIONS

//R_RenderView
typedef void (R_RenderView_type)(void *wtf);
extern R_RenderView_type pr_real_R_RenderView;
extern void my_R_RenderView(void *wtf);

*/

typedef void ( *PF_Configstring_type)(int index, char * string);
extern void my_PF_Configstring(int index,char * string);
extern PF_Configstring_type orig_PF_Configstring;
extern PF_Configstring_type det_PF_Configstring;


typedef void (*G_FreeEdict_type)(edict_t * ent);
typedef edict_t * (*G_Spawn_type) (void);



typedef char *(*ED_NewString_type) (char *string);

typedef void (*ED_CallSpawn_type) (edict_t *ent);
void my_ED_CallSpawn(edict_t *ent);




//5008BB10 - 8
typedef void (*T_Damage_type) (edict_t *targ, edict_t *inflictor, edict_t *attacker, 
vec3_t dir, vec3_t point, vec3_t origin, int damage, int knockback, int dflags, int mod, float penetrate, float absorb);
extern void T_Damage(edict_t *targ, edict_t *inflictor, edict_t *attacker, 
vec3_t dir, vec3_t point, vec3_t origin, int damage, int knockback, int dflags, int mod, float penetrate=0.0, float absorb=0.0);

typedef void (*debug_drawbox_type)(edict_t* self,vec3_t vOrigin, vec3_t vMins, vec3_t vMaxs, int nColor);



typedef void * (__cdecl * Sys_GetGameApi_type)(void * imports);
extern void * my_Sys_GetGameApi(void * imports);



typedef void * ( *Sys_GetPlayerAPI_type)(void * one, void * two, void * three, void * four,void * five);
extern void *  my_Sys_GetPlayerAPI(void * one, void * two, void * three, void * four, void * five);
extern Sys_GetPlayerAPI_type orig_Sys_GetPlayerAPI;

//SV_Trace
typedef bool (*SV_Trace_type)(vec3_t start,vec3_t mins, vec3_t maxs,vec3_t end, edict_t * ent, int brushmask, trace_t * tr);



typedef void (__stdcall *PB_AddFlag_type)(edict_t *ent, char *FlagSkinName, char* FlagGhoulFile);
extern PB_AddFlag_type orig_PB_AddFlag;
extern void __stdcall my_PB_AddFlag(edict_t *ent, char *FlagSkinName, char* FlagGhoulFile);

typedef bool (*PB_InitBody_type)(edict_t *ent,char *userinfo);
extern bool my_PB_InitBody(edict_t *ent,char *userinfo);
extern PB_InitBody_type orig_PB_InitBody;


typedef void (*SimpleModelInit2_type)(edict_t *ent, modelSpawnData_t *modelData,char *skinname,char *partname);
extern void my_SimpleModelInit2(edict_t *ent, modelSpawnData_t *modelData,char *skinname,char *partname);
extern SimpleModelInit2_type orig_SimpleModelInit2;


//no one knows
typedef IPlayerModelInfoC	*(*NewPlayerModelInfo_type)(char *modelname);
extern IPlayerModelInfoC	*my_NewPlayerModelInfo(char *modelname); 
extern NewPlayerModelInfo_type orig_NewPlayerModelInfo;

//p_client.cpp
typedef void (*PutClientInServer_type) (edict_t *ent);
extern void my_PutClientInServer(edict_t *ent);
extern PutClientInServer_type orig_PutClientInServer;


// g_ghoul.cpp
extern ggOinstC	* __stdcall my_AddObjectInstance(ggObjC *curObject, edict_t *whose);
typedef ggOinstC	*(__stdcall *AddObjectInstance_type)(ggObjC *curObject, edict_t *whose);
extern AddObjectInstance_type orig_AddObjectInstance;


//p_client.cpp
typedef void (*respawn_type) (edict_t *self);
extern void my_respawn (edict_t *self);
extern respawn_type orig_respawn;

//GHOUL FUNCTIONS
typedef unsigned int * __attribute__ ((cdecl))(* GetGhoul_type)(bool Client,bool Menu);
typedef unsigned int * __attribute__ ((stdcall))(* FindClientInst_type)(GhoulUUID key);
typedef void __attribute__ ((stdcall))(* GetXForm_type)(float *m);
typedef void __attribute__ ((stdcall))(* SetTintOnAll_type)(float r,float g,float b,float a);
typedef void __attribute__ ((stdcall))(* SetTint_type)(float r,float g,float b,float a);
typedef void __attribute__ ((stdcall))(* AddNoteCallBack_type)(IGhoulCallBack *c,GhoulID Token);
typedef bool __attribute__ ((stdcall))(* Play_type)(const char *Seq,float Now,float PlayPos,bool Restart,IGhoulInst::EndCondition ec, bool MatchCurrentPos, bool reverseAnim);
typedef void *__attribute__ ((stdcall))(* GetUserData_type)(void); // 58
typedef int __attribute__ ((stdcall))(* GetNumChildren_type)(void);
typedef unsigned int *__attribute__ ((stdcall))(* GetChild_type)(int Child,GhoulID &bolt);
typedef unsigned int * __attribute__ ((stdcall))(* GetGhoulObject_type)(void);
typedef unsigned short __attribute__ ((stdcall))(* FindPart_type)(const char *PartName);
typedef GhoulID __attribute__ ((stdcall))(*FindSequence_type)(const char *Filename);
typedef void __attribute__ ((stdcall))(* UnPackReliable_type)(int packetID,InPacket &ip,bool specular);
typedef bool __attribute__ ((stdcall))(* GetBoltMatrix_type)(float Time,Matrix4 &m,unsigned short GhoulID,MatrixType kind,bool ToRoot);
typedef void __attribute__ ((stdcall))(* GetBoundBox_type)(float Time,const Matrix4 &ToWorld,Vect3 &mins,Vect3 &maxs,GhoulID Part,bool Accurate);

typedef GhoulID __attribute__ ((stdcall))(*FindNoteToken_type)(const char *Token);



//FX FUNCTIONS
typedef void (*FX_MakeBarrelExplode_type)(vec3_t pos, edict_t *source);
typedef void (*FX_MakeBloodSpray_type)(vec3_t pos, vec3_t splatDir, int vel, int amount, edict_t *source);
typedef void (*FX_MakeDecalBelow_type)(vec3_t pos, int type, unsigned int lLifeTime);
typedef void (*FX_MakeSparks_type)(vec3_t pos, vec3_t dir, int type);
typedef void (*FX_MakeGumballs_type)(vec3_t pos, vec3_t dir, int type);
typedef void (*FX_MakeGlob_type)(vec3_t pos, short color, int size);
typedef void (*FX_MakeExtinguisherExplode_type)(edict_t *ent, vec3_t dirVel);//, trace_t tr);
typedef void (*FX_MakeDustPuff_type)(vec3_t pos);
typedef void (*FX_MakeElectricArc_type)(vec3_t pos, int len, vec3_t dir);
typedef void (*FX_MakeBulletWhiz_type)(edict_t *ent, vec3_t offset, vec3_t dir, int power, int len);
typedef void (*FX_MakeWallDamage_type)(trace_t &tr, vec3_t dir, int size, int markType,int debris);
typedef void (*FX_MakeSkyLightning_type)(void);
typedef void (*FX_MakeRocketExplosion_type)(edict_t *ent, vec3_t point, int size, vec3_t normal, struct mtexinfo_s *surf);
typedef void (*FX_MakeGrenadeExplosion_type)(edict_t *ent, vec3_t point, int size);
typedef void (*FX_ThrowDebris_type)(vec3_t	origin,vec3_t norm, byte numchunks, byte scale, byte skin,byte x_max,byte y_max,byte z_max, byte surfType);
typedef void (*FX_ThrowGlass_type)(vec3_t origin, byte numchunks);
typedef void (*FX_C4Explosion_type)(edict_t *ent);
typedef void (*FX_Flashpack_type)(vec3_t pos);
typedef void (*FX_NeuralPulse_type)(vec3_t pos);
typedef void (*FX_MakeAutoGunMuzzleFlash_type)(edict_t *self);
typedef void (*FX_StrikeWall_type)(vec3_t spot, byte wallType);
typedef void (*FX_BubbleTrail_type)(vec3_t start, vec3_t end);
typedef void (*FX_SmokeBurst_type)(vec3_t pos, float size);
typedef void (*FX_MakeLine_type)(vec3_t start, vec3_t end, paletteRGBA_t color, int lifetime, int mcastType);
typedef void (*FX_WallSparks_type)(vec3_t pos, vec3_t dir, float size);
typedef void (*FX_Bleed_type)(edict_t *ent, GhoulID boltID, int amount);
typedef void (*FX_BloodCloud_type)(edict_t *ent, GhoulID boltID, int amount);
typedef void (*FX_HeadExplosion_type)(edict_t *ent, GhoulID boltID);
typedef void (*FX_BloodJet_type)(edict_t *ent, vec3_t spot, vec3_t jetDir);
typedef void (*FX_HeliGun_type)(edict_t *ent, IGhoulInst *heli, IGhoulInst *muzzle, GhoulID heliToMuzzleBolt, GhoulID muzEnd);
typedef void (*FX_WhiteBurn_type)(edict_t *ent);
typedef void (*FX_EnemyShot_type)(edict_t *ent, IGhoulInst *gun, byte weapID);
typedef void (*FX_WhiteBlast_type)(vec3_t org);
typedef void (*FX_MinimiTrail_type)(edict_t *ent);
typedef void (*FX_Explosion_type)(vec3_t pos, byte size);
typedef void (*FX_VehicleExplosion_type)(vec3_t pos, byte size);
typedef void (*FX_SmokePuff_type)(vec3_t pos,byte red,byte green,byte blue,byte alpha);
typedef void (*FX_LittleExplosion_type)(vec3_t pos, byte size, byte bSound);
typedef void (*FX_MediumExplosion_type)(vec3_t pos, byte size, byte bSound);
typedef void (*FX_LargeExplosion_type)(vec3_t pos, byte size, byte bSound);
typedef void (*FX_MakeRing_type)(vec3_t pos, short size);
typedef void (*FX_PaperCloud_type)(vec3_t vPos, byte nCount/*0 generates random num of papers*/);
typedef void (*FX_SodaCans_type)(vec3_t vPos, vec3_t vDir, byte nSpeed, byte nCount/*0 generates random num of cans*/);
typedef void (*FX_MakeCoins_type)(vec3_t pos, vec3_t dir, int type);
typedef void (*FX_FloorSpace_type)(edict_t *ent);
typedef void (*FX_DropDustBits_type)(vec3_t spot, int amount);
typedef void (*FX_MakeRicochet_type)(vec3_t vPos);
typedef void (*FX_PhoneHit_type)(vec3_t vPos);
typedef void (*FX_TrashcanHit_type)(vec3_t vPos);
typedef void (*FX_HandleDMShotEffects_type)(vec3_t start, vec3_t dir, vec3_t end, edict_t *shooter, int tracerfx, IGhoulInst *gun, int muzzlefx);
typedef void (*FX_HandleDMShotHitEffects_type)(vec3_t start, vec3_t dir, vec3_t end, edict_t *shooter, int tracerfx, IGhoulInst *gun, int muzzlefx);
typedef void (*FX_HandleDMShotBigHitEffects_type)(vec3_t start, vec3_t dir, vec3_t end, edict_t *shooter, int tracerfx, IGhoulInst *gun, int muzzlefx);
typedef void (*FX_HandleDMMuzzleFlash_type)(vec3_t start, vec3_t dir, edict_t *shooter, IGhoulInst *gun, int muzzlefx);
extern void my_FX_HandleDMMuzzleFlash(vec3_t start, vec3_t dir, edict_t *shooter, IGhoulInst *gun, int muzzlefx);


extern Cvar_Set_type orig_Cvar_Set;
extern Cvar_Get_type orig_Cvar_Get;
extern Com_Printf_type orig_Com_Printf;
extern Cmd_AddCommand_type orig_Cmd_AddCommand;
extern Cmd_RemoveCommand_type orig_Cmd_RemoveCommand;
extern Cmd_Argv_type orig_Cmd_Argv;
extern Cmd_Argc_type	orig_Cmd_Argc;
extern Cmd_Args_type orig_Cmd_Args;
extern Cmd_ExecuteString_type orig_Cmd_ExecuteString;
extern Cbuf_AddText_type orig_Cbuf_AddText;
extern Info_SetValueForKey_type orig_Info_SetValueForKey;
extern Info_ValueForKey_type orig_Info_ValueForKey;

extern SV_UserinfoChanged_type orig_SV_UserinfoChanged;

extern COM_BlockSequenceCRCByte_type orig_COM_BlockSequenceCRCByte;


extern ClientBegin_type orig_ClientBegin;
extern ClientConnect_type orig_ClientConnect;

extern SP_Register_type orig_SP_Register;
extern SP_Print_type orig_SP_Print;
extern SP_Print_Obit_type orig_SP_Print_obit;
extern SP_SPrint_type orig_SP_SPrint;
extern SP_GetStringText_type orig_SP_GetStringText;

extern cprintf_type orig_cprintf;
extern bprintf_type orig_bprintf;
extern centerprintf_type orig_centerprintf;
extern welcomeprint_type orig_welcomeprint;
extern cinprintf_type orig_cinprintf;

extern SP_script_runner_type orig_SP_script_runner;

extern TakePiss_type orig_TakePiss;

extern SV_RemoveSound_type orig_SV_RemoveSound;
extern SV_SoundIndex_td orig_SV_SoundIndex;
extern SV_FindIndex_type orig_SV_FindIndex;


extern T_Damage_type orig_T_Damage;
extern Sys_GetGameApi_type orig_Sys_GetGameApi;
extern debug_drawbox_type orig_debug_drawbox;
extern SV_Trace_type orig_SV_Trace;

extern G_FreeEdict_type orig_G_FreeEdict;
extern G_Spawn_type orig_G_Spawn;
extern ED_NewString_type orig_ED_NewString;
extern ED_CallSpawn_type orig_ED_CallSpawn;

extern FX_MakeBarrelExplode_type orig_FX_MakeBarrelExplode;
extern FX_MakeBloodSpray_type orig_FX_MakeBloodSpray;
extern FX_MakeDecalBelow_type orig_FX_MakeDecalBelow;
extern FX_MakeSparks_type orig_FX_MakeSparks;
extern FX_MakeGumballs_type orig_FX_MakeGumballs;
extern FX_MakeGlob_type orig_FX_MakeGlob;
extern FX_MakeExtinguisherExplode_type orig_FX_MakeExtinguisherExplode;
extern FX_MakeDustPuff_type orig_FX_MakeDustPuff;
extern FX_MakeElectricArc_type orig_FX_MakeElectricArc;
extern FX_MakeBulletWhiz_type orig_FX_MakeBulletWhiz;
extern FX_MakeWallDamage_type orig_FX_MakeWallDamage;
extern FX_MakeSkyLightning_type orig_FX_MakeSkyLightning;
extern FX_MakeRocketExplosion_type orig_FX_MakeRocketExplosion;
extern FX_MakeGrenadeExplosion_type orig_FX_MakeGrenadeExplosion;
extern FX_ThrowDebris_type orig_FX_ThrowDebris;
extern FX_ThrowGlass_type orig_FX_ThrowGlass;
extern FX_C4Explosion_type orig_FX_C4Explosion;
extern FX_Flashpack_type orig_FX_Flashpack;
extern FX_NeuralPulse_type orig_FX_NeuralPulse;
extern FX_MakeAutoGunMuzzleFlash_type orig_FX_MakeAutoGunMuzzleFlash;
extern FX_StrikeWall_type orig_FX_StrikeWall;
extern FX_BubbleTrail_type orig_FX_BubbleTrail;
extern FX_SmokeBurst_type orig_FX_SmokeBurst;
extern FX_MakeLine_type orig_FX_MakeLine;
extern FX_WallSparks_type orig_FX_WallSparks;
extern FX_Bleed_type orig_FX_Bleed;
extern FX_BloodCloud_type orig_FX_BloodCloud;
extern FX_HeadExplosion_type orig_FX_HeadExplosion;
extern FX_BloodJet_type orig_FX_BloodJet;
extern FX_HeliGun_type orig_FX_HeliGun;
extern FX_WhiteBurn_type orig_FX_WhiteBurn;
extern FX_EnemyShot_type orig_FX_EnemyShot;
extern FX_WhiteBlast_type orig_FX_WhiteBlast;
extern FX_MinimiTrail_type orig_FX_MinimiTrail;
extern FX_Explosion_type orig_FX_Explosion;
extern FX_VehicleExplosion_type orig_FX_VehicleExplosion;
extern FX_SmokePuff_type orig_FX_SmokePuff;
extern FX_LittleExplosion_type orig_FX_LittleExplosion;
extern FX_MediumExplosion_type orig_FX_MediumExplosion;
extern FX_LargeExplosion_type orig_FX_LargeExplosion;
extern FX_MakeRing_type orig_FX_MakeRing;
extern FX_PaperCloud_type orig_FX_PaperCloud;
extern FX_SodaCans_type orig_FX_SodaCans;
extern FX_MakeCoins_type orig_FX_MakeCoins;
extern FX_FloorSpace_type orig_FX_FloorSpace;
extern FX_DropDustBits_type orig_FX_DropDustBits;
extern FX_MakeRicochet_type orig_FX_MakeRicochet;
extern FX_PhoneHit_type orig_FX_PhoneHit;
extern FX_TrashcanHit_type orig_FX_TrashcanHit;
extern FX_HandleDMShotEffects_type orig_FX_HandleDMShotEffects;
extern FX_HandleDMShotHitEffects_type orig_FX_HandleDMShotHitEffects;
extern FX_HandleDMShotBigHitEffects_type orig_FX_HandleDMShotBigHitEffects;
extern FX_HandleDMMuzzleFlash_type orig_FX_HandleDMMuzzleFlash;

extern GetGhoul_type orig_GetGhoul;
extern FindClientInst_type orig_FindClientInst;
extern GetXForm_type orig_GetXForm;
extern SetTintOnAll_type orig_SetTintOnAll;
extern SetTint_type orig_SetTint;
extern AddNoteCallBack_type orig_AddNoteCallBack;
extern Play_type orig_Play;
extern FindSequence_type orig_FindSequence;
extern GetUserData_type orig_GetUserData;
extern GetNumChildren_type orig_GetNumChildren;
extern GetChild_type orig_GetChild;
extern GetGhoulObject_type orig_GetGhoulObject;
extern FindPart_type orig_FindPart;
extern UnPackReliable_type orig_UnPackReliable;
extern GetBoltMatrix_type orig_GetBoltMatrix;
extern GetBoundBox_type orig_GetBoundBox;
extern FindNoteToken_type orig_FindNoteToken;