/**
 * @file        ctrl_common.h
 * @date       08/10/2017
 * 
 * @brief      Common  macros and consts used
 */

#ifndef CTRL_COMMON_H_
    #define CTRL_COMMON_H_


#ifndef PI
    #define PI                          (3.141592653589793F)    // PI
#endif
#ifndef PI_REC
    #define PI_REC                      (0.318309886183791F)    // 1/PI
#endif
#ifndef PI_HALF
    #define PI_HALF                     (1.570796326794897F)    // PI/2
#endif    
#ifndef PI_THIRD    
    #define PI_THIRD                    (1.047197551196598F)    // PI/3
#endif
#ifndef PI_SIXTH    
    #define PI_SIXTH                    (0.523598775598299F)    // PI/6
#endif
#ifndef ONE_SIXTH    
    #define ONE_SIXTH                   (0.166666666666667F)    // 1/6
#endif
#ifndef TWO_PI
    #define TWO_PI                      (6.283185307179586F)    // 2*PI
#endif
#ifndef TWO_PI_REC
    #define TWO_PI_REC                  (0.159154943091895F)    // 1/(2*PI)
#endif
#ifndef ONE_THIRD
    #define ONE_THIRD                   (0.333333333333333F)    // 1/3
#endif
#ifndef TWO_THIRD
    #define TWO_THIRD                   (0.666666666666667F)    // 2/3
#endif
#ifndef TWO_PI_DIV_60
    #define TWO_PI_DIV_60               (0.104719755119660F)    // 2.0 * PI / 60
#endif
#ifndef TWO_PI_BY_60_REC
    #define TWO_PI_BY_60_REC            (9.549296585513721F)    // 60 / ( 2.0 * PI )
#endif
#ifndef TWO_PI_THIRD
    #define TWO_PI_THIRD                (2.09439510F)           // 2.0 / 3.0 * PI == 120 degree
#endif
#ifndef FOUR_PI_THIRD
    #define FOUR_PI_THIRD               (4.18879020F)           // 4.0 / 3.0 * PI == 240 degree
#endif
#ifndef SQRT3
    #define SQRT3                       (1.73205081F)           // SQRT(3)
#endif
#ifndef SQRT3REC
    #define SQRT3REC                    (0.57735027F)           // 1/SQRT(3)
#endif
#ifndef SQRT2
    #define SQRT2                       (1.41421356F)           // SQRT(2)
#endif
#ifndef SQRT_HALF
    #define SQRT_HALF                   (0.70710678F)           // 1/SQRT(2)
#endif
#ifndef SQRT2_3
    #define SQRT2_3                     (0.81649658F)           // SQRT(2/3)
#endif
#ifndef SQRT2_BY_3
    #define SQRT2_BY_3                  (0.471404520791032F)    // SQRT(2)/3
#endif
#ifndef SIN30
    #define SIN30                       (0.50000000F)           // sin(30)
#endif
#ifndef SIN60
    #define SIN60                       (0.86602540F)           // sin(60)
#endif
#ifndef SIN60REC
    #define SIN60REC                    (1.15470054F)           // 1/sin(60)
#endif
#ifndef NORM_AVE_TO_RMS
    #define NORM_AVE_TO_RMS             (1.11072073F)           // norm average to rms value for
#endif
#ifndef RPM2RAD
    #define RPM2RAD                     (0.104719755119660F)    // 2*pi/60
#endif


/**
 * @brief      Two side limitation
 *
 * @param      x      concerned parameter to be limited
 * @param      HiLim  The higher limit
 * @param      LoLim  The lower limit
 *
 * @return     
 */
#ifndef SATURATE
    #define SATURATE(x,HiLim,LoLim) { x = (x)>(HiLim) ? (HiLim):(x); \
                                      x = (x)<(LoLim) ? (LoLim):(x);}
#else
    #error ERROR - SATURATE already defined
#endif

#endif // <-- !defined CTRL_COMMON_H_

