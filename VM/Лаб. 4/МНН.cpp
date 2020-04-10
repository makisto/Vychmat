#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

void output(double** a, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{	
			cout << setw(12) << a[i][j];
		}	
		cout << endl;
	}
	cout << endl;
}

void output2(double* b, int n)
{
	for(int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << " = " << b[i] << endl;
	}
	cout << endl;
}

double f(double a, double b)
{
	return((a * a) + (b * b * b) - 4);	
}

double f2(double a, double b)
{
	return((a / (b * b)) - 3);
}

double fx(double a)
{
	return(2 * a);
}

double fy(double a)
{
	return(3 * a * a);
}

double f2x(double a)
{
	return(1 / (a * a));
}

double f2y(double a, double b)
{
	return -1 * ((2 * a) / (b * b * b));
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
		
		for(int j = i; j <= n; j++)
		{
			a[i][j] /= buf2;	
		}
		
		output(a, n);		
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
	double* x = new double[2];
	double* x1 = new double[2];
	double* b = new double[2];
	double** w = new double*[2];
	double** Y = new double*[2];
	
	for(int i = 0; i < 2; i++)
	{
		w[i] = new double[2];
		Y[i] = new double[3];
	}

	x[0] = 2;
	x[1] = 1;
	
	int kk = 0;
	
	while(kk < 3)
	{
		for(int i = 0; i < 2; i++)
		{
			cout << "x" << i + 1 << " = " << x[i] << endl;	
		}
		cout << endl;
		cout << "f1 = " << f(x[0], x[1]) << endl;
		cout << "f2 = " << f2(x[0], x[1]) << endl << endl;
		
		x1[0] = f(x[0], x[1]);
		x1[1] = f2(x[0], x[1]);
		
		w[0][0] = fx(x[0]);
		w[0][1] = fy(x[1]);
		w[1][0] = f2x(x[1]);
		w[1][1] = f2y(x[0], x[1]);
		
		for(int i = 0; i < 2; i++)
		{
			Y[i][2] = x1[i];
			for(int j = 0; j < 2; j++)
			{
				Y[i][j] = w[i][j];
			}
			for(int j = 0; j < 3; j++)
			{
				cout << setw(12) << Y[i][j];
			}
			cout << endl;
		}
		
		cout << endl;
		
		gauss(Y, 2);
		gauss2(Y, b, 2);
	
		for(int i = 0; i < 2; i++)
		{
			x[i] -= b[i];
			//cout << "x" << i + 1 << " = " << x[i] << endl;	
		}
		cout << endl;
		kk++;
	}
	
	return 0;
}
