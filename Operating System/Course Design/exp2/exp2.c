#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char*argv[])
{
	char *readPath=(char *)malloc(10*sizeof(char));
	char *writePath=(char *)malloc(10*sizeof(char));
	if(argc==1)
	{
		printf("Source:");scanf("%s",readPath);getchar();
		printf("Target:");scanf("%s",writePath);getchar();
	}
	else if(argc==2)
	{
		readPath=argv[1];
		char*str=(char *)malloc(10*sizeof(char));
		strcpy(str,argv[1]);
		char*tail=(char *)malloc(10*sizeof(char));
		int i,j,k;		
		for(i=0;i<strlen(str);i++)
			if(str[i]=='.')break;
		k=strlen(str);
		for(j=0;i<strlen(str);i++,j++)	
			tail[j]=str[i];
		tail[j]='\0';
		for(;k>=i-j;k--)
			str[k]='\0';
		strcat(str,"_Copy");
		strcat(str,tail);
		strcpy(writePath,str);
	}
	else if(argc==3)
	{
		readPath=argv[1];
		writePath=argv[2];
	}
	else
	{
		printf("Input error!\n");
		return -1;
	}
	printf("Source:%s\n",readPath);
	printf("Target:%s\n",writePath);



	if(syscall(333,readPath,writePath)==0)
		printf("Success!\n");
	else
		printf("Failed!\n");
	
	return 0;
}
