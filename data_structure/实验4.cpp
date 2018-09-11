//---------------------------------------基于邻接表的有向图相关操作--------------------------------------// 
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define FALSE -1 
#define OK 1
#define ERROR -2 
#define TRUE 1
#define INFEASTABLE -1
#define OVERFLOW -2

#define MAX_VERTICE_NUM 20

typedef enum { DG, DN, UDG, UND }GraphKind; //有向图,有向网,无向图,无向网
typedef int status;
typedef char VertexType;
typedef struct ArcNode {
	int adjvex; 				//该弧所指向的顶点的位置 
	struct ArcNode *nextarc; 	//指向下一条弧的指针 
}ArcNode;
typedef struct VNode{
	VertexType data; 			//顶点信息
	ArcNode *firstarc; 			//第一个表结点的地址,指向第一条依附该顶点的弧的指针
}VNode;

typedef struct ALGraph {
	VNode vertices[MAX_VERTICE_NUM];
	int vexnum, arcnum; //图的当前顶点数和弧数
	char name[20];				//图的名字
	ALGraph *next;			//指向下一个图的指针
}ALGraph;
int visited[MAX_VERTICE_NUM];
//---------------------------------------队列的定义和基本操作，用于广度优先遍历图---------------------------------------// 
struct LinkQueueNode {
	VNode*data;
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
void EnQueue(LKQueue*LQ, VNode*T)
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
VNode *GetHead(LKQueue *LQ)
{
	LinkQueueNode *p;
	VNode *T = NULL;
	if (EmptyQueue(LQ))
		return T;
	else
	{
		p = LQ->front->next;
		return p->data;
	}
}

//---------------------------------------功能函数的声明---------------------------------------// 
void show(ALGraph *G);
ALGraph *CreateGraph(ALGraph *Head, char V[MAX_VERTICE_NUM],char VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM]);
status DestroyGraph(ALGraph *G);
status LocateVex(ALGraph*G, VertexType e);
VertexType GetVex(ALGraph*G, int i);
status PutVex(ALGraph*G, int i, VertexType e);
status FirstAdjVex(ALGraph*G, int i);
status NextAdjVex(ALGraph* G, int i,int j);
status InsertVex(ALGraph* G, VertexType e);
status DeleteVex(ALGraph* G, int i);
status InsertArc(ALGraph* G, int i, int j);
status DeleteArc(ALGraph* G, int i, int j);
status DFSTraverse(ALGraph* G);
void DFS(ALGraph* G, int v);
status BFSTraverse(ALGraph* G);
status SaveData(FILE *fp, ALGraph *G, char filename[30]);
status LoadData(FILE *fp, ALGraph *G, char filename[30]);
ALGraph* ExGraph(ALGraph*Head, char name[20]);

int main() {
	int op = 1;
	VertexType e = 0;
	status a,i,j;
	ALGraph *Head,*G,*G1;
	Head = (ALGraph*)malloc(sizeof(ALGraph));
	Head->arcnum = 0; Head->name[20] = {'\0'}; Head->vertices[0]= {'\0'}; Head->vexnum = 0;
	Head->next = NULL;G = Head->next;

	FILE*fp=NULL; char filename[30];
	char name[20];
	char V[MAX_VERTICE_NUM], VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM];

	while (op) {
		show(G);
		scanf("%d", &op); getchar();
		switch (op) 
		{
			case 1:
				printf("请输入该图的名字（20个字符以内）："); scanf("%s", name, 20); getchar();
				G1 = Head->next;
				while (G1)
				{
					if (strcmp(G1->name, name) == 0) break;
					G1 = G1->next;
				}
				if (G1!= NULL)
				{
					printf("名称已存在，创建失败！");
					getchar();
					break;
				}

				G1= (ALGraph*)malloc(sizeof(ALGraph));
				G1->next = NULL;
				strcpy(G1->name,name);
				printf("请依次输入图的顶点数和边数(格式如x y且顶点数不超过20)："); scanf("%d %d", &((*G1).vexnum), &((*G1).arcnum)); getchar();
				if ((*G1).vexnum > MAX_VERTICE_NUM)
				{
					printf("顶点数超过规定的最大顶点数，创建图失败！");
					getchar();break;
				}
				if ((*G1).vexnum == 0)
				{
					if ((*G1).arcnum == 0)
					{
						G1->vertices[0] = { '\0' };
						G = Head;
						while (G->next)
							G = G->next;
						G->next = G1;
						G = G1;
						printf("创建图成功！");
						getchar(); break;
					}
					else
					{
						printf("顶点数为0而边数不为0，创建失败！");
						getchar(); break;
					}
				}
				printf("请依次输入在图中顶点的数据(一个数据为一个char类型的单字符)："); scanf("%s", V, 20); getchar();

				j = 0;
				for (i = 0; (*G1).arcnum != 0&&i < (*G1).vexnum; i++)
				{
					printf("请依次输入与顶点%c邻接的顶点的数据（若无输入0）：", V[i]); scanf("%s", VR[i], 20); getchar();
					if (VR[i][0] == '0')
						VR[i][0] = '\0';
					else
						j = j + strlen(VR[i]);
				}
				for (; i < MAX_VERTICE_NUM; i++)
					*VR[i] = {'\0'};
				if (j != (*G1).arcnum)
				{
					printf("边数与输入的边数不相同，创建失败！");
					getchar();break;
				}

				if ((G1 = CreateGraph(G1,V,VR)) != NULL)
				{
					G = Head;
					while (G->next)
						G = G->next;
					G->next = G1;
					G = G1;
					printf("创建图成功！");
				}
				else
					printf("创建图失败！");
				getchar();break;
			case 2:
				if (DestroyGraph(G) == OK)
				{
					printf("图销毁成功！\n");
					G1 = Head;
					for (; G1->next != G; G1 = G1->next);
					G1->next = G1->next->next;
					free(G);
					G->next = NULL;
					G = NULL;
				}
				else 
					printf("图销毁失败！\n");
				getchar();break;
			case 3:
				printf("请输入所要查找的顶点的VertexType数据：");scanf("%c", &e); getchar();
				if ((a = LocateVex(G, e)) != ERROR)
					printf("顶点%c在图中的序号为：%d。", e, a);
				else
					printf("图中不存在该顶点！");
				getchar();break;
			case 4:
				printf("请输入所要查找的顶点的序号："); scanf("%d", &i); getchar();
				if ((e = GetVex(G, i)) != ERROR)
					printf("序号为%d的顶点的值为为：%c。", i, e);
				else
					printf("图中不存在该顶点！");
				getchar();break;
			case 5:
				printf("请输入所要修改的顶点的序号："); scanf("%d", &i); getchar();
				printf("请输入修改后的数据："); scanf("%c", &e); getchar();
				if ((PutVex(G,i,e)) != ERROR)
					printf("修改成功！");
				else
					printf("修改失败！");
				getchar();break;
			case 6:
				printf("请输入所要查找的顶点的序号："); scanf("%d", &i); getchar();
				if ((a = FirstAdjVex(G, i)) == ERROR)
					printf("图中不存在该顶点！");
				else if (a != -1)
					printf("序号为%d的顶点的第一邻接点的序号为：%d   值为：%c。", i, a, G->vertices[a].data);
				else
					printf("序号为%d的顶点无邻接点。", i);
				getchar();break;
			case 7:
				printf("请输入所要查找的顶点的序号："); scanf("%d", &i); getchar();
				printf("请输入该顶点的一邻接顶点的序号："); scanf("%d", &j); getchar();
				if ((a = NextAdjVex(G, i, j)) == ERROR)
					printf("图中不存在该顶点！");
				else if (a == -1)
					printf("序号为%d的顶点没有序号为%d的邻接点。", i, j);
				else if(a==-3)
					printf("序号为%d的顶点无下一临接点。", i);
				else
					printf("序号为%d的顶点的下一临界点的序号为：%d   值为：%c。", i, a, G->vertices[a].data);
				getchar();break;
			case 8:
				printf("请输入所要插入的顶点的数据为："); scanf("%c", &e); getchar();
				if ((InsertVex(G, e))== OK)
					printf("插入成功！");
				else
					printf("插入失败！");
				getchar();break;
			case 9:
				printf("请输入所要删除的顶点的序号为："); scanf("%d", &i); getchar();
				if (DeleteVex(G, i) == OK)
					printf("删除成功！");
				else
					printf("删除失败！");
				getchar();break;
			case 10:
				printf("请输入插入弧的弧尾顶点序号和弧头顶点序号(格式如x y)："); scanf("%d %d", &i, &j); getchar();
				if (InsertArc(G, i, j) == OK)
					printf("插入成功！");
				else
					printf("插入失败！");
				getchar();break;
			case 11:
				printf("请输入删除弧的弧尾顶点序号和弧头顶点序号(格式如x y)："); scanf("%d %d", &i, &j); getchar();
				if (DeleteArc(G, i, j) == OK)
					printf("删除成功！");
				else
					printf("删除失败！");
				getchar();break;
			case 12:
				if (DFSTraverse(G) == OK)
					printf("\n遍历成功！");
				else
					printf("遍历失败！");
				getchar();break;
			case 13:
				if (BFSTraverse(G) == OK)
					printf("\n遍历成功！");
				else
					printf("遍历失败！");
				getchar();break;
			case 14:
				if (SaveData(fp, G, filename) == OK)
					printf("数据写入文件成功！");
				else
					printf("数据写入文件失败！");
				getchar();break;
			case 15:
				if (LoadData(fp, G, filename) == OK)
					printf("数据加载成功！");
				else
					printf("数据加载失败！");
				getchar();break;
			case 16:
				if (G == NULL)
				{
					printf("当前没有图，切换失败！");
					getchar(); break;
				}
				G1 = Head->next;
				while (G1)
				{
					printf("图的名字：%s\n其广度优先遍历序列为：", G1->name);
					BFSTraverse(G1);
					printf("\n\n");
					G1 = G1->next;
				}
				printf("请输入切换后的图的名字："); scanf("%s", name,20); getchar();
				G1 = ExGraph(Head, name);
				if (G1 == NULL)
					printf("输入的名字不合法，切换失败！");
				else
				{
					G = G1;
					printf("切换成功，当前活动树为%s。",G->name);
				}
				getchar();break;
			case 0:
				printf("欢迎下次再使用本系统！\n");
				getchar();break;
			default:
			{
				printf("功能选择是无效的输入！\n");
				getchar();
			}
		}
	}
	return 0;
}
/******************
函数名称：LoadData
函数参数：文件指针fp，活动图指针，文件名字filename
函数功能：将文件中的信息加载到活动图中
返回值：成功返回OK，失败返回ERROR
*******************/
status LoadData(FILE *fp, ALGraph*G, char filename[30])
{
	if (G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	printf("请输入要加载数据的文件名: "); scanf("%s", filename, 30); getchar();
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("文件打开失败！");
		return ERROR;
	}
	for (int i = 0; i<(*G).vexnum; i++)
	{
		ArcNode *p, *q;
		p = (*G).vertices[i].firstarc;
		while (p) {
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	(*G).vexnum = 0; (*G).arcnum = 0;
	(*G).vertices[MAX_VERTICE_NUM] = { '\0' };
	
	char V[MAX_VERTICE_NUM], VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM];
	fscanf(fp, "%d %d", &((*G).vexnum), &((*G).arcnum)); 
	fscanf(fp, "%s", V);
	int i;
	for (i = 0; i < (*G).vexnum; i++)
		fscanf(fp, "%s", VR[i]);
	for (;i < MAX_VERTICE_NUM; i++)
		*VR[i] = {'\0'};
	for (int i = 0; i < (*G).vexnum; i++)
		for(int j=0;j<MAX_VERTICE_NUM;j++)
		{
			if(VR[i][j]=='0')
			{
				VR[i][j]='\0';
				break;
			}	
		}
	 G=CreateGraph(G,V,VR);
	 return OK;
}
/******************
函数名称：SaveData
函数参数：文件指针fp，活动图结点，文件名字filename
函数功能：保存活动图的信息
返回值：成功返回OK，失败返回ERROR
*******************/
status SaveData(FILE *fp, ALGraph *G, char filename[30])
{
	if (G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	printf("请输入要写入的文件名: "); scanf("%s", filename,30); getchar();
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("文件打开失败！");
		return ERROR;
	}
	fprintf(fp,"%d %d\n",(*G).vexnum,(*G).arcnum);
	for (int i = 0; i < (*G).vexnum; i++)
		fprintf(fp, "%c", GetVex(G,i));
	fprintf(fp, "\n");
	for (int i = 0; i < (*G).vexnum; i++)
	{
		ArcNode *p = (*G).vertices[i].firstarc;
		if(p==NULL) fprintf(fp,"0");
		while (p)
		{
			fprintf(fp, "%c", GetVex(G, p->adjvex));
			p = p->nextarc;
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return OK;
}
/******************
函数名称：ExGraph
函数参数：多图头指针，图的名字name
函数功能：切换活动图
返回值：成功返回名字为name的图的结构，失败返回NULL
*******************/
ALGraph* ExGraph(ALGraph*Head, char name[20])
{
	ALGraph*L = Head->next;
	while (L)
	{
		if (strcmp(L->name, name) == 0)
			break;
		L = L->next;
	}
	return L;
}
/******************
函数名称：BFSTraverse
函数参数：当前活动图G
函数功能：广度优先搜索图
返回值：成功返回OK，失败返回ERROR
*******************/
status BFSTraverse(ALGraph* G)
{
	if (G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	for (int v = 0; v < (*G).vexnum; v++)
		visited[v] = 0;
	LKQueue *Q=(LKQueue *)malloc(sizeof(LKQueue));
	InitQueue(Q);
	for (int v = 0; v < (*G).vexnum; v++)
	{
		if (!visited[v])
		{
			printf("%c", (*G).vertices[v].data);
			visited[v] = 1;
			EnQueue(Q, &(*G).vertices[v]);
			while (!EmptyQueue(Q))
			{
				int u = LocateVex(G, GetHead(Q)->data);
				OutQueue(Q);
				for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
					if (!visited[w])
					{
						printf("%c", (*G).vertices[w].data);
						visited[w] = 1;
						EnQueue(Q, &(*G).vertices[w]);
					}
			}
		}
	}
	return OK;
}
/******************
函数名称：DFSTraverse
函数参数：当前活动图G,要序号v
函数功能：深度优先搜索图
返回值：无
*******************/
void DFS(ALGraph* G, int v)
{
	ArcNode *p;
	printf("%c", (*G).vertices[v].data);
	visited[v] = 1;
	p = (*G).vertices[v].firstarc;
	while (p)
	{
		if (!visited[p->adjvex])
			DFS(G, p->adjvex);
		p = p->nextarc;
	}
}
/******************
函数名称：DFSTraverse
函数参数：当前活动图G
函数功能：深度优先搜索图
返回值：成功返回OK，失败返回ERROR
*******************/
status DFSTraverse(ALGraph* G)
{
	if (G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	for (int v = 0; v < (*G).vexnum; v++)
		visited[v] = 0;
	for (int v = 0; v < (*G).vexnum; v++)
	{
		if (!visited[v])
			DFS(G, v);
	}
	return OK;
}
/******************
函数名称：DeleteArc
函数参数：当前活动图G、删除弧的弧尾i和弧头j
函数功能：删除弧
返回值：成功返回OK，失败返回ERROR
*******************/
status DeleteArc(ALGraph* G, int i, int j)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	a = GetVex(G, j);
	if (a == ERROR)
		return ERROR;
	ArcNode*p=(*G).vertices[i].firstarc;
	if (p == NULL)
	{
		printf("弧头顶点序号为%d且弧尾顶点序号为%d的弧不存在，", i, j);
		return ERROR;
	}
	if (p->adjvex == j)
	{
		(*G).vertices[i].firstarc = p->nextarc;
		free(p);
		p = (*G).vertices[i].firstarc;
		(*G).arcnum--;
		return OK;
	}
	status flag = 0;
	ArcNode*q;
	while (p)												   
	{
		q = p;
		p = p->nextarc;
		if (p->adjvex == j)
		{
			q->nextarc = p->nextarc;
			free(p);
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		printf("弧头顶点序号为%d且弧尾顶点序号为%d的弧不存在，",i,j);
		return ERROR;
	}
	(*G).arcnum--;
	return OK;
}
/******************
函数名称：InsertArc
函数参数：当前活动图G、插入弧的弧尾i和弧头j
函数功能：插入弧
返回值：成功返回OK，失败返回ERROR
*******************/
status InsertArc(ALGraph* G, int i, int j)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	a = GetVex(G, j);
	if (a == ERROR)
		return ERROR;
	ArcNode*p,*q;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;
	p->nextarc= NULL;
	q = (*G).vertices[i].firstarc;
	if(q==NULL)
		(*G).vertices[i].firstarc=p; 
	else
	{
		while (q->nextarc)
			q = q->nextarc;
		q->nextarc = p;
	}
	(*G).arcnum++;
	return OK;
}
/******************
函数名称：DeleteVex
函数参数：当前活动图G、所要删除顶点的序号i
函数功能：删除顶点
返回值：成功返回OK，失败返回ERROR
*******************/
status DeleteVex(ALGraph* G, int i)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	ArcNode *p, *q=NULL;
	p = (*G).vertices[i].firstarc; 
	while (p) 
	{
		q = p;
		p = p->nextarc;
		free(q);
		(*G).arcnum--; 
	}
	int j;
	for (j = i; j<(*G).vexnum; j++) 
		(*G).vertices[j] = (*G).vertices[j + 1];
	(*G).vexnum--;
	for (j = 0; j<(*G).vexnum; j++) 
	{
		p = (*G).vertices[j].firstarc; 
		while (p)
		{		
			if (p->adjvex == i) 
			{
				if (p == (*G).vertices[j].firstarc) 
				{
					(*G).vertices[j].firstarc = p->nextarc;
					free(p);
					p = (*G).vertices[j].firstarc;
				}
				else {
					q->nextarc = p->nextarc;
					free(p);
					p = q->nextarc;
				}
				(*G).arcnum--;
			}
			else 
			{
				if (p->adjvex>i)
					p->adjvex--;
				q = p;
				p = p->nextarc;
			}
		}
	}
	return OK;
}
/******************
函数名称：InsertVex
函数参数：当前活动图G、所要插入顶点的数据e
函数功能：插入顶点
返回值：成功返回OK，失败返回ERROR
*******************/
status InsertVex(ALGraph* G, VertexType e)
{
	if (G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	if (G->vexnum == MAX_VERTICE_NUM)
	{
		printf("当前图的顶点数已达到规定的最大值，");
		return ERROR;
	}
	int j=G->vexnum;
	G->vertices[j].data= e;
	G->vertices[j].firstarc = NULL;
	G->vexnum++;
	return OK;
}
/******************
函数名称：NextAdjVex
函数参数：当前活动图G、所要查找的顶点的序号i及其邻接结点j
函数功能：输出下一邻接顶点
返回值：成功返回顶点位置，失败返回NULL
*******************/
status NextAdjVex(ALGraph* G, int i, int j)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	ArcNode *p;
	p = (G->vertices[i]).firstarc;
	while (p != NULL&&p->adjvex != j)
		p = p->nextarc;
	if (p == NULL)
		return -1;
	if (p->nextarc == NULL)
		return -3;
	return p->nextarc->adjvex;
}
/******************
函数名称：FirstAdjVex
函数参数：当前活动图G、所要查找的顶点的序号i
函数功能：输出第一邻接顶点
返回值：成功返回顶点位置，失败返回NULL
*******************/
status FirstAdjVex(ALGraph* G, int i)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	if ((G->vertices[i]).firstarc == NULL)
		return -1;
	return (G->vertices[i]).firstarc->adjvex;
}
/******************
函数名称：PutVex
函数参数：当前活动图G、所要修改的顶点的序号i以及修改后的数据e
函数功能：节点赋值
返回值：成功返回OK，失败返回ERROR
*******************/
status PutVex(ALGraph* G, int i, VertexType e)
{
	VertexType a = GetVex(G, i);
	if (a == ERROR)
		return ERROR;
	G->vertices[i].data = e;
	return OK;
}
/******************
函数名称：GetVex
函数参数：当前活动图G，以及所要查找的顶点的序号i
函数功能：查找顶点值
返回值：找到则返回顶点值，未找到返回ERROR
*******************/
VertexType GetVex(ALGraph*G, int i)
{
	if (G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	int j = G->vexnum;
	if (j == 0)
	{
		printf("该图顶点集为空，");
		return ERROR;
	}
	if(i>j-1||i<0)
	{
		printf("输入的序号不合法，");
		return ERROR;
	}
	return G->vertices[i].data;
}
/******************
函数名称：LocateVex
函数参数：当前活动图G，以及所要查找的顶点的VertexType数据e
函数功能：查找顶点
返回值：找到则返回位置i，未找到返回ERROR
*******************/
status LocateVex(ALGraph*G, VertexType e)
{
	if(G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	int i;
	for (i = 0; i < (*G).vexnum; i++)
	{
		if (e == (*G).vertices[i].data)
			return i;
	}
	return ERROR;
}
/******************
函数名称：DestroyGraph
函数参数：遍历指针G
函数功能：销毁图
返回值：成功为OK，失败为ERROR
*******************/
status DestroyGraph(ALGraph *G)
{
	if (G == NULL)
	{
		printf("当前无活动图，");
		return ERROR;
	}
	int i;
	for (i = 0; i<(*G).vexnum; i++) 
	{
		ArcNode *p, *q;
		p = (*G).vertices[i].firstarc;
		while (p) {
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	(*G).vexnum = 0;
	(*G).arcnum = 0;
	(*G).name[20] = {'\0'};
	(*G).vertices[MAX_VERTICE_NUM] = { '\0' };
	return OK;
}
/******************
函数名称：CreateCraph
函数参数：多图的头指针Head
函数功能：创建图
返回值：当前图的结点
*******************/
ALGraph *CreateGraph(ALGraph *G, char V[MAX_VERTICE_NUM], char VR[MAX_VERTICE_NUM][MAX_VERTICE_NUM])
{
	int i, j = 0;
	for (i = 0; i<(*G).vexnum; i++)
	{
		(*G).vertices[i].data = V[i];
		(*G).vertices[i].firstarc = NULL;
	}
	for (i = 0; i<(*G).vexnum; i++)
	{
		for (j = 0; VR[i][j] != '\0'; j++)
		{
			int a = LocateVex(G, VR[i][j]);
			if (a == ERROR)
			{
				printf("数据为%c的顶点在G中不存在，", VR[i][j]);
				return NULL;
			}
			ArcNode*p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = a; p->nextarc = NULL;
			ArcNode*q = (*G).vertices[i].firstarc;
			if (q == NULL)
				(*G).vertices[i].firstarc = p;
			else
			{
				while (q->nextarc)  q = q->nextarc;
				q->nextarc = p;
			}
		}
	}
	for (; i < MAX_VERTICE_NUM; i++)
	{
		(*G).vertices[i].data = 0;
		(*G).vertices[i].firstarc = NULL;
	}
	return G;
}
/******************
函数名称：show
函数参数：遍历指针G
函数功能：显示伪菜单界面
返回值：无
*******************/
void show(ALGraph* G)
{
	system("cls");
	printf("\n\n");
	printf("------------------Menu for Graph------------------\n\n");
	printf("\t1. CreateGraph\t\t9.  DeleteVex\n");
	printf("\t2. DestroyGraph\t\t10. InsertArc\n");
	printf("\t3. LocateVex\t\t11. DeleteArc\n");
	printf("\t4. GetVex\t\t12. DfsTraverse\n");
	printf("\t5. PutVex\t\t13. BFSTraverse\n");
	printf("\t6. FirstAdjVex\t\t14. SaveData\n");
	printf("\t7. NextAdjVex\t\t15. LoadData\n");
	printf("\t8. InsertVex\t\t16. ExGraph\n");
	printf("\t0. Exit\n\n");
	if (G == NULL)
		printf("-----------------当前没有活动图-----------------\n");
	else
	{
		printf("\n--------------当前对图 %s 进行操作--------------\n\n", G->name);
		for (int i = 1; i <= G->vexnum; i++)
		{
			printf("位置：%d  数据：%c\t", i-1, G->vertices[i-1].data);
			if (i % 4 == 0)printf("\n");
			if(i==G->vexnum&&i%4!=0)printf("\n\n");
		}
	}
	printf("    请选择你的操作[0~16]:");
}
