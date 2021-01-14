void sp_det_CreateDetour(char * func_name, int num_args, int address, char * call_conven, int safebytes,bool after = false,void * sofplus_special = NULL);

extern unsigned int num_detours_one;
extern unsigned int num_detours_two;
extern unsigned int num_detours_three;
extern unsigned int num_detours_four;
extern unsigned int num_detours_five;
extern unsigned int num_detours_six;
extern unsigned int num_detours_seven;
extern unsigned int num_detours_eight;
extern unsigned int num_detours_nine;
extern unsigned int num_detours_ten;

typedef struct detour_list_s {
	unsigned int relocated_call;
	unsigned int orig_call;
	unsigned int sofplus;
	char funcname[64];
	char calling_convention[64];
	bool after; //run the code after the call to teh orig?
	struct detour_list_s * next,*prev;
} detour_list_t;



extern detour_list_t detours_one;
extern detour_list_t detours_two;
extern detour_list_t detours_three;
extern detour_list_t detours_four;
extern detour_list_t detours_five;
extern detour_list_t detours_six;
extern detour_list_t detours_seven;
extern detour_list_t detours_eight;
extern detour_list_t detours_nine;
extern detour_list_t detours_ten;


typedef int (__cdecl *cdecl_one_type)(int one);
typedef int (__cdecl *cdecl_two_type)(int one, int two);
typedef int (__cdecl *cdecl_three_type)(int one, int two, int three);
typedef int (__cdecl *cdecl_four_type)(int one, int two, int three, int four);
typedef int (__cdecl *cdecl_five_type)(int one, int two, int three, int four, int five);
typedef int (__cdecl *cdecl_six_type)(int one, int two, int three, int four, int five, int six);
typedef int (__cdecl *cdecl_seven_type)(int one, int two, int three, int four, int five, int six, int seven);
typedef int (__cdecl *cdecl_eight_type)(int one, int two, int three, int four, int five, int six, int seven,int eight);
typedef int (__cdecl *cdecl_nine_type)(int one, int two, int three, int four, int five, int six, int seven,int eight, int nine);
typedef int (__cdecl *cdecl_ten_type)(int one, int two, int three, int four, int five, int six, int seven,int eight, int nine, int ten);


typedef int (__stdcall *stdcall_one_type)(int one);
typedef int (__stdcall *stdcall_two_type)(int one, int two);
typedef int (__stdcall *stdcall_three_type)(int one, int two, int three);
typedef int (__stdcall *stdcall_four_type)(int one, int two, int three, int four);
typedef int (__stdcall *stdcall_five_type)(int one, int two, int three, int four, int five);
typedef int (__stdcall *stdcall_six_type)(int one, int two, int three, int four, int five, int six);
typedef int (__stdcall *stdcall_seven_type)(int one, int two, int three, int four, int five, int six, int seven);
typedef int (__stdcall *stdcall_eight_type)(int one, int two, int three, int four, int five, int six, int seven,int eight);
typedef int (__stdcall *stdcall_nine_type)(int one, int two, int three, int four, int five, int six, int seven,int eight, int nine);
typedef int (__stdcall *stdcall_ten_type)(int one, int two, int three, int four, int five, int six, int seven,int eight, int nine, int ten);

typedef int (__thiscall *thiscall_one_type)(int self,int one);
typedef int (__thiscall *thiscall_two_type)(int self,int one, int two);
typedef int (__thiscall *thiscall_three_type)(int self,int one, int two, int three);
typedef int (__thiscall *thiscall_four_type)(int self,int one, int two, int three, int four);
typedef int (__thiscall *thiscall_five_type)(int self,int one, int two, int three, int four, int five);
typedef int (__thiscall *thiscall_six_type)(int self,int one, int two, int three, int four, int five, int six);
typedef int (__thiscall *thiscall_seven_type)(int self,int one, int two, int three, int four, int five, int six, int seven);
typedef int (__thiscall *thiscall_eight_type)(int self,int one, int two, int three, int four, int five, int six,int seven, int eight);
typedef int (__thiscall *thiscall_nine_type)(int self,int one, int two, int three, int four, int five, int six, int seven,int eight, int nine);
typedef int (__thiscall *thiscall_ten_type)(int self,int one, int two, int three, int four, int five, int six, int seven,int eight, int nine, int ten);


extern int __cdecl my_cdecl_one (int one);
extern int __cdecl my_cdecl_two (int one, int two);
extern int __cdecl my_cdecl_three (int one, int two, int three);
extern int __cdecl my_cdecl_four (int one, int two, int three, int four);
extern int __cdecl my_cdecl_five (int one, int two, int three, int four, int five);
extern int __cdecl my_cdecl_six (int one, int two, int three, int four, int five, int six);
extern int __cdecl my_cdecl_seven (int one, int two, int three, int four, int five, int six, int seven);
extern int __cdecl my_cdecl_eight (int one, int two, int three, int four, int five, int six, int eight);
extern int __cdecl my_cdecl_nine (int one, int two, int three, int four, int five, int six, int eight, int nine);
extern int __cdecl my_cdecl_ten (int one, int two, int three, int four, int five, int six, int eight, int nine, int ten);
extern int __stdcall my_stdcall_one (int one);
extern int __stdcall my_stdcall_two (int one, int two);
extern int __stdcall my_stdcall_three (int one, int two, int three);
extern int __stdcall my_stdcall_four (int one, int two, int three, int four);
extern int __stdcall my_stdcall_five (int one, int two, int three, int four, int five);
extern int __stdcall my_stdcall_six (int one, int two, int three, int four, int five, int six);
extern int __stdcall my_stdcall_seven (int one, int two, int three, int four, int five, int six, int seven);
extern int __stdcall my_stdcall_eight (int one, int two, int three, int four, int five, int six, int eight);
extern int __stdcall my_stdcall_nine (int one, int two, int three, int four, int five, int six, int eight, int nine);
extern int __stdcall my_stdcall_ten (int one, int two, int three, int four, int five, int six, int eight, int nine, int ten);
extern int __thiscall my_thiscall_one (int self,int one);
extern int __thiscall my_thiscall_two (int self,int one, int two);
extern int __thiscall my_thiscall_three (int self,int one, int two, int three);
extern int __thiscall my_thiscall_four (int self,int one, int two, int three, int four);
extern int __thiscall my_thiscall_five (int self,int one, int two, int three, int four, int five);
extern int __thiscall my_thiscall_six (int self,int one, int two, int three, int four, int five, int six);
extern int __thiscall my_thiscall_seven (int self,int one, int two, int three, int four, int five, int six, int seven);
extern int __thiscall my_thiscall_eight (int self,int one, int two, int three, int four, int five, int six, int eight);
extern int __thiscall my_thiscall_nine (int self,int one, int two, int three, int four, int five, int six, int eight, int nine);
extern int __thiscall my_thiscall_ten (int self,int one, int two, int three, int four, int five, int six, int eight, int nine, int ten);