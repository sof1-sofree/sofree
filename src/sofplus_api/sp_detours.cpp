#include <windows.h>

#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include <stdio.h>
#include <stdlib.h>



enum {
	CALL_CDECL,
	CALL_STDCALL,
	CALL_THISCALL
};


detour_list_t detours_one;
detour_list_t detours_two;
detour_list_t detours_three;
detour_list_t detours_four;
detour_list_t detours_five;
detour_list_t detours_six;
detour_list_t detours_seven;
detour_list_t detours_eight;
detour_list_t detours_nine;
detour_list_t detours_ten;




void * sp_det_check_cc(char * call)
{
	void * pointer_to = NULL;
	if ( !strcmp(call,"cdecl" ) ) {
		pointer_to = &my_cdecl_one;
	} else if ( !strcmp(call,"stdcall" ) ) {
		pointer_to = &my_stdcall_one;
	} else if ( !strcmp(call,"thiscall" ) ) {
		pointer_to = &my_thiscall_one;
	}
	return pointer_to;
}

void sp_det_CreateDetour(char * func_name, int num_args, int address, char * call_conven, int safebytes,bool after,void * sofplus_special)
{
	
	detour_list_t * yoMommasDetour;
	void * new_orig = NULL;
	void * myfunc = NULL;
	switch(num_args) {
		case 1:
			
			yoMommasDetour = &detours_one;
			myfunc = sp_det_check_cc(call_conven);
			//myfunc = &my_thiscall_one;
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 2:
			
			yoMommasDetour = &detours_two;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);

		break;
		case 3:
			
			yoMommasDetour = &detours_three;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 4:
			
			yoMommasDetour = &detours_four;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 5:
			
			yoMommasDetour = &detours_five;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 6:
			
			yoMommasDetour = &detours_six;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 7:
			
			yoMommasDetour = &detours_seven;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 8:
			
			yoMommasDetour = &detours_eight;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 9:
			
			yoMommasDetour = &detours_nine;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;
		case 10:
			
			yoMommasDetour = &detours_ten;
			myfunc = sp_det_check_cc(call_conven);
			new_orig = DetourCreate(address , myfunc ,DETOUR_TYPE_JMP,safebytes);
		break;

		default:
		break;
	}

	// detour_list_t * p = getFreeLinkedListSlot_Detours(yoMommasDetour,num_per_type,sizeof(detour_list_s));
	detour_list_t	*z = malloc(sizeof(detour_list_t));

	z->next = (*yoMommasDetour).next;
	z->prev = yoMommasDetour;
	(*yoMommasDetour).next->prev = z;
	(*yoMommasDetour).next = z;

	z->next = NULL;
	strcpy(z->funcname,func_name);
	z->orig_call = address;
	z->relocated_call = new_orig;
	strcpy(z->calling_convention,call_conven);
	z->after = after;
	z->sofplus = sofplus_special;
}



void runSoFPlusFuncs(char * cvarname,char * fmt,va_list vl)
{
	
	// call the sofplus functions for this shitstain name
	char fullcvarname[64];
	strcpy(fullcvarname,"_sf_sv_on_");
	strcat(fullcvarname,cvarname);
	cvar_t * thecvar = findCvar(fullcvarname);
	if ( thecvar ) {
		//this function cvar exists thus : go ahead call the sofplus code
		makeTheStringVaList(fmt,thecvar->string, vl);
		
	}
}


int __cdecl stable_func_body(int cc,int howmany,char * fmt,...)
{
	unsigned char * callCode = __builtin_return_address(1);
	orig_Com_Printf("Yuck1: %08X\n",callCode);
	// orig_Com_Printf("Yuck2: %08X\n",__builtin_return_address(1));

	unsigned char * recognise = *(unsigned int*)(callCode-4);
	orig_Com_Printf("Yuck3: %08X\n",recognise);
	unsigned char * targetCall = (int)callCode + recognise;



	va_list hehe;
	// va_list hehe2;
	va_start(hehe,fmt);
	// va_copy(hehe2,hehe);
	
	int arguments[10];
	for ( int i = 0 ; i < howmany;i++ ) {
		// arguments[i] = malloc(4);
		arguments[i] = va_arg(hehe,int);
		// should probably use va_copy here :D
	}
	
	void * original = NULL;
	detour_list_t	*z, *next;
	for (z=detours_one.next ; z != &detours_one ; z=next)
	{
		next = z->next;
		
		orig_Com_Printf("sofplus module is : %08X\n",o_sofplus);
		orig_Com_Printf("Do you recognise : %08X ?\n",callCode);
		orig_Com_Printf("Difference is : %08X\n",(int)callCode-(int)o_sofplus);
		orig_Com_Printf("or maybe do you recognise : %08X ?\n",targetCall);
		int difference = (int)callCode - (int)o_sofplus;
		int difference2 = (int)targetCall - (int)o_sofplus;
		if ( z->orig_call == callCode || z->orig_call == targetCall || (z->sofplus && (difference == z->sofplus || difference2 == z->sofplus )  )) {
			orig_Com_Printf("Yes I do!!!\n");
			original = z->relocated_call;
			break;
		}
		orig_Com_Printf("Iterating linked list\n");
	}
	
	

	if (!original) {
		orig_Com_Printf("I dont recognise anything!!!\n");
		return;
	}
	orig_Com_Printf("original is %08X\n",original);
	orig_Com_Printf("arg1 is %08X\n",arguments[0]);
	if ( !z->after ) runSoFPlusFuncs(z->funcname,fmt,hehe);
	
	switch(howmany) {
		case 1:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_one_type)original)(arguments[0]);
				break;
				case CALL_STDCALL:
					(*(stdcall_one_type)original)(arguments[0]);
				break;
				case CALL_THISCALL:
					(*(thiscall_one_type)original)(NULL,arguments[0]);
				break;
				default:
				break;
			}
			
		break;
		case 2:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_two_type)original)(arguments[0],arguments[1]);
				break;
				case CALL_STDCALL:
					(*(stdcall_two_type)original)(arguments[0],arguments[1]);
				break;
				case CALL_THISCALL:
					(*(thiscall_two_type)original)(NULL,arguments[0],arguments[2]);
				break;
				default:
				break;
			}
		break;
		case 3:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_three_type)original)(arguments[0],arguments[1],arguments[2]);
				break;
				case CALL_STDCALL:
					(*(stdcall_three_type)original)(arguments[0],arguments[1],arguments[2]);
				break;
				case CALL_THISCALL:
					(*(thiscall_three_type)original)(NULL,arguments[0],arguments[1],arguments[2]);
				break;
				default:
				break;
			}
		break;
		case 4:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_four_type)original)(arguments[0],arguments[1],arguments[2],arguments[3]);
				break;
				case CALL_STDCALL:
					(*(stdcall_four_type)original)(arguments[0],arguments[1],arguments[2],arguments[3]);
				break;
				case CALL_THISCALL:
					(*(thiscall_four_type)original)(NULL,arguments[0],arguments[1],arguments[2],arguments[3]);
				break;
				default:
				break;
			}
		break;
		case 5:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_five_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4]);
				break;
				case CALL_STDCALL:
					(*(stdcall_five_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4]);
				break;
				case CALL_THISCALL:
					(*(thiscall_five_type)original)(NULL,arguments[0],arguments[1],arguments[2],arguments[3],arguments[4]);
				break;
				default:
				break;
			}
		break;
		case 6:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_six_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5]);
				break;
				case CALL_STDCALL:
					(*(stdcall_six_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5]);
				break;
				case CALL_THISCALL:
					(*(thiscall_six_type)original)(NULL,arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5]);
				break;
				default:
				break;
			}
		break;
		case 7:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_seven_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6]);
				break;
				case CALL_STDCALL:
					(*(stdcall_seven_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6]);
				break;
				case CALL_THISCALL:
					(*(thiscall_seven_type)original)(NULL,arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6]);
				break;
				default:
				break;
			}
		break;
		case 8:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_eight_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7]);
				break;
				case CALL_STDCALL:
					(*(stdcall_eight_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7]);
				break;
				case CALL_THISCALL:
					(*(thiscall_eight_type)original)(NULL,arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7]);
				break;
				default:
				break;
			}
		break;
		case 9:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_nine_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8]);
				break;
				case CALL_STDCALL:
					(*(stdcall_nine_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8]);
				break;
				case CALL_THISCALL:
					(*(thiscall_nine_type)original)(NULL,arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8]);
				break;
				default:
				break;
			}
		break;
		case 10:
			switch (cc) {
				case CALL_CDECL:
					(*(cdecl_ten_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8],arguments[9]);
				break;
				case CALL_STDCALL:
					(*(stdcall_ten_type)original)(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8],arguments[9]);
				break;
				case CALL_THISCALL:
					(*(thiscall_ten_type)original)(NULL,arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8],arguments[9]);
				break;
				default:
				break;
			}
		break;

		default:
		break;
	}
	//unsigned int ret = original(arguments[0]);
	// if ( p->after ) {
	// 	strcat(fmt+strlen(fmt)-1," %s\n");
	// 	runSoFPlusFuncs(p->funcname,fmt,hehe);
	// }
	// va_end(hehe2);
	// return ret;
	// return 0;

	va_end(hehe);
}

/*---------ONE---------*/
int __cdecl my_cdecl_one (int one)
{
	orig_Com_Printf("arg1ONE is %08X\n",one);
	stable_func_body(CALL_CDECL,1," %08X\n",one);
}
int __stdcall my_stdcall_one (int one)
{
	stable_func_body(CALL_STDCALL,1," %08X\n");
}
int __thiscall my_thiscall_one (int self,int one)
{
	stable_func_body(CALL_THISCALL,1," %08X\n");
}
/*---------TWO---------*/
int __cdecl my_cdecl_two (int one, int two)
{
	stable_func_body(CALL_CDECL,2," %08X %08X\n");
}
int __stdcall my_stdcall_two (int one, int two)
{
	stable_func_body(CALL_STDCALL,2," %08X %08X\n");
}
int __thiscall my_thiscall_two (int self,int one, int two)
{
	stable_func_body(CALL_THISCALL,2," %08X %08X\n");
}
/*---------THREE---------*/
int __cdecl my_cdecl_three (int one, int two, int three)
{
	stable_func_body(CALL_CDECL,3," %08X %08X %08X\n");
}
int __stdcall my_stdcall_three (int one, int two, int three)
{
	stable_func_body(CALL_STDCALL,3," %08X %08X %08X\n");
}
int __thiscall my_thiscall_three (int self,int one, int two, int three)
{
	stable_func_body(CALL_THISCALL,3," %08X %08X %08X\n");
}
/*---------FOUR---------*/
int __cdecl my_cdecl_four (int one, int two, int three, int four)
{
	stable_func_body(CALL_CDECL,4," %08X %08X %08X %08X\n");
}
int __stdcall my_stdcall_four (int one, int two, int three, int four)
{
	stable_func_body(CALL_STDCALL,4," %08X %08X %08X %08X\n");
}
int __thiscall my_thiscall_four (int self,int one, int two, int three, int four)
{
	stable_func_body(CALL_THISCALL,4," %08X %08X %08X %08X\n");
}
/*---------FIVE---------*/
int __cdecl my_cdecl_five (int one, int two, int three, int four, int five)
{
	stable_func_body(CALL_CDECL,5," %08X %08X %08X %08X %08X\n");
}
int __stdcall my_stdcall_five (int one, int two, int three, int four, int five)
{
	stable_func_body(CALL_STDCALL,5," %08X %08X %08X %08X %08X\n");
}
int __thiscall my_thiscall_five (int self,int one, int two, int three, int four, int five)
{
	stable_func_body(CALL_THISCALL,5," %08X %08X %08X %08X %08X\n");
}
/*---------SIX---------*/
int __cdecl my_cdecl_six (int one, int two, int three, int four, int five, int six)
{
	stable_func_body(CALL_CDECL,6," %08X %08X %08X %08X %08X %08X\n");
}
int __stdcall my_stdcall_six (int one, int two, int three, int four, int five, int six)
{
	stable_func_body(CALL_STDCALL,6," %08X %08X %08X %08X %08X %08X\n");
}
int __thiscall my_thiscall_six (int self,int one, int two, int three, int four, int five, int six)
{
	stable_func_body(CALL_THISCALL,6," %08X %08X %08X %08X %08X %08X\n");
}
/*---------SEVEN---------*/
int __cdecl my_cdecl_seven (int one, int two, int three, int four, int five, int six, int seven)
{
	stable_func_body(CALL_CDECL,7," %08X %08X %08X %08X %08X %08X %08X\n");
}
int __stdcall my_stdcall_seven (int one, int two, int three, int four, int five, int six, int seven)
{
	stable_func_body(CALL_STDCALL,7," %08X %08X %08X %08X %08X %08X %08X\n");
}
int __thiscall my_thiscall_seven (int self,int one, int two, int three, int four, int five, int six, int seven)
{
	stable_func_body(CALL_THISCALL,7," %08X %08X %08X %08X %08X %08X %08X\n");
}
/*---------EIGHT---------*/
int __cdecl my_cdecl_eight (int one, int two, int three, int four, int five, int six, int eight)
{
	stable_func_body(CALL_CDECL,8," %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
int __stdcall my_stdcall_eight (int one, int two, int three, int four, int five, int six, int eight)
{
	stable_func_body(CALL_STDCALL,8," %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
int __thiscall my_thiscall_eight (int self,int one, int two, int three, int four, int five, int six, int eight)
{
	stable_func_body(CALL_THISCALL,8," %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
/*---------NINE---------*/
int __cdecl my_cdecl_nine (int one, int two, int three, int four, int five, int six, int eight, int nine)
{
	stable_func_body(CALL_CDECL,9," %08X %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
int __stdcall my_stdcall_nine (int one, int two, int three, int four, int five, int six, int eight, int nine)
{
	stable_func_body(CALL_STDCALL,9," %08X %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
int __thiscall my_thiscall_nine (int self,int one, int two, int three, int four, int five, int six, int eight, int nine)
{
	stable_func_body(CALL_THISCALL,9," %08X %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
/*---------TEN---------*/
int __cdecl my_cdecl_ten (int one, int two, int three, int four, int five, int six, int eight, int nine, int ten)
{
	stable_func_body(CALL_CDECL,10," %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
int __stdcall my_stdcall_ten (int one, int two, int three, int four, int five, int six, int eight, int nine, int ten)
{
	stable_func_body(CALL_STDCALL,10," %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\n");
}
int __thiscall my_thiscall_ten (int self,int one, int two, int three, int four, int five, int six, int eight, int nine, int ten)
{
	stable_func_body(CALL_THISCALL,10," %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\n");
}







