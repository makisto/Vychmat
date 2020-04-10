#include <iostream>
#include <math.h>

using namespace std;

double f(double y1, double y2, double x)
{
	return x * y2 - y1; 
}

void Eiler(int z, double * x, double * y, double h)
{
	double * Y = new double[2];

	Y[0] = y[1];
	Y[1] = f(y[0], y[1], x[z]);
	for(int i = 0; i < 2; i++)
	{
		y[i] += Y[i] * h;
		printf("Y - %.5f\n", y[i]);
	}
	cout << endl;
}

void RKtime(int z, double * x, double * y, double h)
{
	double * yz = new double[2];
	double * Y = new double[2];

	Y[0] = y[1];
	Y[1] = f(y[0], y[1], x[z]);
	for(int i = 0; i < 2; i++)
	{
		yz[i] = y[i] + Y[i] * h / 2;
		printf("Y* - %.5f\n", yz[i]);
	}
	cout << endl;
		
	Y[0] = yz[1];
	Y[1] = f(yz[0], yz[1], x[z] + h / 2);
	for(int i = 0; i < 2; i++)
	{
		y[i] += Y[i] * h;
		printf("Y - %.5f\n", y[i]);
	}
	cout << endl;		
}

void RKdiff(int z, double * x, double * y, double h)
{
	double * xyz = new double[2];
	double * yz = new double[2];
	double * Y = new double[2];
	
	Y[0] = y[1];
	Y[1] = f(y[0], y[1], x[z]);
	for(int i = 0; i < 2; i++)
	{
		yz[i] = y[i] + Y[i] * h;
		printf("Y* - %.5f\n", yz[i]);
	}
	cout << endl;
	
	xyz[0] = yz[1];
	xyz[1] = f(yz[0], yz[1], x[z + 1]);
	for(int i = 0; i < 2; i++)
	{
		y[i] += (h / 2) * (Y[i] + xyz[i]);
		printf("Y - %.5f\n", y[i]);
	}
	cout << endl;			
}

void RK4(int z, double * x, double * y, double h)
{
	double * k1 = new double[2];
	double * k2 = new double[2];
	double * k3 = new double[2];
	double * k4 = new double[2];

	k1[0] = y[1];
	k1[1] = f(y[0], y[1], x[z]);
	for(int i = 0; i < 2; i++)
	{
		cout << "K1 - " << k1[i] << endl;
	}
	cout << endl;
	
	k2[0] = y[1] + (h / 2) * k1[1];
	k2[1] = f(y[0] + (h / 2) * k1[0], y[1] + (h / 2) * k1[1], x[z] + (h / 2));
	for(int i = 0; i < 2; i++)
	{
		cout << "K2 - " << k2[i] << endl;
	}
	cout << endl;
	
	k3[0] = y[1] + (h / 2) * k2[1];
	k3[1] = f(y[0] + (h / 2) * k2[0], y[1] + (h / 2) * k2[1], x[z] + (h / 2));
	for(int i = 0; i < 2; i++)
	{
		cout << "K3 - " << k3[i] << endl;
	}
	cout << endl;
	
	k4[0] = y[1] + h * k3[1];
	k4[1] = f(y[0] + h * k3[0], y[1] + h * k3[1], x[z] + h);
	for(int i = 0; i < 2; i++)
	{
		cout << "K4 - " << k4[i] << endl;
	}
	cout << endl;
	
	for(int i = 0; i < 2; i++)
	{
		y[i] += (h / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
		cout << "Y - " << y[i] << endl;
	}
	cout << endl; 
}

void control(double * y)
{
	int x1;

	cout << "Хотите изменить значения? 1/2";
	cin >> x1;
	if(x1 != 1)
	{
		cout << "Введите значения" << endl;
		for(int i = 0; i < 2; i++)
		{
			cin >> y[i];
		}
	}
}

int main()
{
	double * y = new double[2];
	double * x = new double[5];
	double y1 = 2;
	double y2 = 1;
	double h = 0.2;
	double x0 = 1;
	int g;
	int z = 0;
	
	for(int i = 0; i < 5; i++)
	{
		x[i] = x0 + i * h;
	}
	
	y[0] = y1;
	y[1] = y2;
	
	RK4(z, x, y, h);
	control(y);
	z++;
	RK4(z, x, y, h);
	control(y);
	z++;
	RK4(z, x, y, h);
	control(y);
	z++;
	RK4(z, x, y, h);
	
	
	/*while(z < 5)
	{
		cout << "Выберите номер метода - ";
		cin >> g;
		/switch(g)
		{
			case 1:
				Eiler(z, x, y, h);
				control(y);
				z++;
				system("PAUSE");
				break;
			case 2:
				RKtime(z, x, y, h);
				control(y);
				z++;
				system("PAUSE");
				break;
			case 3:
				RKdiff(z, x, y, h);
				control(y);
				z++;
				system("PAUSE");
				break;
			case 4:
				RK4(z, x, y, h);
				control(y);
				z++;
				system("PAUSE");
				break;
			default:
				break;	
		}
	}*/
		
	return 0;
}
