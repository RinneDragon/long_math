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

//возведение в степень
LNum power(LNum const&, LNum const&);
//проверка на простоту числа с помощью теста Миллера-Рабина
bool isPrimeNum(LNum const&);
//обнаружение простого делителя числа или возвращение самого числа, если оно простое
LNum RhoPollard(LNum const&);
//полное разложение на простые множители числа и занесение этих значений в массив
vector<LNum> factRhoPollard(LNum const& N);

int main(int argc, char** argv) {

	//здесь пример использования модуля факторизации чисел ро-методом Полларда

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
	//разложение числа на вид : n-1 = 2^(s)*t, t % 2 = 1
	if (COM_NN_D(N, LNum(2)) != Ordinal::GT) return true;
	LNum n = N - LNum(1), s = LNum(0), t;

	while (n % LNum(2) == LNum(0))
	{
		n = n / LNum(2);
		s = s + LNum(1);
	}
	t = n;

	LNum k = LNum(3), a, x;
	// тут мы проверяем свойства простоты и, если число удовлетворяет им, выводим true
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
	//проверяем число на простоту: да - возвращаем само число, нет - программа будет работать до тех пор, пока не найдёт простой делитель
	if (isPrimeNum(N)) return N;
	srand(time(nullptr));
	vector<LNum> mas;
	LNum d;
	do {
		LNum x = LNum(rand()) % N;
		mas.push_back(x);

		bool cycle = false;

		//заполняем массив, пока последовательность не зациклится
		while (!cycle)
		{
			//для вычислений взяли полином x*x+1
			x = (x*x + LNum(1)) % N;
			mas.push_back(x);
			for (size_t i = 0; i < mas.size() - 1; i++)
				if (mas.back() == mas.at(i)) cycle = true;
		}
		mas.pop_back();

		//перебором проверяем все пары чисел на НОД и возвращаем результат, если был найден не равный 1 или cамому числу
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