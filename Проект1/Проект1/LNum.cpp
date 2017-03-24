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

bool operator==(LNum& num, int n){
   int i = 0;
   for(; i < num.len() && n; ++i, n /= 10)
      if(n % 10 != num.digits[i])
	 return false;
   return i == num.len() && !n;
}

bool operator==(int n, LNum& num){
   return operator==(num, n);
}
	 
bool operator!=(LNum& num, int n){
   return !operator==(num, n); 
}
	
bool operator!=(int n, LNum& num){
   return !operator==(num, n); 
}	 
	
int LNum::len()
{
	return digits.size();
}

void LNum::setDigits(string str) 
{
	digits.reserve(str.length());
	for (int i = str.length() - 1; i >= 0; --i)
		digits.push_back(str[i] - '0');
}

bool NZER_N_B(LNum& num)
{
	for (int i = 0; i < num.len(); ++i)
		if (num.digits[i])
			return false;
	return true;
}

//N-1
Ordinal COM_NN_D(LNum& num1, LNum& num2)
{
	int l1 = num1.len();
	int l2 = num2.len();
	if (l1>l2) return Ordinal::GT;
	if (l1<l2) return Ordinal::LT;
	--l1;
	while ((l1>-1) && (num1.digits[l1] == num2.digits[l1])) --l1;
	if (l1 == -1) return Ordinal::EQ;
	if (num1.digits[l1]>num2.digits[l1]) return Ordinal::GT;
	 return Ordinal::LT;
}

LNum ADD_1N_N(LNum& a) {
	LNum b;
	int l = a.len();
	b.digits.reserve(l + 1);
	bool overflow = true;
	for (int i = 0; i < l; ++i)
	{
		b.digits.push_back(a.digits[i] + overflow);
		overflow = b.digits[i] > 9;
		b.digits[i] %= 10;
	}
	if (overflow)
		b.digits.push_back(1);
	return b;
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

