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
struct SqList{  
	ElemType * elem;//指向线性表数据的线性存储区
	int length;//表中元素的个数	
	int listsize;//表的最大元素个数
};
struct MultiList {
	SqList *L;				/*指向一个线性表*/
	int num;				/*自动生成的表的编码*/ 
	struct MultiList *next;	/*指向下一个表节点*/
};
status IntiaList(SqList *L);
status InitiaList2(MultiList *head, MultiList **List);
status DestroyList2(MultiList *head, MultiList **List);
status ClearList(SqList *L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType *e);
status LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType cur, ElemType *pre_e);
status NextElem(SqList L, ElemType cur, ElemType *next_e);
status ListInsert(SqList * L, int i, ElemType e);
status ListDelete(SqList * L, int i, ElemType * e);
status ListTrabverse(SqList L);
status MultiListTrabverse(MultiList *head);
void show();
void updata(MultiList *head);
MultiList *ExList(MultiList *head);
status SaveList(FILE *fp,SqList L, char filename[30]); 
status LoadList(FILE *fp,SqList *L,char filename[30]);

int main(void) {
	int op = 1;
	int i = 0, cur;
	ElemType e = 0,e1=0;
	ElemType pre_e = 0, next_e = 0;
	status a;

	FILE  *fp;
	char filename[30];	/*存储文件名*/

	MultiList head; head.L = NULL; head.next = NULL; 
	MultiList *List = head.next;

	int num;
	while (op) {
		show();
		if (List == NULL)
			printf("\n-----------当前没有活动表-----------\n");
		else
			printf("\n-----------当前对表 %d 进行操作-----------\n", List->num);
		scanf("%d", &op);getchar();
		switch (op) {
		case 1:
			if (InitiaList2(&head, &List) == OK)
				printf("线性表创建成功！\n");
			else
				printf("线性表创建失败！\n");
			getchar();
			break;
		case 2:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				if (DestroyList2(&head, &List) != ERROR)
					printf("线性表销毁成功！\n");
				else
					printf("线性表销毁失败！\n");
			}
			getchar();
			break;
		case 3:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				if (ClearList(List->L) == OK)
					printf("线性表重置成功！\n");
				else
					printf("当前没有活动表！\n");
			}
			getchar();
			break;
		case 4:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
				ListEmpty(*(List->L));
			getchar();
			break;
		case 5:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				a=ListLength(*(List->L));
				if (a!= ERROR)
					printf("线性表的长度为%d", a);
				else
					printf("当前没有活动表。\n");
			}
			getchar();
			break;
		case 6:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入所要查找的元素的位序：");
				scanf("%d", &i);
				if (GetElem(*(List->L), i, &e) != ERROR)
					printf("第%d的元素为%d", i, e);
					getchar(); 
			}
			getchar();
			break;
		case 7:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入所要进行对比的元素e：");
				scanf("%d", &e);
				a = LocateElem(*(List->L), e);
				if (a != ERROR)
					printf("第%d个元素与元素e相同。", a);
				else
					printf("不存在与e相同的元素！");
				getchar();
			}
			getchar(); 
			break;
		case 8:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入数据元素cur：");
				scanf("%d", &cur);
				if (PriorElem(*(List->L), cur, &pre_e) != ERROR)
					printf("%d的前驱数据元素为%d", cur, pre_e);
				getchar();
			}
			getchar(); 
			break;
		case 9:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入数据元素cur：");
				scanf("%d", &cur);
				if (NextElem(*(List->L), cur, &next_e) != ERROR)
					printf("%d的后继数据元素为%d", cur, next_e);
				getchar();
			}
			getchar(); 
			break;
		case 10:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入要插入的元素e：");
				scanf("%d", &e);
				printf("请输入所要插入的位置i：");
				scanf("%d", &i);
				if (ListInsert(List->L, i, e) == OK)
					printf("插入元素成功！");
				else
					printf("插入元素失败！");
				getchar();
			}
			getchar(); 
			break;
		case 11:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else
			{
				printf("请输入要删除的元素的位序i：");
				scanf("%d", &i);
				if (ListDelete(List->L, i, &e) == OK)
					printf("位序为%d的元素的值为%d\n删除元素成功！", i, e);
				else
					printf("删除元素失败！");
				getchar();	
			}
			getchar(); 
			break;
		case 12:
			if (List == NULL)
				printf("当前没有活动表。\n");
			else 
				ListTrabverse(*(List->L));
			getchar(); 
			break;
		case 13:
			if (List == NULL)
				printf("当前没有活动表,不能进行文件读取。\n");
			else
				SaveList(fp,*List->L,filename);
			getchar(); 
			break;
		case 14:
			if (List == NULL)
				printf("当前没有活动表,不能进行文件读取。\n");	
			else
				LoadList(fp,List->L,filename);
			getchar();
			break;
		case 15:
			if (head.next == NULL)
				printf("没有可操作的表。");
			MultiListTrabverse(&head);
			getchar();	
			break;
		case 16:
			if (head.next == NULL)
			{
				printf("没有可操作的表。");
				getchar();	getchar();
				break;
			}
			if(MultiListTrabverse(&head)==NULL)
				break;
			List=ExList(&head);
			break;
		case 0:
			break;
		default:
			printf("功能选择是无效的输入。\n");
			getchar();
		}
		updata(&head);
	}
	printf("欢迎下次再使用本系统！\n");
	getchar();	
}//end of main()
/******************
*函数名称：LoadList
*函数参数：文件指针，线性表L,文件名filename[30] 
*函数功能：数据加载，为线性表输入元素。
*返回值：加载成功返回OK，加载失败返回ERROR
******************/
status LoadList(FILE *fp,SqList *L,char filename[30])
{
	int e1,e;
	printf("请输入要导入数据的文件名: ");
	gets(filename);
	if ((fp=fopen(filename, "r+")) == NULL)
	{
		printf("文件打开失败！\n");
		return ERROR; 
	}
	while (fscanf(fp, "%d", &e1) != EOF)
	{
		L->length = 0;
		printf("表长：%d\n",e1);
		for (int i = 0; i < e1; )
		{
			fscanf(fp, "%d ", &e);
			i++;
			printf("读入第%d个元素%d...\n", i, e);
			ListInsert(L, i, e);
		}
	}
	printf("导入完毕.");
	fclose(fp);
	return OK;
}
/******************
*函数名称：SaveList
*函数参数：文件指针，线性表L,文件名filename[30] 
*函数功能：将L中的数据保存到fp指针指向的文件中
*返回值：OK
******************/ 
status SaveList(FILE *fp,SqList L,char filename[30])
{
	printf("请输入要写入的文件名: "); 
	gets(filename);
	if ((fp=fopen(filename, "w+"))== NULL)
	{
		printf("文件打开失败。");
		getchar();
		return ERROR;
	}
	for (int i = -1; i < L.length; i++)
	{
		if (i == -1)
		{
			fprintf(fp, "%d ", L.length);
			continue;
		}
		fprintf(fp, "%d ", *(L.elem + i));  
	}
	printf("文件写入成功。");
	fclose(fp);	
	return OK;
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
	scanf("%d",&num);
	MultiList * List = head;
	for (int i = 0;i<num&&List!=NULL; i++)
		List = List->next;
	if(List==NULL)
	{
		printf("输入的编码不合法。\n");	
		getchar();getchar();
	}
	return List;
}
/******************
* 函数名称：updata
* 函数参数：无
* 函数功能：更新多表中的每个表对应的编号，便于切换表 
* 返回值：无
*******************/
void updata(MultiList *head)
{
	MultiList *p = head->next;
	int i = 0;
	while (p)
	{
		i++;
		p->num = i;
		p = p->next;
	}
}
/******************
* 函数名称：show
* 函数参数：无
* 函数功能：显示伪菜单界面
* 返回值：无
*******************/
void show()
{
	system("cls");
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList      9. NextElem\n");
	printf("    	  2. DestroyList    10.ListInsert\n");
	printf("    	  3. ClearList      11.ListDelete\n");
	printf("    	  4. ListEmpty      12.ListTrabverse\n");
	printf("    	  5. ListLength     13.SaveList\n");
	printf("    	  6. GetElem        14.LoadList\n");
	printf("	  7. LocateElem     15.MultiListTrabverse\n");
	printf("	  8. PriorElem      16.ExList\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~16]:");
}

/******************
*函数名称:InitiaList
*函数功能:初始化表L的数据指针elem，设置表长为L，表最大长度为LIST_INIT_SIZE
*输入参数:L存放指向SqList的指针
*输出参数:被初始化后的L指针
*返回数值:当表已被初始化时返回ERROR,
*		 否则初始化表成功返回SUCCESS
*调用说明:需要将L的elem成员置空才能初始化L
******************/
status IntiaList(SqList *L)
{
	if(L->elem!=NULL)
		return ERROR; 
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (L->elem == NULL)//分配内存失败 
		return ERROR;
	L->length = 0;//空表长度为0 
	L->listsize = LIST_INIT_SIZE;//初始存储容量 
	return OK;
}

/******************
* 函数名称：InitiaList2
* 函数参数：MultiList的头指针head，遍历指针List
* 函数功能：构造一个空的线性表
* 返回值：成功构造返回OK，否则返回ERROR
******************/
status InitiaList2(MultiList *head,MultiList **List)
{
	*List = head;
	MultiList *q = *List;
	while (*List)
	{
		q = *List;
		(*List) = (*List)->next;
	}
	q->next = (MultiList *)malloc(sizeof(MultiList));
	q->next->L= (SqList *)malloc(sizeof(SqList));
	
	*List = q->next;
	(*List)->L->elem = NULL;
	if (IntiaList((*List)->L) == ERROR)
		return ERROR;
	(*List)->next = NULL;
	return OK;
}

/******************
*函数名称:DestroyList
*函数功能:释放表L的elem指针，使elem指针置空
*输入参数:L存放指向SqList的指针
*输出参数:无
*返回数值:当表尚未被创建时返回ERROR,否则销毁成功返回OK
*调用说明:无
******************/
status DestroyList(SqList *L)
{
	if (L->elem == NULL)
		return ERROR;
	free(L->elem);
	free(L);
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
	DestroyList(p->L);
	free(p);
	*List = NULL;
	return OK;
}

/******************
*函数名称：ClearList
*函数参数：线性表L的地址
*函数功能：重置线性表
*返回值：成功置空返回OK，否则返回ERROR
******************/
status ClearList(SqList *L)
{
	if (L->elem)
	{
		free(L->elem); 
		L->length = 0;
		return OK;
	}
	return ERROR;
}

/******************
*函数名称：ListEmpty
*函数参数：线性表L
*函数功能：判断线性表是否为空
*返回值：若L为空表则返回OK，否则返回ERROR
******************/
status ListEmpty(SqList L)
{
	if (L.elem)
	{
		if (L.length == 0)
		{
			printf("该表为空表。\n");
			return OK;
		}
		else
		{
			printf("该表不为空表。\n");
			return ERROR;
		}
	}
	else
	{
		printf("不存在活动表。\n");
		return ERROR;
	}
}

/******************
*函数名称：ListLength
*函数参数：线性表L
*函数功能：计算线性表L中数据元素个数；
*返回值：成功返回L中数据元素个数，失败返回ERROR
******************/
int ListLength(SqList L)
{
	if (L.elem)
		return L.length;
	return ERROR;
}

/******************
*函数名称：GetElem
*函数参数：线性表L，e为第i个数据的地址；
*函数功能：查找并显示L中第i个元素的值；
*返回值：成功则返回第i个元素的值，否则返回ERROR
******************/
status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0)
	{
		printf("该表为空表，查找失败。\n");
		return ERROR;
	}
	if (i < 1 || i>L.length)
	{
		printf("i值不合法，i的取值范围应为1<=i<=%d。\n", ListLength(L));
		return ERROR;
	}
	*e = L.elem[i - 1];
	return *e;
}

/******************
*函数名称：LocateElem
*函数参数：线性表L，相对比的元素值；
*函数功能：查找L中与e相同数据所在的位序；位序从1开始
*返回值：成功则返回第一个与e相同的数据的位序，不存在则返回0，其余情况返回ERROR
******************/
status LocateElem(SqList L, ElemType e)
{
	int i = 0;
	if (L.length == 0)
		return ERROR;
	while (L.elem[i] != e&&i<L.length) {
		i++;
	}
	if (i >= L.length)
		return ERROR;
	else
		return i + 1;
}

/******************
*函数名称：PriorElem
*函数参数：线性表L，查找的数据cur,前驱pre_e；
*函数功能：查找L中与cur相同的第一个数据，并返回其前驱
*返回值：成功则返回与cur相同的第一个数据，并返回其第一个前驱；若无前驱以及其他情况则返回ERROR
******************/
status PriorElem(SqList L, ElemType cur, ElemType *pre_e)
{
	int i;
	i = LocateElem(L, cur);
	if(i==ERROR||i==0)
	{
		printf("%d 不是活动表中的元素\n",cur);
		return ERROR;
	}
	else if (i>1) {
		*pre_e = L.elem[i - 2];
		return OK;
	}
	else if (i == 1)
	{
		printf("%d is the first letter has no prior_elem\n", cur);
		return ERROR;
	}

}

/******************
*函数名称：NextElem
*函数参数：线性表L，查找的数据cur_e,后驱next_e；
*函数功能：查找L中与cur_e相同的第一个数据，并返回其后驱
*返回值：成功则返回与cur_e相同的第一个数据，并返回其后驱；若无后驱以及其他情况则返回ERROR
******************/
status NextElem(SqList L, ElemType cur, ElemType *next_e)
{
	int i;
	i = LocateElem(L, cur);
	if(i==ERROR||i==0)
	{
		printf("%d 不是活动表中的元素\n",cur);
		return ERROR;
	}
	else if (i>0) {
		if (i < L.length) {
			*next_e = L.elem[i];
			return OK;
		}
		else if(i==L.length)
		{
			printf("%d is the last letter has no next_elem。\n", cur);
			return ERROR;
		}
	}
	else
		return ERROR;
}

/******************
*函数名称：ListInsert
*函数参数：线性表L的地址，插入的位置i，插入的数据元素e。
*函数功能：在L的第i个位置之前插入新的数据元素e；若已插满，则按照分配增量，分配更大的空间。
*返回值：成功插入返回OK，否则返回ERROR
******************/
status ListInsert(SqList * L, int i, ElemType e)
{
	if (i<1 || i>L->length + 1)
	{
		printf("i值不合法，插入失败。\n");
		return ERROR;
	}

	if (L->length >= L->listsize)
	{
		ElemType* newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT));
		if (!newbase) return ERROR;
		L->elem = newbase;
		L->listsize = L->listsize + LISTINCREMENT;
	}
	ElemType*q = &(L->elem[i - 1]);
	ElemType*p = &(L->elem[L->length - 1]);
	for (; p >= q; p--)
		*(p + 1) = *p;
	*q = e;
	L->length++;
	return OK;
}

/******************
*函数名称：ListDelete
*函数参数：线性表L的地址，删除的位序i，指针e的地址。
*函数功能：删除L的第i个数据元素，用e返回其值。
*返回值：成功删除返回OK，否则返回ERROR
******************/
status ListDelete(SqList * L, int i, ElemType * e)
{
	if (i<1 || i>L->length)
		return ERROR;
	ElemType *p;
	p = &L->elem[i - 1];
	*e = *p;
	ElemType * q;
	q = L->elem + L->length - 1;
	for (p++; p <= q; p++)
		*(p - 1) = *p;
	L->length--;
	return OK;
}

/******************
*函数名称：ListTrabverse
*函数参数：线性表L
*函数功能：依次显示线性表中的每个元素。
*返回值：成功遍历返回线性表的长度，否则返回ERROR
******************/
status ListTrabverse(SqList L) {
	int i;
	printf("-----------all elements -----------------------\n");
	for (i = 0; i<L.length; i++) printf("%3d ", L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	if (L.length == 0)
	{
		printf("线性表是空表！\n");
		return ERROR;
	}
	return L.length;
}

/******************
*函数名称：MultiListTrabverse
*函数参数：MultiList头指针head
*函数功能：依次显示每一个线性表的编码、表长以及线性表中的每个元素。
*返回值：成功遍历返回线性表的长度，否则返回ERROR
******************/
status MultiListTrabverse(MultiList *head)
{
	MultiList *p = head->next;
	while (p)
	{
		printf("工作表：%d\t表长度：%d\n", p->num, p->L->length);
		ListTrabverse(*p->L);
		p = p->next;
	}
	return OK;
}
