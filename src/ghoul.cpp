#include <windows.h>
#include "sofheader.h"

unsigned int * ghoulmain 	= 	NULL;
unsigned int * clientinst 	= 	NULL;
unsigned int * objinst 	=	NULL;

void PrintFunctionAddr(void)
{
	orig_UnPackReliable = (UnPackReliable_type)*(unsigned int*)((*(unsigned int*)(ghoulmain))+0x60);
	//printf("UnPackReliable is at %08X\n",ghoulmain);
}
/*
Class function of iGhoul
*/
bool GhoulInstFromID(short int ID)
{
	clientinst=NULL;
	orig_FindClientInst = (FindClientInst_type)*(unsigned int*)((*(unsigned int*)(ghoulmain))+0x24);
	asm volatile("movl %1,%%ecx;"//ghoulmain->ecx
					"push %2;"//push ID
					"call *%3;"//call pr_real_FindClientInst
					"movl %%eax,%0;"//eax->clientinst
					:"=m"(clientinst):"m"(ghoulmain),"m"(ID),"m"(orig_FindClientInst):"%ecx");
	if ( clientinst != NULL )
		return true;
	return false;
}
/*
Class function of iGhoul
*/
bool GhoulGetInst(int slot)
{
	clientinst=NULL;
	slot+=1;
	unsigned int UUID=(slot) << 5;
	UUID=(UUID+slot)*12;
	short int * somearray=(short int*)(0x2015EF94+UUID);
	orig_Com_Printf("somearray is %08X\nand contains %i\n",somearray,*somearray);
	if ( *somearray > 0 )
	{
		orig_Com_Printf("UUID is int %hu\n",*somearray);
		orig_FindClientInst = (FindClientInst_type)*(unsigned int*)((*(unsigned int*)(ghoulmain))+0x24);
		asm volatile(
		"push %2;"//push somearray
		"movl %1,%%ecx;"//ghoulmain->ecx
		"call *%3;"//call orig_FindClientInst
		"movl %%eax,%0;" //eax->clientinst
		:"=m"(clientinst)
		:"m"(ghoulmain),"m"(*somearray),"m"(orig_FindClientInst)
		:"memory","%ecx"
		);
		if ( clientinst != NULL )
			return true;
		return false;
	}
	return false;
}
/*
Class function of GhoulInst
*/
void GhoulSetTintOnAll(float r,float g,float b,float alpha)
{
	orig_SetTintOnAll = (SetTintOnAll_type)*(unsigned int*)((*(unsigned int*)(clientinst)) + 0x40);
	asm volatile(	"push %1;"//push alpha
					"push %2;"//push b
					"push %3;"//push g
					"push %4;"//push r
					"movl %0,%%ecx;"//clientinst->ecx
					"call *%5;"//call orig_SetTintOnAll
					::"m"(clientinst),"m"(alpha),"m"(b),"m"(g),"m"(r),"m"(orig_SetTintOnAll):"%ecx");
}

void GhoulSetTint(float r,float g,float b,float alpha)
{
	orig_SetTint = (SetTint_type)*(unsigned int*)((*(unsigned int*)(clientinst)) + 0x38);
	asm volatile(	"push %1;"//push alpha
					"push %2;"//push b
					"push %3;"//push g
					"push %4;"//push r
					"movl %0,%%ecx;"//clientinst->ecx
					"call *%5;"//call orig_SetTintOnAll
					::"m"(clientinst),"m"(alpha),"m"(b),"m"(g),"m"(r),"m"(orig_SetTint):"%ecx");
}

void GhoulAddNoteCallBack(IGhoulCallBack *c,GhoulID Token)
{
	orig_AddNoteCallBack = (AddNoteCallBack_type)*(unsigned int*)((*(unsigned int*)(clientinst)) + 0x5C);
	asm volatile(	"push %1;"//push Token
					"push %2;"//push c
					"movl %0,%%ecx;"//clientinst->ecx
					"call *%3;"//call orig_SetTintOnAll
					::"m"(clientinst),"m"(Token),"m"(c),"m"(orig_AddNoteCallBack):"%ecx");
}

// 0x44
bool GhoulPlay(GhoulID Seq,float Now,float PlayPos,bool Restart,IGhoulInst::EndCondition ec, bool MatchCurrentPos, bool reverseAnim)
{

	orig_Play = (Play_type)*(unsigned int*)((*(unsigned int*)(clientinst)) + 0x44);
	// orig_Com_Printf("IT IS: %08X\n",orig_Play);
	asm volatile(	"push %1;"//reverseanim
					"push %2;"//matchcurrentpos
					"push %3;"//ec
					"push %4;"//restart
					"push %5;"//playpos
					"push %6;"//now
					"push %7;"//seq
					"movl %0,%%ecx;"//clientinst->ecx
					"call *%8;"//call orig_SetTintOnAll
					::"m"(clientinst),"m"(reverseAnim),"m"(MatchCurrentPos),"m"(ec),"m"(Restart),"m"(PlayPos),"m"(Now),"m"(Seq),"m"(orig_Play):"%ecx");
}

/*
Class function of GhoulInst
*/
void GhoulGetXform(Matrix4 *m)
{
	orig_GetXForm=(GetXForm_type)*(unsigned int*)((*(unsigned int*)(clientinst)) + 0x8);
	asm volatile(	"push %1;"//push m
					"movl %0,%%ecx;"//clientinst->ecx
					"call *%2;"//call orig_GetXForm
					::"m"(clientinst),"m"(m),"m"(orig_GetXForm):"%ecx");
}

/*
Class function of GhoulInst
*/
void GhoulSetXform(Matrix4 *m)
{
	orig_GetXForm=(GetXForm_type)*(unsigned int*)((*(unsigned int*)(clientinst)) +0x0);
	asm volatile(	"push %1;"//push m
					"movl %0,%%ecx;"//clientinst->ecx
					"call *%2;"//call orig_GetXForm
					::"m"(clientinst),"m"(m),"m"(orig_GetXForm):"%ecx");
}

/*
Class function of GhoulInst
*/
bool GhoulGetObject(void)
{
	objinst=NULL;
	orig_GetGhoulObject=(GetGhoulObject_type)*(unsigned int*)((*(unsigned int*)(clientinst)) + 0x88);
	asm volatile("movl %1,%%ecx;"//clientinst->ecx
					"call *%2;"//call orig_GetGhoulObject
					"movl %%eax,%0;"//eax->objinst
					:"=m"(objinst):"m"(clientinst),"m"(orig_GetGhoulObject):"%ecx");
	if (objinst != NULL )
		return true;
	return false;
}

/*
Class function of ObjInst
*/
unsigned short GhoulFindPart(const char * partname)
{
	unsigned int partid;
	orig_FindPart=(FindPart_type)*(unsigned int*)((*(unsigned int*)(objinst)) + 0x1C);

	asm volatile(	"push %2;"//push partname
					"movl %1,%%ecx;"//objinst->ecx
					"call *%3;"//call orig_FindPart
					"movl %%eax,%0;"//eax->partid
					:"=m"(partid):"m"(objinst),"m"(partname),"m"(orig_FindPart):"%ecx");
	
	//asm volatile("movl %0,%%ecx;"::"m"(objinst):"%ecx");
	//return pr_real_FindPart(partname);
	return (unsigned short)partid;
}

/*
Class function of ObjInst
*/
GhoulID GhoulFindNoteToken(const char *Token)
{
	unsigned int ret;
	orig_FindNoteToken=(FindNoteToken_type)*(unsigned int*)((*(unsigned int*)(objinst)) + 0x30);
	asm volatile(	"push %2;"//push Token
					"movl %1,%%ecx;"//objinst->ecx
					"call *%3;"//call orig_FindNoteToken
					"movl %%eax,%0;"//eax->ret
					:"=m"(ret):"m"(objinst),"m"(Token),"m"(orig_FindNoteToken):"%ecx");
	return (unsigned short)ret;
}


GhoulID GhoulFindSequence(const char *Filename)
{
	unsigned int ret;
	orig_FindSequence=(FindSequence_type)*(unsigned int*)((*(unsigned int*)(objinst)) + 0xC);
	asm volatile(	"push %2;"//push Filename
					"movl %1,%%ecx;"//objinst->ecx
					"call *%3;"//call orig_FindNoteToken
					"movl %%eax,%0;"//eax->ret
					:"=m"(ret):"m"(objinst),"m"(Filename),"m"(orig_FindSequence):"%ecx");
	return (unsigned short)ret;
}



/*
Class function of GhoulInst
*/
bool GhoulBoltMatrix(float Time,Matrix4 &m,unsigned short GhoulID,MatrixType kind,bool ToRoot)
{
	int ret = 0;
	orig_GetBoltMatrix = (GetBoltMatrix_type)*(unsigned int*)((*(unsigned int*)(clientinst))+0xC8);
	asm volatile(	"push %2;" //push ToRoot
					"push %3;" //push kind
					"push %4;" //push GhoulID
					"push %5;" //push m
					"push %6;" //push Time
					"movl %1,%%ecx;" //clientinst -> ecx
					"call *%7;" //call orig_GetBoltMatrix
					"movl %%eax,%0;" //eax->ret
					:"=m"(ret)
					:"m"(clientinst),"m"(ToRoot),"m"(kind),"m"(GhoulID),"m"(&m),"m"(Time),"m"(orig_GetBoltMatrix):"%ecx");
	if ( ret > 0 )
		return true;
	return false;

}

void GhoulBoundBox(float Time,const Matrix4 &ToWorld,Vect3 &mins,Vect3 &maxs,GhoulID Part,bool Accurate)
{
	orig_GetBoundBox = (GetBoundBox_type)*(unsigned int*)((*(unsigned int*)(clientinst))+0xCC);
	asm volatile("push %1;" // Accurate
					"push %2;" // Part
					"push %3;" // maxs
					"push %4;" // mins
					"push %5;" // ToWorld
					"push %6;" // Time
					"movl %0,%%ecx;" // clientinst->ecx
					"call *%7;" // orig_GetBoundBox
					::"m"(clientinst),"m"(Accurate),"m"(Part),"m"(&maxs),"m"(&mins),"m"(&ToWorld),"m"(Time),"m"(orig_GetBoundBox):"%ecx");
}





ggObjC *GhoulFindObject(const char* name, const char* subname,bool allSkins,const char *skinname,const char *basefile,bool dontMakeNew)
{
	unsigned int ret = 0;
	void * gameghoul = 0x5015C79C;
 
	static unsigned int orig_FindObject = 0x500A5C10;
	asm volatile("push %2;" // dontMakeNew
					"push %3;" // basefile
					"push %4;" // skinname
					"push %5;" // allSkins
					"push %6;" // subname
					"push %7;" // name
					"movl %1,%%ecx;" // game_ghoul->ecx
					"call *%8;" // FindObject
					"movl %%eax,%0;"
					:"=m"(ret)
					:"m"(gameghoul),"m"(dontMakeNew),"m"(basefile),"m"(skinname),"m"(allSkins),"m"(subname),"m"(name),"m"(orig_FindObject):"%ecx");
	return ret;
}

ggObjC *GhoulFindObjectSmall(IGhoulObj *curObject)
{
	unsigned int ret = 0;
	void * gameghoul = 0x5015C79C;
 
	static unsigned int orig_FindObjectSmall = 0x500A5E10;
	asm volatile(
					"push %2;" // curObject
					"movl %1,%%ecx;" // game_ghoul->ecx
					"call *%3;" // FindObject
					"movl %%eax,%0;"
					:"=m"(ret)
					:"m"(gameghoul),"m"(curObject),"m"(orig_FindObjectSmall):"%ecx");
	return ret;
}
