#include <stdio.h>
int main(void)
{
	int i, n, s = 1;
	printf("Please enter n:");
	scanf("%d", &n);
	i = 0;
	while (s <= n)
	{
		i++;
		s = s*i;
	}
	printf("%d", i);
}
