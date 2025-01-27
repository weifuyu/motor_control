// Automatically generated C++ file on Sun Jan 26 18:47:21 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD svmgen.cpp kernel32.lib

#include <malloc.h>
#include "svm.h"

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
#undef UA
#undef UB
#undef clk
#undef ma
#undef mb
#undef mc
#undef dbg

struct sSVMGEN
{
  // declare the structure here
    double clk_n1;
    SVM_t svm;
};

extern "C" __declspec(dllexport) void svmgen(struct sSVMGEN **opaque, double t, union uData *data)
{
   double  UA   = data[0].d; // input
   double  UB   = data[1].d; // input
   bool    clk  = data[2].b; // input
   int     mode = data[3].i; // input parameter
   double &ma   = data[4].d; // output
   double &mb   = data[5].d; // output
   double &mc   = data[6].d; // output
   int    &dbg  = data[7].i; // output


   if(!*opaque)
   {
      *opaque = (struct sSVMGEN *) malloc(sizeof(struct sSVMGEN));
      bzero(*opaque, sizeof(struct sSVMGEN));
   }
   struct sSVMGEN *inst = *opaque;

   if (inst != NULL) {
       // Implement module evaluation code here:
       if (clk && !inst->clk_n1)
       {
           modulator(&inst->svm, UA, UB, SVM_mode_t(mode));
           ma = inst->svm.m[0];
           mb = inst->svm.m[1];
           mc = inst->svm.m[2];

           dbg = inst->svm.sector;
       }
       inst->clk_n1 = clk;
   }
}

extern "C" __declspec(dllexport) void Destroy(struct sSVMGEN *inst)
{
   free(inst);
}
