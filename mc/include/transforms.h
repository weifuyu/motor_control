/**
 * @file        abc2AB.h
 * @author     
 * @date       01 Jan 2024
 * 
 * @brief      header file for Clarke and Park transformation
 * 
 *      This header file implements the Clarke and Park transformation.
 */ 


#ifndef TRANSFORMS_H_
    #define TRANSFORMS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "commontypes.h"

typedef struct
{
    float32_t     a;
    float32_t     b;
    float32_t     c;
} ABC_t;

typedef struct
{
    float32_t     alpha;
    float32_t     beta;
    float32_t     zero_AB;
} AB0_t;

typedef struct
{
    float32_t     d;
    float32_t     q;
    float32_t     zero_dq;
} DQ0_t;

typedef struct
{
    ABC_t       abc;
    AB0_t       AB0;
    DQ0_t       dq0;
} Transform_Obj_t;


/**
 * @brief      Clarke transformation - amplitude invariant
 *
 * @param      T_inst  The instance of the transformation object
 * @param      numSensors  The number of sensors, 2(phase a,c) or 3(phase a,b,c)
 */
void abc2AB0(Transform_Obj_t *T_inst, int16_t numSensors);

/**
 * @brief      Inverse Clarke transformation - amplitude invariant
 *
 * @param      T_inst  The instance of the transformation object
 * @param      numSensors  The number of sensors, 2(phase a,c) or 3(phase a,b,c)
 */
void AB02abc(Transform_Obj_t *T_inst);

/**
 * @brief      Park transformation
 *
 * @param      T_inst  The instance of the transformation object
 * @param      theta_e  The electrical angle
 */
void AB02dq0(Transform_Obj_t *T_inst, float32_t theta_e);


/**
 * @brief      Inverse Park transformation
 *
 * @param      T_inst  The instance of the transformation object
 * @param      theta_e  The electrical angle
 */
void dq02AB0(Transform_Obj_t *T_inst, float32_t theta_e);



#ifdef __cplusplus
}
#endif

#endif //<- !defined TRANSFORMS_H_