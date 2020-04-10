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
	double * yz = new double[n - 1];
	double * xyz = new double[n - 1];
	double * Y = new double[n - 1];
	double * x = new double[n];
	double y1 = 2;
	double y2 = 1;
	double h = 0.2;
	int z = 0;
	
	for(int i = 0; i < n; i++)
	{
		x[i] = 1 + i * h;
	}
	
	y[0] = y1;
	y[1] = y2;
	
	while(z < n)
	{
		Y[0] = y[1];
		Y[1] = f(y[0], y[1], x[z]);
		for(int i = 0; i < n - 1; i++)
		{
			yz[i] = y[i] + Y[i] * h;
			cout << "Y* - " << yz[i] << endl;
		}
		cout << endl;
		xyz[0] = yz[1];
		xyz[1] = f(yz[0], yz[1], x[z + 1]);
		for(int i = 0; i < n - 1; i++)
		{
			y[i] += (h / 2) * (Y[i] + xyz[i]);
			cout << "Y - " << y[i] << endl;
		}
		cout << endl;
		z++;		
	}
	
	return 0;
}
