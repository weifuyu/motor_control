/**
 * @file        pid.c
 * @author     	
 * @date       	30 Dec 2024
 * 
 * @brief      source file for PI Controller
 * 
 */

#include "ctrl_common.h"
#include "pid.h"

/** \copydoc PID_Data_Init */
void PID_Data_Init(PID_Obj_t* const PID_inst,
    double err,
    double ui,
    double u,
    double uff,
    double err_aw)
{
    PID_inst->err = err;
    PID_inst->ui = ui;
    PID_inst->u = u;
    PID_inst->uff = uff;
    PID_inst->err_aw = err_aw;
} //<- end of PID_Data_Init()


 /** \copydoc PID_Param_Init */
void PID_Param_Init(PID_Obj_t* const PID_inst,
    double     OutHiLim,
    double     OutLoLim,
    double     IntRateLim,
    double     Kp,
    double     Ts,
    double     Ti,
    int         Ki_enable, // Ki_enable == false to disable INTEGRAL, otherwise to use the deduced value
    double     Td,
    int         Kd_enable, // Kd_enable == false to disable DERIVATIVE, otherwise to use the deduced value
    double     Kp_aw)
{
    PID_inst->OutHiLim     = OutHiLim;
    PID_inst->OutLoLim     = OutLoLim;
    PID_inst->IntRateLim   = IntRateLim;
    PID_inst->Kp        = Kp;
    PID_inst->Ts        = Ts;
    PID_inst->Ti        = Ti;
    PID_inst->Td        = Td;

    if (Ki_enable){
        PID_inst->Ki = Kp*Ts/Ti;
    }
    else {
        PID_inst->Ki = 0; // disable INTEGRAL
    }

    if (Kd_enable){
        PID_inst->Kd = Kp*Td/Ts;
    }
    else {
        PID_inst->Kd = 0; // disable DERIVATIVE
    }

    PID_inst->Kp_aw     = Kp_aw;
} //<- end of PID_Param_Init()


/** \copydoc PID_Update */
void PID_Update(PID_Obj_t* const PID_inst, double ref, double fb, double uff)
{
    double err = ref - fb;
    double err_k1 = PID_inst->err;
    double err_aw = PID_inst->err_aw;
    double ui = PID_inst->ui;
    double u = PID_inst->u;

    // compute the incremental proportional output
    // 
    double up = PID_inst->Kp * err;

    // compute the incremental integral output with anti-windup calculation applied
    // 
    double delta_ui = (PID_inst->Ki * (err+err_k1)/2) + (PID_inst->Kp_aw * err_aw);

    // integral change rate limitation
    // 
    SATURATE(delta_ui, PID_inst->IntRateLim, -PID_inst->IntRateLim);

    ui += delta_ui;

    SATURATE(ui, PID_inst->OutHiLim, PID_inst->OutLoLim);

    PID_inst->ui = ui;
    
    // comput the incremental derivative output
    // 
    double ud = PID_inst->Kd*(err - err_k1);

    // compute the control output
    // 
    u = up + ui + ud + uff;
    PID_inst->u = u;

    // control output limitation
    // 
    SATURATE(PID_inst->u, PID_inst->OutHiLim, PID_inst->OutLoLim);

    // update anti-windup error for next iteration
    // 
    PID_inst->err_aw = PID_inst->u - u;

    // update the error history
    //
    PID_inst->err = err;
} //<- end of PID_Update()
