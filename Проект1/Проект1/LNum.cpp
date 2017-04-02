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

int LNum::len() const
{
    return digits.size();
}

void LNum::setDigits(string str) 
{
	digits.resize(str.length());
	for (int i = str.length() - 1; i >= 0; --i)
		digits.push_back(str[i] - '0');
}

void clearZero(LNum& num) {
	while (num.len() > 1 && !num.digits[num.len() - 1])
		num.digits.pop_back();
}

//N-1
Ordinal COM_NN_D(LNum const& num1, LNum const& num2)
{
	int l1 = num1.len();
	int l2 = num2.len();
	if (l1>l2) return Ordinal::GT;
	if (l1<l2) return Ordinal::LT;
	while (--l1 + 1 && num1.digits[l1] == num2.digits[l1]);
	if (l1 == -1) return Ordinal::EQ;
	if (num1.digits[l1]>num2.digits[l1]) return Ordinal::GT;
	return Ordinal::LT;
}

// N-2
bool NZER_N_B(LNum const& num)
{
    for (int i = 0; i < num.len(); ++i)
        if (num.digits[i])
            return false;
    return true;
}

// N-3
LNum ADD_1N_N(LNum const& a) {
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

// N-4
LNum ADD_NN_N(LNum const& a, LNum const& b){
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

// N-5
LNum SUB_NN_N(LNum const& a, LNum const& b) {
	LNum c;
	if (COM_NN_D(a, b) == Ordinal::LT || COM_NN_D(a, b) == Ordinal::EQ) {
        c = { vector<int>({0}) };
        return c;
	}
	int l1 = a.len();
	int l2 = b.len();
	int minLen = l1 > l2 ? l2 : l1;
	int maxLen = l1 > l2 ? l1 : l2;
	c.digits.reserve(maxLen);
	int temp;
	bool overflow = false;
	for (int i = 0; i < minLen; ++i) {
		temp = a.digits[i] - b.digits[i] - overflow;
		if (temp < 0) {
			temp += 10;
			overflow = true;
		} else overflow = false;
		c.digits.push_back(temp);
	}
	for (int i = minLen; i < maxLen; ++i) {
		temp = a.digits[i] - overflow;
		if (temp < 0) {
			temp += 10;
			overflow = true;
		}
		else overflow = false;
		c.digits.push_back(temp);
	}
	clearZero(c);
	return c;
}

// N-6
LNum MUL_ND_N(LNum const& a, int const b) {
	LNum c;
	int l = a.len();
	c.digits.reserve(l + 1);
	c.digits.push_back(0);
	if (!b) return c;
	for (int i = 0; i < l; ++i)
	{
		int res = a.digits[i] * b + c.digits[i];
		c.digits[i] = res % 10;
		c.digits.push_back(res / 10);
	}
	clearZero(c);
	return c;
}

// N-7
LNum MUL_Nk_N(LNum const& num, int const k)
{
    LNum res = num;
    for (int i = 0; i < k; ++i)
        res.digits.insert(res.digits.begin(), 0);
    return res;
}

// N-8
LNum MUL_NN_N(LNum const& left, LNum const& right)
{
    LNum res = { vector<int>({ 0 }) };
    for (auto i = 0; i < right.len(); ++i)
    {
        // This one is pure so no copies
        LNum mul_res = MUL_ND_N(left, right.digits[i]);
        mul_res = MUL_Nk_N(mul_res, i);
        res = ADD_NN_N(res, mul_res);
    }
    return res;
}

// N-9
LNum SUB_NDN_N(LNum const& left, LNum const& right, int const dig)
{
    LNum subbed = MUL_ND_N(right, dig);
    if (COM_NN_D(left, subbed) == Ordinal::GT)
        return SUB_NN_N(left, subbed);
    LNum zero = { vector<int>({ 0 }) };
    return zero;
}

// N-14
//LNum LCM_NN_N(LNum& a, LNum& b)
//{
//    return DIV_NN_N(MUL_NN_N(a, b), GCF_NN_N(a, b));
//}
