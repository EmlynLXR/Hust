#include<stdio.h>
#include<stdlib.h>
double Switch(double);
int main()
{
	double x, tax;
	while (1)
	{
		scanf("%lf", &x);
		if (x != 0)
		{
			tax = Switch(x);//tax = If(x);
			printf("%lf\n", tax);
		}
		else break;
	}
	system("pause");
}
double Switch(double x)
{
	double t; int a;
	a = (int)x / 1000;
	switch (a)
	{
	case 0:t = 0; break;
	case 1:t = (x - 1000)*0.05; break;
	case 2:t = (x - 2000)*0.1 + (2000 - 1000) * 0.05; break;
	case 3:t = (x - 3000)*0.15 + (3000 - 2000)*0.1 +
		(2000 - 1000) * 0.05; break;
	case 4:t = (x - 4000)*0.2 + (4000 - 3000)*0.15 + (3000 - 2000)*0.1 + (2000 - 1000) * 0.05; break;
	default:t = (x - 5000)*0.25 + (5000 - 4000)*0.2 + (4000 - 3000)*0.15 + (3000 - 2000)*0.1 + (2000 - 1000)* 0.05; break;
	}
	return t;
}

