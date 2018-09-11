#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>

#define FALSE -1 
#define OK 1
#define ERROR -2 
#define TRUE 1
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
struct ListNode {
	ElemType data;
	struct ListNode *next;
};
struct MultiList {
	struct ListNode *ListHead;				/*指向一个线性表的头节点*/
	int num;									/*线性表的编码*/
	struct MultiList *next;			/*指向下一个表头节点*/
};

void show(MultiList *List);
status IntiaList(ListNode *L);
status InitiaList2(MultiList *head, MultiList **List);
status DestroyList(ListNode* L);
status DestroyList2(MultiList *head, MultiList **List);
status ClearList(ListNode *L);
status ListEmpty(ListNode L);
int ListLength(ListNode L);
status GetElem(ListNode L, int i, ElemType *e);
status LocateElem(ListNode L, ElemType e);
status PriorElem(ListNode L, ElemType cur, ElemType *pre_e);
status NextElem(ListNode L, ElemType cur, ElemType *next_e);
status ListInsert(ListNode * L, int i, ElemType e);
status ListDelete(ListNode * L, int i, ElemType * e);
status ListTrabverse(ListNode L);
status MultiListTrabverse(MultiList head);
status SaveList(FILE *fp, ListNode L, char filename[30]);
status LoadList(FILE *fp, ListNode *L, char filename[30]);
MultiList *ExList(MultiList *head);

int main()
{
	struct MultiList* head = (MultiList *)malloc(sizeof(MultiList));
	head->ListHead = NULL; head->next = NULL; head->num = 0;
	struct MultiList* List;
	List = head->next;

	FILE  *fp=NULL;
	char filename[30];	/*存储文件名*/

	int op = 1;
	status a;
	int i = 0, cur,num1,num2;
	ElemType e = 0, e1 = 0;
	ElemType pre_e = 0, next_e = 0;
	while (op)
	{
		show(List);
		scanf("%d", &op);
		switch (op)
		{
		case 0:
			break;
		case 1:
			if (InitiaList2(head, &List) == OK)
				printf("线性表创建成功！\n");
			else
				printf("线性表创建失败！\n");
			getchar(); getchar();
			break;
		case 2:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				if (DestroyList2(head, &List) != ERROR)
					printf("线性表销毁成功！\n");
				else
					printf("线性表销毁失败！\n");
			}
			getchar(); getchar();
			break;
		case 3:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				if (ClearList(List->ListHead) != ERROR)
					printf("线性表置空成功！\n");
				else
					printf("线性表置空失败！\n");
			}
			getchar(); getchar();
			break;
		case 4:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				if (ListEmpty(*(List->ListHead)) != ERROR)
					printf("线性表为空表！\n");
				else
					printf("线性表不为空表！\n");
			}
			getchar(); getchar();
			break;
		case 5:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
				printf("线性表的长度为%d", ListLength(*(List->ListHead)));
			getchar(); getchar();
			break;
		case 6:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入所要查找的元素的位序：");
				scanf("%d", &i);
				if (GetElem(*(List->ListHead), i, &e) != ERROR)
					printf("第%d的元素为%d", i, e);
			}
			getchar();getchar();
			break;
		case 7:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入所要进行对比的元素e：");
				scanf("%d", &e);
				a = LocateElem(*(List->ListHead), e);
				if (a != ERROR&&a!=0)
					printf("第%d个元素与元素e相同。", a);
				else  if(a==0)
					printf("不存在与e相同的元素！");
				else
					printf("该表为空表，定位失败。\n");
			}
			getchar();getchar();
			break;
		case 8:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入数据元素cur：");
				scanf("%d", &cur);
				if (PriorElem(*(List->ListHead), cur, &pre_e) == OK)
					printf("%d的前驱数据元素为%d", cur, pre_e);
			}
			getchar();getchar();
			break;
		case 9:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入数据元素cur：");
				scanf("%d", &cur);
				if (NextElem(*(List->ListHead), cur, &next_e) != ERROR)
					printf("%d的后继数据元素为%d", cur, next_e);
			}
			getchar();getchar();
			break;
		case 10:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入所要插入的位置i：");
				scanf("%d", &i);
				printf("请输入要插入的元素e：");
				scanf("%d", &e);
				if (ListInsert(List->ListHead, i, e) == OK)
					printf("插入元素成功！");
				else
					printf("插入元素失败！");
			}
			getchar();getchar();
			break;
		case 11:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入要删除的元素的位序i：");
				scanf("%d", &i);
				if (ListDelete(List->ListHead, i, &e) == OK)
					printf("位序为%d的元素的值为%d\n删除元素成功！", i, e);
				else
					printf("删除元素失败！");
			}
			getchar();getchar();
			break;
		case 12:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
				ListTrabverse(*(List->ListHead));
			getchar(); getchar();
			break;
		case 13:
			if (List == NULL)
				printf("当前没有活动表,不能进行文件读取。\n");
			else
				SaveList(fp, *(List->ListHead), filename);
			getchar();getchar();
			break;
		case 14:
			if (List == NULL)
				printf("当前没有活动表,不能进行文件读取。\n");
			else
				LoadList(fp, List->ListHead, filename);
			getchar();getchar();
			break;
		case 15:
			if (head->next== NULL)
			{
				printf("没有可操作的表。");
				getchar();	getchar();
				break;
			}
			if (MultiListTrabverse(*head) == NULL)
				break;
			List = ExList(head);
			getchar();
			break;
		default:
			printf("功能选择是无效的输入。\n");
			getchar(); getchar();
		}
	}
	printf("欢迎下次再使用本系统！\n");
	getchar();	getchar();
}
/******************
* 函数名称：ExList
* 函数参数：MultiList的头指针
* 函数功能：进行多表切换操作
* 返回值：一个指向切换后的活动表的指针
*******************/
MultiList* ExList(MultiList *head)
{
	int num;
	printf("请输入想要进行操作的表的编号：");
	scanf("%d", &num);
	MultiList * List = head->next;
	if(num<1)
	{
		printf("输入的编码不合法。\n");
		getchar(); 
	}
	for (int i = 1; i<num&&List != NULL; i++)
		List = List->next;
	if (List == NULL)
	{
		printf("输入的编码不合法。\n");
		getchar(); 
	}
	return List;
}
/******************
*函数名称：MultiListTrabverse
*函数参数：MultiList头指针head
*函数功能：依次显示每一个线性表的编码、表长以及线性表中的每个元素。
*返回值：成功遍历返回总线性表的长度，否则返回ERROR
******************/
status MultiListTrabverse(MultiList head)
{
	MultiList *p = (&head)->next;
	if (p == NULL)
		printf("当前无线性表存在。\n");
	while (p)
	{
		printf("工作表：%d\t", p->num);
		ListTrabverse(*p->ListHead);
		printf("\n");
		p = p->next;
	}
	getchar();
	return OK;
}
/******************
*函数名称：LoadList
*函数参数：文件指针，线性表L,文件名filename[30]
*函数功能：数据加载，为线性表输入元素。
*返回值：加载成功返回OK，加载失败返回ERROR
******************/
status LoadList(FILE *fp, ListNode *L, char filename[30])
{
	int e,i=0;
	printf("请输入要导入数据的文件名: ");
	scanf("%s",filename,30);
	if ((fp=fopen(filename, "r+")) == NULL)
	{
		printf("文件打开失败！\n");
		return ERROR;
	}
	L->data = 0;
	while (fscanf(fp, "%d", &e) != EOF)
	{
			i++;
			printf("读入第%d个元素%d...\n", i, e);
			ListInsert(L, i, e);
	}
	getchar();
	
	printf("导入完毕.");
	fclose(fp);
	return OK;
}
/******************
*函数名称：SaveList
*函数参数：文件指针，线性表L的头结点，文件名filename[30]
*函数功能：将L中的数据保存到fp指针指向的文件中
*返回值：成功返回OK，失败返回ERROR
******************/
status SaveList(FILE *fp, ListNode L, char filename[30])
{
	printf("请输入要写入的文件名: ");
	scanf("%s",filename);
	if ((fp=fopen(filename, "w")) ==NULL)
	{
		printf("文件打开失败。");
		getchar();
		return ERROR;
	}
	ListNode*p = &L;
	for (int i = 0; i < L.data&&p!=NULL; i++)
	{
		p = p->next;
		fprintf(fp, "%d ", p->data);
	}
	printf("文件写入成功。\n");
	fclose(fp);			
	return OK;
}
/******************
*函数名称：ListTrabverse
*函数参数：线性表L的头结点
*函数功能：依次显示线性表中的每个元素。
*返回值：成功遍历返回线性表的长度，否则返回ERROR
******************/
status ListTrabverse(ListNode L) 
{
	ListNode*q = &L;
	int i;
	if (L.data == 0)
	{
		printf("线性表是空表！\n");
	}
	else
		printf("表长：%d\n", L.data);
	printf("-----------all elements -----------------------\n");
	for (i = 0; i < L.data; i++)
	{
		q = q->next;
		printf("%3d ", q->data);
	}
	printf("\n------------------ end ------------------------\n");
	return OK;
}
/******************
*函数名称：ListDelete
*函数参数：线性表L的头指针，删除的位序i，指针e的地址。
*函数功能：删除L的第i个数据元素，用e返回其值。
*返回值：成功删除返回OK，否则返回ERROR
******************/
status ListDelete(ListNode* L, int i, ElemType * e)
{
	if (i<1 || i>L->data)
	{
		printf("i值不合法，");
		return ERROR;
	}
	ListNode *q = L;
	for (int j = 0; (j + 1) != i; j++)
		q = q->next;
	ListNode *p = q->next;
	q->next = p->next;
	*e = p->data;
	p->next = NULL;
	free(p);
	L->data--;
	return OK;
}
/******************
*函数名称：ListInsert
*函数参数：线性表L的头指针，插入的位置i，插入的数据元素e。
*函数功能：在L的第i个位置之前插入新的数据元素e。
*返回值：成功插入返回OK，否则返回ERROR
******************/
status ListInsert(ListNode* L, int i, ElemType e)
{
	if (i<1 || i>L->data+1)
	{
		printf("i值不合法，插入失败。\n");
		return ERROR;
	}
	ListNode *q = L;
	for (int j = 0; (j + 1) != i; j++)
		q = q->next;
	ListNode *temp=(ListNode*)malloc(sizeof(ListNode));
	temp->data = e;
	temp->next=q->next;
	q->next = temp;
	L->data++;
	return OK;
}
/******************
*函数名称：NextElem
*函数参数：线性表L的头结点，查找的数据cur_e,后驱next_e；
*函数功能：查找L中与cur_e相同的第一个数据，并用next_e返回其后继
*返回值：成功则返回与cur_e相同的第一个数据，并返回OK；若无后驱以及其他情况则返回ERROR
******************/
status NextElem(ListNode L, ElemType cur, ElemType *next_e)
{
	int i= LocateElem(L, cur);
	if (i == ERROR || i == 0)
	{
		printf("%d 不是活动表中的元素\n", cur);
		return ERROR;
	}
	else if (i == L.data)
	{
		printf("%d is the last letter has no next_elem。\n", cur);
		return ERROR;
	}
	else
	{
		ListNode *q = &L;
		for (int j = 0; (j -1)!= i; j++)
			q = q->next;
		*next_e = q->data;
		return OK;
	}
}
/******************
*函数名称：PriorElem
*函数参数：线性表L的头结点，查找的数据cur,前驱pre_e；
*函数功能：查找L中与cur相同的第一个数据，并用pre_e返回其前驱
*返回值：成功则返回与cur相同的第一个数据，并返回OK；若无前驱以及其他情况则返回ERROR
******************/
status PriorElem(ListNode L, ElemType cur, ElemType *pre_e)
{
	int i = LocateElem(L, cur);
	if (i == ERROR || i == 0)
	{
		printf("%d 不是活动表中的元素\n", cur);
		return ERROR;
	}
	else if (i == 1)
	{
		printf("%d is the first letter has no prior_elem\n", cur);
		return ERROR;
	}
	else {
		ListNode *q = &L;
		for (int j = 0; (j+1) != i; j++)
			q = q->next;
		*pre_e = q->data;
		return OK;
	}
}
/******************
*函数名称：LocateElem
*函数参数：线性表L的头结点，相对比的元素值；
*函数功能：查找L中与e相同数据所在的位序；位序从1开始
*返回值：成功则返回第一个与e相同的数据的位序，不存在则返回0，其余情况返回ERROR
******************/
status LocateElem(ListNode L, ElemType e)
{
	int i = 1;
	if (L.data == 0)
		return ERROR;
	ListNode *q = (&L)->next;
	for (; q->data != e; )
	{
		q = q->next;
		i++;
		if (q == NULL)break;
	}
	if (i > L.data)
		return 0;
	else
		return i ;
}
/******************
*函数名称：GetElem
*函数参数：线性表L的头结点，e为第i个数据的地址；
*函数功能：查找并用e返回L中第i个元素的值；
*返回值：成功则返回OK，否则返回ERROR
******************/
status GetElem(ListNode L, int i, ElemType *e)
{
	if (L.data == 0)
	{
		printf("该表为空表，查找失败。\n");
		return ERROR;
	}
	if (i < 1 || i>L.data)
	{
		printf("i值不合法，i的取值范围应为1<=i<=%d。\n", ListLength(L));
		return ERROR;
	}
	ListNode *q = &L;
	for (int j=0;j!=i;j++)
		q = q->next;
	*e = q->data;
	return OK;
}
/******************
*函数名称：ListLength
*函数参数：线性表L的头结点
*函数功能：计算线性表L中数据元素个数；
*返回值：成功返回L中数据元素个数，失败返回ERROR
******************/
int ListLength(ListNode L)
{
	return L.data;
}
/******************
*函数名称：ListEmpty
*函数参数：线性表L的头结点
*函数功能：判断线性表是否为空
*返回值：若L为空表则返回OK，否则返回ERROR
******************/
status ListEmpty(ListNode L)
{
	if (L.data == 0)
		return OK;
	else
		return ERROR;
}
/******************
*函数名称：ClearList
*函数参数：线性表L的头指针
*函数功能：将线性表L重置为一个空表
*返回值：成功置空返回OK，否则返回ERROR
******************/
status ClearList(ListNode *L)
{
	if (L->next == NULL)
		return OK;
	DestroyList(L->next);
	L->data = 0;
	L->next = NULL;
	return OK;
}
/******************
*函数名称:DestroyList
*函数功能:释放表L的每一个结点的空间及头指针的空间
*输入参数:L存放指向ListNode的指针
*输出参数:无
*返回数值:失败返回ERROR,否则销毁成功返回OK
*调用说明:无
******************/
status DestroyList(ListNode *L)
{
	ListNode *q;
	while (L)
	{
		q = L->next;
		free(L);
		L = q;
	}
	return OK;
}
/******************
*函数名称：DestroyList2
*函数参数：MultiList的头指针head，遍历指针List，
*函数功能：销毁MultiList的结点List，最后List为空。
*返回值：成功销毁返回OK，否则返回ERROR
******************/
status DestroyList2(MultiList *head, MultiList **List)
{
	MultiList *p = head;
	MultiList *q = p;
	while (p != *List)
	{
		q = p;
		p = p->next;
	}
	q->next = p->next;
	if (DestroyList(p->ListHead) == ERROR)
		return ERROR;
	free(p);
	*List = NULL;
	return OK;
}
/******************
*函数名称:InitiaList
*函数功能:初始化表L,
*输入参数:List->HeadList,
*输出参数:被初始化后的L指针
*返回数值:当分配内存失败时返回ERROR,
*		 否则初始化表成功返回SUCCESS
******************/
status IntiaList(ListNode *L)
{
	if (L == NULL)//分配内存失败 
		return ERROR;
	L->next = NULL;
	L->data = 0;
	return OK;
}
/******************
* 函数名称：InitiaList2
* 函数参数：MultiList的头指针head，遍历指针List
* 函数功能：构造一个空的MultiList节点
* 返回值：成功构造返回OK，否则返回ERROR
******************/
status InitiaList2(MultiList *head, MultiList **List)
{
	MultiList *q = head;
	while (q->next)
	{
		q = q->next;
	}
	q->next = (MultiList *)malloc(sizeof(MultiList));
	*List = q->next;
	(*List)->num = q->num + 1;
	(*List)->ListHead = (ListNode*)malloc(sizeof(ListNode));
	if (IntiaList((*List)->ListHead) == ERROR)
		return ERROR;
	(*List)->next = NULL;
	return OK;
}
/******************
* 函数名称：show
* 函数参数：遍历指针List
* 函数功能：显示伪菜单界面
* 返回值：无
*******************/
void show(MultiList *List)
{
	system("cls");
	printf("\n\n");
	printf("      Menu for Linear Table On Chain Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList      9. NextElem\n");
	printf("    	  2. DestroyList    10.ListInsert\n");
	printf("    	  3. ClearList      11.ListDelete\n");
	printf("    	  4. ListEmpty      12.ListTrabverse\n");
	printf("    	  5. ListLength     13.SaveList\n");
	printf("    	  6. GetElem        14.LoadList\n");
	printf("	  7. LocateElem     15.ExList\n");
	printf("	  8. PriorElem      0. Exit\n");
	printf("-------------------------------------------------\n");
	if (List == NULL)
		printf("\n-----------当前没有活动表-----------\n");
	else
		printf("\n-----------当前对表 %d 进行操作-----------\n", List->num);
	printf("    请选择你的操作[0~15]:");
}
