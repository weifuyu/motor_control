
#include "svm.h"
#include "ctrl_common.h"

static void calc_tabc(float32_t tabc[3], float32_t UAB[2]);
static int16_t determine_sector_6N(float32_t tabc[3]); 
static int16_t determine_sector_12N(float32_t tabc[3]); 
static void calc_svm_duty(SVM_t* svm, float32_t tabc[3], SVM_mode_t mode);

static void calc_tabc(float32_t tabc[3], float32_t UAB[2]) 
{
	float32_t Ualpha = UAB[0];
	float32_t Ubeta = UAB[1];

	tabc[0] = Ubeta;
	tabc[1] = (-SQRT3 * Ualpha - Ubeta) / 2.0f;
	tabc[2] = (SQRT3 * Ualpha - Ubeta) / 2.0f;
}

/*!
*
* @brief		identify 6 sectors of SVM modulation
* 				  0° to  60° Sector 0
*				 60° to 120° Sector 1
*				120° to 180° Sector 2
*				180° to 240° Sector 3
*				240° to 300° Sector 4
*				300° to 360° Sector 5
*/
static int16_t determine_sector_6N(float32_t tabc[3])
{
	float32_t ta = tabc[0];
	float32_t tb = tabc[1];
	float32_t tc = tabc[2];

	int16_t sector;

	if (ta > 0) {
		if (tc > 0) {
			sector = 0;
		}
		else {
			if (tb < 0) {
				sector = 1;
			}
			else {
				sector = 2;
			}
		}
	}
	else {
		if (tc < 0) {
			sector = 3;
		}
		else {
			if (tb > 0) {
				sector = 4;
			}
			else {
				sector = 5;
			}
		}
	}

	return sector;
}

/*!
* 
* @brief		identify 12 sectors of SVM modulation
*                   0° to  30° Sector 0
*				   30° to  60° Sector 1
*				   60° to	90° Sector 2
*                  90° to 120° Sector 3
*				  120° to 150° Sector 4
*				  150° to 180° Sector 5
*                 180° to 210° Sector 6
*                 210° to 240° Sector 7
*                 240° to 270° Sector 8
*	              270° to 300° Sector 9
*                 300° to 330° Sector 10
*                 330° to 360° Sector 11
*/
static int16_t determine_sector_12N(float32_t tabc[3])
{
    int16_t sector;
    float32_t ta = tabc[0];
    float32_t tb = tabc[1];
    float32_t tc = tabc[2];

	if (ta > 0) {
		if (tc > 0) {
			if (ta < tc) {
				sector = 0;
			}
			else {
				sector = 1;
			}
		}
		else {
			if (tb < 0) {
				if (tb < tc) {
					sector = 2;
				}
				else {
					sector = 3;
				}
			}
			else {
				if (tb < ta) {
					sector = 4;
				}
				else {
					sector = 5;
				}
			}
		}
	}
    else { // ta < 0
		if (tc < 0) {
			if (tc < ta) {
				sector = 6;
			}
			else {
				sector = 7;
			}
		}
		else {
			if (tb > 0) {
				if (tb > tc) {
					sector = 8;
				}
				else {
					sector = 9;
				}
			}
			else {
				if (ta < tb) {
					sector = 10;
				}
				else {
					sector = 11;
				}
			}
		}
	}

	return sector;
}

/*!
*
* @brief		calculate duty cycle for SVM modulation
* @param[in]	tabc: array of Ualpha, Ubeta, U0
* @param[in]	mode: SVM mode
* @param[out]	svm->m: array of duty cycle for phase A, B, C
*/
static void calc_svm_duty(SVM_t* svm, float32_t tabc[3], SVM_mode_t mode)
{
	float32_t ta = tabc[0];
	float32_t tb = tabc[1];
	float32_t tc = tabc[2];

	float32_t d1 = 0, d2 = 0;

	switch (svm->sector)
	{
	case 0: case 1: // V0(000) <=> V1(100) <=> V2(110) <=> V7(111)
		d1 = tc; // V1(100)
		d2 = ta; // V2(110)
		break;
	case 2: case 3: // V0(000) <=> V3(010) <=> V2(110) <=> V7(111)
		d1 = -tc; // V3(010)
		d2 = -tb; // V2(110)
		break;
	case 4: case 5: // V0(000) <=> V3(010) <=> V4(011) <=> V7(111)
		d1 = ta; // V3(010)
		d2 = tb; //  V4(011)
		break;
	case 6: case 7: // V0(000) <=> V5(001) <=> V4(011) <=> V7(111)
		d1 = -ta; // V5(001)
		d2 = -tc; // V4(011)
			break;
	case 8: case 9: // V0(000) <=> V5(001) <=> V6(101) <=> V7(111)
		d1 = tb; // V5(001)
		d2 = tc; // V6(101)
		break;
	case 10: case 11: // V0(000) <=> V1(100) <=> V6(101) <=> V7(111)
		d1 = -tb; // V1(100)
		d2 = -ta; // V6(101)
		break;
	default:
		break;
	}

	float32_t V0min = -1.0f / 2 + d1 / 3.0f + 2.0f * d2 / 3;
	float32_t V0max = 1.0f / 2 - 2.0f * d1 / 3 - d2 / 3.0f;

	float32_t v_cm = (d2 - d1) / 6; //SVPWM by default
	if (v_cm > V0max)
	{
		v_cm = V0max;
	}
	if (v_cm < V0min)
	{
		v_cm = V0min;
	}

    if (mode == DMPWM3)
	{
        if (((int16_t)((svm->sector + 1) / 2)) % 2 == 0)	// Sectors 0, 3, 4, 7, 8, 11
		{
			v_cm = V0min;
		}
        else // Sectors 1, 2, 5, 6, 9, 10
		{
			v_cm = V0max;
		}
	}

	float32_t ma, mb, mc;
	switch (svm->sector)
	{
	case 0: case 1: // V0(000) <=> V1(100) <=> V2(110) <=> V7(111)
		mc = 1.0f / 2 + v_cm - d1 / 3.0f - 2.0f * d2 / 3;
		mb = mc + d2;
		ma = mb + d1;
		break;
	case 2: case 3: // V0(000) <=> V3(010) <=> V2(110) <=> V7(111)
		mc = 1.0f / 2 + v_cm - d1 / 3.0f - 2.0f * d2 / 3;
		ma = mc + d2;
		mb = ma + d1;
		break;
	case 4: case 5: // V0(000) <=> V3(010) <=> V4(011) <=> V7(111)
		ma = 1.0f / 2 + v_cm - d1 / 3.0f - 2.0f * d2 / 3;
		mc = ma + d2;
		mb = mc + d1;
		break;
	case 6: case 7: // V0(000) <=> V5(001) <=> V4(011) <=> V7(111)
		ma = 1.0f / 2 + v_cm - d1 / 3.0f - 2.0f * d2 / 3;
		mb = ma + d2;
		mc = mb + d1;
		break;
	case 8: case 9: // V0(000) <=> V5(001) <=> V6(101) <=> V7(111)
		mb = 1.0f / 2 + v_cm - d1 / 3.0f - 2.0f * d2 / 3;
		ma = mb + d2;
		mc = ma + d1;
		break;
	case 10: case 11: // V0(000) <=> V1(100) <=> V6(101) <=> V7(111)
		mb = 1.0f / 2 + v_cm - d1 / 3.0f - 2.0f * d2 / 3;
		mc = mb + d2;
		ma = mc + d1;
		break;
	default:
		ma = 0;
		mb = 0;
		mc = 0;
		break;
	}

	if (ma < 0)
	{
		ma = 0;
	}
	if (mb < 0)
	{
		mb = 0;
	}
	if (mc < 0)
	{
		mc = 0;
	}

	if (ma > 1)
	{
		ma = 1;
	}
	if (mb > 1)
	{
		mb = 1;
	}
	if (mc > 1)
	{
		mc = 1;
	}

	svm->m[0] = ma;
	svm->m[1] = mb;
	svm->m[2] = mc;
}

/*!
*
* @brief		SVM modulation
* @param[in]	svm: SVM_t structure
* @param[in]	Ualpha: alpha
* @param[in]	Ubeta: beta
* @param[in]	mode: SVM mode
* @param[out]	svm->UAB: array of alpha, beta
* @param[out]	svm->sector: sector
* @param[out]	svm->m: array of duty cycle for phase A, B, C
*/
void modulator(SVM_t * svm, const float32_t Ualpha, const float32_t Ubeta, SVM_mode_t mode)
{
	svm->UAB[0] = Ualpha;
	svm->UAB[1] = Ubeta;

	float32_t tabc[3] = {0}; // Initialize tabc array to zero

	calc_tabc(tabc, svm->UAB);
	
	//svm->sector = determine_sector_6N(tabc);
	svm->sector = determine_sector_12N(tabc);

	calc_svm_duty(svm, tabc, mode);
}