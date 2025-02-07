// Automatically generated C++ file on Fri Jan 17 16:49:49 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD ipark.cpp kernel32.lib

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
#undef d
#undef q
#undef clk
#undef theta_e
#undef A
#undef B

struct sIPARK
{
  // declare the structure here
   bool clk_n1;
   Transform_Obj_t T_inst;
};

extern "C" __declspec(dllexport) void ipark(struct sIPARK **opaque, double t, union uData *data)
{
   float   d       = data[0].f; // input
   float   q       = data[1].f; // input
   bool    clk     = data[2].b; // input
   float   theta_e = data[3].f; // input
   float  &A       = data[4].f; // output
   float  &B       = data[5].f; // output

   if(!*opaque)
   {
      *opaque = (struct sIPARK *) malloc(sizeof(struct sIPARK));
      bzero(*opaque, sizeof(struct sIPARK));
   }
   struct sIPARK *inst = *opaque;

// Implement module evaluation code here:
   if(clk && !inst->clk_n1)
   {
      inst->T_inst.dq0.d = d;
      inst->T_inst.dq0.q = q;
      inst->T_inst.dq0.zero_dq = 0;

      dq02AB0(&inst->T_inst, theta_e);

      A = inst->T_inst.AB0.alpha;
      B = inst->T_inst.AB0.beta;
   }

   inst->clk_n1 = clk;
}

extern "C" __declspec(dllexport) void Destroy(struct sIPARK *inst)
{
   free(inst);
}
