#include <iostream>
#include <math.h>

using namespace std;

double f(double y1, double y2, double x)
{
	return x * y2 - y1; 
}

int main()
{
	int n = 3;
	double * y = new double[n - 1];
	double * Y = new double[n - 1];
	double * x = new double[n];
	double y1 = 2;
	double y2 = 1;
	double h = 0.2;
	double x0 = 1;
	int z = 0;
	
	for(int i = 0; i < n; i++)
	{
		x[i] = x0 + i * h;
	}
	
	y[0] = y1;
	y[1] = y2;
	
	while(z < n)
	{
		Y[0] = y[1];
		Y[1] = f(y[0], y[1], x[z]);
		for(int i = 0; i < n - 1; i++)
		{
			y[i] = y[i] + Y[i] * h;
			cout << y[i] << endl;
		}
		cout << endl;
		z++;		
	}
	
	return 0;
}
