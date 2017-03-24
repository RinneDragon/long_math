#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include "LNum.h"

using namespace std;

struct ILNum {
	int len();
	void setDigits(string str);
    // Отрицательно ли число
	bool minus;
    // Натуральная часть числа
	LNum nPart;
};

istream& operator>>(istream&, ILNum&);
ostream& operator<<(ostream&, ILNum&);
LNum ABS_Z_N(ILNum&);
int POZ_Z_D(ILNum&);
ILNum MUL_ZM_Z(ILNum&);
ILNum TRANS_N_Z(LNum&);
LNum TRANS_Z_N(ILNum&);
ILNum ADD_ZZ_Z(ILNum&, ILNum&);
ILNum SUB_ZZ_Z(ILNum&, ILNum&);
ILNum MUL_ZZ_Z(ILNum&, ILNum&);
ILNum DIV_ZZ_Z(ILNum&, ILNum&);
ILNum MOD_ZZ_Z(ILNum&, ILNum&);
