#include<stdio.h>
#include<stdlib.h>
#define max(x,y,z)  (x>y?(x>z?x:z):(y>z?y:z))
float sum(float x, float y);
int main()//void main(void)
{
	int a, b, c;
	float d, e;
	printf("Enter three integers:");
	scanf("%d,%d,%d", &a, &b, &c);
	printf("\nthe maximum of them is %d\n", max(a, b, c));

	printf("Enter two floating point numbers:");
	scanf("%f,%f", &d, &e);
	printf("\nthe sum of them is  %f\n", sum(d, e));
	system("pause");
}

/*int max(int x, int y, int z)
{
	int t;
	if (x>y)
		t = x;
	else
		t = y;
	if (t<z)
		t = z;
	return t;
}*/

float sum(float x, float y)
{
	return x + y;
}
