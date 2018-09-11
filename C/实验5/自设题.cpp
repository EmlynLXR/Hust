#include <stdio.h>
#include<stdlib.h>
void reverse();
int main()
{
	printf("input:\n");
	reverse();
	system("pause");
	return 0;
}
void reverse()
{
	int i, j;
	char c, ch[10];
	for (i = 0; i<10; i++)
	{
		c = getchar();
		if (c == ' ' || c == '\t' || c == '\n')
	    		break;
		ch[i] = c;
	}
	if (c != '\n')
	{
		reverse();
	}
	for (j = 0; j<i; j++)
	{
		putchar(ch[j]);
	}
	printf(" ");
}
