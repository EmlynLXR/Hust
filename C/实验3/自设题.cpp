#include<stdio.h>
#include<stdlib.h>
void swapdate1(int, int);
void swapdate2(int*, int*);
int main()
{
	int x, y;
	scanf("%d %d", &x, &y);
	printf("main x=%d,y=%d\n", x, y);
	swapdate1(x, y);
	printf("main x=%d,y=%d\n", x, y);
	swapdate2(&x, &y);
	printf("main x=%d,y=%d\n", x, y);
	system("pause");
	return 0;
}
void swapdate1(int x, int y)
{
	int temp;
	temp = x; x = y; y = temp;
	printf("swapdate1:x=%d,y=%d\n", x, y);
}
void swapdate2(int *x, int *y)
{
	int temp;
	temp = *x; *x = *y; *y = temp;
	printf("swapdate1:x=%d,y=%d\n", *x, *y);
} 

