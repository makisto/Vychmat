#include <iostream>
#include <math.h>
#include <graphics.h>

using namespace std;

double f(double x)
{
	return (sqrt(x));
}

double resurect(double * x, double * y, int n)
{
	for(int i = 0; i < n; i++)
	{
		y[i] = f(x[i]);		
	}
}

double Aithken(int n, double * x, double * y, double xi, int k)
{	
	for(int i = 0; i < n - 1; i++)
	{
		y[i] = ((y[i] * (xi - x[i + k])) - (y[i + 1] * (xi - x[i]))) / (x[i] - x[i + k]);	
	}
	if(n > 0)
	{
		Aithken(n - 1, x, y, xi, k + 1);
	}
	
	return y[0];
}

int main()
{
	int n;
	double h = 0.2;
	cout << "Количество узлов интерполяции: ";
	cin >> n;
	/*cout << "Шаг интерполяции: ";
	cin >> h;*/
	
	//double xi = 1;
	
	double* x = new double[n];
	double* y = new double[n];
	
	for(int i = 0; i < n; i++)
	{
		x[i] = i;
		y[i] = f(x[i]);
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
		lineto(i * scale,  weight - Aithken(n, x, y, i, 1) * scale);
		resurect(x, y, n);			
	}
	
	setcolor(BLUE);
	for(int i = 0; i < n; i ++)
	{
		circle(i * scale,  weight - f(i) * scale, 4);			
	}
	
	delay(999999);
	
	return 0;
}
