#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>

#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>

using namespace std;

int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


int main()
{
	int N, M;
	N = M = 6; 
	int n = N + M;

	vector<double> ck;

	for (int k = 0; k < n + 1; k++) {
		double c;
		if (k % 2 == 0) {
			if (k % 4 == 0) {
				c = 1.0 / factorial(k);
			}
			else {
				c = -1.0 / factorial(k);
			}
		}
		else {
			c = 0;
		}
		ck.push_back(c);
	}

	gsl_matrix* A = gsl_matrix_alloc(M ,M);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			double value = ck[N - M + i + j + 1];
			gsl_matrix_set(A, i, j, value);
		}
	}

	gsl_vector* b = gsl_vector_alloc(M);

	for (int i = 0; i < M; i++) {
		double value = -ck[N + 1 + i];
		gsl_vector_set(b, i, value);
	}

	
	gsl_vector* x = gsl_vector_alloc(M);
	gsl_permutation* p = gsl_permutation_alloc(M);
	int signum;
	gsl_linalg_LU_decomp(A, p, &signum);
	gsl_linalg_LU_solve(A, p, b, x);

	vector<double> bk, reversed;

	bk.push_back(1.0);

	//wypisanie wyników
	for (int i = 0; i < M; i++) {
		cout << "x" << i << " = " << gsl_vector_get(x, i) << endl;
		reversed.push_back(gsl_vector_get(x, i));
	}

	for (int i = M - 1; i >= 0; i--) {
		bk.push_back(reversed[i]);
	}
	vector<double> ak;

	for (int i = 0; i <= N; i++) {
		double a = 0;
		for (int j = 0; j <= i; j++) {
			a += ck[i - j] * bk[j];
		}
		ak.push_back(a);/*
		cout << "a" << i << " = " << a << endl;
		cout << "b" << i << " = " << bk[i] << endl;*/
	}

	double start = -5.0;
	double end = 5.0;

	ofstream file;
	file.open("data.txt");


	for (double x = start; x <= end; x += 0.1) {
		double y;
		double licznik = 0, mianownik = 0;
		for (int i = 0; i <= N; i++) {
			licznik += ak[i] * pow(x, i);
		}
		for (int i = 0; i <= M; i++) {
			mianownik += bk[i] * pow(x, i);
		}
		y = licznik / mianownik;
		file << x << " " << y << "\n";
		cout << "(" << x << ", " << y << "), \n";
	}

	return 0;
}