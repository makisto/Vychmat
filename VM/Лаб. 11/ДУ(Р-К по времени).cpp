#include <iostream>
#include <math.h>

using namespace std;

double f(double y1, double y2, double x)
{
	return x * y2 - y1; 
}

double * rk(double a, double b, double h)
{
	double * y = new double[2];
	double * yz = new double[2];
	double * Y = new double[2];
	
	y[0] = 2;
	y[1] = 1;
			
	int n = (b - a) / h;
	
	double * x = new double[n];
	for(int i = 0; i < n; i++)
	{
		x[i] = a + i * h;
	}

	int z = 0;
	while(z < n)
	{	
		Y[0] = y[1];
		Y[1] = f(y[0], y[1], x[z]);
		for(int i = 0; i < 2; i++)
		{
			yz[i] = y[i] + Y[i] * h / 2;
		}
		Y[0] = yz[1];
		Y[1] = f(yz[0], yz[1], x[z] + h / 2);
		for(int i = 0; i < 2; i++)
		{
			y[i] += Y[i] * h;
		}
		z++;		
	}
	
	return y;	
}

int main()
{
	double h = 0.2;
	double a;
	double b;
	cin >> a >> b;
	int k = 1;
	double sum1, sum2;
	int z = 1;
	double * y1 = new double[2];
	double * y2 = new double[2];
	double eps = 1e-8;
	
	cout << "Eps - " << eps << endl;
	do
	{
		cout << z << endl;
		y1 = rk(a, b, h / k);
		for(int i = 0; i < 2; i++)
		{
			printf("Y - %.8f\n", y1[i]);
		}
		cout << (h / k) << endl << endl;
		
		y2 = rk(a, b, h / (k * 2));
		for(int i = 0; i < 2; i++)
		{
			printf("Y - %.8f\n", y2[i]);
		}
		cout << (h / (k * 2)) << endl << endl;
		
		sum1 = y1[0] - y2[0];
		sum2 = y1[1] - y2[1];
		
		k *= 2;
		z++;
	}while((fabs(sum1) > 3 * eps) || (fabs(sum2) > 3 * eps));
		
	return 0;
}
