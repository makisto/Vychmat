#include <iostream>
#include <complex>
#include <graphics.h>

using namespace std;

double f(double x)
{
	return (1 / x);
}

complex<double> interpol(int n1, double * y, double xi, double x, double h1)
{
	complex<double> a[n1];
	complex<double> Q;
	complex<double> r;
	double n = n1;
	double z = 0;
	int j1;	
	double h;
	
	if(n1 % 2 == 1)
	{
		z += 0.5;
	}
	else
	{
		z++;
	}
	
	for(int j = 0; j < n; j++)
	{
		j1 = (-n / 2) + z;
		for(int k = 0; k < n; k++)
		{
			h = -2 * M_PI * ((k * j1) / n);
			r = (cos(h) + 1i * sin(h));
			a[j] += y[k] * r;
		}
		z++;	
	}
	
	if(n1 % 2 == 1)
	{
		z = 0.5;
	}
	else
	{
		z = 1;
	}
	
	for(int j = 0; j < n; j++)
	{
		j1 = (-n / 2) + z;
		h = 2 * M_PI * j1 * ((xi - x) / (n * h1));
		r = (cos(h) + 1i * sin(h));
		Q += a[j] * r;
		z++;			
	}
	
	return Q / n;
}

int main()
{
	int n;
	double h;
    double x0;
    
    cout << "Количество узлов интерполяции: " << endl;
    cin >> n;
    cout << "Шаг узлов интерполяции: " << endl;
    cin >> h;
    cout << "Начальная точка: " << endl;
    cin >> x0;
    
	double y[n];
	double x[n];
	
	for(int i = 0; i < n; i++)
	{
		x[i] = x0 + i * h;
		y[i] = f(x[i]);
	}		

	complex<double> eps;
	
	int height = 1280;
	int weight = 620;
	int scale = 100;
	
	initwindow(height, weight);
		
	moveto(0,  weight);
	setcolor(WHITE);
	for(double i = 0; i <= 99; i += 0.01)
	{
		lineto(i * scale,  weight / 2 - f(i) * scale);			
	}
	
	moveto(0,  weight);
	setcolor(RED);
	for(double i = 0; i <= 99; i += 0.01)
	{
		eps = interpol(n, y, i, x[0], h);
		lineto(i * scale,  weight / 2 - real(eps) * scale);			
	}
	
	moveto(0,  weight);
	setcolor(GREEN);
	for(double i = 0; i <= 99; i += 0.01)
	{
		eps = interpol(n, y, i, x[0], h);
		lineto(i * scale,  weight / 2 - imag(eps) * scale);			
	}
	
	moveto(0,  weight);
	setcolor(BLUE);
	for(double i = x[0]; i <= x[n - 1]; i += h)
	{
		circle(i * scale,  weight / 2 - f(i) * scale, 4);			
	}

	delay(9999999);
}
