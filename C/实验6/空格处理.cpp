/*（2）利用大小为n的指针数组指向用gets函数输入的n行，每行不超过80个字符。
编写一个函数，它将每一行中连续的多个空格字符压缩为一个空格字符。
在调用函数中输出压缩空格后的各行，空行不予输出。*/

#include <stdio.h>  
void ChangeInput(void) 
{ 
	for(;;)
	{
		char s[100][80];     
    	char *p[100];     
    	int i,n; 
	    scanf("%d",&n);
    	if(!n) break;
    	getchar();
    	for (i=0; i<n; i++)     
		{
			fgets(s[i],80,stdin);         
	     	p[i] = s[i];     
		} 
        for (i=0; i<n; i++)     
		{ 
			int j; 
            for (j=0; p[i][j]!='\0';j++ )
			{ 
				if (p[i][j]==' ' && p[i][j+1]==' ')             
				{ 
					int k=j+1; 
                    while (p[i][k++]==' ');                 
     				k--; 
                    int tmp=j+1; 
                    while (p[i][tmp++]=p[i][k++]);             
				}  
			}     
		}      
        for (i=0; i<n; i++)
			if(p[i][0]!='\n') printf("%s",*(p+i));
			putchar('\n');
	}   
}
int main(void)
{ 
    ChangeInput();     
	return 0; 
}  







 