#define  R
#include<stdio.h>
#include <assert.h>
int integer_fraction(float x);
int main(void)
{
	float  r = 0.0, s = 0.0;
	int s_integer = 0;
	printf("input a number: ");
	scanf("%f", &r);
#ifdef  R
	s = 3.14159*r*r;
	printf("area of round is: %f\n", s);
	s_integer = integer_fraction(s);
	printf("the integer fraction of area is %d\n", s_integer);
	assert((s - s_integer)<1.0);
#endif
}
int integer_fraction(float x)
{
	int i = (int)x;
	return i;
}

