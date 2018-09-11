#include "stdio.h"
#include<stdlib.h>
int main(void)//void main(void)
{
     float *p;
     p=(float *)malloc(sizeof(float));
     scanf("%f",p);
     printf("%f\n",*p);
}

