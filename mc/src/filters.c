/**
 * @file        filters.c
 * @date       	Jan 2025
 * 
 * @brief      source interface file for filters
 * 
 *      This source file provide the interface to the filters.
 */

#include "filters.h"


/** \copydoc lpf_1st_init */
void lpf_1st_init(Lpf1st_Obj_t* const lpf_1st_inst, float32_t y, float32_t u, 
				float32_t a0, float32_t a1, float32_t b1)
{
	lpf_1st_inst->y = y;
	lpf_1st_inst->u = u;

	lpf_1st_inst->a0 = a0;
	lpf_1st_inst->a1 = a1;
	lpf_1st_inst->b1 = b1;
}

/** \copydoc lpf_1st_update */
void lpf_1st_update(Lpf1st_Obj_t* const lpf_1st_inst, float32_t u)
{
	float32_t u_k1 = lpf_1st_inst->u;
	lpf_1st_inst->y = lpf_1st_inst->b1 * lpf_1st_inst->y;
	lpf_1st_inst->y += lpf_1st_inst->a0 * u;
	lpf_1st_inst->y += lpf_1st_inst->a1 * u_k1;

	lpf_1st_inst->u = u;
}