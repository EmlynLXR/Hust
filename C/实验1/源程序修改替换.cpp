#include<stdio.h>
int main( )
{
   int a, b;
   printf("Input two integers:");
   scanf("%d %d",&a,&b);
   a=a^b;   b=a^b;   a=a^b; 
  printf("\na=%d,b=%d",a,b);
   return 0;
}
/*#include<stdio.h>
int main( )
{
   int a, b, t;
   printf("Input two integers:");
   scanf("%d %d",&a,&b);
   a=b-a; b=b-a; a=b+a;
   printf("\na=%d,b=%d",a,b);
   return 0;
}*/

