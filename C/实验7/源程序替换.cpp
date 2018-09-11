#include "stdio.h"
#include "stdlib.h"
struct s_list{ 
int data; /* 数据域 */
struct s_list *next; /* 指针域 */ 
} ;
void create_list (struct s_list **headp,int *p);
int main(void)//void main(void)
{
	struct s_list *head=NULL,*p;
	int s[]={1,2,3,4,5,6,7,8,0}; /* 0为结束标记 */
	create_list(&head,s); 
	p=head; /*遍历指针p指向链头 */
	while(p){
		printf("%d\t",p->data); /* 输出数据域的值 */
		p=p->next; /*遍历指针p指向下一结点 */
	}
	printf("\n");
}
void create_list(struct s_list **headp,int *p)
{
    struct s_list * loc_head=NULL,*tail;
    struct s_list * temp;
    if(p[0]==0) 
    ;
    else { 
        loc_head=(struct s_list *)malloc(sizeof(struct s_list));
        loc_head->data=*p++; 
        tail=loc_head; 
        while(*p){ 
            temp=(struct s_list *)malloc(sizeof(struct s_list));
            temp->next=loc_head; 
            loc_head=temp;   
            loc_head->data=*p++; 
            }
        tail->next=NULL; 
        }
    *headp=loc_head; 
}

