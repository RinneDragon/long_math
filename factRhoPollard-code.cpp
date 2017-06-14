#pragma once

#include "LNum.h"
#include "ILNum.h"
#include "RNum.h"
#include "Ordinal.h"
#include "Signum.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

//���������� � �������
LNum power(LNum const&, LNum const&);
//�������� �� �������� ����� � ������� ����� �������-������
bool isPrimeNum(LNum const&);
//����������� �������� �������� ����� ��� ����������� ������ �����, ���� ��� �������
LNum RhoPollard(LNum const&);
//������ ���������� �� ������� ��������� ����� � ��������� ���� �������� � ������
vector<LNum> factRhoPollard(LNum const& N);

int main(int argc, char** argv) {

	//����� ������ ������������� ������ ������������ ����� ��-������� ��������

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
	//���������� ����� �� ��� : n-1 = 2^(s)*t, t % 2 = 1
	if (COM_NN_D(N, LNum(2)) != Ordinal::GT) return true;
	LNum n = N - LNum(1), s = LNum(0), t;

	while (n % LNum(2) == LNum(0))
	{
		n = n / LNum(2);
		s = s + LNum(1);
	}
	t = n;

	LNum k = LNum(3), a, x;
	// ��� �� ��������� �������� �������� �, ���� ����� ������������� ��, ������� true
	while (k != LNum(0))
	{
		a = LNum(rand()) % (N - LNum(3)) + LNum(2);
		x = power(a, t) % N;
		k = k - LNum(1);

		if ((x == LNum(1) || (x == (N - LNum(1))))) continue;
		x = power(a, t);

		for (LNum p = LNum(0); COM_NN_D(p, s) == Ordinal::LT; p = p + LNum(1))
		{
			if ((x % N == 1) || (x % N == (N - LNum(1)))) return true;
			x = x * x;

		}
		return false;
	}
	return true;
}



LNum RhoPollard(LNum const& N)
{
	//��������� ����� �� ��������: �� - ���������� ���� �����, ��� - ��������� ����� �������� �� ��� ���, ���� �� ������ ������� ��������
	if (isPrimeNum(N)) return N;
	srand(time(nullptr));
	vector<LNum> mas;
	LNum d;
	do {
		LNum x = LNum(rand()) % N;
		mas.push_back(x);

		bool cycle = false;

		//��������� ������, ���� ������������������ �� ����������
		while (!cycle)
		{
			//��� ���������� ����� ������� x*x+1
			x = (x*x + LNum(1)) % N;
			mas.push_back(x);
			for (size_t i = 0; i < mas.size() - 1; i++)
				if (mas.back() == mas.at(i)) cycle = true;
		}
		mas.pop_back();

		//��������� ��������� ��� ���� ����� �� ��� � ���������� ���������, ���� ��� ������ �� ������ 1 ��� c����� �����
		for (size_t i = 1; i < mas.size(); i++)
		{
			for (size_t j = 0; j < mas.size() - 1; j++)
			{
				d = GCF_NN_N(mas.at(i) - mas.at(j), N);
				if ((d != LNum(1)) && (d != N) && (isPrimeNum(d))) return d;
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
	cout << "factorization: ";
	do
	{
		x = RhoPollard(n);
		mas.push_back(x);
		n = n / x;
	} while (!isPrimeNum(n));
	mas.push_back(n);
	return mas;
}