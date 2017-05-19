#include "RNum.h"

// Выводит дробь в виде `a/b`
ostream& operator<<(ostream& os, RNum& ex) 
{
	if (ex.den.len() == 1 && ex.den.digits[0] == 1)
		os << ex.num;
	else
		os << ex.num << '/' << ex.den;
    return os;
}

// Считывает дробь вида `a/b`
istream& operator>>(istream& is, RNum& ex)
{
    string s;
    string s1, s2;
    getline(is, s);
    int n = s.find('/', 0);
    s1 = s.substr(0, n);
    s2 = (n != -1 ? s.substr(n + 1, s.length() - n) : "1");
    ex.num.setDigits(s1);
    ex.den.setDigits(s2);
    return is;
}

RNum operator+(RNum const& l, RNum const& r) { return ADD_QQ_Q(l, r); }
RNum operator-(RNum const& l, RNum const& r) { return SUB_QQ_Q(l, r); }
RNum operator*(RNum const& l, RNum const& r) { return MUL_QQ_Q(l, r); }
RNum operator/(RNum const& l, RNum const& r) { return DIV_QQ_Q(l, r); }

//Q-1
RNum RED_Q_Q(RNum const& numb)
{
	LNum NOD = GCF_NN_N(ABS_Z_N(numb.num), numb.den);
	RNum shortNum;
	shortNum.den = DIV_NN_N(numb.den, NOD);
	shortNum.num = DIV_ZZ_Z(numb.num, TRANS_N_Z(NOD)); 
	return shortNum;
}

//Q-2
bool INT_Q_B(RNum const& num) {
	return num.den.digits == vector<int>({ 1 });
}

//Q-3
RNum TRANS_Z_Q(ILNum const& num) {
	return{ num, { vector<int>({ 1 }) } };
}

//Q-4
ILNum TRANS_Q_Z(RNum const& num) {
	return num.num;
}


//Q-5
RNum ADD_QQ_Q(RNum const& a, RNum const& b) //сложение дробей LCM_NN_N MUL_ZZ_Z ADD_ZZ_Z
{
	RNum c;
	c.den = LCM_NN_N(a.den, b.den);
	c.num = ADD_ZZ_Z(MUL_ZZ_Z(a.num, TRANS_N_Z(DIV_NN_N(c.den, a.den))), MUL_ZZ_Z(b.num, TRANS_N_Z(DIV_NN_N(c.den, b.den))));
	return c;
}

//Q-6
RNum SUB_QQ_Q(RNum const& a, RNum const& b)
{
	RNum c = b;
	c.num.negative = !b.num.negative;
	return ADD_QQ_Q(a, c);
}

//Q-7
RNum MUL_QQ_Q(RNum const& a, RNum const& b)
{
	RNum c;
	c.den = MUL_NN_N(a.den, b.den);
	c.num = MUL_ZZ_Z(a.num, b.num);
	return c;
}

//Q-8
RNum DIV_QQ_Q(RNum const& a, RNum const& b) // вроде все
{
	ILNum num;
	LNum den = MUL_NN_N(a.den, b.num.nPart);
	num.negative = a.num.negative ^ b.num.negative;
	num.nPart = MUL_NN_N(a.num.nPart, b.den);
	return RED_Q_Q({ num, den });
}
