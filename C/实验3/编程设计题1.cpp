#include<stdio.h>
int max(int, int);
int main()
{
	int a, b;
	int i, j;
	while (scanf("%d %d", &a, &b))
	{
		if (a != 0 )
		{
			printf("%d\n",max(a, b));
		}
		else break;
	}
}
int max(int a, int b)
{
	if (a >= b)
	{
		if (a%b == 0)return b;
		else return max(a%b, b);
	}
	else
	{
		if (b%a == 0)return a;
		else return max(a, b%a);
	}
}
