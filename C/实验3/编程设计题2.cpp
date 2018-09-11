#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int IsPrime(int m)
{
	int k, limit;
	if (m == 2)return 1;
	if (!(m % 2))return 0;
	limit = m / 2;
	for (k = 3; k <= limit; k += 2)
		if (!(m%k))return 0;
	return 1;
}
int main(void)
{
	int begin, end, x, k, j;
	bool flag;
	while (scanf("%d %d", &begin, &end) && begin != 0)
	{
		x = (begin % 2 == 0) ? begin - 2 : begin - 1;
		while (begin >= 0 && end >= begin)
		{
			x = x + 2;
			if (x > end)
			{
				printf("\n"); break;
			}
			flag = true;
			for (k = 2; k <= x / 2 && flag == true; k++)
			{
				for (j = k; j <= x&&flag == true; j++)
				{
					if (IsPrime(j) && IsPrime(k) && x == (j + k))
					{
						printf("%d=%d+%d\n", x, k, j); flag = false;
					}
				}
			}
		}
	}
	system("pause");
}

