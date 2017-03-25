#include <iostream>
#include <string>
#include <vector>

#include "LNum.h"
#include "ILNum.h"
#include "RNum.h"
//#include "Polynome.h"

int main()
{
	LNum a;
	int b;
	cin >> a >> b;
	cout << MUL_ND_N(a, b);
	system("pause");
	return 0;
}