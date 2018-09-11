#include<stdio.h>
int main()
{
	unsigned long a;
	scanf("%ul",&a);
	int str[4];
	for(int i=0;i<4;i++)
	{
		str[i]=a%256;
		a=a/256;
	}
	printf("%d.%d.%d.%d",str[0],str[1],str[2],str[3]);
}

