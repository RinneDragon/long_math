#pragma once

#include "LNum.h"
#include "ILNum.h"
#include "RNum.h"
#include "Ordinal.h"
#include "Signum.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	LNum N;
	cin >> N;
	vector<LNum> mas = factRhoPollard(N);
	cout << "Factorization of RhoPollard: ";
	for (size_t i = 0; i < mas.size(); i++)
	{
		cout << mas.at(i) << ' ';
	}
	return EXIT_SUCCESS;
}