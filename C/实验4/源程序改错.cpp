#include "stdio.h"
#include<stdlib.h>
#define SUM a + b
#define DIF a - b
#define SWAP(a, b)  t=a,a = b, b = t//#define SWAP(a, b)  a = b, b = a
void main()//void main
{
	int a, b, t;//int b, t;
    printf("Input two integers a, b:");
    scanf_s("%d,%d", &a, &b);
	printf("\nSUM=%d\n the difference between square of a and square of b is:%d", SUM, (SUM)*(DIF));
	// printf("\nSUM=%d\n the difference between square of a and square of b is:%d",SUM, SUM*DIF);
	SWAP(a, b);
	printf("\nNow a=%d,b=%d\n", a, b);//Printf("\nNow a=%d,b=%d\n", a, b);
	system("pause");
}