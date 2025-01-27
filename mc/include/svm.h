
#pragma once

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
		double		UAB[2];
		int			sector;
		double		m[3];
	} SVM_t;

	void modulator(SVM_t* svm, const double Ualpha, const double Ubeta, SVM_mode_t mode);

#ifdef __cplusplus
}
#endif // __cplusplus
