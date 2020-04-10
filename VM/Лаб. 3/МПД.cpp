#include <iostream>

using namespace std;

double f(double a)
{
	return ((a * a) - a - 3);
}

int main()
{
	double c;
	double a = 2;
	double b = 3;
	int k = 0;
	double e = 0.00000001;
	for(;;)
	{
		c = (a + b) / 2;
		cout << "X = " << c << endl;
		if(f(a) * f(c) < 0)
		{
			b = c;	
		}
		else if(f(c) * f(b) < 0)
		{
			a = c;	
		}
		//cout << i + 1 << "-й шаг::" << endl;
		cout << a << " " << b << endl << endl;
		k++;
		if((b - a) < 0)
		{
			if(((b - a) * -1.0) / 2 < e)
			break;
		}
		else
		{
			if((b - a) / 2 < e)
			break;
		}
	}
	
	cout << k << endl;
	return 0;
}
