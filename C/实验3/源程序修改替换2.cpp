#include "stdio.h"
long double sum_fac(int);
int main(void)
{
	int k;
	for (k = 1; k<6; k++)
		printf("k=%d\tthe sum is %llf\n", k, sum_fac(k));
}
long double sum_fac(int n)
{
	static long double s = 0;
	static long double fac = 1;
	fac *= 1 / (long double)n;
	s += fac;
	return s;
}
