// Automatically generated C++ file on Fri Jan 17 15:46:31 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD park.cpp kernel32.lib

#include <malloc.h>
#include "transforms.h"

extern "C" __declspec(dllexport) int (*Display)(const char *format, ...) = 0; // works like printf()
extern "C" __declspec(dllexport) const double *DegreesC                  = 0; // pointer to current circuit temperature
extern "C" __declspec(dllexport) const int *StepNumber                   = 0; // pointer to current step number
extern "C" __declspec(dllexport) const int *NumberSteps                  = 0; // pointer to estimated number of steps
extern "C" __declspec(dllexport) const char* const *InstanceName         = 0; // pointer to address of instance name
extern "C" __declspec(dllexport) const char *QUX                         = 0; // path to QUX.exe
extern "C" __declspec(dllexport) const bool *ForKeeps                    = 0; // pointer to whether being evaluated non-hypothetically
extern "C" __declspec(dllexport) const bool *HoldICs                     = 0; // pointer to whether instance initial conditions are being held
extern "C" __declspec(dllexport) int (*DFFT)(struct sComplex *u, bool inv, unsigned int N, double scale) = 0; // discrete Fast Fourier function

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
#undef theta_e
#undef d
#undef q

struct sPARK
{
   // declare the structure here
   bool clk_n1;
   Transform_Obj_t T_inst;
};

extern "C" __declspec(dllexport) void park(struct sPARK **opaque, double t, union uData *data)
{
   double  A       = data[0].d; // input
   double  B       = data[1].d; // input
   bool    clk     = data[2].b; // input
   double  theta_e = data[3].d; // input
   double &d       = data[4].d; // output
   double &q       = data[5].d; // output

   if(!*opaque)
   {
      *opaque = (struct sPARK *) malloc(sizeof(struct sPARK));
      bzero(*opaque, sizeof(struct sPARK));
   }
   struct sPARK *inst = *opaque;

// Implement module evaluation code here:
   if(clk && !inst->clk_n1)
   {
      inst->T_inst.AB0.alpha = A;
      inst->T_inst.AB0.beta = B;
      inst->T_inst.AB0.zero_AB = 0;
      
      AB02dq0(&inst->T_inst, theta_e);
      
      d = inst->T_inst.dq0.d;
      q = inst->T_inst.dq0.q;
   }
   inst->clk_n1 = clk;
}

extern "C" __declspec(dllexport) void Destroy(struct sPARK *inst)
{
   free(inst);
}
