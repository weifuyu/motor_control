// Automatically generated C++ file on Fri Jan 17 17:02:51 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD iclarke.cpp kernel32.lib

#include <malloc.h>
#include "transforms.h"

union uData
{
   bool b;
   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i;
   unsigned int ui;
   float f;
   double d;
   long long int i64;
   unsigned long long int ui64;
   char *str;
   unsigned char *bytes;
};

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

void bzero(void *ptr, unsigned int count)
{
   unsigned char *first = (unsigned char *) ptr; 
   unsigned char *last  = first + count; 
   while(first < last)
      *first++ = '\0'; 
}

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef A
#undef B
#undef clk
#undef u
#undef v
#undef W

struct sICLARKE
{
  // declare the structure here
  bool clk_n1;
  Transform_Obj_t T_inst;
};

extern "C" __declspec(dllexport) void iclarke(struct sICLARKE **opaque, double t, union uData *data)
{
   float   A   = data[0].f; // input
   float   B   = data[1].f; // input
   bool    clk = data[2].b; // input
   float  &u   = data[3].f; // output
   float  &v   = data[4].f; // output
   float  &W   = data[5].f; // output

   if(!*opaque)
   {
      *opaque = (struct sICLARKE *) malloc(sizeof(struct sICLARKE));
      bzero(*opaque, sizeof(struct sICLARKE));
   }
   struct sICLARKE *inst = *opaque;

// Implement module evaluation code here:
   if (inst != NULL) {
       if (clk && !inst->clk_n1)
       {
           inst->T_inst.AB0.alpha = A;
           inst->T_inst.AB0.beta = B;
           inst->T_inst.AB0.zero_AB = 0;

           AB02abc(&inst->T_inst);

           u = inst->T_inst.abc.a;
           v = inst->T_inst.abc.b;
           W = inst->T_inst.abc.c;
       }
       inst->clk_n1 = clk;
   }
}

extern "C" __declspec(dllexport) void Destroy(struct sICLARKE *inst)
{
   free(inst);
}
