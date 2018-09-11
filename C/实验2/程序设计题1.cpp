#include<stdio.h>
int main()
{
	int str[100][100];
	int i, j;
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (i = 0, j = 0; i<n; i++)str[i][j] = 1;
		for (i = 0; i<n; i++) { for (j = 0; j <= i; j++)	if (i == j) str[i][j] = 1; }
		for (i = 2; i<n; i++)
		{
			for (j = 1; j <= i - 1; j++)
				str[i][j] = str[i - 1][j - 1] + str[i - 1][j];
		}
		for (i = 0; i<n; i++)
		{
			for (int k = 0; k<2 * (n - i - 1); k++)printf(" ");
			for (j = 0; j <= i; j++)
			{
				if (j == 0)printf("%d", str[i][j]);
				else printf("%4d", str[i][j]);
				if (i == j)printf("\n");
			}
		}
	}
}
