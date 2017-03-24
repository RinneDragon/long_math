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
