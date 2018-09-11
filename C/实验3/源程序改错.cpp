#include "stdio.h"
long sum_fac(int);
int main()
{
	int k;
	for (k = 1; k<6; k++)
		printf("k=%d\tthe sum is %ld\n", k, sum_fac(k));
}
long sum_fac(int n)
{
	long s = 0;
	int i;
	long fac = 1;//long fac;
	for (i = 1; i <= n; i++)
	{
		fac *= i;
		s += fac;
	}
	//fac*=i;
	//s+=fac;
	return s;
}
