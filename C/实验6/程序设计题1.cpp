#include<stdio.h>
void f(long x);
int main()
{
	long x[100];
	int N;scanf("%d",&N);
	for(int i=0;i<N;i++)
    {
        scanf("%ld",&x[i]);
    }
    for(int i=0;i<N;i++)
	{
		f(x[i]);
	    printf("\n");
	} 
}
void f(long x)
{
	char mask=0x0f;
	char *p=(char*)&x+3;
	for(int i=0;i<4;i++)
	{
		printf("%X ",((*p)>>4)&mask);
		printf("%X",(*p)&mask);
		if(i!=3)printf(" ");
		p--;
	}
}
