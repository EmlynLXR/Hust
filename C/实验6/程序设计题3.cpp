#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 4
void s_sort(int a[], int x, int y);
int main(int argc, char *argv[])
{
    int flag;
    if (argc > 2) printf("error\n");
    else
    {
        if (argc == 2)
        {
            if(strcmp(argv[1], "-d"))    
                printf("error\n");
            else  flag = 1;
        }
        else flag = 0;
    }
    int i;
    int a[n];
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    void(*p)(int a[], int x, int y);
    p = s_sort;
    p(a, n, flag);

    return 0;
}
void s_sort(int a[], int x, int y)
{
    int i, j, t;
    for (i = 0; i < x - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if ((y) ? (a[j] > a[i]) : (a[j] < a[i]))
            {
                t = a[j];
                a[j] = a[i];
                a[i] = t;
            }
        }
    }
    for (i = 0; i < x; i++)
        printf("%d ", a[i]);
    printf("\n");
}

