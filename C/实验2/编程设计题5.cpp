#include<stdio.h>
#include<stdbool.h>
int main()
{
	int N;
	scanf("%d", &N);
	getchar();
	for (int k = 0; k<N; k++)//控制输入N组数据
	{
		int i = 0;
		bool flag = true;
		char c;
		while ((c = getchar()) != '\n')//循环输入单个字符c
		{
			if (flag == true && c == ' ')//3.1
			{
				putchar(c);
				flag = false;
			}
			if (flag == true && c != ' ')//3.2
			{
				printf("%c", c);
			}
			if (flag == false && c != ' ')//3.3
			{
				printf("%c", c);
				flag = true;
			}
			else continue;
		}
		printf("\n");
	}
}

