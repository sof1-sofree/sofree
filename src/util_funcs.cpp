#include <windows.h>
#include "sofheader.h"

#include <string.h>
#include <stdarg.h>


/*
This function has to return a 'list/array' of filenames
*/
bool ListDirectoryContents(const char *sDir, char *** out_list,int *out_length)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char sPath[2048];

    *out_length = 0;

    //Specify a file mask. *.* = We want everything!
    sprintf(sPath, "%s\\*.*", sDir);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", sDir);
        return false;
    }

    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories.
        if(strcmp(fdFile.cFileName, ".") != 0
                && strcmp(fdFile.cFileName, "..") != 0)
        {
            //Build up our file path using the passed in
            //  [sDir] and the file/foldername we just found:
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);

            //Is the entity a File or Folder?
            if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("Directory: %s\n", sPath);
                // ListDirectoryContents(sPath); //Recursion, I love it!
            }
            else{
            	// address of text
            	char * filepath = malloc( strlen(sPath) + 1);
            	strcpy(filepath,sPath);
            	// address of addresses of text :: length starts at 0
            	*out_list = my_realloc(*out_list, (*out_length + 1) * sizeof(char*));

            	// orig_Com_Printf("File1: %s\n", sPath);
                // orig_Com_Printf("File2: %s\n", filepath);
                
            	// sets the address of addresses of text ( array )
            	*(*out_list+*out_length) = filepath;
            	// orig_Com_Printf("File3: %s\n", *(out_list+*out_length));
            	(*out_length)++;
                
            }
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.

    FindClose(hFind); //Always, Always, clean things up!

    return true;
}



int SP_ReferenceToID(const char * ref_string)
{
	// begin list
	void * begin = *(unsigned int*)0x20390DB4;
	void * iter = *(unsigned int*)begin;
	int count = 0;
	while ( iter != begin ) {
		count++;
		// ecx=i->second
		// orig_Com_Printf("Execution : %i\n",count);
		int out = orig_SPSP_FindStringID(*(unsigned int*)(iter+0x10),ref_string);
		if ( out != -1 ) {
			// orig_Com_Printf("answer1 is : %i\n",out);
			// orig_Com_Printf("answer2 is : %i\n",*(unsigned char*)(iter+0xC));
			return (*(unsigned char*)(iter+0xC) << 8) | out;
		} else {
			orig_SP_ListByIDNextEnd(&iter);
			if ( iter == begin ) {
				// orig_Com_Printf("reached the end\n");
				return -1;
			}
		}
	}
}

int changesize(FILE *fp, __int64 size)
{
    int filedes = _fileno(fp);
    return _chsize_s(filedes, size);
}

void *my_realloc(void * buffer,int size)
{
	// paranoid of leaks .. lol
	void * tmp = realloc(buffer,size);
	if ( tmp == NULL ) {
		orig_Com_Error(ERR_FATAL,"realloc failed\n");
	}
	return tmp;
}


edict_t *get_ent_from_player_slot(unsigned int slot)
{
	if ( slot > 31 ) return NULL;
	// method1
	// void * gclient = (void*)((*(unsigned int*)CLIENT_BASE) + ( slot * SIZE_OF_CLIENT));
	// if ( !gclient ) {
	// 	return NULL;
	// }
	// edict_t * ent = *(edict_t**)(gclient + CLIENT_ENT);
	// if (!ent) return NULL;
	// return ent;

	// method2

	return *(unsigned int*)EDICT_BASE + (slot+1)*SIZE_OF_EDICT;
}

// NB. could do a faster method like access ent->num :P lol
int get_player_slot_from_ent(edict_t * ent)
{

	unsigned int difference = (unsigned int)ent- *(unsigned int*)EDICT_BASE;
	// orig_Com_Printf("%08X\n%08X\n",ent,*(unsigned int*)EDICT_BASE);
	// orig_Com_Printf("difference : %08X\nmod : %08X\n",difference,difference%SIZE_OF_EDICT);

	return (!(difference % SIZE_OF_EDICT) && ent)?difference/SIZE_OF_EDICT-1:-1;
}

int replacechar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}


void writeCvarAsVector(vec3_t inarray,char * outcvar) {
	char tmp[64];

	sprintf(tmp,"%s%s",outcvar,"_1");
	cvar_t *cvar_x = orig_Cvar_Get(tmp,"",0,NULL);
	setCvarFloat(cvar_x,inarray[0]);

	sprintf(tmp,"%s%s",outcvar,"_2");
	cvar_t * cvar_y = orig_Cvar_Get(tmp,"",0,NULL);
	setCvarFloat(cvar_y,inarray[1]);

	sprintf(tmp,"%s%s",outcvar,"_3");
	cvar_t * cvar_z = orig_Cvar_Get(tmp,"",0,NULL);
	setCvarFloat(cvar_z,inarray[2]);
}

void readCvarAsVector(char *vectorname,vec3_t outarray)
{
	char tmp[64];

	sprintf(tmp,"%s%s",vectorname,"_1");
	cvar_t * in_x = findCvar(tmp);

	sprintf(tmp,"%s%s",vectorname,"_2");
	cvar_t * in_y = findCvar(tmp);

	sprintf(tmp,"%s%s",vectorname,"_3");
	cvar_t * in_z = findCvar(tmp);

	if ( !in_x || !in_y || !in_z ) {
		orig_Com_Error(ERR_FATAL,"sofree script error: supplied vector to function corrupt/non-existant _1 _2 _3\n");
		return false;
	} else {
		outarray[0] = in_x->value;
		outarray[1] = in_y->value;
		outarray[2] = in_z->value;
		return true;
	}
}


cvar_t * findCvar(char * cvarname)
{
	cvar_t	*var;
	cvar_t * cvar_vars = *(unsigned int*)0x2024B1D8;
	
	for (var=cvar_vars ; var ; var=var->next)
		if (!strcmp (cvarname, var->name))
			return var;
	return NULL;
}

void setCvarUnsignedInt(cvar_t * which,unsigned int val){
	which->modified = true;
	orig_Z_Free(which->string);
	char intstring[64];
	which->value = (float)val;
	sprintf(intstring,"%u",val);
	which->string = orig_CopyString(intstring);
}


void setCvarInt(cvar_t * which,int val){
	which->modified = true;
	orig_Z_Free(which->string);
	char intstring[64];
	which->value = (float)val;
	sprintf(intstring,"%d",val);
	which->string = orig_CopyString(intstring);
}

void setCvarByte(cvar_t * which, unsigned char val) {
	which->modified = true;
	orig_Z_Free(which->string);
	char bytestring[64];
	sprintf(bytestring,"%hhu",val);
	which->value = atof(bytestring);
	which->string = orig_CopyString(bytestring);
}


void setCvarFloat(cvar_t * which, float val) {

	which->modified = true;
	orig_Z_Free(which->string);
	char floatstring[64];
	sprintf(floatstring,"%f",val);
	which->string = orig_CopyString(floatstring);
	which->value = val;
}

void setCvarString(cvar_t * which, char * newstr) {

	which->modified = true;
	orig_Z_Free(which->string);
	
	
	which->string = orig_CopyString(newstr);
	which->value = atof(which->string);
}



sound_overrides_t * getFreeLinkedListSlot_Overrides( sound_overrides_t ** linkedList, int * num,int itemSize)
{
	sound_overrides_t * p = *linkedList;
	if ( *num > 0 ) {
		while ( p->next != NULL )
		{
			p = p->next;
		}
		p->next = malloc(itemSize);
		p = p->next;
	} else
	{
		*linkedList = malloc(itemSize);
		p = *linkedList;
	}
	return p;
}

detour_list_t * getFreeLinkedListSlot_Detours(detour_list_t ** linkedList, int * num,int itemSize)
{
	detour_list_t * p = *linkedList;
	if ( *num > 0 ) {
		while ( p->next != NULL )
		{
			p = p->next;
		}
		p->next = malloc(itemSize);
		p = p->next;
	} else
	{
		*linkedList = malloc(itemSize);
		p = *linkedList;
	}
	return p;
}

script_list_t * getFreeLinkedListSlot_Scripts(script_list_t ** linkedList, int * num,int itemSize)
{
	script_list_t * p = *linkedList;
	if ( *num > 0 ) {
		while ( p->next != NULL )
		{
			p = p->next;
		}
		// orig_Com_Printf("Why do i crash?\n");
		p->next = malloc(itemSize);
		p = p->next;
		// orig_Com_Printf("Why do i crash2?\n");
	} else
	{
		// orig_Com_Printf("Why do i crash3?\n");
		*linkedList = malloc(itemSize);
		p = *linkedList;
	}
	// orig_Com_Printf("Why do i crash4?\n");
	return p;
}

void createConsoleLine(char * fmt,char **inner,char **outer,int length, va_list vl)
{
	// inner starts after a delimitter
	//so its processing the shit behind/preceeding the delimitter

	// orig_Com_Printf("format is : %s\n",fmt);

	

	char ac_line[256];
	strcpy(ac_line,"sp_sc_func_exec ");
	// set p end of just copied:/
	char * p=ac_line+16;
	// append start till len-1
	strncpy(p,*inner,length-1);
	// put a null char lol
	p[length-1]='\0';

	char args[256];
	//targ,attacker,inflictor,targ_num,attacker_num,inflictor_num,mod,damage
	// attach arguments
	
	vsprintf(args,fmt,vl);
	
	strcat(ac_line,args);
	// stuff into console
	// orig_Com_Printf(ac_line);
	orig_Cbuf_AddText(ac_line);
	// orig_Cmd_ExecuteString(ac_line);


	// set the inner_counter to point to this
	*inner = *outer+1;
}
//char* targ,char * attacker, char* inflictor,int targ_num,int attacker_num,int inflictor_num, int mod, int damage
//char* targ,char * attacker, char* inflictor,int targ_num,int attacker_num,int inflictor_num, int mod, int damage
void makeTheStringElips(char * fmt,cvar_t *readcvar, ...)
{
	
	char * readstring = readcvar->string;
	va_list args;
	va_start(args,readstring);
	// va_list copy;
	// va_copy(copy,args)
	// va_end(copy)
	char * outer_pointer = readstring;
	char * inner_pointer = readstring;
	int count = 0;
	
	// if the cvar has content
	if ( strlen(readstring) > 0 )
	{
		// infinite loop
		while ( 1 )
		{
			count++;
			if ( *outer_pointer == ',') {
				
				createConsoleLine(fmt,(char**)&inner_pointer,(char**)&outer_pointer,count,args);
				
			} else if ( *outer_pointer == '\0' )
			{
				
				createConsoleLine(fmt,(char**)&inner_pointer,(char**)&outer_pointer,count,args);
				
				break;
			}
			// move across
			outer_pointer++;
		}	
		
	}
	va_end(args);
}

void makeTheStringVaList(char * fmt,char * readstring, va_list vl)
{
	
	char * outer_pointer = readstring;
	char * inner_pointer = readstring;
	int count = 0;
	
	// if the cvar has content
	if ( strlen(readstring) > 0 )
	{
		// infinite loop
		while ( 1 )
		{
			count++;
			if ( *outer_pointer == ',') {
				
				createConsoleLine(fmt,(char**)&inner_pointer,(char**)&outer_pointer,count,vl);
				
			} else if ( *outer_pointer == '\0' )
			{
				
				createConsoleLine(fmt,(char**)&inner_pointer,(char**)&outer_pointer,count,vl);
				
				break;
			}
			// move across
			outer_pointer++;
		}	
		
	}

}

void debug_drawbox(edict_t* self,float *vOrigin, float *vMins, float *vMaxs, int nColor , int exceptWho)
{
	vec3_t vO;
	vec3_t mns, mxs;
	if (self)
	{
		VectorCopy((void*)self+EDICT_MINS, mns);
		VectorCopy((void*)self+EDICT_MAXS, mxs);
	}
	else
	{
		VectorCopy(vMins, mns);
		VectorCopy(vMaxs, mxs);
	}
	
	if (self)
	{
		VectorCopy((void*)self+EDICT_S_ORIGIN, vO);
	}
	else
	{
		VectorCopy(vOrigin, vO);
	}
	paletteRGBA_t p;
	p.a = 255;
	float colors[] = {
		255, 0, 0, //0
		255, 0, 127, //1
		255, 0, 255, //2
		127, 0, 255, //3
		0, 0, 255, //4
		0, 127, 255, //5
		0, 255, 255, //6
		0, 255, 127, //7
		0, 255, 0, //8
		127, 255, 0, //9
		255, 255, 0, //10
		255, 127, 0 //11
	};

	p.r = colors[nColor*3];
	p.g = colors[nColor*3+1];
	p.b = colors[nColor*3+2];
	
	
	// netchan.message = reliable
	// client.datagram = unreliable
	// default = unreliable

	/*
	MULTICAST_ALL,
	MULTICAST_PHS,
	MULTICAST_PVS,
	MULTICAST_ALL_R,
	MULTICAST_PHS_R,
	MULTICAST_PVS_R
	*/

	orig_MSG_WriteByte(sv_multicast,svc_temp_entity);
	orig_MSG_WriteByte(sv_multicast,TE_TESTBOX);
	vec3_t V1,V2;
	VectorAdd(vO,mns,V1);
	orig_MSG_WritePos(sv_multicast,V1);
	VectorAdd(vO,mxs,V2);
	orig_MSG_WritePos(sv_multicast,V2);
	orig_MSG_WriteByte(sv_multicast,p.r);
	orig_MSG_WriteByte(sv_multicast,p.g);
	orig_MSG_WriteByte(sv_multicast,p.b);

	// orig_MSG_WriteByte(sv_multicast,svc_temp_entity);
	// orig_MSG_WriteByte(sv_multicast,TE_NEURALPULSE);
	// orig_MSG_WritePos(sv_multicast,vO);

	// 
	my_SV_Multicast(vO, MULTICAST_PVS , exceptWho);
	
	
}

/*void drawBoxesOnEnts(void)
{
	edict_t * trig = NULL;
	
	trig = orig_G_Find(0,EDICT_CLASSNAME,"trigger_",8);
	while ( trig ){
		// green
		//orig_Com_Printf("Found trigger %i!\n",counter);
		debug_drawbox(trig,NULL,NULL,NULL,8);
		trig = orig_G_Find(trig,EDICT_CLASSNAME,"trigger_",8);
	}
	trig = orig_G_Find(0,EDICT_CLASSNAME,"func_",5);
	while ( trig ){
		// red
		//orig_Com_Printf("Found trigger %i!\n",counter);
		debug_drawbox(trig,NULL,NULL,NULL,0);
		trig = orig_G_Find(trig,EDICT_CLASSNAME,"func_",5);
	}

	trig = orig_G_Find(0,EDICT_CLASSNAME,"player",6);
	while ( trig ){
		// blue
		//orig_Com_Printf("Found trigger %i!\n",counter);
		// if ( trig != ent ) {
			debug_drawbox(trig,trig->s.origin,NULL,NULL,4,get_player_slot_from_ent(trig) + 1);
		// }
		trig = orig_G_Find(trig,EDICT_CLASSNAME,"player",6);
	}

	trig = orig_G_Find(0,EDICT_CLASSNAME,"environ_",8);
	while ( trig ){
		// notsure
		//orig_Com_Printf("Found trigger %i!\n",counter);
		
		debug_drawbox(trig,NULL,NULL,NULL,2);
		
		trig = orig_G_Find(trig,EDICT_CLASSNAME,"environ_",8);
	}

	trig = orig_G_Find(0,EDICT_CLASSNAME,"item_",5);
	while ( trig ){
		// notsure
		//orig_Com_Printf("Found trigger %i!\n",counter);
		
		debug_drawbox(trig,NULL,NULL,NULL,6);
		
		trig = orig_G_Find(trig,EDICT_CLASSNAME,"item_",5);
	}
	trig = orig_G_Find(0,EDICT_CLASSNAME,"misc_",5);
	while ( trig ){
		// notsure
		//orig_Com_Printf("Found trigger %i!\n",counter);
		
		debug_drawbox(trig,NULL,NULL,NULL,10);
		
		trig = orig_G_Find(trig,EDICT_CLASSNAME,"misc_",5);
	}

}
*/

void drawBoxesOnEnts(int round,int mode)
{
	void (*debugdraw)(edict_t* self,float *vOrigin, float *vMins, float *vMaxs, int nColor, int exceptWho);
	if ( mode == 1 )
		debugdraw = debug_drawbox2;
	else if ( mode == 2 )
		debugdraw = debug_drawbox3;
	unsigned int g_edicts = stget(0x5015CCA0,0);
	unsigned int num_edicts = stget(0x5015C938,0);
	

	if ( round == 5 ) {
		// remaining
		g_edicts = g_edicts + 0x464* (num_edicts / 5)*4;
		num_edicts = (num_edicts - (num_edicts / 5)*4);
	}
	if ( round == 4) {
		// remaining
		g_edicts = g_edicts + 0x464* (num_edicts / 5)*3;
		num_edicts = num_edicts / 5;
	} else
	if ( round == 3) {
		// remaining
		g_edicts = g_edicts + 0x464* (num_edicts / 5)*2;
		num_edicts = num_edicts / 5;
	} else
	if ( round == 2) {
		// remaining
		g_edicts = g_edicts + 0x464* (num_edicts / 5);
		num_edicts = num_edicts / 5;
	} else
	if ( round == 1  ) {
		// naturally truncates towards 0
		num_edicts = num_edicts / 5;
	} 
	int withoutClassname = 0;
	int unrecognisedClassname = 0;
	int butHaveOrigin = 0;
	// orig_Com_Printf("g_edicts is %i\n",g_edicts);
	for ( int i = g_edicts;i < (g_edicts + 0x464*num_edicts);i = (unsigned int)i + 0x464 ) {
		edict_t * ent = i;
		if ( !ent->inuse || ( !ent->s.origin[0] && !ent->s.origin[1] && !ent->s.origin[2]  && !ent->mins[0] && !ent->mins[1] && !ent->mins[2] && !ent->maxs[0] && !ent->maxs[1] && !ent->maxs[2])  ) continue;
		if ( ent->classname ) {
			// orig_Com_Printf("classname is %s\n",ent->classname);
			if ( !strncmp(ent->classname,"trigger_",8) ) {
				// orig_Com_Printf( "%f %f %f\n",ent->s.origin[0],ent->s.origin[1],ent->s.origin[2]); 	
				debugdraw(ent,NULL,NULL,NULL,8,0);
			} else
			if ( !strncmp(ent->classname,"func_",5) ) {
				debugdraw(ent,NULL,NULL,NULL,0,0);
			} else
			if ( !strncmp(ent->classname,"player",6) ) {
				debugdraw(ent,ent->s.origin,NULL,NULL,4,get_player_slot_from_ent(ent) + 1);
			} else
			if ( !strncmp(ent->classname,"environ_",8) ) {
				debugdraw(ent,NULL,NULL,NULL,2,0);
			} else
			if ( !strncmp(ent->classname,"item_",5) ) {
				debugdraw(ent,NULL,NULL,NULL,6,0);
			} else
			if ( !strncmp(ent->classname,"misc_",5) ) {
				debugdraw(ent,NULL,NULL,NULL,10,0);
			} else 
			{
				// if ( ent->s.origin[0] || ent->s.origin[1] || ent->s.origin[2] ) {
				// 	butHaveOrigin++;
				// }
				unrecognisedClassname++;
				// orig_Com_Printf("unrecognised : %s\n",ent->classname);
				// if ( !strncmp(ent->classname,"noclass",7) ) {
				// 	debug_drawbox2(ent,NULL,NULL,NULL,1);
				// } 
				// else debug_drawbox2(ent,NULL,NULL,NULL,1);
				void * vent = ent;
				void * owner = stget(vent,EDICT_OWNER);
				if (owner) {
					int slot = get_player_slot_from_ent(owner);
					if ( slot != -1 && slot < maxclients->value ) {
						debugdraw(ent,NULL,NULL,NULL,1,slot + 1);
					}
				} else {
					debugdraw(ent,NULL,NULL,NULL,1,0);
				}
			}
		}
		else
		{
			// if ( ent->s.origin[0] || ent->s.origin[1] || ent->s.origin[2] ) {
			// 	butHaveOrigin++;
			// }
			withoutClassname++;
			void * vent = ent;
			void * owner = stget(vent,EDICT_OWNER);
			if (owner) {
				int slot = get_player_slot_from_ent(owner);
				if ( slot != -1 && slot < maxclients->value ) {
					debugdraw(ent,NULL,NULL,NULL,1,slot + 1);
				}
			} else {
				debugdraw(ent,NULL,NULL,NULL,1,0);
			}
		}

	}
	// orig_Com_Printf("withoutClass = %i unrecog = %i\n",withoutClassname,unrecognisedClassname);
	// orig_Com_Printf("%i of the %i unknown have origin\n",butHaveOrigin,withoutClassname+unrecognisedClassname);
}

/*
PVS vs PHS
PHS is visible of visible ( bigger )
PVS is visible ( smaller )
https://www.phatcode.net/res/224/files/html/ch70/70-02.html


22 * 12 ~256 lazer limit !!! hmm
*/
void laserLine(vec3_t from, vec3_t to)
{

	// endpos
	

	// flags
	*(int*)0x5015C51C = *(int*)0x5015C51C | EFF_POS2;
	// set global pos2 values
	// call CFXSender:Exec
	*(float*)0x5015C524 = from[0];
	*(float*)0x5015C528 = from[1];
	*(float*)0x5015C52C = from[2];


	//startpos

	int index = orig_SV_FindIndex("environ/tripbeam", CS_EFFECTS, MAX_EFPACKS, 0,"effect");
	static (__thiscall *fxRunner_exec)(void* self,int effectID, vec3_t pos, multicast_t castType, edict_t *ignoreClient) = 0x500852E0;
	// fxRunner.exec(index, vorigin);
	fxRunner_exec((void*)0x5015C518,index,to,MULTICAST_PVS,0);
}


void debug_drawbox2(edict_t* self,float *vOrigin, float *vMins, float *vMaxs, int nColor , int exceptWho)
{


	vec3_t vO;
	vec3_t mns, mxs;
	if (self)
	{
		VectorCopy(self->mins, mns);
		VectorCopy(self->maxs, mxs);
	}
	else
	{
		VectorCopy(vMins, mns);
		VectorCopy(vMaxs, mxs);
	}

	// orig_Com_Printf("mins is %f %f %f\n",self->mins[0],self->mins[1],self->mins[2]);
	// orig_Com_Printf("maxs is %f %f %f\n",self->maxs[0],self->maxs[1],self->maxs[2]);
	// corpse stuff override
	//	mns[0] = -8;
	//	mns[1] = -8;
	//	mxs[0] = 8;
	//	mxs[1] = 8;
	//	mxs[2] = 8;

	vec3_t corners[] = {
		{mns[0], mns[1], mns[2]},
		{mns[0], mns[1], mxs[2]},
		{mns[0], mxs[1], mns[2]},
		{mns[0], mxs[1], mxs[2]},
		{mxs[0], mns[1], mns[2]},
		{mxs[0], mns[1], mxs[2]},
		{mxs[0], mxs[1], mns[2]},
		{mxs[0], mxs[1], mxs[2]}
	};

	if (self)
	{
		VectorCopy(self->s.origin, vO);
	}
	else
	{
		VectorCopy(vOrigin, vO);
	}
	// orig_Com_Printf("v0 is %f %f %f\n",vO[0],vO[1],vO[2]);
	paletteRGBA_t p;
	float colors[] = {
		255, 0, 0, //0
		255, 0, 127, //1
		255, 0, 255, //2
		127, 0, 255, //3
		0, 0, 255, //4
		0, 127, 255, //5
		0, 255, 255, //6
		0, 255, 127, //7
		0, 255, 0, //8
		127, 255, 0, //9
		255, 255, 0, //10
		255, 127, 0 //11
	};

	
	int lines[] = {
		0,	1,
		0,	2,
		0,	4,
		7,	6,
		7,	5,
		7,	3,
		2,	3,
		2,	6,
		6,	4,
		4,	5,
		5,	1,
		1,	3
	};
	vec3_t c1, c2, mid;
	int i = 0;
	p.a = 255;

	p.r = colors[nColor*3];
	p.g = colors[nColor*3+1];
	p.b = colors[nColor*3+2];
	// for (i = 0; i < 12; i++)
	// {

		VectorAdd(vO, corners[0], c1);
		VectorAdd(vO, corners[7], c2);
		// FX_MakeLine(c1, c2, p); // need a better one than this

		orig_MSG_WriteByte (sv_multicast, svc_temp_entity);//1
		orig_MSG_WriteByte (sv_multicast, TE_TEST_LINE);//1
		orig_MSG_WritePos(sv_multicast,c1);//6
		orig_MSG_WritePos(sv_multicast,c2);//6
		orig_MSG_WriteLong(sv_multicast,p.c);//4
		// lifetime
		orig_MSG_WriteLong(sv_multicast,1);//4

		// orig_MSG_WriteByte(sv_multicast,svc_temp_entity);
		// orig_MSG_WriteByte(sv_multicast,TE_NEURALPULSE);
		// orig_MSG_WritePos(sv_multicast,vO);

		

		// laserLine(c1,c2);
	// }

		VectorAdd(vO, corners[3], c1);
		VectorAdd(vO, corners[4], c2);
		// FX_MakeLine(c1, c2, p); // need a better one than this

		orig_MSG_WriteByte (sv_multicast, svc_temp_entity);//1
		orig_MSG_WriteByte (sv_multicast, TE_TEST_LINE);//1
		orig_MSG_WritePos(sv_multicast,c1);//6
		orig_MSG_WritePos(sv_multicast,c2);//6
		orig_MSG_WriteLong(sv_multicast,p.c);//4
		// lifetime
		orig_MSG_WriteLong(sv_multicast,1);//4


		VectorAdd(vO, corners[2], c1);
		VectorAdd(vO, corners[5], c2);
		// FX_MakeLine(c1, c2, p); // need a better one than this

		orig_MSG_WriteByte (sv_multicast, svc_temp_entity);//1
		orig_MSG_WriteByte (sv_multicast, TE_TEST_LINE);//1
		orig_MSG_WritePos(sv_multicast,c1);//6
		orig_MSG_WritePos(sv_multicast,c2);//6
		orig_MSG_WriteLong(sv_multicast,p.c);//4
		// lifetime
		orig_MSG_WriteLong(sv_multicast,1);//4


		VectorAdd(vO, corners[1], c1);
		VectorAdd(vO, corners[6], c2);
		// FX_MakeLine(c1, c2, p); // need a better one than this

		orig_MSG_WriteByte (sv_multicast, svc_temp_entity);//1
		orig_MSG_WriteByte (sv_multicast, TE_TEST_LINE);//1
		orig_MSG_WritePos(sv_multicast,c1);//6
		orig_MSG_WritePos(sv_multicast,c2);//6
		orig_MSG_WriteLong(sv_multicast,p.c);//4
		// lifetime
		orig_MSG_WriteLong(sv_multicast,1);//4

		VectorSubtract(c2,c1,mid);
		VectorScale(mid,0.5,mid);
		VectorAdd(c1,mid,mid);

		my_SV_Multicast(mid, MULTICAST_PVS , exceptWho);
}

void debug_drawbox3(edict_t* self,float *vOrigin, float *vMins, float *vMaxs, int nColor , int exceptWho)
{


	vec3_t vO;
	vec3_t mns, mxs;
	if (self)
	{
		VectorCopy(self->mins, mns);
		VectorCopy(self->maxs, mxs);
	}
	else
	{
		VectorCopy(vMins, mns);
		VectorCopy(vMaxs, mxs);
	}

	// orig_Com_Printf("mins is %f %f %f\n",self->mins[0],self->mins[1],self->mins[2]);
	// orig_Com_Printf("maxs is %f %f %f\n",self->maxs[0],self->maxs[1],self->maxs[2]);
	// corpse stuff override
	//	mns[0] = -8;
	//	mns[1] = -8;
	//	mxs[0] = 8;
	//	mxs[1] = 8;
	//	mxs[2] = 8;

	vec3_t corners[] = {
		{mns[0], mns[1], mns[2]},
		{mns[0], mns[1], mxs[2]},
		{mns[0], mxs[1], mns[2]},
		{mns[0], mxs[1], mxs[2]},
		{mxs[0], mns[1], mns[2]},
		{mxs[0], mns[1], mxs[2]},
		{mxs[0], mxs[1], mns[2]},
		{mxs[0], mxs[1], mxs[2]}
	};

	if (self)
	{
		VectorCopy(self->s.origin, vO);
	}
	else
	{
		VectorCopy(vOrigin, vO);
	}
	// orig_Com_Printf("v0 is %f %f %f\n",vO[0],vO[1],vO[2]);
	paletteRGBA_t p;
	float colors[] = {
		255, 0, 0, //0
		255, 0, 127, //1
		255, 0, 255, //2
		127, 0, 255, //3
		0, 0, 255, //4
		0, 127, 255, //5
		0, 255, 255, //6
		0, 255, 127, //7
		0, 255, 0, //8
		127, 255, 0, //9
		255, 255, 0, //10
		255, 127, 0 //11
	};

	
	int lines[] = {
		0,	1,
		0,	2,
		0,	4,
		7,	6,
		7,	5,
		7,	3,
		2,	3,
		2,	6,
		6,	4,
		4,	5,
		5,	1,
		1,	3
	};
	vec3_t c1, c2, mid;
	int i = 0;
	p.a = 255;

	p.r = colors[nColor*3];
	p.g = colors[nColor*3+1];
	p.b = colors[nColor*3+2];
	for (i = 0; i < 12; i++)
	{

		VectorAdd(vO, corners[lines[i*2]], c1);
		VectorAdd(vO, corners[lines[i*2+1]], c2);
		

		orig_MSG_WriteByte (sv_multicast, svc_temp_entity);//1
		orig_MSG_WriteByte (sv_multicast, TE_TEST_LINE);//1
		orig_MSG_WritePos(sv_multicast,c1);//6
		orig_MSG_WritePos(sv_multicast,c2);//6
		orig_MSG_WriteLong(sv_multicast,p.c);//4
		// lifetime
		orig_MSG_WriteLong(sv_multicast,1);//4
	}
	VectorAdd(vO, corners[0], c1);
	VectorAdd(vO, corners[7], c2);
	VectorSubtract(c2,c1,mid);
	VectorScale(mid,0.5,mid);
	VectorAdd(c1,mid,mid);
	my_SV_Multicast(mid, MULTICAST_PVS , exceptWho);
}


#include "geometry.h"
#include <cstdlib>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

class Ray
{
public:
    Ray(const Vec3f &orig, const Vec3f &dir) : orig(orig), dir(dir)
    {
        invdir = 1 / dir;
        sign[0] = (invdir.x < 0);
        sign[1] = (invdir.y < 0);
        sign[2] = (invdir.z < 0);
    }
    Vec3f orig, dir; // ray orig and dir
    Vec3f invdir;
    int sign[3];
};

class AABBox
{
public:
    AABBox(const Vec3f &b0, const Vec3f &b1) { bounds[0] = b0, bounds[1] = b1; }
    bool intersect(const Ray &r, float &t) const
    {
        float tmin, tmax, tymin, tymax, tzmin, tzmax;

        tmin = (bounds[r.sign[0]].x - r.orig.x) * r.invdir.x;
        tmax = (bounds[1-r.sign[0]].x - r.orig.x) * r.invdir.x;
        tymin = (bounds[r.sign[1]].y - r.orig.y) * r.invdir.y;
        tymax = (bounds[1-r.sign[1]].y - r.orig.y) * r.invdir.y;

        if ((tmin > tymax) || (tymin > tmax))
            return false;

        if (tymin > tmin)
        tmin = tymin;
        if (tymax < tmax)
        tmax = tymax;

        tzmin = (bounds[r.sign[2]].z - r.orig.z) * r.invdir.z;
        tzmax = (bounds[1-r.sign[2]].z - r.orig.z) * r.invdir.z;

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        if (tzmin > tmin)
        tmin = tzmin;
        if (tzmax < tmax)
        tmax = tzmax;

        t = tmin;

        if (t < 0) {
            t = tmax;
            if (t < 0) return false;
        }

        return true;
    }
    Vec3f bounds[2];
};


/*
Ray ray(Vec3f(0), randDir);
        float t;
        if (box.intersect(ray, t)) {
            Vec3f Phit = ray.orig + ray.dir * t;
            std::cerr << ray.orig << " " << Phit << std::endl;
        }

	AABBox box(Vec3f(-1), Vec3f(1));
*/

vec_t VectorNormalize (vec3_t v)
{
	float	length, ilength;

	length = DotProduct(v, v);
	length = sqrt (length);		// FIXME

	if (length)
	{
		ilength = 1/length;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}
		
	return length;

}

vec_t VectorLength(vec3_t v)
{
	float	length;
	
	length = DotProduct(v, v);
	length = sqrt (length);		// FIXME

	return length;
}


void intersect(edict_t * fromPlayer)
{
	unsigned int g_edicts = stget(0x5015CCA0,0);
	unsigned int num_edicts = stget(0x5015C938,0);
	
	for ( int i = g_edicts;i < (g_edicts + 0x464*num_edicts);i = (unsigned int)i + 0x464 ) {
		edict_t * ent = i;
		if ( !ent->inuse || ( !ent->s.origin[0] && !ent->s.origin[1] && !ent->s.origin[2]  && !ent->mins[0] && !ent->mins[1] && !ent->mins[2] && !ent->maxs[0] && !ent->maxs[1] && !ent->maxs[2])  ) continue;
		
		if ( ent == fromPlayer) continue;

		void * vent = ent;
		void * owner = stget(vent,EDICT_OWNER);
		if (owner == fromPlayer) {			
			// dont intersect with own stuff
			continue;
		}

		vec3_t absmins,absmaxs,mid,dir;
		VectorAdd(ent->s.origin, ent->mins, absmins);
		VectorAdd(ent->s.origin, ent->maxs, absmaxs);

		AABBox box(Vec3f(absmins[0],absmins[1],absmins[2]), Vec3f(absmaxs[0],absmaxs[1],absmaxs[2]));

		vec3_t fwd;
		orig_AngleVectors(fromPlayer->client->v_angle,fwd,NULL,NULL);

		Vec3f vDir(fwd[0],fwd[1],fwd[2]);
		float fDuck = 35.0f;
		void * vPlayer = fromPlayer;
		void * vClient = stget(vPlayer,EDICT_GCLIENT);
		unsigned int pm_flags = stget(vClient,0x10);

		if ( pm_flags & PMF_DUCKED ) {
			// orig_Com_Printf("you are crouching\n");
			fDuck = 0.0f;
		}
		Vec3f vOrg(fromPlayer->s.origin[0],fromPlayer->s.origin[1],fromPlayer->s.origin[2] + fDuck);
		Ray ray(vOrg,vDir);
		float t;
		if ( box.intersect(ray,t) ) {
			char text[256];
			if ( ent->classname ) {
				sprintf(text,"say you intersected with %s flags: %i\n",ent->classname,ent->flags);
			} else {
				sprintf(text,"say intersected with unknown classname\n");
			}
			orig_Cbuf_AddText(text);
			return;
		}
	}
}

/*
table name is often passed from lua so.
access from lua stack
*/
void luaReadTableAsVector(int tableStackPos, float* vecOut) {
	lua_pushstring(L,"x");
	lua_gettable(L,tableStackPos);
	// top of stack is value after gettable called.
	vecOut[0]=lua_tonumber(L,-1);
	lua_pop(L,1);
	
	lua_pushstring(L,"z");
	lua_gettable(L,tableStackPos);
	vecOut[1]=lua_tonumber(L,-1);
	lua_pop(L,1);

	lua_pushstring(L,"y");
	lua_gettable(L,tableStackPos);
	vecOut[2]=lua_tonumber(L,-1);
	lua_pop(L,1);

	// vecOut now stores table values.
}



void luaPushVectorAsTable(vec3_t inVec) {
	lua_newtable(L);

	lua_pushstring(L,"x");
	lua_pushnumber(L,inVec[0]);
	lua_settable(L,-3); //attach to table
	
	lua_pushstring(L,"y");
	lua_pushnumber(L,inVec[2]);
	lua_settable(L,-3);
	
	lua_pushstring(L,"z");
	lua_pushnumber(L,inVec[1]);
	lua_settable(L,-3);

	//table is still on stack
}

/*

int args = lua_gettop(L);
assert(args == 1 && "invalid arg count");

*/