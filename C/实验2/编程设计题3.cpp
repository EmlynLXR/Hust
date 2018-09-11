#include<stdio.h>
#include<math.h>
/* 函数原型：计算f(x) */
double f(double);
/* 函数原型：计算f(x)的导数 */
double ff(double);
int main()
{
	double x = 3;
	double xx = x - f(x) / ff(x);
	while (fabs(xx - x)>1e-6)
	{
		x = xx;
		xx = x - f(x) / ff(x);
	}
	printf("%lf\n", xx);
}
/*函数介绍：计算f(x)
输入参数：double x
返 回 值：f(x)*/
double f(double x)
{
	return (3 * pow(x, 3) - 4 * pow(x, 2) - 5 * x + 13);
}
/*
函数介绍：计算f(x)
输入参数：double x
返 回 值：f(x)的导数
*/
double ff(double x)
{
	return (9 * pow(x, 2) - 8 * x - 5);
}

