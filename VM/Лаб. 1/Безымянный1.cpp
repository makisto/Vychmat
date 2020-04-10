#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

void swapI(double** a, int n, int p1, int p2)
{
	double tmp;
	for (int i = 0; i <= n; i++)
	{
		tmp = a[p1][i];
		a[p1][i] = a[p2][i];
		a[p2][i] = tmp;
	}
}
void swapJ(double**a, int n, int p1, int p2)
{
	double tmp;
	for (int i = 0; i < n; i++)
	{
		tmp = a[i][p1];
		a[i][p1] = a[i][p2];
		a[i][p2] = tmp;
	}
}
void output(double **a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
double * gauss(double **a, int n)
{
	double *x;
	double max;
	int k, index;
	x = new double[n];
	k = 0;
	while (k < n)
	{
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		if (max == 0) return 0;
		swapI(a, n, index, k);
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			for (int j = k; j < n; j++)
				a[i][j] = a[i][j] / temp;
			a[i][n] = a[i][n] / temp;
			if (i != k)
			{
				for (int j = k; j < n; j++)
				{
					a[i][j] = a[i][j] - a[k][j];
					if (i < k) a[i][j] = 0;
				}
				a[i][n] = a[i][n] - a[k][n];
			}
		}
		k++;
	}
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = a[k][n];
		for (int i = 0; i < k; i++)
			a[i][n] -= a[i][k] * x[k];
	}
	return x;
}
int main()
{
	ifstream fin("bakayaro.txt");
	int N;
	fin >> N;
	double **a; double *x;
	a = new double*[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = new double[N + 1];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			fin >> a[i][j];
		}
	}
	output(a, N);
	//swapI(a, N, 1, 2);
	x = gauss(a, N);
	output(a, N);
	for (int i = 0; i < N; i++)
		cout << "x" << i << " = " << x[i]<<endl;
	system("PAUSE");
	return 0;
}
