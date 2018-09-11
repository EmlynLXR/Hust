#include<stdio.h> 
#include<stdlib.h>
#define M 10
#define N 20
int getnumber()
{
	char c; int m;
L:	c = getchar();
	if (c == '.') return -1;
	switch (c)
	{
	case '0':m = 0; break;
	case '1':m = 1; break;
	case '2':m = 2; break;
	case '3':m = 3; break;
	case '4':m = 4; break;
	case '5':m = 5; break;
	case '6':m = 6; break;
	case '7':m = 7; break;
	case '8':m = 8; break;
	case '9':m = 9; break;
	default: goto L;
	}
	return m;
}
int main()
{
	int a[N + M + 1], b[N + M + 1], i;
	bool flag = 0;
	printf("请输入第一个数：");
	for (i = M + N; i >= 0; i--)
	{
		a[i] = getnumber();
	}
	printf("请输入第二个数：");
	for (i = M + N; i >= 0; i--)
	{
		b[i] = getnumber();
	}
	for (i = 0; i <= M + N; i++)
	{
		if (a[i] == -1) continue;
		a[i] += b[i];
		if (flag)
			a[i]++;
		flag = 0;
		if (a[i] >= 10)
		{
			a[i] -= 10;
			flag++;
		}
	}
	printf("运算结果为：");
	for (i = M + N; i >= 0; i--)
	{
		if (a[i] == -1) printf(".");
		else printf("%d", a[i]);
	}
}