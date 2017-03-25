#include "Polynome.h"

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

// P-4
Polynome MUL_Pxk_P(Polynome& pol, int k)
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
        while (k-- > 0) res.coefficients.insert(res.coefficients.begin(), Rzero);
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
