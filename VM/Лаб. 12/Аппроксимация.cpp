#include <iostream>
#include <math.h>
#include <graphics.h>

using namespace std;

void output(double** a, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{	
			cout << a[i][j] << "\t\t";	
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
		
		/*if(a[i][i] == 0)
		{
			cout << "Система не имеет решений" << endl;
			return 0;
		} */
		
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
		/*if(a[i][i] == 0)
		{
			cout << "Система не имеет решений" << endl;
			return 0;
		} */
		b[i] = a[i][n] / a[i][i];	
        for (int k = i - 1; k >= 0; k--) 
		{
            a[k][n] -= a[k][i] * b[i];
        }
    }
}

double g0()
{
	return 1;
}

double g1(double x)
{
	return x;
}

double g2(double x)
{
	return sqrt(x);
}

double f(double x)
{
	return x * x;
}

int main()
{
	int n;
	cout << "Количество точек - ";
	cin >> n;
	
	double ** C = new double*[3];
	double * b = new double[3];
	double * x = new double[n];
	double * y = new double[n];
	double Y;
	
	for(int i = 0; i < 3; i++)
	{
		C[i] = new double[4];
	}
	
	for(int i = 0; i < n; i++)
	{
		x[i] = i;
		y[i] = f(x[i]);
		C[0][0] += g0() * g0();
		C[0][1] += g0() * g1(x[i]);
		C[0][2] += g0() * g2(x[i]);
		C[0][3] += y[i] * g0();
		C[1][0] += g1(x[i]) * g0();
		C[1][1] += g1(x[i]) * g1(x[i]);
		C[1][2] += g1(x[i]) * g2(x[i]);
		C[1][3] += y[i] * g1(x[i]);
		C[2][0] += g2(x[i]) * g0();
		C[2][1] += g2(x[i]) * g1(x[i]);
		C[2][2] += g2(x[i]) * g2(x[i]);	
		C[2][3] += y[i] * g2(x[i]);
	}
	
	output(C, 3);
	gauss(C, 3);
	gauss2(C, b, 3);
	output2(b, 3);
		
	int height = 1280;
	int weight = 720;
	int scale = 20;
	
	initwindow(height, weight);

	setcolor(BLUE);
	for(int i = 0; i < n; i++)
	{
		circle(height / 2 + i * scale,  weight / 2 - f(i) * scale, 4);			
	}
	
	moveto(height / 2,  weight / 2);
	setcolor(BLACK);
	for(double i = 0; i < n; i += 0.2)
	{
		lineto(height / 2 + i * scale,  weight / 2 - (b[0] * g0() + b[1] * g1(i) + b[2] * g2(i)) * scale);
		setcolor(RED);
	}
	
	delay(999999);
	
	return 0;
}
