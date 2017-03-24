#include <iostream>
#include <string>
#include <vector>

#include "LNum.h"
#include "ILNum.h"
#include "RNum.h"
//#include "Polynome.h"

int main()
{
	LNum a, b;
	cin >> a >> b;
	cout << SUB_NN_N(a, b);
	system("pause");
	return 0;
}