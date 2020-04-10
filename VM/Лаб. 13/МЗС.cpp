#include <iostream>
#include <math.h>

using namespace std;
 
double f(double x) 
{
	return x * x - 5 * x;
}
 
int main() 
{
	double gold = (1 + sqrt(5)) / 2;
	int z = 1;
	double a = 2;
	double b = 3; 
	double eps = 1e-4; 
	double x1 = b - (b - a) / gold; 
	double x2 = a + (b - a) / gold;
	
	while(fabs(b - a) / 2 > eps)
	{
		cout << z << endl;
		printf("x1 - %.8f, x2 - %.8f\n", x1, x2);
		printf("a - %.8f, b - %.8f\n", a, b);
	    if (f(x1) > f(x2))
		{
			a = x1;
			x1 = x2;
			x2 = b - (x1 - a);
		} 
	    else
	    {
	    	b = x2;
	    	x2 = x1;
	    	x1 = a + (b - x2);
		}
	    printf("F(x) - %.8f\n", f((a + b) / 2));
	    printf("X - %.8f\n\n", (a + b) / 2);
		z++;
	}
	
	return 0;
}
