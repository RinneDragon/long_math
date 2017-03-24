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
RNum RED_Q_Q(RNum& numb) // функция сокращения дробей ABS_Z_N GCF_NN_N DIV_ZZ_Z DIV_NN_N
{
	LNum NOD = GCF_NN_N(ABS_Z_N(numb.num), numb.den);
	RNum shortNum;
	shortNum.den = DIV_NN_N(numb.den, NOD);
	shortNum.num = DIV_ZZ_Z(numb.num, NOD);
	return shortNum;
}

RNum DIV_QQ_Q(RNum& numb1, RNum& numb2) // функция деления дробей MUL_ZZ_Z MUL_NN_N
{
	RNum numb3;
	numb3.num.minus = numb1.num.minus^numb2.num.minus;
	numb3.num.nPart = MUL_NN_N(numb1.num.nPart, numb2.den);
	numb3.den = MUL_NN_N(numb1.den, numb2.num.nPart);
	return numb3;
}

RNum ADD_QQ_Q(RNum& numb1, RNum& numb2) //сложение дробей LCM_NN_N MUL_ZZ_Z ADD_ZZ_Z DIV_
{
	RNum numb3;
	LNum numb1_2 = DIV_NN_N(LCM_NN_N(numb1.den, numb2.den), numb1.den);
	LNum numb2_2 = DIV_NN_N(LCM_NN_N(numb1.den, numb2.den), numb2.den);
	numb3.den = LCM_NN_N(numb1.den, numb2.den);
	numb3.num = ADD_ZZ_Z(MUL_ZZ_Z(numb1.num, numb1_2), MUL_ZZ_Z(numb2.num, numb1_2));
	return numb3;
}
/*RNum DIV_QQ_Q(RNum& a, RNum& b){
    RNum c;
    c.num.minus = a.num.minus ^ b.num.minus;
    c.num.nPart = MUL_NN_N(a.num.nPart, b.den);
    c.den = MUL_NN_N(a.den, b.num.nPart);
    return c;
}*/
