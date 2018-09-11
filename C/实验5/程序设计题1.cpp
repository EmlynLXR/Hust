#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[3][4], b[4][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			scanf_s("%d", &a[i][j]);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			b[i][j] = a[j][i];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
			printf("%5d", b[i][j]);
		printf("\n");
	}
	system("pause");
}