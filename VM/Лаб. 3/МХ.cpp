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
	double d;
	int k = 0;
	double e = 0.00000001;
	for(;;)
	{
		c = (a * f(b) - b * f(a)) / (f(b) - f(a));
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
		if((c - d) < e)
		{
			if(((c - d) * -1.0) < e)
			break;
		}
		else
		{
			if((c - d) < e)
			break;
		}
		d = c;
	}

	cout << k << endl;
	return 0;
}
