#include<stdio.h>
#include<string.h>
#define M 80
void blank(char*p[100],int N);
int main()
{
   while(1)
   {
   	   int N;
       scanf("%d",&N);
       if(N==0)break;
       getchar();
       int i;
       char b[100][M];
       char *p[100];
       for(i=0;i<N;i++)
       {
             fgets(b[i],80,stdin);
             p[i]=b[i];
       }
       blank(p,N);
   }
}
void blank(char *p[100],int n)
{
	for(int i=0;i<n;i++)
    {
    	int j=0;
    	for (j = 0; p[i][j]!='\0'; j++)
    	{
    		if(p[i][j]==' '&&p[i][j+1]==' ')
    		{
    			int k=j+1,temp=j+1;
    			while(p[i][k++]==' ');
    			k--;j++;
    			for(;p[i][k]!='\0';k++,j++)
    			      p[i][j]=p[i][k];
    			p[i][j]='\0';
    		    j=temp;
    		}
    	}
	     if(p[i][0]!='\n')printf("%s", p[i]);
    }
    printf("\n");
}
/*#include <stdio.h>
#include <stdlib.h>
int foo(char* a)
{
    int i = 0, j = 0;
    while (a[i] != '\0')
    {
        a[j++] = a[i++];
        if (a[i] == ' ')
        {
            a[j++] = a[i++];
            while (a[i] == ' ') i++;
        }
    }
    a[j] = 0;
    return 0;
}
int main(void)
{
    int n = 2, i;
    char *buf[n];
    for (i = 0; i < n; i++)
    {
        buf[i] = (char*)malloc(80);
        gets(buf[i]);
    }
    for (i = 0; i < n; i++)
    {
        foo(buf[i]);
        printf("%d, %s\n", i + 1, buf[i]);
    }
for (i = 0; i < n; i++)
        free(buf[i]);
    return 0;
}*/
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 2
int s_delete(char *);
int main()
{
	int i;
	//int n;
	//scanf("%d",&n); 
	char a[80] = { 0 };
	char *p[n] ={NULL};
	for (i = 0; i < n; i++)
	{
		fgets(a, 80, stdin);//getsº¯Êý
		p[i]= (char *)malloc(strlen(a) + 1);
		strcpy(p[i],a);
	}
	for (i = 0; i <n; i++)
	{
		s_delete(p[i]);
	}
	system("pause");
	return 0;
}
int s_delete(char *p)
{
	enum CASE{COPY,DELETE};
	char other[80] = { 0 };
	int state = COPY;
	int j, m=0;
	for (j = 0; j < 100; j++)
	{
		if (p[j] == '\0') break;
		switch (state)
		{
		case COPY:
			if (p[j] == ' ')
			{
				other[m] = ' ';
				m++;
				state = DELETE;
			}
			else
			{
				other[m] = p[j];
				m++;
			}
			break;
		case DELETE:
			if (p[j] == ' ');
			else
			{
				other[m] = p[j];
				m++;
				state = COPY;
			}
			break;
		}
	}
	strcpy(p,other);
	printf("%s", p);
	return 0;
}*/
