#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include "LNum.h"

using namespace std;

struct ILNum {
	int len();
    int len() const;
	void setDigits(string str);
    // Отрицательно ли число
	bool minus;
    // Натуральная часть числа
	LNum nPart;
};

istream& operator>>(istream&, ILNum&);
ostream& operator<<(ostream&, ILNum&);
LNum ABS_Z_N(ILNum const&);
int POZ_Z_D(ILNum const&);
ILNum MUL_ZM_Z(ILNum const&);
ILNum TRANS_N_Z(LNum const&);
LNum TRANS_Z_N(ILNum const&);
ILNum ADD_ZZ_Z(ILNum const&, ILNum const&);
ILNum SUB_ZZ_Z(ILNum const&, ILNum const&);
ILNum MUL_ZZ_Z(ILNum const&, ILNum const&);
ILNum DIV_ZZ_Z(ILNum const&, ILNum const&);
ILNum MOD_ZZ_Z(ILNum const&, ILNum const&);
