#include "ILNum.h"

// Аналогично с LNum.h, задания на сайте Позднякова.

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, ILNum& a)
{
    if(a.minus)
        os << '-';
    for (auto it = a.nPart.digits.rbegin(); it != a.nPart.digits.rend(); ++it)
        os << *it;
    return os;
}

// Перегрузка оператора ввода
istream& operator>>(istream& is, ILNum& a)
{
    string s;
    getline(is, s);
    a.setDigits(s);
    return is;
}

void ILNum::setDigits(string str) 
{
    minus = str[0] == '-';
    nPart.digits.reserve(str.length() - minus);
    for (int i = str.length() - 1; i >= minus; --i)
        nPart.digits.push_back(str[i] - '0');
}

int ILNum::len()
{
    return nPart.len();
}

int ILNum::len() const
{
    return nPart.len();
}

//Z-1
LNum ABS_Z_N(ILNum const& a) {
	return a.nPart;
}

//Z-2
int POZ_Z_D(ILNum const& a) {
	if (!NZER_N_B(a.nPart)) return 0;
	else if (a.minus == true) return 1;
	else return 2;
}

//Z-3
ILNum MUL_ZM_Z(ILNum const& a) {
	ILNum c;
	c = a;
	c.minus = !a.minus;
	return c;
}

// Z-4
ILNum TRANS_N_Z(LNum const& num)
{
    return { false , num };
}

//Z-5
LNum TRANS_Z_N(ILNum const& num) {
	return num.nPart;
}

//Z-6
ILNum ADD_ZZ_Z(ILNum const& a, ILNum const& b) {
	if (a.minus ^ b.minus)
	{
		if (COM_NN_D(a.nPart,b.nPart) == Ordinal::GT)
			return{ a.minus, SUB_NN_N(a.nPart,b.nPart) };
		if (COM_NN_D(a.nPart, b.nPart) == Ordinal::LT)
			return{ b.minus, SUB_NN_N(b.nPart,a.nPart) };
		return{ false, { vector<int>({ 0 }) } };
	}
	return{ a.minus, ADD_NN_N(a.nPart,b.nPart) };
}
