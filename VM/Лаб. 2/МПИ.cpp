#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>

using namespace std;

void output(double** a, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			cout << a[i][j] << "\t";
		}	
		cout << endl;
	}
	cout << endl;
}

int main()
{
	ifstream fin("b.txt");
	srand(time(NULL));
	
	int n;
	//cout << "¬ведите n" << endl;
	fin >> n;
	double** a = new double*[n];
	double* b = new double[n];
	double** c = new double*[n];
	double* d = new double[n];
	double* e = new double[n];
	
	for(int i = 0; i < n; i++)
	{
		a[i] = new double[n + 1];
		c[i] = new double[n];
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			//a[i][j] = rand() % 10 + 1;
			fin >> a[i][j];
		}
	}
	
	output(a, n);
		
	for(int i = 0; i < n; i++)
	{
		double buf = a[i][i];
		//cout << buf << endl;
		for(int j = 0; j <= n; j++)
		{
			a[i][j] /= buf;
		}
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			c[i][j] = a[i][j];
		}
		b[i] = a[i][n];
		d[i] = 0;
		e[i] = 0;
		c[i][i] = 0;
	}
	
	output(a, n);
	for(int i = 0; i < n; i++)
	{
		cout << b[i] << endl;
	}
	cout << endl;
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout << c[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	
	for(int i = 0; i < n; i++)
	{
		cout << d[i] << endl;
	}
	cout << endl;
	
	int k = 0;

	while(k < 3)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				e[i] += (c[i][j] * d[j]);
			}
		}
		
		for(int i = 0; i < n; i++)
		{
			d[i] = e[i];
			e[i] = 0;
			d[i] = b[i] - d[i];
			cout << d[i] << endl;
		}
		cout << endl;
		k++;	
	}
	
	return 0;
}
