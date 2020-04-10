#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
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
	srand(time(NULL));
	
	ifstream fin("b.txt");
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
	
	double max = 0;
	for(int i = 0; i < n; i++)
	{
		if(abs(b[i]) > max)
		{
			max = b[i];
		}
	}
	cout << max << endl;
		
	double max2 = 0;
	double max3 = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(c[i][j] > 0)
			{
				max3 += c[i][j];
			}
			else
			{
				max3 += -1 * (c[i][j]);	
			}	
		}
		if(max2 < max3)
		{
			max2 = max3;	
		}
		max3 = 0;
	}
	cout << max2 << endl << endl;
	
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
	
	/*int k = ((log((0.0001 * (1 - max2))/(max)))/ (log(max2))) + 1;
	cout << k << endl;*/
	int N = 0;
    double buf3 = 0;
    
	while(N < 3)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
			    buf3 += (c[i][j] * d[j]);
			}
			d[i] = b[i] - buf3;	
			buf3 = 0;
			cout << d[i] << endl;
		}
		cout << endl;
		N++;	
	}
	
	return 0;
}
