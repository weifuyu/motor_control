// Automatically generated C++ file on Mon Jan 20 18:14:20 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD lpf_1st.cpp kernel32.lib

#include <malloc.h>
#include "filters.h"

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
#undef y

struct sLPF_1ST
{
  // declare the structure here
   bool init_done;
   bool   clk_n1;
   Lpf1st_Obj_t lpf_1st_inst;
};

extern "C" __declspec(dllexport) void lpf_1st(struct sLPF_1ST **opaque, double t, union uData *data)
{
   float   u   = data[0].f; // input
   bool    clk = data[1].b; // input
   float   a0  = data[2].f; // input parameter
   float   a1  = data[3].f; // input parameter
   float   b1  = data[4].f; // input parameter
   float  &y   = data[5].f; // output

   if(!*opaque)
   {
      *opaque = (struct sLPF_1ST *) malloc(sizeof(struct sLPF_1ST));
      bzero(*opaque, sizeof(struct sLPF_1ST));
   }
   struct sLPF_1ST *inst = *opaque;

// Implement module evaluation code here:

   if(!inst->init_done)
   {
      lpf_1st_init(&inst->lpf_1st_inst, u, u, a0, a1, b1);

      inst->init_done = true;
   }

   if (clk && !inst->clk_n1)   // rising edge
   {
      lpf_1st_update(&inst->lpf_1st_inst, u);
   }
   
   y = inst->lpf_1st_inst.y;

   inst->clk_n1 = clk;
}

extern "C" __declspec(dllexport) void Destroy(struct sLPF_1ST *inst)
{
   free(inst);
}
