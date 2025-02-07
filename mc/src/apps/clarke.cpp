// Automatically generated C++ file on Thu Jan 16 11:08:59 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD clarke.cpp kernel32.lib

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
#undef u
#undef v
#undef A
#undef B

struct sCLARKE
{
   bool clk_n1;
   Transform_Obj_t T_inst;
};

extern "C" __declspec(dllexport) void clarke(struct sCLARKE **opaque, double t, union uData *data)
{
   float   u   = data[0].f; // input
   float   v   = data[1].f; // input
   bool    clk = data[2].b; // input
   float  &A   = data[3].f; // output
   float  &B   = data[4].f; // output

   if(!*opaque)
   {
      *opaque = (struct sCLARKE *) malloc(sizeof(struct sCLARKE));
      bzero(*opaque, sizeof(struct sCLARKE));
   }
   struct sCLARKE *inst = *opaque;

// Implement module evaluation code here:

   if (clk && !inst->clk_n1) // rising edge
   {
      inst->T_inst.abc.a = u;
      inst->T_inst.abc.b = v;

      abc2AB0(&inst->T_inst, 2);

      A = inst->T_inst.AB0.alpha;
      B = inst->T_inst.AB0.beta; 
   }

   inst->clk_n1 = clk;
}

extern "C" __declspec(dllexport) void Destroy(struct sCLARKE *inst)
{
   free(inst);
}
