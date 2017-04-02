#include "Polynome.h"
#include <algorithm>
#include <stdarg.h>

ostream& operator<<(ostream& os, Polynome& pl)
{
	bool first = true;
	for (int i = pl.coefficients.size() - 1; i >= 0; --i)
	{
		RNum& curCoeff = pl.coefficients[i];
		if (!NZER_N_B(curCoeff.num.nPart))
		{
			if (!first)
				cout << ' ' << (curCoeff.num.minus ? '-' : '+') << ' ';
			else if (curCoeff.num.minus)
				cout << '-';
			if (curCoeff.den.len() == 1 && curCoeff.den.digits[0] == 1)
				os << curCoeff.num.nPart;
			else
				os << curCoeff.num.nPart << '/' << curCoeff.den;
			if (i)
				cout << "x^" << i;
			first = false;
		}
	}
	return os;
}

istream& operator>>(istream& is, Polynome& pl)
{
	int n;
	cout << "Input degree: ";
	cin >> n;
	cin.get();
	cout << "Input " << ++n << " coefficients" << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << "x^" << n - i - 1 << ": ";
		RNum buf;
		cin >> buf;
		pl.coefficients.push_back(move(buf));
	}
	reverse(pl.coefficients.begin(), pl.coefficients.end());
	return is;
}

//Суммирование полиномов
//P-1 @solodov
Polynome ADD_PP_P(Polynome const&pol1, Polynome const& pol2)
{
	Polynome sum, poly1 = pol1, poly2 = pol2;
	sum.coefficients.resize(max(DEG_P_N(poly1), DEG_P_N(poly2)));

	if (DEG_P_N(poly1) < DEG_P_N(poly2))
		swap(poly1, poly2);

	int i = 0;

	for (i = 0; i <= DEG_P_N(poly2); i++)
	{
		sum.coefficients[i] = ADD_QQ_Q(poly1.coefficients[i], poly2.coefficients[i]);
	}

	for (int f = i; f <= DEG_P_N(poly1); f++)
	{
		sum.coefficients[f] = poly1.coefficients[f];
	}

	return sum;
}

//Вычитание полиномов
//P-2 @solodov
Polynome SUB_PP_P(Polynome const&pol1, Polynome const&pol2)
{
	Polynome sub, poly1 = pol1, poly2 = pol2;
	sub.coefficients.resize(max(DEG_P_N(poly1), DEG_P_N(poly2)));

	if (DEG_P_N(poly1) < DEG_P_N(poly2))
		swap(poly1, poly2);

	int i = 0;

	for (i = 0; i <= DEG_P_N(poly2); i++)
	{
		sub.coefficients[i] = SUB_QQ_Q(poly1.coefficients[i], poly2.coefficients[i]);
	}

	for (int f = i; f <= DEG_P_N(poly1); f++)
	{
		sub.coefficients[f] = poly1.coefficients[f];
	}

	return sub;
}

//Умножение многочлена на рациональное число
//P-3 @solodov
Polynome MUL_PQ_P(Polynome const& poly, RNum const& num)
{
	Polynome res;
	res.coefficients.resize(DEG_P_N(poly));

	for (int i = 0; i <= DEG_P_N(poly); i++)
	{
		res.coefficients[i] = MUL_QQ_Q(poly.coefficients[i], num);
	}
	return res;
}

// Умножение полинома на x в степени k
//P-4 @anon
Polynome MUL_Pxk_P(Polynome const& pol, int const k)
{
	// Why would you?
	if (k == 0) return pol;
	// Making zero as it is needed in 2 branches
	LNum Lnzero = { vector<int>({ 1 }) };
	ILNum ILzero = { false, vector<int>({ 0 }) };
	RNum Rzero = { ILzero, Lnzero };
	// Non-const links are dirty
	auto res = pol;
	if (k >  0)
	{
		// Shifting left
		auto i = k;
		while (i-- > 0) res.coefficients.insert(res.coefficients.begin(), Rzero);
	}
	else
	{
		// This branch eats lesser coefs
		if (pol.coefficients.size() == -k)
			// No more pol
			res = { vector<RNum>({ Rzero }) };
		else
			res.coefficients.erase(res.coefficients.begin(), res.coefficients.begin() + -k);
	}
	return res;
}

//Старший коэффициент многочлена
//P-5 @solodov
RNum LED_P_Q(Polynome const& poly)
{
	return poly.coefficients[DEG_P_N(poly)];
}

//Степень многочлена. return -1 if every coord == 0;
//P-6 @solodov
int DEG_P_N(Polynome const& poly)
{
	for (int i = poly.coefficients.size() - 1; i >= 0; i--)
	{
		if (!NZER_N_B(poly.coefficients[i].num.nPart))
		{
			return i;
		}
	}

	//если нет ненулевых коэффициентов.
	return -1;
}

//Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей
//P-7 @solodov
RNum FAC_P_Q(Polynome const& poly)
{
	int count = DEG_P_N(poly);
	RNum res;
	res.den.setDigits("1");
	res.num.setDigits("0");

	if (count < 2)
	{
		res.num = poly.coefficients[0].num;
		res.den = poly.coefficients[0].den;
	}
	else if (count < 3)
	{
		res.num.nPart = GCF_NN_N(poly.coefficients[0].num.nPart, poly.coefficients[1].num.nPart);
		res.den = LCM_NN_N(poly.coefficients[0].den, poly.coefficients[1].den);
	}
	else
	{
		res.num.nPart = GCF_NN_N(poly.coefficients[0].num.nPart, poly.coefficients[1].num.nPart);
		res.den = LCM_NN_N(poly.coefficients[0].den, poly.coefficients[1].den);
		for (int i = 2; i < count; i++)
		{
			res.num.nPart = GCF_NN_N(res.num.nPart, poly.coefficients[i].num.nPart);
			res.den = LCM_NN_N(res.den, poly.coefficients[1].den);
		}
	}

	return res;
}

//Умножение многочленов
//P-8 @solodov
Polynome MUL_PP_P(Polynome const& poly1, Polynome const& poly2) {
	Polynome mul, maxpoly = poly1, minpoly = poly2, service;

	if (DEG_P_N(poly1) < DEG_P_N(poly2))
		swap(maxpoly, minpoly);

	for (int f = 0; f <= DEG_P_N(minpoly); f++)
	{
		service = MUL_PQ_P(maxpoly, minpoly.coefficients[f]);
		service = MUL_Pxk_P(service, f);
		mul = ADD_PP_P(service, mul);
	}
	return mul;
}

//Частное от деления многочлена на многочлен при делении с остатком
//P-9 @solodov
Polynome DIV_PP_P(Polynome const& poly1, Polynome const& poly2, Polynome &remainder) {
	Polynome div, maxpoly = poly1, minpoly = poly2, service;

	if (DEG_P_N(poly1) < DEG_P_N(poly2))
		swap(maxpoly, minpoly);

	int degMinPoly = DEG_P_N(minpoly), degMaxPoly = DEG_P_N(maxpoly);

	div.coefficients.resize(degMaxPoly);

	for (int powerofx = degMaxPoly; powerofx >= degMinPoly; powerofx--)
	{
		div.coefficients[powerofx - degMinPoly] = DIV_QQ_Q(maxpoly.coefficients[powerofx], minpoly.coefficients[degMinPoly]);

		service = MUL_PQ_P(minpoly, div.coefficients[powerofx - degMinPoly]);
		service = MUL_Pxk_P(service, powerofx - degMinPoly);
		maxpoly = SUB_PP_P(maxpoly, service);
	}

	remainder = maxpoly;
	return div;
}

//Остаток от деления многочлена на многочлен при делении с остатком
//P-10 @solodov
Polynome MOD_PP_P(Polynome const& poly1, Polynome const& poly2)
{
	Polynome remainder;
	DIV_PP_P(poly1, poly2, remainder);

	return remainder;
}

//НОД многочленов для рациональных чисел
//P-11 @solodov
Polynome GCF_PP_P(Polynome const& poly1, Polynome const& poly2) {
	Polynome divident = poly1, divider = poly2, tempo;

	while (DEG_P_N(divider) != 0 && !NZER_N_B(divider.coefficients[0].num.nPart))
	{
		tempo = divider;
		divider = MOD_PP_P(divident, divider);
		divident = tempo;
	}	

	return divident;
}

//Производная многочлена
//P-12 @solodov
Polynome DER_P_P(Polynome const& poly)
{
	int degPoly = DEG_P_N(poly);
	Polynome der;
	der.coefficients.resize(degPoly);

	for (int f = degPoly; f > 0; f--)
	{
		RNum Rf;
		Rf.num.nPart.setDigits(std::to_string(f));
		Rf.den.setDigits("1");

		der.coefficients[f - 1] = ADD_QQ_Q(poly.coefficients[f], Rf);
	}
	return der;
}


//Преобразование многочлена — кратные корни в простые
//P-13
Polynome NMR_P_P(Polynome const&, Polynome const&);

