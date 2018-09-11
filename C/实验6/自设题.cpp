#include<stdio.h>
void fun(int *, int *, int *, int *);
int main()
{
    int  x[3], y[3], z[3][3], r[3], * pz;
    int  i,j;  
	pz = *z;
    printf("input x:");
    for(i=0; i<3; i++)
        scanf("%d", x+i);        
    printf("input y:");
    for(i=0; i<3; i++)
        scanf("%d", y+i);
    fun(x, y, pz, r);	   
	for(j=0; j<3; j++)
        printf("%3c ", *(pz + j));
    printf("\n");	
	for(i=1; i<3; i++)
    {
        for(j=0; j<3; j++)
            printf("%3d ", *(pz + 3*i + j));
        printf("\n");
    }
	printf("Result is: (%d)i + (%d)j + (%d)k\n", *r, *(r+1), *(r+2));
    return 0;
}
void fun(int *x, int *y, int *pz, int *r)
{
    int i, j;    
	j = 'i';
	for(i=0; i<3; i++)
			*(pz + i) = j++;    
    for(i=0; i<3; i++)
        *(pz + 3 + i) = *(x + i);
    for(i=0; i<3; i++)
        *(pz + 6 + i) = *(y + i);
    *(r + 0) = (*(x + 1)) * (*(y + 2)) - (*(x + 2)) * (*(y + 1));
    *(r + 1) = (*(x + 2)) * (*(y)) - (*(x)) * (*(y + 2));
    *(r + 2) = (*(x)) * (*(y + 1)) - (*(x + 1)) * (*(y));
}

