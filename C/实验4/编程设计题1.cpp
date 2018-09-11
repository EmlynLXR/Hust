#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define s(a,b,c) (a+b+c)/2
#define area(s,a,b,c) sqrt(s*(s-a)*(s-b)*(s-c))
int main()
{
	int a, b, c;
	while (scanf("%d %d %d", &a, &b, &c) != EOF)
	{
		printf("%lf %lf\n", (double)s(a, b, c), area((double)s(a, b, c), a, b, c));
	}
	return 0;
	system("pause");
}
