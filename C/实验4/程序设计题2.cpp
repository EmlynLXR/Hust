#include<stdio.h>
#define CHANGE 1//#define CHANGE 0
int main()
{
	int N;
	scanf("%d", &N);
	getchar();
	for (int j = 0; j < N; j++)
	{
		char c;
		int i = 0;
		char s[100];
		fgets(s, 100, stdin);
		c = s[0];
#if CHANGE
for (i = 0; s[i] != '\0'; i++)
		   {
			if (s[i] >= 97 && s[i] <= 122)
				printf("%c", s[i] - 32);
			else if (s[i] >= 65 && s[i] <= 90)
				printf("%c", s[i] + 32);
			else printf("%c", s[i]);
		}
#else
		for (i = 0; s[i] != '\0'; i++)
		{
			printf("%c", s[i]);
		}
#endif
	    }
}



