
#include "svm.h"
#include "ctrl_common.h"

static void calc_tabc(double tabc[3], double UAB[2]);
static int determine_sector_6N(double tabc[3]); 
static int determine_sector_12N(double tabc[3]); 
static void calc_svm_duty(SVM_t* svm, double tabc[3], SVM_mode_t mode);

static void calc_tabc(double tabc[3], double UAB[2]) 
{
	double Ualpha = UAB[0];
	double Ubeta = UAB[1];

	tabc[0] = Ubeta;
	tabc[1] = (-SQRT3 * Ualpha - Ubeta) / 2.0;
	tabc[2] = (SQRT3 * Ualpha - Ubeta) / 2.0;
}

/*!
*
* @brief		identify 6 sectors of SVM modulation
* 				  0бу to  60бу Sector 0
*				 60бу to 120бу Sector 1
*				120бу to 180бу Sector 2
*				180бу to 240бу Sector 3
*				240бу to 300бу Sector 4
*				300бу to 360бу Sector 5
*/
static int determine_sector_6N(double tabc[3])
{
	double ta = tabc[0];
	double tb = tabc[1];
	double tc = tabc[2];

	int sector;

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
*                   0бу to  30бу Sector 0
*				   30бу to  60бу Sector 1
*				   60бу to	90бу Sector 2
*                  90бу to 120бу Sector 3
*				  120бу to 150бу Sector 4
*				  150бу to 180бу Sector 5
*                 180бу to 210бу Sector 6
*                 210бу to 240бу Sector 7
*                 240бу to 270бу Sector 8
*	              270бу to 300бу Sector 9
*                 300бу to 330бу Sector 10
*                 330бу to 360бу Sector 11
*/
static int determine_sector_12N(double tabc[3])
{
    int sector;
    double ta = tabc[0];
    double tb = tabc[1];
    double tc = tabc[2];

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

static void calc_svm_duty(SVM_t* svm, double tabc[3], SVM_mode_t mode)
{
	double ta = tabc[0];
	double tb = tabc[1];
	double tc = tabc[2];

	double d1 = 0, d2 = 0;

	double ma, mb, mc;

	switch (svm->sector)
	{
	case 0: // V0(000) <=> V1(100) <=> V2(110) <=> V7(111)
	case 1:
		d1 = tc; // V1(100)
		d2 = ta; // V2(110)
		break;
	case 2: // V0(000) <=> V3(010) <=> V2(110) <=> V7(111)
    case 3:
		d1 = -tc; // V3(010)
		d2 = -tb; // V2(110)
		break;
	case 4: // V0(000) <=> V3(010) <=> V4(011) <=> V7(111)
    case 5:
		d1 = ta; // V3(010)
		d2 = tb; //  V4(011)
		break;
	case 6: // V0(000) <=> V5(001) <=> V4(011) <=> V7(111)
    case 7:
		d1 = -ta; // V5(001)
		d2 = -tc; // V4(011)
			break;
	case 8: // V0(000) <=> V5(001) <=> V6(101) <=> V7(111)
    case 9:
		d1 = tb; // V5(001)
		d2 = tc; // V6(101)
		break;
	case 10: // V0(000) <=> V1(100) <=> V6(101) <=> V7(111)
    case 11:
		d1 = -tb; // V1(100)
		d2 = -ta; // V6(101)
		break;
	default:
		break;
	}

	double V0min = -1.0 / 2 + d1 / 3.0 + 2.0 * d2 / 3.0;
	double V0max = 1.0 / 2 - 2.0 * d1 / 3.0 - d2 / 3.0;

	double v_cm = (d2 - d1) / 6; //SVPWM by default
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
        if (((int)((svm->sector + 1) / 2)) % 2 == 0)	// Sectors 0, 3, 4, 7, 8, 11
		{
			v_cm = V0min;
		}
        else // Sectors 1, 2, 5, 6, 9, 10
		{
			v_cm = V0max;
		}
	}

	switch (svm->sector)
	{
	case 0: // V0(000) <=> V1(100) <=> V2(110) <=> V7(111)
    case 1:
		mc = 1.0 / 2 + v_cm - d1 / 3.0 - 2.0 * d2 / 3;
		mb = mc + d2;
		ma = mb + d1;
		break;
	case 2: // V0(000) <=> V3(010) <=> V2(110) <=> V7(111)
    case 3:
		mc = 1.0 / 2 + v_cm - d1 / 3.0 - 2.0 * d2 / 3;
		ma = mc + d2;
		mb = ma + d1;
		break;
	case 4: // V0(000) <=> V3(010) <=> V4(011) <=> V7(111)
    case 5:
		ma = 1.0 / 2 + v_cm - d1 / 3.0 - 2.0 * d2 / 3;
		mc = ma + d2;
		mb = mc + d1;
		break;
	case 6: // V0(000) <=> V5(001) <=> V4(011) <=> V7(111)
    case 7:
		ma = 1.0 / 2 + v_cm - d1 / 3.0 - 2.0 * d2 / 3;
		mb = ma + d2;
		mc = mb + d1;
		break;
	case 8: // V0(000) <=> V5(001) <=> V6(101) <=> V7(111)
    case 9:
		mb = 1.0 / 2 + v_cm - d1 / 3.0 - 2.0 * d2 / 3;
		ma = mb + d2;
		mc = ma + d1;
		break;
	case 10: // V0(000) <=> V1(100) <=> V6(101) <=> V7(111)
    case 11:
		mb = 1.0 / 2 + v_cm - d1 / 3.0 - 2.0 * d2 / 3;
		mc = mb + d2;
		ma = mc + d1;
		break;
	default:
		ma = 0;
		mb = 0;
		mc = 0;
		break;
	}

	svm->m[0] = ma;
	svm->m[1] = mb;
	svm->m[2] = mc;
}

void modulator(SVM_t * svm, const double Ualpha, const double Ubeta, SVM_mode_t mode)
{
	svm->UAB[0] = Ualpha;
	svm->UAB[1] = Ubeta;

	double tabc[3] = {0}; // Initialize tabc array to zero

	calc_tabc(tabc, svm->UAB);
	
	//svm->sector = determine_sector_6N(tabc);
	svm->sector = determine_sector_12N(tabc);

	calc_svm_duty(svm, tabc, mode);
}