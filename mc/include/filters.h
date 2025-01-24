/**
 * @file       filters.h
 * 
 * @brief      header file for filters
 * 
 *      This header file implements vairious filters
 */
#ifndef FILTERS_H_
    #define FILTERS_H_

#ifdef __cplusplus
extern "C" {
#endif


// y(k) = b_1 y(k-1) + a_0 x(k) + a_1 x(k-1)
//
typedef struct
{
    // filter-1st data
    double   y;
    double   u;
    // filter-1st param
    double   a0;
    double   a1;
    double   b1;
} Lpf1st_Obj_t;
 
 
/**
 * @brief      first order lowpass filter init
 *
 * @param      lpf_1st_inst The LPF_1ST instance
 * @param[in]  a0
 * @param[in]  a1
 * @param[in]  b1   The filter coefficients of a general 1st order filter. 
 *                  $y(k) = b_1 y(k-1) + a_0 x(k) + a_1 x(k-1)$ 
 *                  usually $a_0 + a_1 + b_1 = 1$ to have unity gain.
 */
void lpf_1st_init(Lpf1st_Obj_t* const lpf_1st_inst, double y, double u,
                double a0, double a1, double b1);

/**
 * @brief      first order lowpass filter update
 * 
 * @param      lpf_1st_inst The LPF_1ST instance
 * 
 *     Implment a general first order lowpass filter
 */
void lpf_1st_update(Lpf1st_Obj_t* const lpf_1st_inst, double u);

#ifdef __cplusplus
}
#endif

#endif // <-- !defined FILTERS_H_
