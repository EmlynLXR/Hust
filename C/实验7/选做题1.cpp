#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*定义存入学生信息的结构*/
struct stu{
	char id[15];
	char name[20];
	float english;
	float math;
	float phy;
	float c;
	float sum;
	float avg;
	struct stu *next;	
};
/*定义输入的要修改的学生信息的结构*/
struct stu_change{
	char id[15];
	char sub[20];
	float score;
};
struct stu *head=NULL;
struct stu_change s[10];
void creat(int n);
void show(int n);
void sshow(int n);
void ssshow(int n);
void change();
void sum_and_avg(int n);
void sort(struct stu *head);
/*修改学生信息的函数*/
void change()
{
	int a;scanf("%d",&a);
	for(int i=0;i<a;i++)
	{
		scanf("%s",s[i].id);
		scanf("%s",s[i].sub);
		scanf("%f",&s[i].score);
	}
	for(int i=0;i<a;i++)
	{
		struct stu *p=(struct stu*)malloc(sizeof(struct stu));
		p=head;
	    while(p)
    	{
    		if(strcmp(p->id,s[i].id)==0)
	        {
	        	if(strcmp(s[i].sub,"English")==0)
	        	   {p->english=s[i].score;break;}
	        	else if(strcmp(s[i].sub,"Math")==0)
	        	   {p->math=s[i].score;break;}
	        	else if(strcmp(s[i].sub,"Physics")==0)
	        	   {p->phy=s[i].score;break;}
	        	else if(strcmp(s[i].sub,"C")==0)
	        	   {p->c=s[i].score;break;}
	        }
	        p=p->next;
        }
    }
} 
/*用交换结点数据域的方法升序排序的函数*/
void sort(struct stu *head)
{
	struct stu *p1=head,*p2;
	int len=0,i,j;
	char *temp1=(char*)malloc(15);
	char *temp2=(char*)malloc(20);
	float temp3;float temp4;float temp5;float temp6;float temp7;float temp8;
	while(p1){len++;p1=p1->next;}
	for(i=0,p1=head;i<len-1;i++,p1=p1->next)
	for(j=i+1,p2=p1->next;j<len;j++,p2=p2->next)
	if(p1->avg>p2->avg)
	{
		strcpy(temp1,p1->id);strcpy(p1->id,p2->id);strcpy(p2->id,temp1);
		strcpy(temp2,p1->name);strcpy(p1->name,p2->name);strcpy(p2->name,temp2);
		temp3=p1->english;p1->english=p2->english;p2->english=temp3;
		temp4=p1->math;p1->math=p2->math;p2->math=temp4;
		temp5=p1->phy;p1->phy=p2->phy;p2->phy=temp5;
		temp6=p1->c;p1->c=p2->c;p2->c=temp6;
		temp7=p1->sum;p1->sum=p2->sum;p2->sum=temp7;
		temp8=p1->avg;p1->avg=p2->avg;p2->avg=temp8;
	}
}
/*求各学生的总分和平均分的函数*/
void sum_and_avg(int n)
{
	struct stu *p=head;
	for(int i=0;i<n;i++)
	{
		p->sum=p->english+p->math+p->phy+p->c;
		p->avg=p->sum/4;
	    p=p->next;
    }
}
/*建立一个单向链表*/
void creat(int n)
{
    struct stu *p=head;
    scanf("%s",head->id);
	scanf("%s",head->name);
	scanf("%f",&head->english);
	scanf("%f",&head->math);
	scanf("%f",&head->phy);
	scanf("%f",&head->c);
	for(int i=1;i<n;i++)
	{
		p->next=(struct stu*)malloc(sizeof(struct stu));
		p=p->next;
		scanf("%s",p->id);
		scanf("%s",p->name);
		scanf("%f",&p->english);
		scanf("%f",&p->math);
		scanf("%f",&p->phy);
		scanf("%f",&p->c);
	}
	p->next=NULL;
}
int main()
{
	head=(struct stu*)malloc(sizeof(struct stu));
	int n;
	scanf("%d",&n);
	creat(n);
	show(n);
    change();
    printf("Alter:\n");
    show(n);
    sum_and_avg(n);
    printf("SumAndAvg:\n");
    sshow(n);
    sort(head);
    printf("Sort:(交换数据域)\n");
    ssshow(n);
	return 0;
}
/*输出学生信息的函数*/
void show(int n)
{
	printf("%-15s%-20s%-10s%-10s%-10s%-10s\n","ID","Name","English","Math","Physics","C");
    struct stu *p=head;
	for(int i=0;i<n;i++)
	{
		printf("%-15s",p->id);
		printf("%-20s",p->name);
		printf("%-10.2f",p->english);
		printf("%-10.2f",p->math);
		printf("%-10.2f",p->phy);
		printf("%-10.2f\n",p->c);
		p=p->next;
	}
	printf("\n");
}
/*输出学生总分和平均分的函数*/
void sshow(int n)
{
	printf("%-15s%-20s%-10s%-10s\n","ID","Name","SUM","AVG");
    struct stu *p=head;
	for(int i=0;i<n;i++)
	{
		printf("%-15s",p->id);
		printf("%-20s",p->name);
		printf("%-10.2f",p->sum);
		printf("%-10.2f\n",p->avg);
		p=p->next;
	}
	printf("\n");
}
/*输出排序后学生信息的函数*/ 
void ssshow(int n)
{
	printf("%-15s%-20s%-10s\n","ID","Name","AVG");
    struct stu *p=head;
	for(int i=0;i<n;i++)
	{
		printf("%-15s",p->id);
		printf("%-20s",p->name);
		printf("%-10.2f\n",p->avg);
		p=p->next;
	}
	printf("\n");
}
