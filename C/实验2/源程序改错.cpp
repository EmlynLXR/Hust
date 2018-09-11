#include <stdio.h>
int main(void)//void main(void)
{
	int i, n, s = 1;
	printf("Please enter n:");
	scanf("%d", &n);//scanf("%d",n); 
	for (i = 1; i <= n; i++)//for(i=1,i<=n,i++)
		s = s*i;
	printf("%d! = %d", n, s);
}

