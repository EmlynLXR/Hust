#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	char ch;
	if(argc!=2){
		printf("Arguments error!\n");
		exit(-1);
	}
  	if(freopen(argv[1],"r",stdin)==NULL){    /*使stdin指向目标文件*/
	printf("Can't open %s file!\n",argv[1]);
	exit(-1);
	}	
    while((ch=getchar())!=EOF)    /* 从stdin中读字符 */
	   putchar(ch);                
	fclose(stdin);       /* 关闭stdin */
    return 0;	
}
