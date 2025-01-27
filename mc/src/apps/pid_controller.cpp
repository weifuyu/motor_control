// Automatically generated C++ file on Wed Jan  8 09:16:35 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD pid_controller.cpp kernel32.lib

#include <malloc.h>
#include "pid.h"

extern "C" __declspec(dllexport) int (*Display)(const char *format, ...) = 0; // works like printf()
extern "C" __declspec(dllexport) const double *DegreesC                  = 0; // pointer to current circuit temperature
//extern "C" __declspec(dllexport) const int *StepNumber                   = 0; // pointer to current step number
//extern "C" __declspec(dllexport) const int *NumberSteps                  = 0; // pointer to estimated number of steps
//extern "C" __declspec(dllexport) const char* const *InstanceName         = 0; // pointer to address of instance name
//extern "C" __declspec(dllexport) const char *QUX                         = 0; // path to QUX.exe
//extern "C" __declspec(dllexport) const bool *ForKeeps                    = 0; // pointer to whether being evaluated non-hypothetically
//extern "C" __declspec(dllexport) const bool *HoldICs                     = 0; // pointer to whether instance initial conditions are being held
//extern "C" __declspec(dllexport) int (*DFFT)(struct sComplex *u, bool inv, unsigned int N, double scale) = 0; // discrete Fast Fourier function

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
#undef ref
#undef clk
#undef fb
#undef uff
#undef u
#undef _DBG

struct sPID_CONTROLLER
{
  // declare the structure here
  bool init_done;
  bool   clk_n1;      // clk[n-1]
  PID_Obj_t PID_inst;
};

extern "C" __declspec(dllexport) void pid_controller(struct sPID_CONTROLLER **opaque, double t, union uData *data)
{
   double  ref        = data[ 0].d; // input
   bool    clk        = data[ 1].b; // input
   double  fb         = data[ 2].d; // input
   double  uff        = data[ 3].d; // input
   double  OutHiLim   = data[ 4].d; // input parameter
   double  OutLoLim   = data[ 5].d; // input parameter
   double  IntRateLim = data[ 6].d; // input parameter
   double  Kp         = data[ 7].d; // input parameter
   double  Ts         = data[ 8].d; // input parameter
   double  Ti         = data[ 9].d; // input parameter
   bool    Ki_enable  = data[10].b; // input parameter
   double  Td         = data[11].d; // input parameter
   bool    Kd_enable  = data[12].b; // input parameter
   double  Kp_aw      = data[13].d; // input parameter
   double &u          = data[14].d; // output
   double &_DBG       = data[15].d; // debug

   if(!*opaque)
   {
      *opaque = (struct sPID_CONTROLLER *) malloc(sizeof(struct sPID_CONTROLLER));
      bzero(*opaque, sizeof(struct sPID_CONTROLLER));
   }
   struct sPID_CONTROLLER *inst = *opaque;

// Implement module evaluation code here:

   if (!inst->init_done){
      PID_Data_Init(&inst->PID_inst,
         0, //err,
         0, //ui,
         0, //u,
         0, //uff
         0); //err_aw);

      PID_Param_Init(&inst->PID_inst,
         OutHiLim,
         OutLoLim,
         IntRateLim,
         Kp,
         Ts,
         Ti,
         Ki_enable,
         Td,
         Kd_enable,
         Kp_aw);

      Display("pid_controller: Kp=%f, Ts=%f, Ti=%f, Ki=%f, Td=%f, Kd=%f\n",
               Kp, Ts, Ti, inst->PID_inst.Ki, Td, inst->PID_inst.Kd);
         
      inst->init_done = true;
   }

   if (clk && !inst->clk_n1)   // rising edge
   {
      PID_Update(&inst->PID_inst, ref, fb, uff);
   }

   u  = inst->PID_inst.u;

   inst->clk_n1 = clk;

   _DBG = inst->PID_inst.ui;
}

extern "C" __declspec(dllexport) double MaxExtStepSize(struct sPID_CONTROLLER *inst, double t)
{
   return 1e308; // implement a good choice of max timestep size that depends on struct sPID_CONTROLLER
}


extern "C" __declspec(dllexport) void Destroy(struct sPID_CONTROLLER *inst)
{
   free(inst);
}
