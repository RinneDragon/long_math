#include <iostream>
#include <string>
#include <vector>

#include "LNum.h"
#include "ILNum.h"
#include "RNum.h"
//#include "Polynome.h"

int main()
{
	ILNum a,b;
	//int b;
	cin >> a >> b;
	cout << SUB_ZZ_Z(a, b);
	system("pause");
	return 0;
}