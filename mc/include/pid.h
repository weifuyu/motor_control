/**
 * @file        PID.h
 * @author     
 * @date       30 Dec 2024
 * 
 * @brief      header file for PID Controller
 * 
 *      This header file implements a general purpose PID controller. Integral saturation,
 *      PID output saturation and anti-windup are implemented.
 */ 



#ifndef PID_H_
    #define PID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ctrl_common.h"

//*****************************************************************************
//
//! \brief Defines the PID controller object
//
//*****************************************************************************
typedef struct
{
	// PID datas
	double	    err;        // error
    double     err_k1;     // error(k-1)
    double     ui;         // integral output
	double     u;          // output 
    double     uff;        // feedforward
    double     err_aw;     // anti-windup error
	// PID params
	double     OutHiLim;
	double     OutLoLim;
	double     IntRateLim;
	double     Kp;
	double     Ts;
    double     Ti;
    double     Ki;     // discrete Ki=Kp*Ts/Ti
    double     Td;
    double     Kd;     // discrete Kd=Kp*Td/Ts
    double     Kp_aw;  // anti-windup gain
} PID_Obj_t;

/**
 * @brief      PID controller data initialization
 * 
 * @param[in]  PID_inst     The PID instance
 * @param[in]  err          The error
 * @param[in]  err_k1       The error(k-1)
 * @param[in]  ui           The integral
 * @param[in]  u            The output
 * @param[in]  uff          The feedforward, add to output before anti-windup
 * @param[in]  err_aw       The anti-windup error
 */
void PID_Data_Init(PID_Obj_t* const PID_inst,
    double err,
    double ui,
    double u,
    double uff,
    double err_aw);

/**
 * @brief      PID controller parammeters initialization
 *
 * @param      PID_inst     The PID instance
 * @param[in]  OutHiLim     The higher limit to the output
 * @param[in]  OutLoLim     The lower limit to the output
 * @param[in]  IntRateLim   The rate limit for integral, should be positive
 * @param[in]  Kp	        PID controller proportional gain
 * @param[in]  Ts           Ts is the loop rate
 * @param[in]  Ti           Ti is the integral time constant
 * @param[in]  Ki_enable    Ki is the discrete integral gain, Ki=Ki=Kp*Ts/Ti. Ki<=0 to disable INTEGRAL
 * @param[in]  Td           Td is the derivative time constant
 * @param[in]  Kd_enable    Kd is the derivateive gain, Kd=Kp*Td/Ts. Kd<=0 to disable DERIVATIVE
 * @param[in]  Kp_aw        Kp_aw is the anti-windup gain
 */
void PID_Param_Init(PID_Obj_t* const PID_inst,
    double OutHiLim,
    double OutLoLim,
    double IntRateLim,
    double Kp,
    double Ts,
    double Ti,
    int     Ki_enable,
    double Td,
    int     Kd_enable,
    double Kp_aw);


/**
 * @brief      PID controller update
 *
 * @param      PID_inst The PID instance
 * @param[in]  ref      The reference
 * @param[in]  fb       The feedback
 * 
 * 		This is PID controller update function. It calculates the PID output based on the error input.
 */
void PID_Update(PID_Obj_t* const PID_inst,  double ref, double fb, double uff);

#ifdef __cplusplus
}
#endif

#endif //<- !defined PID_H_
