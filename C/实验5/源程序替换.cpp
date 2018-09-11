#include<stdio.h>
#include<stdlib.h>
#define M 10
#define N 3
int main()
{
	int i, k = 0, count = M, a[M];
	for (i = 0; i < M; i++)
		a[i] = 1;//a数组的每个元素初值为1，表示所有人都在圈内
	for (i = 0;; i++)
	{
		if (a[i] == 0)//说明这个人已经不再圈里
		{
			if (i == M - 1)
				i = -1;
			continue;
		}
		k++;
		if (k == N)
		{
			a[i] = 0;
			printf("%6d", i + 1);
			k = 0;
			count--;
		}
		if (count == 0)
			break;
		if (i == M - 1)//如果到大数组末尾，就跳到数组头部
			i = -1;
	}
	printf("\n");
	system("pause");
}
