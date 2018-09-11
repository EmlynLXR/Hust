#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
void change();
void sum_and_avg(int n);
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
	return 0;
}
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
