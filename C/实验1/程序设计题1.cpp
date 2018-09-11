#include<stdio.h>
int main()
{
	char c;
	scanf("%c",&c);
	printf("%c",(c>='A'&&c<='Z')?(c-'A'+'a'):c);
	return 0;
}
