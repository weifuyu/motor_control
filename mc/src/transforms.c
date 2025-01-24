/**
 * @file        transform.c
 * @author     	
 * @date       	13 Jan 2024
 * 
 * @brief       Implements the Clarke, iClarke, Park & iPark transformation
 * 
 */

 #include <math.h>
 #include "ctrl_common.h"
 #include "transforms.h"

    /** \copydoc abc2AB0 */
void abc2AB0(Transform_Obj_t *T_inst, int numSensors)
{
    if (numSensors == 2)
    {// assume phase a&b sensing, a+b+c = 0
        T_inst->abc.c = -T_inst->abc.a - T_inst->abc.b;

        T_inst->AB0.alpha = T_inst->abc.a;
        T_inst->AB0.beta = SQRT3REC*(T_inst->abc.a + 2*T_inst->abc.b);
        T_inst->AB0.zero_AB = 0;
    }
    else if (numSensors == 3)   // 3-phase
    {
        T_inst->AB0.alpha = TWO_THIRD*T_inst->abc.a-ONE_THIRD*(T_inst->abc.b+T_inst->abc.c);
        T_inst->AB0.beta = SQRT3REC*(T_inst->abc.b-T_inst->abc.c);
        T_inst->AB0.zero_AB = ONE_THIRD*(T_inst->abc.a+T_inst->abc.b+T_inst->abc.c);
    }
    
} //<- end of abc2AB0

    /** \copydoc AB02dq0 */
void AB02dq0(Transform_Obj_t *T_inst, double theta_e)
{
    T_inst->dq0.d = T_inst->AB0.alpha * cos(theta_e) + T_inst->AB0.beta * sin(theta_e);
    T_inst->dq0.q = - T_inst->AB0.alpha * sin(theta_e) + T_inst->AB0.beta * cos(theta_e);
    T_inst->dq0.zero_dq = T_inst->AB0.zero_AB;
} //<- end of AB02dq0

    /** \copydoc dq02AB0 */
void dq02AB0(Transform_Obj_t *T_inst, double theta_e)
{
    T_inst->AB0.alpha = T_inst->dq0.d * cos(theta_e) - T_inst->dq0.q * sin(theta_e);
    T_inst->AB0.beta = T_inst->dq0.d * sin(theta_e) + T_inst->dq0.q * cos(theta_e);
    T_inst->AB0.zero_AB = T_inst->dq0.zero_dq;
} //<- end of dq02AB0

/** \copydoc AB02abc */
void AB02abc(Transform_Obj_t *T_inst)
{
    T_inst->abc.a = T_inst->AB0.alpha + T_inst->AB0.zero_AB;
    T_inst->abc.b = -T_inst->AB0.alpha/2 + SQRT3/2*T_inst->AB0.beta + T_inst->AB0.zero_AB;
    T_inst->abc.c = -T_inst->AB0.alpha/2 - SQRT3/2*T_inst->AB0.beta + T_inst->AB0.zero_AB;
} //<- end of AB02abc

// EOF transform.c
