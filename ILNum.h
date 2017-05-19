#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iterator>

#include "LNum.h"
#include "Signum.h"

using namespace std;

struct ILNum {
	int len();
    int len() const;
	void setDigits(string str);
    // Отрицательно ли число
	bool negative;
    // Натуральная часть числа
	LNum nPart;
    ILNum() = default;
    ILNum(bool negative, LNum const& part)
        : negative(negative),
          nPart(part) {
    }
    explicit ILNum(int const& num) {
        if (num < 0) {
            negative = true;
            nPart = LNum(-num);
        } else {
            negative = false;
            nPart = LNum(num);
        }
    }
    explicit ILNum(LNum const& num)
        : negative(false),
          nPart(num) {
    }
    ILNum(ILNum const& other) = default;
    ILNum(ILNum&& other) noexcept = default;
    ~ILNum() = default;
    ILNum& operator=(ILNum const& other) = default;
    ILNum& operator=(ILNum&& other) noexcept = default;
};

istream& operator>>(istream&, ILNum&);
ostream& operator<<(ostream&, ILNum&);
ILNum operator+ (ILNum const& l, ILNum const& r);
ILNum operator- (ILNum const& l, ILNum const& r);
ILNum operator* (ILNum const& l, ILNum const& r);
ILNum operator/ (ILNum const& l, ILNum const& r);
ILNum operator% (ILNum const& l, ILNum const& r);
LNum ABS_Z_N(ILNum const&);
Signum POZ_Z_D(ILNum const&);
ILNum MUL_ZM_Z(ILNum const&);
ILNum TRANS_N_Z(LNum const&);
LNum TRANS_Z_N(ILNum const&);
ILNum ADD_ZZ_Z(ILNum const&, ILNum const&);
ILNum SUB_ZZ_Z(ILNum const&, ILNum const&);
ILNum MUL_ZZ_Z(ILNum const&, ILNum const&);
ILNum DIV_ZZ_Z(ILNum const&, ILNum const&);
ILNum MOD_ZZ_Z(ILNum const&, ILNum const&);
