#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include "RNum.h"

struct Polynome {
	vector<RNum> coefficients;
};

ostream& operator<<(ostream& os, Polynome& pl);
istream& operator >> (istream& is, Polynome& pl);

Polynome ADD_PP_P(Polynome const&, Polynome const&);
Polynome SUB_PP_P(Polynome const&, Polynome const&);
Polynome MUL_PQ_P(Polynome const&, RNum const&);
Polynome MUL_Pxk_P(Polynome const&, int const);
RNum LED_P_Q(Polynome const&);
int DEG_P_N(Polynome const&);
RNum FAC_P_Q(Polynome const&);
Polynome MUL_PP_P(Polynome const&, Polynome const&);
Polynome DIV_PP_P(Polynome const&, Polynome const&);
Polynome MOD_PP_P(Polynome const&, Polynome const&);
Polynome GCF_PP_P(Polynome const&, Polynome const&);
Polynome DER_P_P(Polynome const&, Polynome const&);
Polynome NMR_P_P(Polynome const&, Polynome const&);

const Polynome operator%(const Polynome& left, const Polynome& right) {
	return MOD_PP_P(left, right);
}