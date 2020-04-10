#include <iostream>
#include <math.h>

using namespace std;

double f(double x)
{
	return sqrt(x);
}

double triangle(double a, double b, double h)
{	
	double sum = 0;
	double sum2 = 0;
	double n1 = 0;
	int n = 0;
	
	n1 = (b - a) / h + 1;
	/*for(double i = a; i < b + h; i += h)
	{
		n1++;
	}*/	
	n = n1;
	cout << n << endl;
/*	if(n % 2 == 0)
	{
		n--;
	}*/
	
	double * y = new double[n];
		
	for(int i = 0; i < n; i++)
	{
		y[i] = f(a + i * h);
	}
	
	for(int i = 1; i < n - 1; i++)
	{
		sum += y[i];
	}
	
	sum2 = 0.5 * (y[0] + y[n - 1]);
	
	return h * (sum + sum2);
}

double Simpson(double a, double b, double h)
{
	double sum3 = 0;
	double sum4 = 0;
	double sum5 = 0;
	double n1 = 0;
	int n = 0;
	
	/*for(double i = a; i < b + h; i += h)
	{
		n1++;	
	}*/
	
	n1 = (b - a) / h + 1;
	n = n1;
	
	/*if(n % 2 == 0)
	{
		n--;
	}*/
	
	double * y = new double[n];
	
	for(int i = 0; i < n; i++)
	{
		y[i] = f(a + i * h);	
	}
	
	for(int i = 1; i < n - 1; i++)
	{
		if(i % 2 != 0)
		{
			sum3 += y[i];	
		}
		else
		{
			sum4 +=	y[i];	
		}
	}
	
	sum5 = y[0] + y[n - 1];
	
	return ((h / 3) * (sum5 + 4 * sum3 + 2 * sum4));
}

int main()
{
	double eps;
	
	double h; 
	double a; 
	double b;
	
	cout << "Верхний предел " << endl;
	cin >> b;
	cout << "Нижний предел " << endl;
	cin >> a;
	cout << "Шаг " << endl;
	cin >> h;

	int k = 1;
	int z = 0;
	double a1, a2;
			
	eps = 1e-8;
	
	/*cout << triangle(a, b, h) << endl;
	cout << Simpson(a, b, h) << endl;*/
	cout << "Формула трапеции " << endl;
	do
	{
		cout << "Шаг " << ++z << endl;
		a1 = triangle(a, b, h / k);
		a2 = triangle(a, b, h / (k * 2));

		cout << "Ih - ";
		printf("%.8f", a1);
		cout << endl;
		cout << "Ih/2 - ";
		printf("%.8f", a2);
		cout << endl << endl;
		
		k *= 2;	
		cout << "H = " << h / k << endl;
		
		cout << fabs(a1 - a2) << endl;
		cout << 3 * eps << endl << endl;
	} while(fabs(a1 - a2) > 3 * eps);
	
	z = 0;
	k = 1;
	
	cout << "Формула Симпсона " << endl;	
	do
	{
		cout << "Шаг " << ++z << endl;
		
		a1 = Simpson(a, b, h / k);
		a2 = Simpson(a, b, h / (k * 2));
		
		cout << "Ih - ";
		printf("%.8f", a1);
		cout << endl;
		cout << "Ih/2 - ";
		printf("%.8f", a2);
		cout << endl << endl;
		
		k *= 2;	
		cout << "H = " << h / k << endl;
		
		cout << fabs(a1 - a2) << endl;
		cout << 15 * eps << endl << endl;
	} while(fabs(a1 - a2) > 15 * eps);

	return 0;
}
