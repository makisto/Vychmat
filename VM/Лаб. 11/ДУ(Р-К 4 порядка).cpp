#include <iostream>
#include <math.h>

using namespace std;

double f(double y1, double y2, double x)
{
	return x * y2 - y1; 
}

double * rk(double h)
{
	double * y = new double[2];
	double * k1 = new double[2];
	double * k2 = new double[2];
	double * k3 = new double[2];
	double * k4 = new double[2];

	y[0] = 2;
	y[1] = 1;
	
	int n1 = 0.6 / h + 1;
	double * x = new double[n1];
	for(int i = 0; i < n1; i++)
	{
		x[i] = 1 + i * h;
	}
	
	double sum = 0;
	int z = 0;
	while(z < n1)
	{
		k1[0] = y[1];
		k1[1] = f(y[0], y[1], x[z]);

		k2[0] = y[1] + (h / 2) * k1[1];
		k2[1] = f(y[0] + (h / 2) * k1[0], y[1] + (h / 2) * k1[1], x[z] + (h / 2));

		k3[0] = y[1] + (h / 2) * k2[1];
		k3[1] = f(y[0] + (h / 2) * k2[0], y[1] + (h / 2) * k2[1], x[z] + (h / 2));

		k4[0] = y[1] + h * k3[1];
		k4[1] = f(y[0] + h * k3[0], y[1] + h * k3[1], x[z] + h);

		for(int i = 0; i < 2; i++)
		{
			y[i] += (h / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
		}
		z++;	
	}
	
	return y;
}

int main()
{
	double h = 0.2;
	int k = 1;
	double sum1, sum2;
	int z = 1;
	double * y1 = new double[2];
	double * y2 = new double[2];
	double eps = 1e-4;
	
	cout << "Eps - " << eps << endl;
	do
	{
		cout << z << endl;
		y1 = rk(h / k);
		for(int i = 0; i < 2; i++)
		{
			printf("Y - %.8f\n", y1[i]);
		}
		cout << (h / k) << endl << endl;
		
		y2 = rk(h / (k * 2));
		for(int i = 0; i < 2; i++)
		{
			printf("Y - %.8f\n", y2[i]);
		}
		cout << (h / (k * 2)) << endl << endl;
		
		sum1 = y1[0] - y2[0];
		sum2 = y1[1] - y2[1];
		
		k *= 2;
		z++;
	}while((fabs(sum1) > 15 * eps) || (fabs(sum2) > 15 * eps));
		
	return 0;
}
