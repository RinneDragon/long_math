#include "LNum.h"

// Здесь должны быть объявления функций, описанные в LNum.h для натуральных чисел,
// Пример такой функции приведён снизу. Подробное описание функций ищите на сайте Позднякова.
// Примечание: obj.digits - хранит число в перевёрнутом виде.

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, LNum& a)
{
	for (auto it = a.digits.rbegin(); it != a.digits.rend(); ++it)
		os << *it;
	return os;
}

// Перегрузка оператора ввода
istream& operator>>(istream& is, LNum& a)
{
	string s;
	getline(is, s);
	a.setDigits(s);
	return is;
}

bool NZER_N_B(LNum& num)
{
	for (int i = 0; i < num.len(); ++i)
		if (num.digits[i])
			return false;
	return true;
}

int LNum::len()
{
	return digits.size();
}

void LNum::setDigits(string& str) 
{
	digits.reserve(str.length());
	for (int i = str.length() - 1; i >= 0; --i)
		digits.push_back(str[i] - '0');
}
//N-1
Ordinal COM_NN_D(LNum& num1, LNum& num2)
{
	int l1 = num1.length();
	int l2 = num2.length();
	if (l1>l2) return Ordinal::GT;
	if (l1<l2) return Ordinal::LT;
	--l1;
	while ((l1>-1) && (num1.digits[l1] == num2.digits[l1])) --l1;
	if (l1 == -1) return Ordinal::EQ;
	if (num1.digits[l1]>num2.digits[l1]) return Ordinal::GT;
	if (num1.digits[l1]<num2.digits[l1]) return Ordinal::LT;
}

//N-3
LNum ADD_1N_N(LNum& numb)
{
	numb.digits[1] += 1;
	if (numb.digits[1] == 10)
	{
		numb.digits[1] = 0;
		bool overflow = true;
	}
	int i = 0;
	while ((overflow = true) && (i<(numb.length() - 1)))
	{
		i++;
		numb.digits[i] += 1;
		if (numb.digits[i]<10)
		{
			overflow = false;
		}
		else
		{
			numb.digits[i] = 0;
		}

	}
	if (overflow = true)
	{
		numb.bush_back(1);
	}
	return numb;
}

LNum ADD_NN_N(LNum& a, LNum& b){
	LNum c;
	int l1 = a.len();
	int l2 = b.len();
	int minLen = l1 > l2 ? l2 : l1;
	int maxLen = l1 > l2 ? l1 : l2;
	c.digits.reserve(maxLen + 1);
	bool overflow = false;
	for(int i = 0; i < maxLen; ++i)
	{
		c.digits.push_back((i < minLen ? a.digits[i] + b.digits[i] : (l1 > l2 ? a.digits[i] : b.digits[i])) + overflow);
		overflow = c.digits[i] > 9;
		c.digits[i] %= 10;
	}
	if (overflow)
		c.digits.push_back(1);
	return c;
}

