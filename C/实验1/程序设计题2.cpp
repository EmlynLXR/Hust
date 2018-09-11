#include<stdio.h>
int main()
{
	unsigned short x,m,n;
	printf("输入x、m（0~15）和n（1~16-m）：\n ");
	scanf("%hu%hu%hu",&x,&m,&n);
	if(m>=0&&m<=15&&n>=1&&n<=(16-m))//判断m、n的值是否在合理范围内 
	{
		x=(x>>m)<<(16-n);
		printf("ans=%hu\n",x);
	}
	else
		printf("输入错误！\n");
	return 0;
}
