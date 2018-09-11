#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define FALSE -1 
#define OK 1
#define ERROR -2 
#define TRUE 1
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int Key;				//定义关键字类型为int 
typedef struct TElemType {
	Key i;						//关键字，本系统采用完全二叉树中对应的位置 
	char c;						//字符型数据 
}TElemType;
typedef struct BiTNode {
	TElemType data;				//二叉树结点中的数据域 
	BiTNode *lchild, *rchild;	//左右孩子指针
}BiTNode;
typedef struct BiTree { 
	char name[20];				//二叉树的名字 
	BiTNode* HeadNode; 			//二叉树根结点
}BiTree;
typedef struct Forest {
	BiTree *elem;				//数据域 
	int length;					//二叉树的个数 
	int listsize;				 
}Forest;

//---------------------------------------队列的定义和基本操作，用于层次遍历二叉树---------------------------------------// 
struct LinkQueueNode {
	BiTNode *data;
	struct LinkQueueNode *next;
};
struct LKQueue {
	LinkQueueNode*front, *rear;
};
/******************
函数名称：InitQueue
函数参数：队列LQ
函数功能：初始化一个队列 
返回值：无
*******************/
void InitQueue(LKQueue *LQ)
{
	LinkQueueNode*p;
	p = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	LQ->front = p;
	LQ->rear = p;
	LQ->front->next = NULL;
}
/******************
函数名称：EmptyQueue
函数参数：队列LQ
函数功能：判断队列是否为空 
返回值：若队列为空返回1，否则返回0 
*******************/
int EmptyQueue(LKQueue*LQ)
{
	if (LQ->front == LQ->rear)
		return 1;
	else
		return 0;
}
/******************
函数名称：EnQueue
函数参数：队列LQ，结点T 
函数功能：将T结点插入队列尾端 
返回值：无
*******************/
void EnQueue(LKQueue*LQ, BiTNode*T)
{
	LinkQueueNode *p;
	p = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	p->data = T;
	p->next = NULL;
	LQ->rear->next = p;
	LQ->rear = p;
} 
/******************
函数名称：OutQueue
函数参数：队列LQ 
函数功能：将队列第一个元素出列 
返回值：成功返回1，失败即队列已为空时返回0 
*******************/
int OutQueue(LKQueue*LQ)
{
	LinkQueueNode *p;
	if (EmptyQueue(LQ))
	{
		return 0;
	}
	else
	{
		p = LQ->front->next;
		LQ->front->next = p->next;
		if (p->next == NULL)
			LQ->rear = LQ->front;
		free(p);
		return 1;
	}
}
/******************
函数名称：GetHead
函数参数：队列LQ 
函数功能：返回队列第一个元素
返回值：返回第一个元素，若队列为空则返回NULL 
*******************/
BiTNode *GetHead(LKQueue *LQ)
{
	LinkQueueNode *p;
	BiTNode *T=NULL;
	if (EmptyQueue(LQ))
		return T;
	else
	{
		p = LQ->front->next;
		return p->data;
	}
}

//---------------------------------------功能函数的声明---------------------------------------// 
void show(BiTree*F);//显示伪菜单 
void updata(BiTNode *F);//将对应的位置赋值给关键字 
int InitBiTree(Forest *L);//初始化一个空二叉树 
int DestroyBiTree(Forest L,BiTree *F);//销毁二叉树 
int DestroyBiTree2(BiTNode *T);

BiTNode *CreateBiTree(char*definition);//按definition的序列生成二叉树 
int PreCreateBiTree(BiTNode **T,char*definition,int *i);

int ClearBiTree(BiTNode *T);//请空二叉树 
int BiTreeEmpty(BiTNode T);//判断二叉树是否为空 
int BiTreeDepth(BiTNode *T);//返回二叉树的深度 
BiTNode* Root(BiTNode *T);//返回二叉树的根结点 
BiTNode* Value(BiTNode *T,Key e);//返回关键字为e的结点 
int Assign(BiTNode *T,Key e,char c);//修改关键字为e的结点 

BiTNode* Parent(BiTNode *T,Key e);//返回关键字为e的结点的双亲结点 
BiTNode* LeftChild(BiTNode*T,Key e);//返回关键字为e的结点的左孩子结点 
BiTNode* RightChild(BiTNode*T,Key e);//返回关键字为e的结点的右孩子结点 
BiTNode* LeftSibling(BiTNode*T,Key e);//返回关键字为e的结点的左兄弟结点 
BiTNode* RightSibling(BiTNode*T,Key e);//返回关键字为e的结点的右兄弟结点 

int InsertChild(BiTNode*T, Key e, int LR,BiTNode*p);//插入子树 
void change(BiTNode *T);//按照树变二叉树的规则将二叉树变为右子树为空的二叉树 
int DeleteChild(BiTNode*T, Key e, int LR);//删除子树 

int PreOrderTraverse(BiTNode *T);//先序遍历 
int InOrderTraverse(BiTNode *T);//中序遍历 
int PostOrderTraverse(BiTNode *T);//后序遍历 
int LevelOrderTraverse(BiTNode *T);//层次遍历 

int SaveData(FILE *fp, BiTNode*T, char filename[30]);//保存数据 
int SaveData1(FILE *fp, BiTNode*T, char filename[30]);
int LoadData(FILE *fp, BiTNode**T, char filename[30]);//加载数据 
int ForestTraverse(Forest L);//遍历森林 
BiTree *ExBiTree(Forest L, char name[20]);//切换树 

int main()
{
	Forest L;
	L.elem = (BiTree *)malloc(LIST_INIT_SIZE * sizeof(BiTree));  
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	
	BiTree *F=NULL,*F1;//F为遍历指针，F1用于接收返回的树结点 
	BiTNode *T;//用于接收返回的二叉树结点指针 
	
	FILE  *fp = NULL;//文件指针 
	char filename[30];//存储文件名

	int op = 1;//功能选择 
	char s[100];//存储录入的字符串用于生成二叉树，或用于存储读入的二叉树名称 
	Key e;char a;//数据域临时变量 
	int LR;//左或右的选择 

	while (op)
	{
		show(F);
		scanf("%d", &op); getchar();
		switch (op)
		{
			case 0:
				printf("欢迎下次再使用本系统！\n");
				getchar();	
				break;
			case 1:
				if (InitBiTree(&L)== OK)
				{
					F=&(L.elem[L.length-1]);
					printf("创建一个空二叉树成功！\n");					
				}
				else
					printf("创建一个空二叉树失败！\n");
				getchar();
				break;
			case 2:
				if (DestroyBiTree(L,F)== OK)
				{
					F=NULL;
					printf("销毁二叉树成功！\n");					
				}
				else
					printf("销毁二叉树失败！\n");
				getchar();
				break;
			case 3:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else
				{
					if (F->HeadNode->lchild != NULL)
						printf("当前活动树中已有数据，不能重新生成！");
					else
					{
						printf("请输入先序遍历序列（每一个元素都为char类型,若为空则输入#）：\n");
						fgets(s, 100, stdin);
						F->HeadNode->lchild = CreateBiTree(s);
						if (s[0] != ' '&&s[0]!='#'&&F->HeadNode->lchild == NULL)
							printf("构建二叉树失败！请确认输入的序列是否是一个正确的先序遍历序列！");
						else
							printf("构建二叉树成功！");
					}
				}
				getchar();
				break;
			case 4:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else if (ClearBiTree(F->HeadNode) == OK)
					printf("二叉树清空成功！");
				else
					printf("二叉树清空失败！");
				getchar();
				break;
			case 5:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else if (BiTreeEmpty(*(F->HeadNode)) == OK)
					printf("当前活动树为空二叉树！");
				else
					printf("当前活动树不是空二叉树！");
				getchar();
				break;
			case 6:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else
					printf("二叉树的深度为%d。",BiTreeDepth(F->HeadNode->lchild));
				getchar();
				break;
			case 7:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else if (F->HeadNode->lchild == NULL)
					printf("根结点为空，该活动树为空二叉树！");
				else
					printf("根结点的存放的数据为：%c。", Root(F->HeadNode)->data.c);
				getchar();
				break;
			case 8:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else  if (F->HeadNode->lchild == NULL)
					printf("该活动树为空二叉树，不能进行查找！");
				else
				{
					printf("请输入要查找的数据的关键字:");scanf("%d", &e);getchar();
					T = Value(F->HeadNode->lchild, e);
					if (T!=NULL)
						printf("关键字为%d的数据为%c。", e, T->data.c);
					else
						printf("没有找到含有该关键字的结点！");
				}	
				getchar(); 
				break;
			case 9:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("该活动树为空二叉树，无法进行修改！");
				else
				{
					printf("请输入要修改的数据的关键字:");scanf("%d", &e);getchar();
					printf("请输入要修改后的数据:");scanf("%c", &a);getchar();
					if (Assign(F->HeadNode->lchild, e, a) == OK)
						printf("修改成功！");
					else
						printf("没有找到含有该关键字的结点！");	 
				}
				getchar();
				break;
			case 10:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("该活动树为空二叉树，无法进行查找！");
				else
				{
					printf("请输入要查找的数据的关键字:"); scanf("%d", &e);	getchar(); 
					if (e == 1)
						printf("该关键字对应数据结点为根节点，无双亲结点！");
					else
					{
						T = Parent(F->HeadNode->lchild, e);
						if (T != NULL)
							printf("关键字为%d的数据的双亲结点的关键字：%d    数据：%c。", e, T->data.i, T->data.c);
						else
							printf("没有找到含有该关键字的结点,查找失败！");
					}
				}
				getchar();
				break;
			case 11:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("该活动树为空二叉树，无法进行查找！");
				else
				{
					printf("请输入要查找的数据的关键字:"); scanf("%d", &e);	getchar();
					T=LeftChild(F->HeadNode->lchild, e);
					if (T == NULL)
						printf("没有找到含有该关键字的结点或是含有该关键字的结点没有左孩子结点！");
					else
						printf("关键字为%d的结点的左孩子结点的关键字：%d    数据：%c。", e,T->data.i,T->data.c);
				}
				getchar();
				break;
			case 12:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("该活动树为空二叉树，无法进行查找！");
				else
				{
					printf("请输入要查找的数据的关键字:"); scanf("%d", &e);	getchar();
					T = RightChild(F->HeadNode->lchild, e);
					if (T == NULL)
						printf("没有找到含有该关键字的结点或是含有该关键字的结点没有右孩子结点！");
					else
						printf("关键字为%d的结点的右孩子结点的关键字：%d    数据：%c。", e, T->data.i, T->data.c);
				}
				getchar();
				break;
			case 13:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("该活动树为空二叉树，无法进行查找！");
				else
				{
					printf("请输入要查找的数据的关键字:"); scanf("%d", &e);	getchar();
					if (e == 1)printf("该关键字对应数据结点为根节点，无左兄弟结点！");
					else
					{
						T = LeftSibling(F->HeadNode->lchild, e);
						if (T == NULL)
							printf("没有找到含有该关键字的结点！");
						else if (T->data.i == e)
							printf("含有该关键字的结点为某一结点的左孩子结点，无左兄弟结点！");
						else
							printf("关键字为%d的数据的左兄弟结点的关键字：%d    数据：%c。", e, T->data.i, T->data.c);
					}
				}
				getchar();
				break;
			case 14:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else  if(F->HeadNode->lchild==NULL)
					printf("该活动树为空二叉树，无法进行查找！");
				else
				{
					printf("请输入要查找的数据的关键字:"); scanf("%d", &e);	getchar();
					if (e == 1)printf("该关键字对应数据结点为根节点，无右兄弟结点！");
					else
					{
						T = RightSibling(F->HeadNode->lchild, e);
						if (T == NULL)
							printf("没有找到含有该关键字的结点！");
						else if (T->data.i == e)
							printf("含有该关键字的结点为某一结点的右孩子结点，无右兄弟结点！");
						else
							printf("关键字为%d的数据的右兄弟结点的关键字：%d    数据：%c！", e, T->data.i, T->data.c);
					}
				}
				getchar();
				break;
			case 15:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else
				{
					printf("请输入子树的先序遍历序列（每一个元素都为char类型,若为空则输入#）：\n");
					fgets(s, 30, stdin);
					if (s[0] == '\n')
						printf("未输入任意字符，构建二叉树失败！");
					else if(s[0]=='#')
					{
						F->HeadNode->lchild == NULL;
						printf("构建二叉树成功，该树为空树,无法进行插入！");	
					}
					else
					{
						T = CreateBiTree(s);
						if (s[0] != ' '&&T == NULL)
							printf("构建二叉树失败！请确认输入的序列是否是一个正确的先序遍历序列！");
						else
						{
							printf("构建二叉树成功！\n");
							printf("请输入所要插入位置的双亲结点的关键字(根结点的双亲结点定义为表头结点)："); scanf("%d", &e);	getchar();
							if(e!=0)
							{
								printf("以0代表插入左子树，1代表插入右子树，请输入LR的值："); scanf("%d", &LR); getchar();
							}	
							if(InsertChild(F->HeadNode, e,LR,T)==OK)
								printf("插入成功！");
							else
								printf("插入失败！");							
						}
					}
				}
				getchar();
				break;
			case 16:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else if (DeleteChild(F->HeadNode, e, LR) == OK)
					printf("删除成功！");
				else
					printf("删除失败！");
				getchar();
				break;
			case 17:
				if (F == NULL)
					printf("当前没有活动树！");
				else if (F->HeadNode->lchild == NULL)
					printf("该树为空二叉树！");
				else
					PreOrderTraverse(F->HeadNode->lchild);
				getchar(); 
				break;
			case 18:
				if (F == NULL)
					printf("当前没有活动树！");
				else if (F->HeadNode->lchild == NULL)
					printf("该树为空二叉树！");
				else
					InOrderTraverse(F->HeadNode->lchild);
				getchar(); 
				break;
			case 19:
				if (F == NULL)
					printf("当前没有活动树！");
				else if (F->HeadNode->lchild == NULL)
					printf("该树为空二叉树！");
				else
					PostOrderTraverse(F->HeadNode->lchild);
				getchar();
				break;
			case 20:
				if (F == NULL)
					printf("当前没有活动树！");
				else if (F->HeadNode->lchild == NULL)
					printf("该树为空二叉树！");
				else
					LevelOrderTraverse(F->HeadNode->lchild);
				getchar();
				break;
			case 21:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else if (SaveData(fp,F->HeadNode->lchild,filename)== OK)
					printf("数据写入文件成功！");
				else
					printf("数据写入文件失败！");
				getchar();
				break;
			case 22:
				if (F == NULL)
					printf("当前没有活动树！\n");
				else if (LoadData(fp, &(F->HeadNode->lchild), filename) == OK)
					printf("录入数据成功！");
				else
					printf("录入数据失败！");
				getchar();
				break;
			case 23:
				if (L.elem == NULL)
					printf("当前没有活动树！\n");
				else	
				{
					ForestTraverse(L);
					printf("请输入要切换的表的名字："); scanf("%s", &s); getchar();
					F1=ExBiTree(L, s);
					if (F1 == NULL)
						printf("输入的名字不存在！\n");
					else
					{
						F=F1;
						printf("切换成功！");	
					}
				}
				getchar();
				break;
			default:
				printf("功能选择是无效的输入！\n");
				getchar();
		}
		if(F!=NULL)
			if(F->HeadNode!=NULL)
				updata(F->HeadNode->lchild);
	}
	return 0;
}
					    
/******************
函数名称：ForestTraverse
函数参数：存放森林的顺序表 
函数功能：遍历全部的树
返回值：成功返回OK，否则返回ERROR
*******************/
int ForestTraverse(Forest L)
{
	int i;
	for (i = 0;i < L.length;i++) 
	{
		printf("树的名字：%s\n", L.elem[i].name);
		if(L.elem[i].HeadNode->lchild==NULL)
			printf("该树为空树！");
		else
			PreOrderTraverse(L.elem[i].HeadNode->lchild);
		printf("\n\n"); 		
	}
	printf("遍历结束，");
	return OK;
}
/******************
函数名称：ExBiTree
函数参数：存放森林的顺序表 ，要切换的树的名字 
函数功能：切换工作树
返回值：切换成功则返回切换后森林结构的结点，否则返回NULL
*******************/
BiTree *ExBiTree(Forest L, char name[20])
{
	int i;
	for (i = 0;i < L.length;i++) 
	{
		if (strcmp(L.elem[i].name,name) == 0) 
			break;
	}
	if (i+1>L.length) 
	{
		printf("二叉树不存在，");
		return NULL;
	}
	else
		return &(L.elem[i]);
}
/******************
函数名称：LoadData
函数参数：文件指针，二叉树的表头结点T,文件名filename[30]
函数功能：加载数据
返回值：成功返回OK，失败返回ERROR
*******************/
int LoadData(FILE *fp, BiTNode**T, char filename[30])
{
	printf("请输入要导入数据的文件名: ");
	scanf("%s", filename);getchar();
	if ((fp=fopen(filename, "r+")) == NULL)
	{
		printf("文件打开失败！\n");
		return ERROR;
	}
	char *temp;
	fgets(temp, 1024, fp);
	if (*T == NULL)
	{
		*T=CreateBiTree(temp);
		if((*T==NULL&&temp=='\0')||temp!='\0'&&*T!=NULL)
		{
			printf("导入完毕，");
			fclose(fp);
			return OK;		
		}
	}
	if (ClearBiTree((*T)) == ERROR)
		return ERROR;
	*T=CreateBiTree(temp);
	if((*T==NULL&&temp=='\0')||temp!='\0'&&*T!=NULL)
	{
		printf("导入完毕，");
		fclose(fp);
		return OK;		
	}
	fclose(fp);
	return ERROR;
}
/******************
函数名称：SaveData
函数参数：文件指针，二叉树的表头结点T,文件名filename[30]
函数功能：保存数据
返回值：成功返回OK，失败返回ERROR
*******************/
int SaveData(FILE *fp, BiTNode*T, char filename[30])
{
	printf("请输入要写入的文件名: "); scanf("%s", filename);getchar();
	if ((fp=fopen(filename, "w")) ==NULL)
	{
		printf("文件打开失败！");
		return ERROR;
	}
	if (SaveData1(fp, T, filename) == OK)
	{
		fclose(fp);
		return OK;
	}
	fclose(fp);
	return ERROR;
}
/******************
函数名称：SaveData1
函数参数：文件指针，二叉树的表头结点T,文件名filename[30]
函数功能：按先序遍历序列向文件filename中依次写入数据的关键字和字符
返回值：成功返回OK，失败返回ERROR
*******************/
int SaveData1(FILE *fp, BiTNode*T, char filename[30])
{
	if (T) {
		fprintf(fp, "%c",T->data.c);
		SaveData1(fp, T->lchild, filename);
		SaveData1(fp, T->rchild, filename);
	}
	else
		fprintf(fp, "%c",'#');
	return OK;
}	  
/******************
函数名称：LevelOrderTraverse
函数参数：指向二叉树的根结点的指针F->HeadNode->lchild
函数功能：按层遍历二叉树
返回值：成功返回OK，失败返回ERROR
*******************/	
int LevelOrderTraverse(BiTNode *T)
{
	LKQueue*Q;
	BiTNode *p;
	InitQueue(Q);
	if (T!= NULL)
	{
		EnQueue(Q, T);
		while (!EmptyQueue(Q))
		{
			p = GetHead(Q);
			OutQueue(Q);
			if(p==NULL)
				putchar('#');
			else
				printf("%c",p->data.c);
			if (p->lchild != NULL)
				EnQueue(Q, p->lchild);
			if (p->rchild != NULL)
				EnQueue(Q, p->rchild);
		}
	}
}
/******************
函数名称：PostOrderTraverse
函数参数：指向二叉树的根结点的指针F->HeadNode->lchild
函数功能：后序遍历二叉树
返回值：成功返回OK，失败返回ERROR
*******************/
int PostOrderTraverse(BiTNode *T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c", T->data.c);
	}
	else
		putchar('#');
	return OK;
}
/******************
函数名称：InOrderTraverse
函数参数：指向二叉树的根结点的指针F->HeadNode->lchild
函数功能：中序遍历二叉树
返回值：成功返回OK，失败返回ERROR
*******************/
int InOrderTraverse(BiTNode *T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		printf("%c", T->data.c);
		InOrderTraverse(T->rchild);
	}
	else
		putchar('#');
	return OK;
}
/******************
函数名称：PreOrderTraverse
函数参数：指向二叉树的根结点的指针F->HeadNode->lchild
函数功能：前序遍历二叉树
返回值：成功返回OK，失败返回ERROR
*******************/
int PreOrderTraverse(BiTNode *T)
{
	if (T) {
		printf("%c", T->data.c);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	else
		putchar('#');
	return OK;
}
/******************
函数名称：DeleteChild
函数参数：二叉树的根结点，关键字e ，判断标志LR
函数功能：删除子树
返回值：成功插入返回OK，否则返回ERROR
*******************/
int DeleteChild(BiTNode*T, Key e, int LR)
{
	if(T==NULL) 
	{ 
		printf("该活动树为空二叉树，");
		return ERROR;
	}
	printf("请输入所要删除子树的双亲结点的关键字(根结点的双亲结点定义为表头结点)："); scanf("%d", &e); getchar();
	if(e==0)
	{
		DestroyBiTree2(T->lchild);
		T->lchild=NULL;
		return OK;
	}
	BiTNode*p = Value(T->lchild, e);
	if (p == NULL)
	{
		printf("含有该关键字的结点不存在，");
		return ERROR; 
	}	
	else
	{
		printf("以0代表删除左子树，1代表删除右子树，请输入LR的值："); scanf("%d", &LR); getchar();
		BiTNode*temp;
		if (LR == 0)
		{
			temp = p->lchild;
			p->lchild = NULL;
			if (DestroyBiTree2(temp) == OK)
				return OK;
		}
		else if (LR == 1)
		{
			temp = p->rchild;
			p->rchild = NULL;
			if (DestroyBiTree2(temp) == OK)
				return OK;
		}
		else
		{
			printf("输入的LR值不合法，");
			return ERROR;
		}
	}
}
/******************
函数名称：change
函数参数：二叉树的根结点
函数功能：通过树变二叉树的方式将要插入的子树转变为没有右子树的树
返回值：无
*******************/
void change(BiTNode*T)
{	
	if(T==NULL)
		return ;
	change(T->lchild);
	change(T->rchild);
	if(T->lchild==NULL)
		T->lchild=T->rchild;
	else
		T->lchild->rchild=T->rchild;
	T->rchild=NULL;
	return ;
}
/******************
函数名称：get_nums_bitree
函数参数：二叉树的根结点
函数功能：统计二叉树的结点数 
返回值：返回二叉树的结点数 
*******************/
int get_nums_bitree(BiTNode *T) 
{
	if (T==NULL) 
		return 0;
	else 
		return get_nums_bitree(T->lchild) + get_nums_bitree(T->rchild) + 1;
}
/******************
函数名称：InsertChild
函数参数：二叉树的根结点，关键字e ，判断标志LR， 代表子树的字符串s
函数功能：插入子树
返回值：成功插入返回OK，否则返回ERROR
*******************/
int InsertChild(BiTNode*T, Key e, int LR, BiTNode*p)  
{
    change(p);
	if(e==0)
	{
		p->rchild=T->lchild;
		T->lchild=p;
		return OK;
	}
	BiTNode*q=Value(T->lchild,e);
	if(q==NULL)
	{
		printf("e值不合法，");
		return ERROR;
	}				
	if(LR==0)
	{
		p->rchild=q->lchild;
		q->lchild=p;
	}
	else if(LR==1)
	{
		p->rchild=q->rchild;
		q->rchild=p;		
	} 
	else
	{
		printf("LR值不合法，");
		return ERROR;		
	}
	return OK;
}
/******************
函数名称：RightSibling
函数参数：二叉树的根结点，关键字e
函数功能：寻找右兄弟结点
返回值：如果查找到返回结点指针，否则返回NULL
*******************/
BiTNode *RightSibling(BiTNode*T, Key e)
{
	BiTNode*temp = Parent(T, e);
	if (temp == NULL)
		return NULL;
	else
		return temp->rchild;
}
/******************
函数名称：LeftSibling
函数参数：二叉树的根结点，关键字e
函数功能：寻找左兄弟结点
返回值：如果查找到返回结点指针，否则返回NULL
*******************/
BiTNode *LeftSibling(BiTNode*T, Key e)
{
	BiTNode*temp = Parent(T,e);
	if (temp == NULL)
		return NULL;
	else
		return temp->lchild;
}
/******************
函数名称：RightChild
函数参数：二叉树的根结点，关键字e
函数功能：寻找右孩子结点
返回值：如果查找到返回结点指针，否则返回NULL
*******************/
BiTNode * RightChild(BiTNode*T, Key e)
{
	BiTNode *temp = Value(T, e);
	if (temp == NULL)
		return NULL;
	return temp->rchild;
}
/******************
函数名称：LeftChild
函数参数：二叉树的根结点，关键字e
函数功能：寻找左孩子结点
返回值：如果查找到返回结点指针，否则返回NULL
*******************/
BiTNode * LeftChild(BiTNode*T, Key e)
{
	BiTNode *temp=Value(T, e);
	if (temp == NULL)
		return NULL;
	return temp->lchild;
}
/******************
函数名称：Parent
函数参数：二叉树的根结点，关键字e
函数功能：寻找双亲结点
返回值：如果查找到就返回结点指针，否则返回NULL
*******************/
BiTNode * Parent(BiTNode *T, Key e)
{												
	if ((T->lchild != NULL && e == T->lchild->data.i)
		|| (T->rchild != NULL && e == T->rchild->data.i)) {
		return T;
	}
	else {
		BiTNode*temp=NULL;
		if(T->lchild != NULL)
			temp=Parent(T->lchild,e);
		if(temp==NULL&&T->rchild != NULL)
			temp= Parent(T->rchild, e);
		return temp;
	}
}
/******************
函数名称：Assign
函数参数：二叉树的根结点，关键字e，数据c
函数功能：将关键字为e的结点的数据改为c
返回值：如果查找到结点就返回OK，否则返回ERROR
*******************/
int Assign(BiTNode *T, Key e, char c)
{
	BiTNode *temp;
	if ((temp = Value(T, e) )== NULL)
		return ERROR;
	temp->data.c = c;
	return OK;
}
/******************
函数名称：Value
函数参数：二叉树的根结点，关键字e
函数功能：返回二叉树相应结点的数据域
返回值：如果存在就返回二叉树相应结点，否则返回NULL
*******************/
BiTNode * Value(BiTNode *T, Key e)
{
	if (T == NULL)
		return NULL;
	if (T->data.i == e)
		return T;
	BiTNode * temp;
	temp = Value(T->lchild, e);
	if (temp == NULL)
	{
		temp= (BiTNode*)malloc(sizeof(BiTNode));
		temp = Value(T->rchild, e);
	}
	return temp;
}
/******************
函数名称：Root
函数参数：二叉树的表头结点
函数功能：返回二叉树根节点
返回值：二叉树根节点
*******************/
BiTNode *Root(BiTNode *T)
{
	return T->lchild;
}
/******************
函数名称：BiTreeDepth
函数参数：二叉树的根结点的指针 
函数功能：返回二叉树的深度
返回值：返回二叉树的深度
*******************/
int BiTreeDepth(BiTNode *T)
{
	int deep = 0;
	if (T)
	{
		int leftdeep = BiTreeDepth(T->lchild);
		int rightdeep = BiTreeDepth(T->rchild);
		deep = leftdeep >= rightdeep ? leftdeep + 1 : rightdeep + 1;
	}
	return deep;
}
/******************
函数名称：BiTreeEmpty
函数参数：二叉树的表头结点
函数功能：判断二叉树是否为空
返回值：是返回OK，不是返回ERROR
*******************/
int BiTreeEmpty(BiTNode T)
{
	if ((&T)->lchild == NULL)
		return OK;
	else
		return ERROR;
}
/******************
函数名称：ClearBiTre
函数参数：指向二叉树的表头结点的指针F->HeadNode
函数功能：清空二叉树
返回值：成功返回OK，失败返回ERROR
*******************/
int ClearBiTree(BiTNode *T)
{
	if(T==NULL)
		return OK;
	if (DestroyBiTree2(T->lchild) == ERROR)
		return ERROR;
	T->lchild = NULL;
	return OK;
}
/******************
函数名称：PreCreateBiTree
函数参数：二叉树的根结点T的地址，输入的字符串s，用于定位字符串元素的i
函数功能：用递归生成二叉树 
返回值：成功返回OK，失败返回ERROR
*******************/
int PreCreateBiTree(BiTNode **T, char*s, int *i)
{
	if (s[*i] == '#') *T = NULL;
	else if (s[*i] == '\n'|| s[*i] == ' ') return ERROR;
	else
	{
		if (!((*T) = ((BiTNode*)malloc(sizeof(BiTNode))))) return ERROR;
		(*T)->data.c = s[*i];
		if ((PreCreateBiTree(&((*T)->lchild), s, &(++(*i))) == ERROR))
			return ERROR;
		if ((PreCreateBiTree(&((*T)->rchild), s, &(++(*i)))) == ERROR)
			return ERROR;
	}
	return OK;
}
/******************
函数名称：CreateBiTree
函数参数：字符串definition
函数功能：按照输入的definition序列生成二叉树 
返回值：成功返回root，失败返回NULL
*******************/
BiTNode * CreateBiTree(char*definition)
{
	if (definition[0] == '\n')
	{
		printf("未输入任意字符，");	
		return NULL;
	}
	else if(definition[0]=='#')
	{
		printf("该树为空树，");	
		return NULL;
	} 
	int i = 0;
	BiTNode *root = (BiTNode*)malloc(sizeof(BiTNode));
	if (PreCreateBiTree(&root, definition, &i) == ERROR)
		return NULL;
	root->data.i = 1;
	return root;
}
/******************
函数名称：DestroyBiTree2
函数参数：指向Forest的头结点L和遍历指针F
函数功能：销毁森林结构中F对应结点，且将并使F指向NULL， 
返回值：成功返回OK，失败返回ERROR
*******************/
int DestroyBiTree(Forest L,BiTree *F) 
{
	int i;
	for (i = 0;i < L.length;i++) 
	{
		if (strcmp(L.elem[i].name,F->name) == 0) 
			break;
	}
	if (i+1>L.length) 
	{
		printf("当前没有活动树，");
		return ERROR;
	}
	DestroyBiTree2(L.elem[i].HeadNode->lchild);
	free(L.elem[i].HeadNode);
	for (;i<L.length;i++) 
	{  
		strcpy(L.elem[i].name, L.elem[i+1].name);
		L.elem[i].HeadNode = L.elem[i+1].HeadNode;
	}
	L.elem[L.length].HeadNode=NULL;
	L.length--;
	return OK;
}
/******************
函数名称：DestroyBiTree2 
函数参数：根结点 
函数功能：销毁二叉树T
返回值：成功返回OK，失败返回ERROR
*******************/
int DestroyBiTree2(BiTNode *T)
{
	if (T == NULL) {
		return OK;
	}
	DestroyBiTree2(T->lchild);
	DestroyBiTree2(T->rchild);
	free(T);
	return OK;
}
/******************
函数名称：InitBiTree
函数参数：Forest的头指针
函数功能：构造空二叉树T
返回值：成功返回OK，失败返回ERROR
*******************/
int InitBiTree(Forest *L)
{
	int i;
	char name[20];
	printf("请输入该树的名字（20个字符以内）：");scanf("%s",name);getchar();
	for (i = 1;i <= L->length;i++) 
	{
		if (strcmp(L->elem[i - 1].name, name) == 0) break;   
	}
	if (i <= L->length) 
	{
		printf("名称已存在，");  
		return ERROR;
	}
	BiTree *newbase;
	if (L->length >= L->listsize) {
		newbase = (BiTree *)realloc(L->elem, (L->listsize + LISTINCREMENT)*sizeof(BiTree));  
		if (!newbase) 
		{
			printf("分配内存失败，");
			return ERROR;
		}    
		L->listsize += LISTINCREMENT;
		L->elem = newbase;
	}
	strcpy(L->elem[L->length].name, name);
	L->elem[L->length].HeadNode = (BiTNode*)malloc(sizeof(BiTNode));  
	L->elem[L->length].HeadNode->data.i= 0;
	L->elem[L->length].HeadNode->data.c= 0; 
	L->elem[L->length].HeadNode->lchild = L->elem[L->length].HeadNode->rchild = NULL;
	(L->length)++; 
	return OK;
}
/******************
函数名称：show
函数参数：遍历指针F
函数功能：显示伪菜单界面
返回值：无
*******************/
void show(BiTree* F)
{
	system("cls");
	printf("\n\n");
	printf("         Menu for BiTree On Chain Structure  \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitBiTree           13. LeftSibling\n");
	printf("    	  2. DestroyBiTree        14. RightSibling\n");
	printf("    	  3. CreateBiTree         15. InsertChild\n");
	printf("    	  4. ClearBiTree          16. DeleteChild\n");
	printf("    	  5. BiTreeEmpty          17. PreOrderTraverse\n");
	printf("    	  6. BiTreeDepth          18. InOrderTraverse\n");
	printf("	  7. Root                 19. PostOrderTraverse\n");
	printf("	  8. Value                20. LevelOrderTraverse\n");
	printf("	  9. Assign		  21. SaveData\n");
	printf("	  10. Parent		  22. LoadData\n");		
	printf("	  11. LeftChild		  23. ExBiTree\n");
	printf("	  12. RightChild	  0. Exit\n");
	printf("-------------------------------------------------\n");
	if (F == NULL)
		printf("\n-----------当前没有活动树-----------\n");
	else
		printf("\n-----------当前对树 %s 进行操作-----------\n", F->name);
	printf("    请选择你的操作[0~23]:");
}
/******************
函数名称：updata
函数参数：根结点 
函数功能：将结点所在位置的赋值给结点数据域的key
返回值：无
*******************/
void updata(BiTNode *T)
{
	if (T == NULL)return;
	if (T->lchild)
	{
		T->lchild->data.i = 2 * T->data.i;
		updata(T->lchild);
	}
	if (T->rchild)
	{
		T->rchild->data.i = 2 * T->data.i + 1;
		updata(T->rchild);
	}
}
