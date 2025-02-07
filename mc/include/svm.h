#pragma once

#include "commontypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef enum
	{
		SVPWM = 0,
        DMPWM3 = 1,
	} SVM_mode_t;
	
	typedef struct
	{
		float32_t		UAB[2];
		int16_t			sector;
		float32_t		m[3];
	} SVM_t;

	void modulator(SVM_t* svm, const float32_t Ualpha, const float32_t Ubeta, SVM_mode_t mode);

#ifdef __cplusplus
}
#endif // __cplusplus
