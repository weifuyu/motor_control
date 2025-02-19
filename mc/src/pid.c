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
    float32_t err,
    float32_t ui,
    float32_t u,
    float32_t uff,
    float32_t err_aw)
{
    PID_inst->err = err;
    PID_inst->ui = ui;
    PID_inst->u = u;
    PID_inst->uff = uff;
    PID_inst->err_aw = err_aw;
} //<- end of PID_Data_Init()


 /** \copydoc PID_Param_Init */
void PID_Param_Init(PID_Obj_t* const PID_inst,
    float32_t     OutHiLim,
    float32_t     OutLoLim,
    float32_t     IntRateLim,
    float32_t     Kp,
    float32_t     Ts,
    float32_t     Ti,
    int16_t       Ki_enable, // Ki_enable == false to disable INTEGRAL, otherwise to use the deduced value
    float32_t     Td,
    int16_t       Kd_enable, // Kd_enable == false to disable DERIVATIVE, otherwise to use the deduced value
    float32_t     Kp_aw)
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
void PID_Update(PID_Obj_t* const PID_inst, float32_t ref, float32_t fb, float32_t uff)
{
    float32_t err = ref - fb;
    float32_t err_k1 = PID_inst->err;
    float32_t err_aw = PID_inst->err_aw;
    float32_t ui = PID_inst->ui;
    float32_t u = PID_inst->u;

    // compute the incremental proportional output
    // 
    float32_t up = PID_inst->Kp * err;

    // compute the incremental integral output with anti-windup calculation applied
    // 
    float32_t delta_ui = (PID_inst->Ki * (err+err_k1)/2) + (PID_inst->Kp_aw * err_aw);

    // integral change rate limitation
    // 
    SATURATE(delta_ui, PID_inst->IntRateLim, -PID_inst->IntRateLim);

    ui += delta_ui;

    SATURATE(ui, PID_inst->OutHiLim, PID_inst->OutLoLim);

    PID_inst->ui = ui;
    
    // comput the incremental derivative output
    // 
    float32_t ud = PID_inst->Kd*(err - err_k1);

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
