#include "LNum.h"
#include <random>
#include <ctime>
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

bool operator==(LNum const& l, LNum const& r) {
    return COM_NN_D(l, r) == Ordinal::EQ;
}

bool operator!=(LNum& num, int n){
   return !operator==(num, n); 
}
	
bool operator!=(int n, LNum& num){
   return !operator==(num, n); 
}

LNum operator+(LNum const& l, LNum const& r) { return ADD_NN_N(l, r); }
LNum operator-(LNum const& l, LNum const& r) 
{
	if (COM_NN_D(l, r) == Ordinal::LT) return SUB_NN_N(r, l);
	else return SUB_NN_N(l, r);
}
LNum operator*(LNum const& l, LNum const& r) { return MUL_NN_N(l, r); }
LNum operator/(LNum const& l, LNum const& r) { return DIV_NN_N(l, r); }
LNum operator%(LNum const& l, LNum const& r) { return MOD_NN_N(l, r); }


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
	for(int i = 0; i < digits.size(); ++i)
		digits[i] = str [str.length() - 1 - i] - '0';
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
            return true;
    return false;
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
//N-10
LNum DIV_NN_Dk(LNum const& a, LNum const& b)
{
	LNum k;
	k.setDigits("0");

	if (!NZER_N_B(b) || (COM_NN_D(a, b) == Ordinal::LT))
	{
		return k;
	}

	LNum c = a;
	int n = a.len() - b.len();
	LNum mulB = MUL_Nk_N(b, n);

	if (COM_NN_D(a, mulB) == Ordinal::LT)
	{
		--n;
		mulB = MUL_Nk_N(b, n);
	}

	while (COM_NN_D(c, mulB) != Ordinal::LT)
	{
		c = SUB_NN_N(c, mulB);
		k = ADD_1N_N(k);
	}

	return MUL_Nk_N(k, n);
}
//N-11
LNum DIV_NN_N(LNum const& a, LNum const& b)
{
	LNum t;
	t.setDigits("0");

	if (!NZER_N_B(b) || (COM_NN_D(a, b) == Ordinal::LT))
	{
		return t;
	}

	LNum c = a;
	while (COM_NN_D(c, b) != Ordinal::LT)
	{
		t = ADD_NN_N(t, DIV_NN_Dk(c, b));
		c = SUB_NN_N(c, MUL_NN_N(DIV_NN_Dk(c, b), b));
	}
	return t;
}
//N-12
LNum MOD_NN_N(LNum const& a, LNum const& b)
{

	if (!NZER_N_B(b))
		return { vector<int>({ 0 }) };
	if (COM_NN_D(a, b) == Ordinal::LT) return a;
	return SUB_NN_N(a, MUL_NN_N(DIV_NN_N(a, b), b));
}

//N-13
LNum GCF_NN_N(LNum const& a, LNum const& b)
{
	LNum t;
	t.setDigits("0");

	if (!NZER_N_B(b))
	{
		return a;
	}
	LNum a1, b1, c;
	switch (COM_NN_D(a, b))
	{
	case Ordinal::LT:
		a1 = b;
		b1 = a;
		break;
	case Ordinal::GT:
		a1 = a;
		b1 = b;
		break;
	default:
		return a;
	}
	while (NZER_N_B(b1))
	{
		c = b1;
		b1 = MOD_NN_N(a1, b1);
		a1 = c;
	}
	return a1;
}
//N-14
LNum LCM_NN_N(LNum const& a, LNum const& b)
{
    return DIV_NN_N(MUL_NN_N(a, b), GCF_NN_N(a, b));
}
LNum power(LNum const& a, LNum const& b)
{
	auto y = b;
	auto mul = a;
	LNum res = LNum(1);
	while (NZER_N_B(y))
	{
		if (y % LNum(2) == 1) res = res*mul;
		mul = mul * mul;
		y = y / LNum(2);
	}
	return res;
}

bool isPrimeNum(LNum const& N)
{
	srand(time(nullptr));
	//разложение числа на вид : n-1 = 2^(s)*t, t % 2 = 1
	if (COM_NN_D(N, LNum(2)) != Ordinal::GT) return true;
	LNum n = N - LNum(1), s = LNum(0), t;
	//cout << endl
		 //<< "Entering first cycle" << endl;
	while (n % LNum(2) == LNum(0))
	{
		n = n / LNum(2);
		s = s + LNum(1);
		//cout << "Iteration with n = " << n << "; s = " << s << endl;
	}
	t = n;
	//cout << s << ' ' << t << endl;
	LNum k = LNum(3), a, x;
	//cout << "Entering second cycle" << endl;
	while (k != LNum(0))
	{
		a = LNum(rand()) % (N - LNum(3)) + LNum(2);
		x = power(a, t) % N;
		k = k - LNum(1);
		//cout << "Started with a = " << a << "; x = " << x << "; k = " << k << endl;
		if ((x == LNum(1) || (x == (N - LNum(1))))) continue;
		x = power(a, t);
		/*cout << "x changed to " << x << endl
			 << "Entering inner cycle ";*/
		for (LNum p = LNum(0);COM_NN_D(p, s) == Ordinal::LT; p = p + LNum(1))
		{			
			if ((x % N == 1) || (x % N == (N - LNum(1)))) return true;
			//cout << "x start = " << x << endl;
			x = x * x;
			//cout << "x end = " << x << endl;
		}
		return false;
	}
	return true;
}



LNum RhoPollard(LNum const& N)
{
	if (isPrimeNum(N)) return N;
	srand(time(nullptr));
	vector<LNum> mas;
	LNum d;
	do {
		LNum x = LNum(rand()) % N;
		mas.push_back(x);

		bool cycle = false;

		while (!cycle)
		{
			x = (x*x + LNum(1)) % N;
			mas.push_back(x);
			for (size_t i = 0; i < mas.size() - 1; i++)
				if (mas.back() == mas.at(i)) cycle = true;
		}
		mas.pop_back();
		for (size_t i = 1; i < mas.size(); i++)
		{
			for (size_t j = 0; j < mas.size() - 1; j++)
			{
				d = GCF_NN_N(mas.at(i) - mas.at(j), N);
				if ( (d != LNum(1)) && (d != N) && (isPrimeNum(d))) return d;
			}
		}
		mas.clear();		
	} while ((d == LNum(1)) || (d == N) || (!isPrimeNum(d)));
	return d;
	
}

vector<LNum> factRhoPollard(LNum const& N)
{
	LNum x, n = N;
	vector<LNum> mas;
	do
	{
		x = RhoPollard(n);
		mas.push_back(x);
		n = n/x;
	} while (!isPrimeNum(n));
	mas.push_back(n);
	return mas;
}