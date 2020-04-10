#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include <iomanip>

using namespace std;

ifstream fin("bakayaro.txt");

void output(double** a, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{	
			cout << setw(12) << a[i][j];
			//fout << a[i][j] << "\t";
		}	
		cout << endl;
		//fout << endl;
	}
	cout << endl;
	//fout << endl;
}

void output2(double* b, int n)
{
	for(int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << " = " << b[i] << endl;
		//fout << "x" << i + 1 << " = " << b[i] << endl;
	}
	cout << endl;
	//fout << endl;
}

void swap(double** a, int n, int p1, int p2)
{
	double tmp;
	for(int i = p2; i <= n; i++)
	{
		tmp = a[p1][i];
		a[p1][i] = a[p2][i];
		a[p2][i] = tmp;
	}
}

int gauss(double** a, int n)
{
	double max;
	double buf;
	double buf2;
	int max_row;
	
	for(int i = 0; i < n; i++)
	{
		max = abs(a[i][i]);
		max_row = i;
		
		for(int j = i + 1; j < n; j++)
		{
			if(max < abs(a[j][i]))
			{
				max = abs(a[j][i]);
				max_row = j;	
			}
		}
		
		swap(a, n, max_row, i);
		
		if(a[i][i] == 0)
		{
			cout << "Система не имеет решений" << endl;
			return 0;
		} 
		
		buf2 = a[i][i];
		for(int j = i + 1; j < n; j++)
		{
			buf = -1 * (a[j][i] / a[i][i]); 
			for(int k = i; k <= n; k++)
			{
				if(i == k) 
				{
					a[j][k] = 0;
				}
				else
				{
					a[j][k] += buf * a[i][k];									
				}				
			}	
		}
		
		output(a, n);
		
		for(int j = i; j <= n; j++)
		{
			a[i][j] /= buf2;	
		}		
	}
}

int gauss2(double** a, double* b, int n)
{
	for (int i = n - 1; i >= 0; i--) 
	{
		if(a[i][i] == 0)
		{
			cout << "Система не имеет решений" << endl;
			return 0;
		} 
		b[i] = a[i][n] / a[i][i];	
        for (int k = i - 1; k >= 0; k--) 
		{
            a[k][n] -= a[k][i] * b[i];
        }
    }
}
	
int main()
{
	srand(time(NULL));

	int n;
	//cout << "Введите n" << endl;
	fin >> n;
	
	double **a = new double*[n];
	double *b = new double[n];
	
	for(int i =0; i < n; i++)
	{
		a[i] = new double[n + 1];
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			fin >> a[i][j];
			//a[i][j] = rand() % 100 + (-50);
		}	
	}
	
	output(a, n);
	gauss(a, n);
	output(a, n);
	gauss2(a, b, n);	
	output2(b, n);

	return 0;
}
