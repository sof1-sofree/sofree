#include <windows.h>

#include "sofheader.h"



PM_AddCurrents_type orig_PM_AddCurrents = (PM_AddCurrents_type)0x20052DB0;
PM_StepSlideMove__type orig_PM_StepSlideMove_ = (PM_StepSlideMove__type) NULL;
PM_StepSlideMove_type orig_PM_StepSlideMove = (PM_StepSlideMove_type)NULL;
PM_SnapPosition_type orig_PM_SnapPosition = (PM_SnapPosition_type)NULL;
PM_InitialSnapPosition_type orig_PM_InitialSnapPosition = (PM_InitialSnapPosition_type)NULL;
PM_CatagorizePosition_type orig_PM_CatagorizePosition = (PM_CatagorizePosition_type)NULL;
PM_AirMove_type orig_PM_AirMove = (PM_AirMove_type)NULL;
SPSP_FindStringID_type orig_SPSP_FindStringID = (SPSP_FindStringID_type) 0x200576C0;
SP_ListByIDNextEnd_type orig_SP_ListByIDNextEnd = (SP_ListByIDNextEnd_type) 0x20085230;
SP_GetStringTextString_type orig_SP_GetStringTextString = (SP_GetStringTextString_type)0x200581A0;
FS_LoadFile_type orig_FS_LoadFile = (FS_LoadFile_type)0x20025370;

SP_vnsprintf_type orig_SP_vnsprintf = (SP_vnsprintf_type)0x20056B90;
SetMyBolt_type orig_SetMyBolt = (SetMyBolt_type)0X20089250;
AddBoltedItem_type orig_AddBoltedItem = (AddBoltedItem_type)0x500121C0;
FindOInst_type orig_FindOInst = (FindOInst_type) 0x500A51D0;
SimpleModelScale_type orig_SimpleModelScale = (SimpleModelScale_type)0x500B34F0;
PutBits_type orig_PutBits = (PutBits_type)NULL;
COM_BlockChecksum_type orig_COM_BlockChecksum = (COM_BlockChecksum_type)NULL;
SV_ExecuteClientMessage_type orig_SV_ExecuteClientMessage = (SV_ExecuteClientMessage_type)NULL;
DoRespawn_type orig_DoRespawn = ( DoRespawn_type)NULL;
SV_Configstrings_f_type orig_SV_Configstrings_f = (SV_Configstrings_f_type) NULL;
SV_New_f_type orig_SV_New_f = (SV_New_f_type) NULL;
MSG_WriteUnknownDelta_type orig_MSG_WriteUnknownDelta = (MSG_WriteUnknownDelta_type)NULL;

SV_EmitPacketEntities_type orig_SV_EmitPacketEntities = (SV_EmitPacketEntities_type)NULL;
MSG_WriteDeltaEntity_type orig_MSG_WriteDeltaEntity = (MSG_WriteDeltaEntity_type)NULL;

SV_WriteFrameToClient_type orig_SV_WriteFrameToClient = (SV_WriteFrameToClient_type)NULL;
NET_SendPacket_type orig_NET_SendPacket = (NET_SendPacket_type)0x2004E9A0;
SV_Multicast_type orig_SV_Multicast = (SV_Multicast_type)NULL;
SV_Multicast_type orig_SV_Multicast2 = (SV_Multicast_type)NULL;

Netchan_OutOfBandPrint_type orig_Netchan_OutOfBandPrint = (Netchan_OutOfBandPrint_type)0x2004D2F0;
NET_StringToAdr_type orig_NET_StringToAdr = (NET_StringToAdr_type)0x2004E2D0;

//inven funcs
SetOwner_type orig_SetOwner = (SetOwner_type) 0x40005B30;
selectWeapon_type orig_selectWeapon = (selectWeapon_type)0x400024D0;
initNewWeapon_type orig_initNewWeapon = (initNewWeapon_type)0x400020C0;
takeOutWeapon_type orig_takeOutWeapon = (takeOutWeapon_type)0x400025A0; //5
rulesSetFreelySelectWeapon_type orig_rulesSetFreelySelectWeapon = (rulesSetFreelySelectWeapon_type)0x400051A0;
becomeDisguised_type orig_becomeDisguised = (becomeDisguised_type)0x40002C90;

ClientThink_type orig_ClientThink = (ClientThink_type)NULL;

SVC_DirectConnect_type orig_SVC_DirectConnect = (SVC_DirectConnect_type)NULL;

SV_InitGameProgs_type orig_SV_InitGameProgs = (SV_InitGameProgs_type)NULL;

GetGameAPI_type orig_GetGameAPI = (GetGameAPI_type)0x500AD9B0;
GetGameAPI_type pmy_GetGameAPI = &my_GetGameAPI;

GetPickupFromType_type orig_GetPickupFromType = (GetPickupFromType_type)0x5006A4A0;
I_Spawn_type orig_I_Spawn = (I_Spawn_type)0x500AA030;
AddWeaponTypeForPrecache_type orig_AddWeaponTypeForPrecache = (AddWeaponTypeForPrecache_type)0x500F62E0;

SV_Init_type orig_SV_Init = (SV_Init_type)0x2005F8A0;

//sofplus function
GeoGetCC_type orig_GeoGetCC = (GeoGetCC_type)NULL;
spfileChecksum_type orig_spfileChecksum = (spfileChecksum_type)NULL;

Cmd_Score_f_type orig_Cmd_Score_f = (Cmd_Score_f_type)NULL;


setDMMode_type orig_setDMMode = (setDMMode_type)NULL;
dmClientRespawn_type orig_dmClientRespawn = (dmClientRespawn_type)NULL;
dmClientScoreboardMessage_type orig_dmClientScoreboardMessage = (dmClientScoreboardMessage_type) NULL; 
ctfClientScoreboardMessage_type orig_ctfClientScoreboardMessage = (ctfClientScoreboardMessage_type)NULL;

Qcommon_Init_type orig_Qcommon_Init = (Qcommon_Init_type)NULL;

linkentity_type orig_linkentity = (linkentity_type)0x20063E60;

// FindBoltInstance_type orig_FindBoltInstance = (FindBoltInstance_type)0x500A4290;
ctf_base_touch_type orig_ctf_base_touch = (ctf_base_touch_type)0x500725D0;
itemFlagTouch_type orig_itemFlagTouch = (itemFlagTouch_type)NULL;
SZ_Init_type orig_SZ_Init = (SZ_Init_type)0x2001E700;

SZ_Write_type orig_SZ_Write = (SZ_Write_type)0x2001E7B0;
MSG_WriteShort_type orig_MSG_WriteShort = (MSG_WriteShort_type)0x2001CB70;
MSG_WriteLong_type orig_MSG_WriteLong = (MSG_WriteLong_type)0x2001CBF0;
MSG_WritePos_type orig_MSG_WritePos = (MSG_WritePos_type)0x2001CE00;
Netchan_Transmit_type orig_Netchan_Transmit = (Netchan_Transmit_type)0x2004D400;
SV_StartSound_type orig_SV_StartSound = (SV_StartSound_type)NULL;

AngleVectors_type orig_AngleVectors = (AngleVectors_type)0x20054B30;

SV_GhoulIndex_type orig_SV_GhoulIndex = (SV_GhoulIndex_type)0x2005D5B0;

Z_FreeTags_type orig_Z_FreeTags = (Z_FreeTags_type)0x2001F010;

Z_TagMalloc_type orig_Z_TagMalloc = (Z_TagMalloc_type)0x2001F090;

Z_Free_type orig_Z_Free = (Z_Free_type)0x2001EBC0;
CopyString_type orig_CopyString = (CopyString_type)0x2001EA20;

SpawnEntities_type orig_SpawnEntities = (SpawnEntities_type)0x500BDB50;



SV_LinkEdict_type orig_SV_LinkEdict = (SV_LinkEdict_type)0x20063E60;

G_Find_type orig_G_Find = (G_Find_type)0x500C26A0;



spectator_respawn_type orig_spectator_respawn = (spectator_respawn_type)0x500F35D0;

SV_SendClientDatagram_type orig_SV_SendClientDatagram = (SV_SendClientDatagram_type)NULL;
SV_SendClientMessages_type orig_SV_SendClientMessages = (SV_SendClientMessages_type)NULL;
sendRestartPrediction_type orig_sendRestartPrediction = (sendRestartPrediction_type)0x500F3860; //5
ReliableWriteByteToClient_type orig_ReliableWriteByteToClient = (ReliableWriteByteToClient_type)0x2005cc50;//8

getCurWeapon_type orig_getCurWeapon = (getCurWeapon_type)NULL;

NetWrite_type orig_NetWrite = (NetWrite_type)NULL;




Sys_GetPlayerAPI_type orig_Sys_GetPlayerAPI = (Sys_GetPlayerAPI_type)NULL;
getViewModel_type orig_getViewModel = (getViewModel_type)NULL;

PF_Configstring_type orig_PF_Configstring = (PF_Configstring_type)0x2005CA40;
PF_Configstring_type det_PF_Configstring = (PF_Configstring_type)NULL;
FS_FileExists_type orig_FS_FileExists = (FS_FileExists_type)0x20024DF0;
SP_script_runner_type orig_SP_script_runner = (SP_script_runner_type)NULL;
cplusplus_new_type orig_cplusplus_new = (cplusplus_new_type)0x501070B0;
CScript_type orig_CScript = (CScript_type)NULL;
script_use_type orig_script_use = (script_use_type)0x50076570;

PB_AddFlag_type orig_PB_AddFlag = (PB_AddFlag_type)0x500A3F30;

Cvar_Set_type orig_Cvar_Set = (Cvar_Set_type)0x20022190;
Cvar_Get_type orig_Cvar_Get = (Cvar_Get_type)0x20021AE0;
Com_Printf_type orig_Com_Printf = (Com_Printf_type)0x2001C6E0;
Com_Error_type orig_Com_Error = (Com_Error_type)0x2001C9A0;
Cmd_AddCommand_type orig_Cmd_AddCommand = (Cmd_AddCommand_type)GetProcAddress(GetModuleHandle(NULL), "Cmd_AddCommand");
Cmd_RemoveCommand_type orig_Cmd_RemoveCommand = (Cmd_RemoveCommand_type)GetProcAddress(GetModuleHandle(NULL), "Cmd_RemoveCommand");
Cmd_Argv_type orig_Cmd_Argv = (Cmd_Argv_type)0x20018D30;
Cmd_Argc_type orig_Cmd_Argc = (Cmd_Argc_type)0x20018D20;
Cmd_Args_type orig_Cmd_Args = (Cmd_Args_type)0x20018D50;
Cmd_ExecuteString_type orig_Cmd_ExecuteString = (Cmd_ExecuteString_type)0x200194F0;
Cbuf_AddText_type orig_Cbuf_AddText = (Cbuf_AddText_type)0x20018180;
Info_SetValueForKey_type orig_Info_SetValueForKey = (Info_SetValueForKey_type)0x20055750;
Info_ValueForKey_type orig_Info_ValueForKey = (Info_ValueForKey_type)0x20055590;
COM_BlockSequenceCRCByte_type orig_COM_BlockSequenceCRCByte = (COM_BlockSequenceCRCByte_type)0x2001F1B0;

SV_UserinfoChanged_type orig_SV_UserinfoChanged = (SV_UserinfoChanged_type)0x2005F7D0;
MSG_WriteString_type orig_MSG_WriteString = (MSG_WriteString_type)0x2001CD00;
MSG_WriteByte_type orig_MSG_WriteByte = (MSG_WriteByte_type)0x2001CB00;
PF_WriteString_type orig_PF_WriteString = (PF_WriteString_type)0x2005CBC0;
PF_Unicast_type orig_PF_Unicast = (PF_Unicast_type)NULL;
PF_WriteByte_type orig_PF_WriteByte = ( PF_WriteByte_type)0x2005CB40;

PF_StartSound_type orig_PF_StartSound = (PF_StartSound_type)0x2005CD30;

SV_RemoveSound_type orig_SV_RemoveSound = (SV_RemoveSound_type)0x2005D5F0;
SV_FindIndex_type orig_SV_FindIndex = (SV_FindIndex_type)0x2005D320;
SV_SoundIndex_td orig_SV_SoundIndex = (SV_SoundIndex_td)NULL;

welcomeprint_type orig_welcomeprint = (welcomeprint_type)0x2005C5A0;
cprintf_type orig_cprintf = (cprintf_type)0x2005C2E0;
bprintf_type orig_bprintf = (bprintf_type)0x200618D0;
centerprintf_type orig_centerprintf = (centerprintf_type)0x2005C490;
cinprintf_type orig_cinprintf = (cinprintf_type)0x2005C670;

SP_Register_type orig_SP_Register = (SP_Register_type)0x20057F20;
SP_Print_type orig_SP_Print = (SP_Print_type)0x20058280;
SP_Print_Obit_type orig_SP_Print_obit = (SP_Print_Obit_type)0x5015CAB4;
SP_SPrint_type orig_SP_SPrint = (SP_SPrint_type)0x5015CAB8;
SP_GetStringText_type orig_SP_GetStringText = (SP_GetStringText_type)0x5015CABC;



ClientBegin_type orig_ClientBegin = (ClientBegin_type)NULL;
ClientConnect_type orig_ClientConnect = (ClientConnect_type) NULL;
TakePiss_type orig_TakePiss = (TakePiss_type) 0x500273A0;

G_FreeEdict_type orig_G_FreeEdict = (G_FreeEdict_type)0x500C3880;
ED_NewString_type orig_ED_NewString = (ED_NewString_type)0x500BD6D0;
ED_CallSpawn_type orig_ED_CallSpawn = (ED_CallSpawn_type)NULL;
G_Spawn_type orig_G_Spawn = (G_Spawn_type)0x500C3690;
T_Damage_type orig_T_Damage = (T_Damage_type)NULL;
Sys_GetGameApi_type orig_Sys_GetGameApi = (Sys_GetGameApi_type)NULL;
ShutdownGame_type orig_ShutdownGame = (ShutdownGame_type)0x500AD5B0;
debug_drawbox_type orig_debug_drawbox = (debug_drawbox_type)0x500CEE40;
SV_Trace_type orig_SV_Trace = (SV_Trace_type)0x20064E60;


PB_InitBody_type orig_PB_InitBody = (PB_InitBody_type) NULL;
SimpleModelInit2_type orig_SimpleModelInit2 = (SimpleModelInit2_type) 0x500B3870;
NewPlayerModelInfo_type orig_NewPlayerModelInfo = (NewPlayerModelInfo_type)0x500EEF20;
PutClientInServer_type orig_PutClientInServer = (PutClientInServer_type)NULL;
AddObjectInstance_type orig_AddObjectInstance = (AddObjectInstance_type)0x500A5D10;
respawn_type orig_respawn = (respawn_type) 0x500F3550;


//ghoul
GetGhoul_type orig_GetGhoul = (GetGhoul_type)0x20069630;
FindClientInst_type orig_FindClientInst = (FindClientInst_type)NULL;//0x2006CBC0;
GetXForm_type orig_GetXForm = (GetXForm_type)NULL;
SetTintOnAll_type orig_SetTintOnAll = (SetTintOnAll_type)NULL; // 40
Play_type orig_Play = (Play_type)NULL; // 44
SetTint_type orig_SetTint = (SetTint_type)NULL;
AddNoteCallBack_type orig_AddNoteCallBack = (AddNoteCallBack_type)NULL;
GetUserData_type orig_GetUserData = (GetUserData_type)NULL; //58
GetNumChildren_type orig_GetNumChildren = (GetNumChildren_type)NULL; // 80
GetChild_type orig_GetChild = (GetChild_type)NULL; // 84
GetGhoulObject_type orig_GetGhoulObject = (GetGhoulObject_type)NULL;
FindPart_type orig_FindPart = (FindPart_type)NULL;
UnPackReliable_type orig_UnPackReliable=(UnPackReliable_type)NULL;
GetBoltMatrix_type orig_GetBoltMatrix=(GetBoltMatrix_type)NULL;
GetBoundBox_type orig_GetBoundBox=(GetBoundBox_type)NULL;
FindNoteToken_type orig_FindNoteToken = (FindNoteToken_type)NULL;
FindSequence_type orig_FindSequence = (FindSequence_type)NULL;

FX_MakeBarrelExplode_type orig_FX_MakeBarrelExplode = (FX_MakeBarrelExplode_type)0x50084210;
FX_MakeBloodSpray_type orig_FX_MakeBloodSpray = (FX_MakeBloodSpray_type)0x50083C80;
FX_MakeDecalBelow_type orig_FX_MakeDecalBelow = (FX_MakeDecalBelow_type)0x50083D50;

FX_MakeSparks_type orig_FX_MakeSparks = (FX_MakeSparks_type)0xDEADBEEF;

FX_MakeGumballs_type orig_FX_MakeGumballs = (FX_MakeGumballs_type)0x50083EC0;
FX_MakeGlob_type orig_FX_MakeGlob = (FX_MakeGlob_type)0xDEADBEEF;

FX_MakeExtinguisherExplode_type orig_FX_MakeExtinguisherExplode = (FX_MakeExtinguisherExplode_type)0xDEADBEEF;
FX_MakeDustPuff_type orig_FX_MakeDustPuff = (FX_MakeDustPuff_type)0x50083F40;

FX_MakeElectricArc_type orig_FX_MakeElectricArc = (FX_MakeElectricArc_type)0x50083F70;
FX_MakeBulletWhiz_type orig_FX_MakeBulletWhiz = (FX_MakeBulletWhiz_type)0x50083FB0;
FX_MakeWallDamage_type orig_FX_MakeWallDamage = (FX_MakeWallDamage_type)0x500840D0;
FX_MakeSkyLightning_type orig_FX_MakeSkyLightning = (FX_MakeSkyLightning_type)0x50084240;

FX_MakeRocketExplosion_type orig_FX_MakeRocketExplosion = (FX_MakeRocketExplosion_type)0xDEADBEEF;
FX_MakeGrenadeExplosion_type orig_FX_MakeGrenadeExplosion = (FX_MakeGrenadeExplosion_type)0xDEADBEEF;

FX_ThrowDebris_type orig_FX_ThrowDebris = (FX_ThrowDebris_type)0x50084270;

FX_ThrowGlass_type orig_FX_ThrowGlass = (FX_ThrowGlass_type)0xDEADBEEF;

FX_C4Explosion_type orig_FX_C4Explosion = (FX_C4Explosion_type)0x50084370;
FX_Flashpack_type orig_FX_Flashpack = (FX_Flashpack_type)0x500843F0;
FX_NeuralPulse_type orig_FX_NeuralPulse = (FX_NeuralPulse_type)0x50084420;

FX_MakeAutoGunMuzzleFlash_type orig_FX_MakeAutoGunMuzzleFlash = (FX_MakeAutoGunMuzzleFlash_type)0xDEADBEEF;

FX_StrikeWall_type orig_FX_StrikeWall = (FX_StrikeWall_type)0x500844B0;

FX_BubbleTrail_type orig_FX_BubbleTrail = (FX_BubbleTrail_type)0xDEADBEEF;
FX_SmokeBurst_type orig_FX_SmokeBurst = (FX_SmokeBurst_type)0xDEADBEEF;

FX_MakeLine_type orig_FX_MakeLine = (FX_MakeLine_type)0x50084460;
FX_WallSparks_type orig_FX_WallSparks = (FX_WallSparks_type)0x50083E60;
FX_Bleed_type orig_FX_Bleed = (FX_Bleed_type)0x50084500;
FX_BloodCloud_type orig_FX_BloodCloud = (FX_BloodCloud_type)0x50084640;
FX_HeadExplosion_type orig_FX_HeadExplosion = (FX_HeadExplosion_type)0x500847F0;
FX_BloodJet_type orig_FX_BloodJet = (FX_BloodJet_type)0x500848B0;

FX_HeliGun_type orig_FX_HeliGun = (FX_HeliGun_type)0xDEADBEEF;
FX_WhiteBurn_type orig_FX_WhiteBurn = (FX_WhiteBurn_type)0xDEADBEEF;
FX_EnemyShot_type orig_FX_EnemyShot = (FX_EnemyShot_type)0xDEADBEEF;
FX_WhiteBlast_type orig_FX_WhiteBlast = (FX_WhiteBlast_type)0xDEADBEEF;
FX_MinimiTrail_type orig_FX_MinimiTrail = (FX_MinimiTrail_type)0xDEADBEEF;
FX_Explosion_type orig_FX_Explosion = (FX_Explosion_type)0xDEADBEEF;

FX_VehicleExplosion_type orig_FX_VehicleExplosion = (FX_VehicleExplosion_type)0x50084960;
FX_SmokePuff_type orig_FX_SmokePuff = (FX_SmokePuff_type)0x500849A0;
FX_LittleExplosion_type orig_FX_LittleExplosion = (FX_LittleExplosion_type)0x50084A10;
FX_MediumExplosion_type orig_FX_MediumExplosion = (FX_MediumExplosion_type)0x50084A60;
FX_LargeExplosion_type orig_FX_LargeExplosion = (FX_LargeExplosion_type)0x50084AB0;
FX_MakeRing_type orig_FX_MakeRing = (FX_MakeRing_type)0x50084B00;
FX_PaperCloud_type orig_FX_PaperCloud = (FX_PaperCloud_type)0x50084B40;
FX_SodaCans_type orig_FX_SodaCans = (FX_SodaCans_type)0x50084B80;
FX_MakeCoins_type orig_FX_MakeCoins = (FX_MakeCoins_type)0x50083F00;
FX_FloorSpace_type orig_FX_FloorSpace = (FX_FloorSpace_type)0xDEADBEEF;
FX_DropDustBits_type orig_FX_DropDustBits = (FX_DropDustBits_type)0x50084BE0;
FX_MakeRicochet_type orig_FX_MakeRicochet = (FX_MakeRicochet_type)0x500840A0;
FX_PhoneHit_type orig_FX_PhoneHit = (FX_PhoneHit_type)0x50084C20;
FX_TrashcanHit_type orig_FX_TrashcanHit = (FX_TrashcanHit_type)0x50084C50;
FX_HandleDMShotEffects_type orig_FX_HandleDMShotEffects = (FX_HandleDMShotEffects_type)0x50084C80;
FX_HandleDMShotHitEffects_type orig_FX_HandleDMShotHitEffects = (FX_HandleDMShotHitEffects_type)0x50084D00;
FX_HandleDMShotBigHitEffects_type orig_FX_HandleDMShotBigHitEffects = (FX_HandleDMShotBigHitEffects_type)0x50084DB0;
FX_HandleDMMuzzleFlash_type orig_FX_HandleDMMuzzleFlash = (FX_HandleDMMuzzleFlash_type)0x50084E60;
