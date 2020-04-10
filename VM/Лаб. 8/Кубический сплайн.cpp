#include <iostream>
#include <math.h>
#include <iomanip>
#include <graphics.h>

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
		cout << "M" << i + 1 << " = " << b[i] << endl;
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
		b[i + 1] = a[i][n] / a[i][i];	
        for (int k = i - 1; k >= 0; k--) 
		{
            a[k][n] -= a[k][i] * b[i + 1];
        }
    }
}

double f(double x)
{
	return (sqrt(x));
}

double Spline(double xi, double * m, double * x, double * y, double * h, int n)
{
	double sum = 0;
	double sum1, sum2, sum3, sum4;
	int k;
	
	for(int i = 0; i < n; i++)
	{
		if((xi > x[i]) && (xi < x[i + 1]))
		{
			k = i + 1;	
		}
	}
	
	sum1 = m[k - 1] * (pow((x[k] - xi), 3) / (6 * h[k - 1]));
	sum2 = m[k] * (pow((xi - x[k - 1]), 3) / (6 * h[k - 1]));
	sum3 = (y[k - 1] - ((m[k - 1] * pow(h[k - 1], 2)) / 6)) * ((x[k] - xi) / h[k - 1]);
	sum4 = (y[k] - ((m[k] * pow(h[k - 1], 2)) / 6)) * ((xi - x[k - 1]) / h[k - 1]);
	
	sum += sum1 + sum2 + sum3 + sum4;
	
	return sum;	
}

int main()
{
	int n;
	
	cout << "Количество узлов интерполяции: " << endl;
	cin >> n;
	
	double * m = new double[n];
	double * x = new double[n];
	double * y = new double[n];
	double * h = new double[n - 1];
	double * d = new double[n - 2];
	double ** c = new double * [n - 2];
	
	m[0] = m[n - 1] = 0;
	
	for(int i = 0; i < n - 2; i++)
	{
		c[i] = new double[n - 1];
	}
	
	for(int i = 0; i < n; i++)
	{
		x[i] = i;
		y[i] = f(x[i]);
	}
	
	for(int i = 0; i < n - 1; i++)
	{
		h[i] = x[i + 1] - x[i];
	}
	
	for(int i = 0; i < n - 2; i++)
	{
		d[i] = ((y[i + 2] - y[i + 1]) / h[i + 1]) - ((y[i + 1] - y[i]) / h[i]);
	}
	
	for(int i = 0; i < n - 2; i++)
	{
		c[i][n - 2] = d[i];
		for(int j = 0; j <= n - 2; j++)
		{
			if(i == j)
			{
				c[i][j] = (h[i] + h[i + 1]) / 3;
			}
			if(j == i + 1)
			{
				c[i][j] = h[i + 1] / 6;	
			}
			if(j == i - 1)
			{
				c[i][j] = h[i] / 6;		
			}
			if(abs(i - j) > 1)
			{
				c[i][j] = 0;
			}
			c[i][n - 2] = d[i];
		}
	}
	cout << endl;
	
	gauss(c, n - 2);
	gauss2(c, m, n - 2);
	output2(m, n);
		
	int height = 1280;
	int weight = 720;
	int scale = 200;
	
	initwindow(height, weight);
	
	moveto(0,  weight);
	setcolor(WHITE);
	for(double i = 0; i < 99; i += 0.01)
	{
		lineto(i * scale,  weight - f(i) * scale);			
	}
	
	moveto(0,  weight);
	setcolor(RED);
	for(double i = 0; i < x[n - 1]; i += 0.01)
	{
		lineto(i * scale,  weight - Spline(i, m, x, y, h, n) * scale);		
	}
	
	setcolor(BLUE);
	for(int i = 0; i < n; i++)
	{
		circle(i * scale,  weight - y[i] * scale, 4);			
	}
	
	delay(9999999);
	
	return 0;	
}
