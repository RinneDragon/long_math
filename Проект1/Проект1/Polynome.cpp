#include "Polynome.h"
#include <algorithm>

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

// Умножение полинома на x в степени k
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

//Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей
RNum FAC_P_Q(Polynome const& poly)
{
	int count = poly.coefficients.size();
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

//Умножение многочлена на рациональное число
Polynome MUL_PQ_P(Polynome const& poly, RNum const& num)
{
	Polynome res;
	for (int i = 0; i < poly.coefficients.size(); i++)
	{
		res.coefficients[i] = MUL_QQ_Q(poly.coefficients[i], num);
	}
	return res;
}

//Суммирование полиномов
Polynome ADD_PP_P(Polynome const&pol1, Polynome const& pol2)
{
	Polynome sum, poly1 = pol1, poly2 = pol2;

	if (poly1.coefficients.size() < poly2.coefficients.size())
		swap(poly1, poly2);

	int dem = poly1.coefficients.size() - poly2.coefficients.size(), i = 0;

	for (i = 0; i < min(poly1.coefficients.size(), poly2.coefficients.size()); i++)
	{
		sum.coefficients.push_back(ADD_QQ_Q(poly1.coefficients[i], poly2.coefficients[i]));
	}

	for (int f = 0; f < dem; f++)
	{
		sum.coefficients.push_back(poly1.coefficients[i++]);
	}

	return sum;
}

//Вычитание полиномов
Polynome SUB_PP_P(Polynome const&pol1, Polynome const&pol2)
{
	Polynome sub, poly1 = pol1, poly2 = pol2;

	if (poly1.coefficients.size() < poly2.coefficients.size())
		swap(poly1, poly2);

	int dem = poly1.coefficients.size() - poly2.coefficients.size(), i = 0;

	for (i = 0; i < min(poly1.coefficients.size(), poly2.coefficients.size()); i++)
	{
		sub.coefficients.push_back(SUB_QQ_Q(poly1.coefficients[i], poly2.coefficients[i]));
	}

	for (int f = 0; f < dem; f++)
	{
		sub.coefficients.push_back(poly1.coefficients[i++]);
	}

	return sub;
}

//Степень многочлена 
int DEG_P_N(Polynome const& poly)
{
	int ma = 0;
	for (int i = poly.coefficients.size() - 1; i >= 0; i--)
	{
		if (poly.coefficients[i].num.nPart.len() != 0)
		{
			ma = i;
			break;
		}
	}

	return ma;
}

//Старший коэффициент многочлена
RNum LED_P_Q(Polynome  const&poly)
{
	return poly.coefficients[DEG_P_N(poly)];
}


//Умножение многочленов
Polynome MUL_PP_P(Polynome const& poly1, Polynome const& poly2) {
	Polynome mul, maxpoly = poly1, minpoly = poly2, service;

	if (poly1.coefficients.size() < poly2.coefficients.size())
		swap(maxpoly, minpoly);

	for (int f = 0; f < minpoly.coefficients.size(); f++)
	{
		service = MUL_PQ_P(maxpoly, minpoly.coefficients[f]);
		service = MUL_Pxk_P(service, (minpoly.coefficients.size() - 1) - f);
		mul = ADD_PP_P(service, mul);
	}
	return mul;
}


//Частное от деления многочлена на многочлен при делении с остатком
Polynome DIV_PP_P(Polynome const& poly1, Polynome const& poly2) {
	Polynome div, maxpoly = poly1, minpoly = poly2, service;
	int DEGminpoly = DEG_P_N(minpoly);

	if (poly1.coefficients.size() < poly2.coefficients.size())
		swap(maxpoly, minpoly);

	div = MUL_Pxk_P(div, DEG_P_N(maxpoly) - DEGminpoly);

	for (int f = maxpoly.coefficients.size() - 1; f >= DEGminpoly; f--)
	{
		div.coefficients[f] = DIV_QQ_Q(maxpoly.coefficients[f], minpoly.coefficients[minpoly.coefficients.size() - 1]);

		service = MUL_PQ_P(minpoly, minpoly.coefficients[f]);
		service = MUL_Pxk_P(service, f - DEGminpoly);
		maxpoly = SUB_PP_P(maxpoly, service);
	}

	return div;
}

//Остаток от деления многочлена на многочлен при делении с остатком
Polynome MOD_PP_P(Polynome const& poly1, Polynome const& poly2)
{
	Polynome mod, maxpoly = poly1, minpoly = poly2, service;
	int DEGminpoly = DEG_P_N(minpoly);

	if (poly1.coefficients.size() < poly2.coefficients.size())
		swap(maxpoly, minpoly);

	mod = MUL_Pxk_P(mod, DEGminpoly - 1);

	for (int f = maxpoly.coefficients.size() - 1; f >= DEGminpoly; f--)
	{
		service = MUL_PQ_P(minpoly, minpoly.coefficients[f]);
		service = MUL_Pxk_P(service, f - DEGminpoly);
		maxpoly = SUB_PP_P(maxpoly, service);
	}
	for (int i = DEGminpoly - 1; i >= 0; i--)
	{
		mod.coefficients[i] = maxpoly.coefficients[i];
	}
	return mod;
}

//НОД многочленов
// DEG_P_N - степень многочлена
//MOD_PP_P - Остаток от деления многочлена на многочлен при делении с остатком
Polynome GCF_PP_P(Polynome const& poly1, Polynome const& poly2) {
	Polynome * nod = new Polynome[min(DEG_P_N(poly1), DEG_P_N(poly2))];
	
	



	delete[]nod;

	Polynome res;

	return res;
}

//Производная многочлена
Polynome DER_P_P(Polynome const& poly)
{
	Polynome der;
	der = MUL_Pxk_P(der, DEG_P_N(poly) - 1);

	for (int f = DEG_P_N(poly); f > 0; f--)
	{
		RNum Rf;
		Rf.num.nPart.setDigits(std::to_string(f));
		Rf.den.setDigits("1");

		der.coefficients[f - 1] = ADD_QQ_Q(poly.coefficients[f], Rf);
	}
	return der;
}


Polynome NMR_P_P(Polynome const&, Polynome const&);
