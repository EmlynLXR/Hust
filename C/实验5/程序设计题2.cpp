#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<stdbool.h>
void fac(int);
int main()
{
	int N, i = 0; //scanf_s("%d ", &N);
	int a;
	/*for (i = 0; i < N; i++)
	scanf_s("%d", &s[i]);
	i = 0;
	while (i<N)
	{
	fac(s[i]);
	i++;
	}*/
	while ((scanf_s("%d", &a)) != EOF)
	{
		fac(a); i++;
	}
	system("pause");
}
void fac(int a)
{
	int n = sizeof(int)*CHAR_BIT;
	int i = 0;
	int s[100], b = 2;
	bool flag = true;
	if (a >= 0)flag = true;
	else
	{
		a = 0 - a; flag = false;
	}
	for (; a != 0; i++)
	{
		s[i] = a % b;
		a = a / 2;
	}
	for (; i < n; i++)
		s[i] = 0;
	if (flag == true);
	else
	{
		for (i = 0; i < n; i++)
			if (s[i] == 1)s[i] = 0;
			else s[i] = 1;
			s[0] = s[0] + 1;
			for (i = 0; i<n; i++)
				if (s[i] == 2) { s[i] = 0; s[i + 1]++; }
				else break;
	}
	for (i = n - 1; i >= 0; i--)
	{
		printf("%d", s[i]);
	}
	printf("\n");
}