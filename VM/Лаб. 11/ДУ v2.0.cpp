#include <iostream>
#include <math.h>

using namespace std;

double f(double * y, double x)
{
	return x * y[1] - y[0]; 
}

void Eiler(int z, double * x, double * y, double h, int n)
{
	cout << "Метод Эйлера" << endl;
	
	double * Y = new double[n];

	for(int i = 0; i < n - 1; i++)
	{
		Y[i] = y[i + 1];
	}
	Y[n - 1] = f(y, x[z]);
	for(int i = 0; i < n; i++)
	{
		y[i] += Y[i] * h;
		printf("Y - %.4f\n", y[i]);
	}
	cout << endl;
}

void RKtime(int z, double * x, double * y, double h, int n)
{
	cout << "Метод Рунге-Кутта 2 порядка с усреднением по времени" << endl;
	
	double * yz = new double[n];
	double * Y = new double[n];

	for(int i = 0; i < n - 1; i++)
	{
		Y[i] = y[i + 1];
	}
	Y[n - 1] = f(y, x[z]);
	
	for(int i = 0; i < n; i++)
	{
		yz[i] = y[i] + Y[i] * h / 2;
		printf("Y* - %.4f\n", yz[i]);
	}
	cout << endl;
	
	for(int i = 0; i < n - 1; i++)
	{
		Y[i] = yz[i + 1];
	}
	Y[n - 1] = f(yz, x[z] + h / 2);
	
	for(int i = 0 ; i < n; i++)
	{
		y[i] += Y[i] * h;
		printf("Y - %.4f\n", y[i]);
	}
	cout << endl;		
}

void RKdiff(int z, double * x, double * y, double h, int n)
{
	cout << "Метод Рунге-Кутта 2 порядка с усреднением по производной" << endl;
	
	double * xyz = new double[n];
	double * yz = new double[n];
	double * Y = new double[n];
	
	for(int i = 0; i < n - 1; i++)
	{
		Y[i] = y[i + 1];
	}
	Y[n - 1] = f(y, x[z]);
	
	for(int i = 0; i < n; i++)
	{
		yz[i] = y[i] + Y[i] * h;
		printf("Y* - %.4f\n", yz[i]);
	}
	cout << endl;
	
	for(int i = 0; i < n - 1; i++)
	{
		xyz[i] = yz[i + 1];
	}
	xyz[n - 1] = f(yz, x[z + 1]);
	
	for(int i = 0 ; i < n; i++)
	{
		y[i] += (h / 2) * (Y[i] + xyz[i]);
		printf("Y - %.4f\n", y[i]);
	}
	cout << endl;			
}

void RK4(int z, double * x, double * y, double h, int n)
{
	cout << "Метод Рунге-Кутта 4 порядка" << endl;
	
	double * k1 = new double[n];
	double * k2 = new double[n];
	double * k3 = new double[n];
	double * k4 = new double[n];
	double * Y = new double[n];
	
	for(int i = 0; i < n - 1; i++)
	{
		k1[i] = y[i + 1];
	}
	k1[n - 1] = f(y, x[z]);
	
	for(int i = 0; i < n; i++)
	{
		printf("K1 - %.4f\n", k1[i]);
	}
	cout << endl;
	
	for(int i = 0; i < n - 1; i++)
	{
		k2[i] = y[i + 1] + (h / 2) * k1[i + 1];
	}
	for(int i = 0; i < n; i++)
	{
		Y[i] = y[i] + (h / 2) * k1[i];
	}
	k2[n - 1] = f(Y, x[z] + (h / 2));
	for(int i = 0; i < n; i++)
	{
		printf("K2 - %.4f\n", k2[i]);
	}
	cout << endl;
	
	for(int i = 0; i < n - 1; i++)
	{
		k3[i] = y[i + 1] + (h / 2) * k2[i + 1];
	}
	for(int i = 0; i < n; i++)
	{
		Y[i] = y[i] + (h / 2) * k2[i];
	}
	k3[n - 1] = f(Y, x[z] + (h / 2));
	for(int i = 0; i < n; i++)
	{
		printf("K3 - %.4f\n", k3[i]);
	}
	cout << endl;
	
	for(int i = 0; i < n - 1; i++)
	{
		k4[i] = y[i + 1] + h * k3[i + 1];
	}
	for(int i = 0; i < n; i++)
	{
		Y[i] = y[i] + h * k3[i];
	}
	k4[n - 1] = f(Y, x[z] + h);
	for(int i = 0; i < n; i++)
	{
		printf("K4 - %.4f\n", k4[i]);
	}
	cout << endl;
	
	for(int i = 0; i < n; i++)
	{
		y[i] += (h / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
		printf("Y - %.4f\n", y[i]);
	}
	cout << endl;
}

void control(double * y, int n)
{
	int x1;

	cout << "Хотите изменить значения? 1/2"; // 1 - не менять, 2 - менять
	cin >> x1;
	if(x1 != 1)
	{
		cout << "Введите значения" << endl;
		for(int i = 0; i < n; i++)
		{
			cin >> y[i];
		}
	}
}

int main()
{
	int n = 2;
	double h = 0.2;
	double x0 = 1;
	int g = 4;
	int z = 0;
	
	/*cout << "Разрядность - ";
	cin >> n;
	cout << "Шаг - ";
	cin >> h;
	cout << "Начальная точка - ";
	cin >> x0;
	cout << "Количество шагов - ";
	cin >> g;*/
	
	double * y = new double[n];
	double * x = new double[g + 1];
	
	for(int i = 0; i < g + 1; i++)
	{
		x[i] = x0 + i * h;
	}
	
	/*cout << "Введите начальные условия:" << endl;
	for(int i = 0; i < n; i++)
	{
		cout << "y" << i << ":";
		cin >> y[i];
	}*/
	
	y[0] = 2;
	y[1] = 3;
	
	int x1, x2;
	int k = (g - 1);
	cout << "Введите последовательность методов - ";
	cin >> x2; //вводить последовательность из 4 цифр
	while(z < g)
	{
		x1 = x2 / (1 * pow(10, k));
		switch(x1)
		{
			case 1:
				Eiler(z, x, y, h, n);
				break;
			case 2:
				RKdiff(z, x, y, h, n);
				break;
			case 3:
				RKtime(z, x, y, h, n);
				break;
			case 4:
				RK4(z, x, y, h, n);
				break;
			default:
				break;	
		}
		z++;
		/*if(z == g)
		{
			break;
		}*/
		control(y, n);
		x2 -= (x1 * pow(10, k));
		k--;
	}
		
	return 0;
}
