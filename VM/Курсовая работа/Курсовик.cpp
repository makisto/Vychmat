#include <iostream>
#include <math.h>
#include <graphics.h>
#include <iomanip>
#include <conio.h>

#define EPS 1e-9
#define A 0
#define B 1
#define YA 4
#define YB 10
#define H 0.05

using namespace std;

double f(double y0, double y1, double y2, double x)
{
	return (pow(y2, 3) + 8 * cos(x) * y2 - 4 * x - 7 * pow(M_E, x) * y1 + 5 * y0 * (x + 8));
}

double MPD(double y0, double y1, double x)
{
	double L = A;
	double R = B;
	double C = 0;
	
	while(fabs(((R - L) / 2)) >= EPS)
	{
		C = (L + R) / 2;
		if(f(y0, y1, C, x) * f(y0, y1, L, x) < 0)
		{
			R = C;
		}
		else if(f(y0, y1, C, x) * f(y0, y1, R, x) < 0) 
		{
			L = C;
		}
		else
		{
			break;
		}
	}
	
	return C;
}

double * rk(double x0, double xn, double y0, double y1, double h)
{	
	double * y = new double[2];
	double * yz = new double[2];
	double * Y = new double[2];
	
	y[0] = y0;
	y[1] = y1;

	while(fabs(xn - x0) >= EPS)
	{	
		Y[0] = y[1];
		Y[1] = MPD(y[0], y[1], x0);
		//Y[1] = f(y[0], y[1], x0);
		for(int i = 0; i < 2; i++)
		{
			yz[i] = y[i] + Y[i] * h / 2;
		}
		Y[0] = yz[1];
		Y[1] = MPD(yz[0], yz[1], x0 + h / 2);
		//Y[1] = f(yz[0], yz[1], x0 + h / 2);
		for(int i = 0; i < 2; i++)
		{
			y[i] += Y[i] * h;
		}
		x0 += h;
	}
	
	return y;
}

double * count(double x0, double xn, double y0, double y1)
{
	double * Y1 = new double[2];
	double * Y2 = new double[2];
	int k = 1;
	double sum1, sum2;

	do
	{
		Y1 = rk(x0, xn, y0, y1, H / k);		
		Y2 = rk(x0, xn, y0, y1, H / (k * 2));
		
		sum1 = Y1[0] - Y2[0];
		sum2 = Y1[1] - Y2[1];
		
		k *= 2;
	}while((fabs(sum1) > 3 * EPS) || (fabs(sum2) > 3 * EPS));
	
	return Y2;
}

double shooting()
{
	double L = 0;
	double R = 10;
	double C = 0;
	
	double * y1 = new double[2];
	double * y2 = new double[2];
	double * y3 = new double[2];
	
	/*int i = 0;
	
	double * z1 = new double[2];
	
	int isLeft = 0;
	int isRight = 0;
	
	do
	{
		z1 = count(A, B, YA, i);
		if(z1[0] > YB)
		{
			R = z1[0];
			isRight++;	
		}
		else if(z1[0] < YB)
		{
			L = z1[0];
			isLeft++;	
		}
		cout << L << endl << R << endl;
		i++;		
	}while((isLeft == 0) || (isRight == 0));*/
		
	do
	{
		C = (L + R) / 2;	
		y1 = count(A, B, YA, L);
		y2 = count(A, B, YA, R);
		y3 = count(A, B, YA, C);
		
		if((y3[0] - YB) * (y1[0] - YB) < 0)
		{
			R = C;
		}
		else if((y3[0] - YB) * (y2[0] - YB) < 0)
		{
			L = C;
		}
		else
		{
			break;
		}
	}while(fabs((y1[0] - y2[0])/ 2) >= EPS);	
	
	return C;
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

double Spline(double xi, double * m, double * x, double * y, double * h, int n)
{
	double sum = 0;
	double sum1, sum2, sum3, sum4;
	int k = 0;
	
	for(int i = 0; i < n; i++)
	{
		if((xi > x[i]) && (xi < x[i + 1]))
		{
			k = i + 1;	
		}
	}
	
	if(xi == x[0])
	{
		k = 1;
	}
	if(xi == x[1])
	{
		k = 1;
	}
	if(xi == x[2])
	{
		k = 2;
	}
	if(xi == x[3])
	{
		k = 3;
	}
	if(xi == x[4])
	{
		k = 4;
	}
	if(xi == x[5])
	{
		k = 5;
	}
	
	sum1 = m[k - 1] * (pow((x[k] - xi), 3) / (6 * h[k - 1]));
	sum2 = m[k] * (pow((xi - x[k - 1]), 3) / (6 * h[k - 1]));
	sum3 = (y[k - 1] - ((m[k - 1] * pow(h[k - 1], 2)) / 6)) * ((x[k] - xi) / h[k - 1]);
	sum4 = (y[k] - ((m[k] * pow(h[k - 1], 2)) / 6)) * ((xi - x[k - 1]) / h[k - 1]);
	
	sum += sum1 + sum2 + sum3 + sum4;
	
	return sum;	
}

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

double triangle(double K, double h)
{	
	double sum = 0;
	double sum2 = 0;
	double n1 = 0;
	int n = 0;
	
	n1 = (B - A) / h + 1;
	n = n1;	
	
	double * y = new double[n];
	double * y2 = new double[2];
		
	for(int i = 0; i < n; i++)
	{
		y2 = count(A, A + i * h, YA, K);
		y[i] = pow(y2[0], 2);
	}
	
	for(int i = 1; i < n - 1; i++)
	{
		sum += y[i];
	}
	
	sum2 = 0.5 * (y[0] + y[n - 1]);
	
	return h * (sum + sum2);
}

int main()
{	
	double K = shooting();
	double * y2 = new double[2];
	
	int n = 6;
	double hi = 0.2;
	int k = 1;
	
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
		x[i] = A + i * hi;
		y2 = count(A, x[i], YA, K);
		y[i] = y2[0];
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
	
	for(double i = 0.0; i < B; i += H) 
	{
		y2 = count(A, i, YA, K);
		printf("X=%3.4f Y=%5.8f\tY^=%5.8f\tINT=%5.8f\n", i, y2[0], y2[1], Spline(i, m, x, y, h, n));	
	}
	y2 = count(A, B, YA, K);
	printf("X=%3.d Y=%5.8f\tY^=%5.8f\tINT=%5.8f\n", B, y2[0], y2[1], Spline(B, m, x, y, h, n));
	
	cout << "Интеграл - " << triangle(K, hi) << endl;
	
	_getch();
	
	int height = 1366;
	int weight = 768;
	int scale = 50;
	
	initwindow(height, weight);
	
	setcolor(GREEN);
	for(double i = 0.0; i <= 1; i += 0.2)
	{	
		y2 = count(A, i, YA, K);
		circle(height / 2 + i * scale, weight - y2[0] * scale, 4);			
	}
	
	moveto(height / 2, weight / 2);
	setcolor(BLACK);
	for(double i = 0.0; i < 2 + H; i += H) 
	{
		y2 = count(A, i, YA, K);
		lineto(height / 2 + i * scale, weight - y2[0] * scale);	
		setcolor(WHITE);
	}
	
	moveto(height / 2, weight / 2);
	setcolor(BLACK);
	for(double i = 0.00; i < x[n - 1]; i += 0.01)
	{
		lineto(height / 2 + i * scale,  weight - Spline(i, m, x, y, h, n) * scale);
		setcolor(RED);	
	}
	lineto(height / 2 + 1 * scale,  weight - Spline(B, m, x, y, h, n) * scale);	
	
	delay(9999999);
	
	return 0;
}	
