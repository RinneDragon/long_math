#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include "Ordinal.h"
using namespace std;

struct LNum {
    // Метод len, возвращающий длину числа
    int len();
    int len() const;
    void setDigits(string str);
    // Значение числа хранится перевёрнутым. (123 хранится как 3 -> [0], 2 -> [1], 1 -> [2])
    vector<int> digits;
};

ostream& operator<<(ostream&, LNum&);
istream& operator >> (istream&, LNum&);
bool operator==(LNum&, int);
bool operator==(int, LNum&);
bool operator!=(LNum&, int);
bool operator!=(int, LNum&);
// N-1
Ordinal COM_NN_D(LNum const&, LNum const&);
// N-2
bool NZER_N_B(LNum const&);
// N-3
LNum ADD_1N_N(LNum const&);
// N-4
LNum ADD_NN_N(LNum const&, LNum const&);
// N-5
LNum SUB_NN_N(LNum const&, LNum const&);
// N-6
LNum MUL_ND_N(LNum const&, int const);
// N-7
LNum MUL_Nk_N(LNum const&, int const);
// N-8
LNum MUL_NN_N(LNum const&, LNum const&);
// N-9
LNum SUB_NDN_N(LNum const&, LNum const&, int const);
// N-10
LNum DIV_NN_N(LNum const&, LNum const&);
// N-11
LNum MOD_NN_N(LNum const&, LNum const&);
// N-12
LNum GCF_NN_N(LNum const&, LNum const&);
// N-13
LNum LCM_NN_NN(LNum const&, LNum const&);
