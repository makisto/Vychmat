#include <iostream>
#include <math.h>
#include <iomanip>
#include <graphics.h>

using namespace std;

double f(double a)
{
	return (sqrt(a));
}

double lagrange(double xi, double * x, int n)
{
	double sum = 0;
		
	double * y = new double[n];
	double * p = new double[n];
	double * q = new double[n];
	
	for(int i = 0; i < n; i++)
	{
		y[i] = f(x[i]);
		q[i] = 1;
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == i) 
			{
				continue;
			}
			else
			{
				q[i] *= ((xi - x[j]) / (x[i] - x[j]));
			}		
		}
		p[i] = q[i] * y[i];
		sum += p[i];
	}
	
	return sum;
}

int main()
{	
	int n;
	double h = 0.2;
	cout << "Количество узлов интерполяции: ";
	cin >> n;
	/*cout << "Шаг интерполяции: ";
	cin >> h;
	double xi = 1;*/
	
	double * x = new double[n];
	
	for(int i = 0; i < n; i++)
	{
		x[i] = i;
	}
	
	int height = 1280;
	int weight = 720;
	int scale = 200;
	
	initwindow(height, weight);
	
	moveto(0,  weight);
	setcolor(WHITE);
	for(double i = 0; i < 99; i += h)
	{
		lineto(i * scale,  weight - f(i) * scale);			
	}
	
	moveto(0,  weight);
	setcolor(RED);
	for(double i = 0; i < 99; i += h)
	{
		lineto(i * scale,  weight - lagrange(i, x, n) * scale);			
	}
	
	setcolor(BLUE);
	for(int i = 0; i < n; i ++)
	{
		circle(i * scale,  weight - f(i) * scale, 4);			
	}
	
	delay(999999);
	
	return 0;
}	
