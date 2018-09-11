#include<stdio.h>
#include<stdlib.h>
int main()
{
	char str[100];
	FILE *fp;
	int i,len=0;
	while((str[len]=getchar())!='\n')
	    len++;
	if(str[0]!=' ')str[0]=str[0]-32;
	for(i=1;i<len;i++)
	   	if(str[i-1]==' '&&str[i]!='\n')
	         str[i]=str[i]-32;
	fp=fopen("d:\\test.txt","w+");
  	i=0;
    while(str[i]!='\n')
    {
	   fputc(str[i],fp);
	   i++;
    } 
    fclose(fp);
}
