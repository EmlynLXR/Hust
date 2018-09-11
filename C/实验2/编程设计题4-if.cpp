#include<stdio.h>
#include<stdlib.h>
double If(double);
int main()
{
	double x, tax;
	while (1)
	{
		scanf("%lf", &x);
		if (x != 0)
		{
			tax = If(x);
			printf("%lf\n", tax);
		}
		else break;
	}
	system("pause");
}
double If(double x)
{
	double t;
	if (x <= 1000)t = 0;
	else if (x <= 2000)t = (x - 1000)*0.05;
	else if (x <= 3000)t = (x - 2000)*0.1 + (2000 - 1000) * 0.05;
	else if (x <= 4000)t = (x - 3000)*0.15 + (3000 - 2000)*0.1 + (2000 - 1000) * 0.05;
	else if (x <= 5000)t = (x - 4000)*0.2 + (4000 - 3000)*0.15 + (3000 - 2000)*0.1 + (2000 - 1000) * 0.05;
	else t = (x - 5000)*0.25 + (5000 - 4000)*0.2 + (4000 - 3000)*0.15 + (3000 - 2000)*0.1 + (2000 - 1000) * 0.05;
	return t;
}

