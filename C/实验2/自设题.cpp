#include<stdio.h>
#include<stdlib.h>
int main()
{
	int N,i,j;
	printf("«Î ‰»Î±ﬂ≥§N£∫"); scanf_s("%d", &N);
	printf("\n");
	for ( i = 0; i < N; i++)
	{
		for (j = 0; j < N-i-1; j++)
			printf(" ");
		for (j = 0; j <= i; j++)
			printf("%c ", '*');
		printf("\n");
	}
	for (i = N - 1; i > 0; i--)
	{
		for (j = 1; j <= N - i; j++)
			printf(" ");
		for (j = 1; j <= i; j++)
			printf("%c ", '*');
		printf("\n");
	}
	system("pause");
	return 0;
}