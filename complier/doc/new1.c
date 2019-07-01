#include"stdafx.h" 
#include"conio.h"    //包含getch函数的头文件
#include"stdlib.h"    //包含exit函数的头文件
#include <stdio.h>
#include <string.h>
char prog[81],token[8],ch,tmp;
int syn,p,m,n,sum,rows;
char *rwtab[6]={"begin","if","then","while","do","end"};
void scaner();
void main()
{
FILE *out;
FILE *in;

rows=1;
if((out=fopen("d:\\output.txt","wt"))==NULL)
{printf("\non error buiding d:\\output.txt\n");
getch();
exit(1);
}
if((in=fopen("d:\\input.txt","rt"))==NULL)
{printf("\nConn't found d:\\input.txt\n");
getch();
exit(1);
}/* printf("\n please input a string(end with '#'):\n");*/
rewind(in);
rewind(out);
fprintf(out,"%-5s%-10s%-5s%5s\n","type","name","rows","cols");
do{
p=0;
 do
 {     /*scanf("%c",&ch);*/
    if(p==80)
    {printf("\non error colunm's length more than 80!\n");
    getch();
    exit(1);
    }
    ch=fgetc(in);
    prog[p++]=ch;
    }while(ch!=EOF&&ch!='\n');
    prog[p]='#';
    tmp=ch;
 p=0;
 do{
    scaner();
    switch(syn)
     {case 11:fprintf(out,"%-5d%-10d%-5d%5d\n",syn,sum,rows,p);
          break;
      case -1:printf("you have input a wrong string,rows cols=(%d,%d)\n",rows,p);
          getch();
          exit(0);
      default:if(syn!=0) fprintf(out,"%-5d%-10s%-5d%5d\n",syn,token,rows,p);
          break;
      }
    }while(syn!=0);
    if(tmp=='\n') rows++;
  }while(ch!=EOF);
  fclose(in);
  fclose(out);
}

void scaner()
 {  sum=0;
    for(m=0;m<8;m++)token[m++]=NULL;
    ch=prog[p++];
    m=0;
 while((ch==' ')||(ch=='\n'))ch=prog[p++];
 if(((ch<='z')&&(ch>='a'))||((ch<='Z')&&(ch>='A')))
 { while(((ch<='z')&&(ch>='a'))||((ch<='Z')&&(ch>='A'))||((ch>='0')&&(ch<='9')))
        {   token[m++]=ch;
            ch=prog[p++];
        }
      p--;
      syn=10;
      for(n=0;n<6;n++)
    if(strcmp(token,rwtab[n])==0)
       { syn=n+1;
         break;
       }
 }
 else if((ch>='0')&&(ch<='9'))
 { while((ch>='0')&&(ch<='9'))
        {   sum=sum*10+ch-'0';
            ch=prog[p++];
        }
    p--;
    syn=11;
 }
    else switch(ch)
    { case '<':token[m++]=ch;
          ch=prog[p++];
           if(ch=='=')
            {  syn=22;
               token[m++]=ch;
            }
          else
            {  syn=20;
               p--;
            }
          break;
     case '>':token[m++]=ch;
          ch=prog[p++];
          if(ch=='=')
            { syn=24;
              token[m++]=ch;
            }
          else
            { syn=23;
              p--;
            }
          break;
     case '+': token[m++]=ch;
          ch=prog[p++];
          if(ch=='+')
            { syn=17;
              token[m++]=ch;
            }
          else
            { syn=13;
              p--;
            }
          break;

     case '-':token[m++]=ch;
          ch=prog[p++];
          if(ch=='-')
            { syn=29;
              token[m++]=ch;
            }
          else
            { syn=14;
              p--;
            }
          break;

     case '!':ch=prog[p++];
          if(ch=='=')
           { syn=21;
             token[m++]=ch;
           }
          else
          { syn=31;
             p--;
          }
          break;

     case '=':token[m++]=ch;
          ch=prog[p++];
          if(ch=='=')
            { syn=25;
              token[m++]=ch;
            }
          else
            { syn=18;
              p--;
            }
          break;
     case '*': syn=15;
           token[m++]=ch;
           break;
     case '/': syn=16;
           token[m++]=ch;
           break;
     case '(': syn=27;
           token[m++]=ch;
           break;
     case ')': syn=28;
           token[m++]=ch;
           break;
     case '{': syn=5;
           token[m++]=ch;
           break;
     case '}': syn=6;
           token[m++]=ch;
           break;
     case ';': syn=26;
          token[m++]=ch;
          break;
     case '\"': syn=30;
           token[m++]=ch;
           break;
     case EOF:syn=0;break;
     case '#': syn=0; break;
     case ':':syn=17;
           token[m++]=ch;
           break;
    default: syn=-1;
         break;
       }
token[m++]='\0';
} 