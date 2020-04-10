#include <iostream>
#include <math.h>
#include <graphics.h>

using namespace std;

double f(double x)
{
	return (sqrt(x));
}

double factorial(int x)
{
	double sum = 1;
	for(int i = 1; i <= x; i++)
	{
		sum *= i;
	}	
	return sum;
}

double Newton(int n, double * x, double ** y, double xi, double h)
{
	double q = (xi - x[0]) / h;
	double qi;
	double sum = 0;
	for(int i = 1; i < n; i++)
	{
		qi = 1;
		for(int j = 0; j < i; j++)
		{
			qi *= q - j;
		}
		sum += (y[0][i] / factorial(i)) * qi;
	}
	sum += y[0][0];
		
	return sum;
}

int main()
{
	int n;
	double h = 0.2;
	double h2;
	cout << " оличество узлов интерпол€ции: ";
	cin >> n;
	/*cout << "Ўаг узлов интерпол€ции: ";
	cin >> h;
	cout << "Ўаг интерпол€ции: ";
	cin >> h2;*/
	
	double k = 0;
	
	double* x = new double[n];
	double** y = new double*[n];
	
	for(int i = 0; i < n; i++)
	{
		x[i] = i;
		y[i] = new double[n];
		y[i][0] = f(x[i]);
	}
	
	for(int i = 1; i < n; i++)
	{
		for(int j = 0; j < n - 1 - k; j++)
		{
			y[j][i]	= y[j + 1][i - 1] - y[j][i - 1]; 
		}
		k++;
	}
	
	int height = 1280;
	int weight = 720;
	int scale = 200;
	
	initwindow(height, weight);
	
	moveto(0,  weight);
	setcolor(WHITE);
	for(double i = 0; i < 999; i += h)
	{
		lineto(i * scale,  weight - f(i) * scale);			
	}
	
	moveto(0,  weight);
	setcolor(RED);
	for(double i = 0; i < 999; i += h)
	{
		lineto(i * scale,  weight - Newton(n, x, y, i, 1) * scale);		
	}
	
	setcolor(BLUE);
	for(int i = 0; i < n; i ++)
	{
		circle(i * scale,  weight - f(i) * scale, 4);			
	}
	
	delay(999999);
	
	return 0;
}
