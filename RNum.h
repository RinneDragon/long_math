#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include "LNum.h"
#include "ILNum.h"

using namespace std;
  
// Числа вида `a/b`, вводятся в отдельной строке.
struct RNum {
    // Числитель
    ILNum num;
    // Знаменатель
    LNum den;
    RNum() = default;
    RNum(ILNum const& num, LNum const& den)
        : num(num),
          den(den) {
    }
    RNum(RNum const& other) = default;
    RNum(RNum&& other) noexcept = default;
    ~RNum() = default;
    RNum& operator=(RNum const& other) = default;
    RNum& operator=(RNum&& other) noexcept = default;
};

ostream& operator<<(ostream&, RNum&);
istream& operator>> (istream&, RNum&);
RNum operator+ (RNum const& l, RNum const& r);
RNum operator- (RNum const& l, RNum const& r);
RNum operator* (RNum const& l, RNum const& r);
RNum operator/ (RNum const& l, RNum const& r);
RNum RED_Q_Q(RNum const&);
bool INT_Q_B(RNum const&);
RNum TRANS_Z_Q(ILNum const&);
ILNum TRANS_Q_Z(RNum const&);
RNum ADD_QQ_Q(RNum const&, RNum const&);
RNum SUB_QQ_Q(RNum const&, RNum const&);
RNum MUL_QQ_Q(RNum const&, RNum const&);
RNum DIV_QQ_Q(RNum const&, RNum const&);
