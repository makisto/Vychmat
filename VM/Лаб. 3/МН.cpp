#include <iostream>

using namespace std;

double f(double a)
{
	return ((a * a) - a - 3);
}

double pf(double a)
{
	return ((2 * a) - 1);
}

int main()
{
	double c = 2;
	int k = 0;
	double d;
	double e = 0.00000001;
	cout << "Xo = " << c << endl << endl;
	for(;;)
	{
		c -= (f(c) / pf(c));
		//cout << i + 1 << "-й шаг::" << endl;
		cout << "X = " << c << endl << endl;
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
