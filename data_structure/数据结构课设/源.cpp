#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define OK 1
#define ERROR 0 


typedef struct TElemType {
	char id[20];								    //身份证号
	char name[20];							//姓名
	struct BSTNode *friends;				//好友集
	struct BSTNode *fan;					//粉丝集
	struct BSTNode *concern;				//关注人集
	struct BSTNode *hobby;				//兴趣爱好集
}TElemType;
typedef struct BSTNode {
	struct TElemType data;					//数据信息
	int BF;										//平衡因子
	struct BSTNode *lchild, *rchild;		//左右孩子指针
}BSTNode;
typedef struct Forest {
	char name[20];
	struct BSTNode *HeadNode;			 //二叉树头结点
	struct Forest *next;
}Forest;

void show(Forest *head);	 //显示菜单
void show1();	//显示集合操作菜单
int InitAVL(Forest *head, Forest **F);
int DestroyAVL(BSTNode*T);
int DestroyAVL1(Forest *head, Forest *F);
BSTNode*SearchAVL(BSTNode*T, char name[20],int choice);
int InsertAVL(BSTNode*T, TElemType data);
int DeleteAVL(BSTNode*T, char name[20]);

BSTNode *Balance(BSTNode *T);
int Depth(BSTNode *T);
BSTNode*Parent(BSTNode *T, char id[20]);
BSTNode*LL(BSTNode*root);
BSTNode*RR(BSTNode*root);
BSTNode*LR(BSTNode*root);
BSTNode*RL(BSTNode*root);

int set_size(BSTNode*T);
int set_member(BSTNode*T, char id[20]);

int set_intersection(BSTNode*T1, BSTNode*T2,BSTNode*T3);
int set_intersection1(BSTNode*T1, BSTNode*T2);

void copy(BSTNode*T1, BSTNode*T2);
int set_union(BSTNode*T1, BSTNode*T2);
int set_union1(BSTNode*T1, BSTNode*T2);

int set_diffrence(BSTNode*T1, BSTNode*T2, BSTNode*T3);
int set_diffrence1(BSTNode*T1, BSTNode*T2);

int set_subset(BSTNode*T1, BSTNode*T2);
int set_equal(BSTNode*T1, BSTNode*T2);

int search_common(BSTNode*T1, BSTNode*T2);
int second_friends(BSTNode*T1, BSTNode*T2);

BSTNode *aggregate(BSTNode *T, int choice);
int aggregate_init(BSTNode**T, int choice);
int aggregate_destroy(BSTNode*T, int choice);
int Delete(BSTNode*F, char id[20], int choice);
int aggregate_insert(BSTNode*T1, BSTNode*T, int choice, char id[20]);
int InsertAVL2(BSTNode*T1, int choice, TElemType data);
int aggregate_remove(BSTNode*T1, BSTNode*T, int choice, char id[20]);
int operate_aggregate(BSTNode*root, BSTNode*T, int choice);

void TraverseAVL(BSTNode*T);	//中序遍历
void TraverseAVL2(BSTNode*T); //前序遍历
void Traverse(Forest *head);	//遍历整个森林
Forest *ExAVL(Forest *head, char name[20]);//切换AVL树

int SaveData(Forest*F);
int SaveData1(FILE *fp, BSTNode*T, int choice);
int SaveData2(FILE *fp, BSTNode*T);
int LoadData(Forest*F);
int random(BSTNode *T, int gross);
int random1(BSTNode *F,BSTNode *T, int gross,char hobby[60][20]);

int j=0;//格式化输出

int main()
{
	system("color F1");//改变颜色
	Forest *head = (Forest*)malloc(sizeof(Forest));
	head->HeadNode = NULL; memset(head->name, '0', 20); head->next = NULL;

	Forest *F = head->next;
	BSTNode *T = (BSTNode*)malloc(sizeof(BSTNode));
	BSTNode *T1 = (BSTNode*)malloc(sizeof(BSTNode));
	BSTNode *agg1 = NULL, *agg2 = NULL;
	Forest *F1 = (Forest*)malloc(sizeof(Forest));

	int op = 1;
	int choice=0,choice2=0,choice3=0,re=0;
	char id[20], name[20]; char s[100];
	TElemType data; 

	while (op)
	{
		show(F);
		scanf("%d", &op); getchar();
		switch (op)
		{
		case 0:
			printf("欢迎下次再使用本系统！\n");
			getchar(); break;
		case 1:case 7:
			if (InitAVL(head, &F) == OK)
				printf("创建AVL树成功！\n");
			else
				printf("创建AVL树失败！\n");
			getchar();
			break;
		case 2:case 8:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else if(DestroyAVL1(head, F) == OK)
			{
				F = NULL;
				printf("销毁当前AVL树成功！\n");
			}
			else
				printf("销毁当前AVL树失败！\n");
			getchar();
			break;
		case 3:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，查找失败！");
			else
			{
				re = 0;
				while (re == 0)
				{
					printf("1：按名称查询\t2：按身份证号查询\n"); scanf("%d", &choice3); getchar();
					switch (choice3)
					{
					case 1:re = 1; printf("请输入要查找的成员的名称："); scanf("%s", name); getchar(); break;
					case 2:re = 1; printf("请输入要查找的成员的身份证号："); scanf("%s", name); getchar();	break;
					default:printf("输入错误，请重新选择");
					}
				}
				T = SearchAVL(F->HeadNode->lchild, name,choice3);
				if (T != NULL)
				{
					printf("名称为%s的结点信息如下：\n。", name);
					printf("\n身份证号：%s", T->data.id);
					printf("\n\n好友集：\n");
					j = 0;
					if (T->data.friends == NULL|| T->data.friends->lchild==NULL) printf("无");
					else TraverseAVL(T->data.friends->lchild);
					printf("\n\n粉丝集：\n");
					j = 0;
					if (T->data.fan == NULL|| T->data.fan->lchild == NULL) printf("无");
					else TraverseAVL(T->data.fan->lchild);
					printf("\n\n关注人集：\n");
					j = 0;
					if (T->data.concern == NULL|| T->data.concern->lchild == NULL) printf("无");
					else TraverseAVL(T->data.concern->lchild);
					printf("\n\n兴趣爱好集：\n");
					j = 0;
					if (T->data.hobby == NULL|| T->data.hobby->lchild == NULL) printf("无");
					else TraverseAVL(T->data.hobby->lchild);
				}
				else
					printf("没有找到符合条件的成员！");
			}
			getchar();
			break;
		case 4:case 9:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else
			{
				printf("请输入所要插入的成员的身份证号："); scanf("%s", data.id);	getchar();
				printf("请输入所要插入的成员的名称："); scanf("%s", data.name); getchar();
				data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
				if (InsertAVL(F->HeadNode, data) == OK)
					printf("插入成功！");
				else
					printf("该身份证号身份已存在，插入失败！");
			}
			getchar();
			break;
		case 5:case 10:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，删除失败！");
			else
			{
				printf("请输入要删除的成员的身份证号（若多成员则以空格断开）："); fgets(s, 100, stdin);
				for (int i = 0, j = 0; i < 100; i++)
				{
					if (s[i] == ' ' || s[i] == '\n')
					{
						id[j] = '\0'; j = 0;
						T = SearchAVL(F->HeadNode->lchild, id, 2);
						if (DeleteAVL(F->HeadNode, id) == OK)
						{
							Delete(F->HeadNode->lchild, id, 1);
							Delete(F->HeadNode->lchild, id, 2);
							Delete(F->HeadNode->lchild, id, 3);
							printf("成员%s删除成功！\n", id);
						}
						else
							printf("没有找到成员%s，删除失败！\n",id);
					}
					else
					{
						id[j] = s[i];  j++;
					}
				}
			}
			getchar();
			break;
		case 6:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else if (F->HeadNode->lchild == NULL)
				printf("当前活动树为空树！\n");
			else
			{
				j = 0;
				printf("先序遍历：\n");
				TraverseAVL2(F->HeadNode->lchild);
				j = 0;
				printf("\n中序遍历：\n");
				TraverseAVL(F->HeadNode->lchild);
			}	
			getchar();
			break;
		case 11:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("若A集合属于成员的某一集合，则：\nA所属成员的身份证号："); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("A为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("输入错误，请重新输入");
					}
				}
				if (agg1 == NULL)
				{
					printf("集合A未初始化，无法进行操作！");
					getchar();
					break;
				}
				printf("若B集合属于成员的某一集合，则：\nB所属成员的身份证号："); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("B为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("输入错误，请重新输入");
					}
				}
				if (agg2 == NULL)
				{
					printf("集合B未初始化，无法进行操作！");
					getchar();
					break;
				}
				if (set_intersection1(agg1, agg2) == OK)
					printf("\n遍历交集成功！");
			}
			getchar();
			break;
		case 12:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("若A集合属于成员的某一集合，则：\nA所属成员的身份证号："); scanf("%s", id); getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("A为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("输入错误，请重新输入");
					}
				}

				printf("若B集合属于成员的某一集合，则：\nB所属成员的身份证号："); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("B为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("输入错误，请重新输入");
					}
				}

				if (agg1 == NULL)
					printf("集合A未初始化，无法进行判断！");
				else if (agg2 == NULL)
					printf("集合B未初始化，无法进行判断！");
				if (set_union1(agg1, agg2) == OK)
					printf("\n遍历并集成功！");
			}
			getchar();
			break;
		case 13:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("若A集合属于成员的某一集合，则：\nA所属成员的身份证号："); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("A为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("输入错误，请重新输入");
					}
				}

				printf("若B集合属于成员的某一集合，则：\nB所属成员的身份证号："); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("B为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("输入错误，请重新输入");
					}
				}

				if (agg1 == NULL)
					printf("集合A未初始化，无法进行判断！");
				else if (agg2 == NULL)
					printf("集合B未初始化，无法进行判断！");
				if (set_diffrence1(agg1, agg2) == OK)
					printf("\n遍历差集成功！");
			}
			getchar();
			break;
		case 14:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  
				printf("该集合中成员个数为：%d。", set_size(F->HeadNode->lchild));
			getchar();
			break;
		case 15:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("请输入所要查找的成员的身份证号："); scanf("%s", id);	getchar();
				if (set_member(F->HeadNode->lchild, id) == OK)
					printf("该元素是该集合成员！");
				else
					printf("该元素不是该集合成员！");
			}
			getchar();
			break;
		case 16:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("形如A为B的子集，则：\nA所属成员的身份证号："); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("A为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1; agg1 = aggregate(T, choice); break;
					default:printf("输入错误，请重新输入");
					}
				}

				printf("形如A为B的子集，则：\nB所属成员的身份证号："); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("B为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("输入错误，请重新输入");
					}
				}

				if (agg1 == NULL)
					printf("集合A未初始化，无法进行判断！");
				else if (agg2 == NULL)
					printf("集合B未初始化，无法进行判断！");
				if (set_subset(agg1->lchild, agg2->lchild) == OK)
					printf("所输入的A集合是B集合的子集！");
				else 
					printf("所输入的A集合不是B集合的子集！");
			}
			getchar();
			break;
		case 17:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("形如A集合与B集合相同，则：\nA所属成员的身份证号："); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("A为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:re = 1;  agg1 = aggregate(T, choice); break;
					default:printf("输入错误，请重新输入");
					}
				}

				printf("形如A集合与B集合相同，则：\nB所属成员的身份证号："); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("B为该结点的哪一集合：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice2); getchar();
					switch (choice2)
					{
					case 1:case 2:case 3:case 4:re = 1; agg2 = aggregate(T1, choice2); break;
					default:printf("输入错误，请重新输入");
					}
				}

				if (agg1 == NULL)
					printf("集合A未初始化，无法进行判断！");
				else if (agg2 == NULL)
					printf("集合B未初始化，无法进行判断！");
				if (set_equal(agg1->lchild, agg2->lchild) == OK)
					printf("所输入的A集合和B集合相同！");
				else
					printf("所输入的A集合和B集合不相同！");
			}
			getchar();
			break;
		case 18:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，初始化失败！");
			else
			{
				printf("请输入所要初始化的成员的身份证号："); scanf("%s", id); getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
					printf("没有找到成员%s！", id);
				else
				{
					re = 0;
					while (re == 0)
					{
						printf("选择所要操作的对象：\n1.好友集\t2.粉丝集\t3.关注人集\t4.兴趣爱好集\n"); scanf("%d", &choice); getchar();
						switch (choice)
						{
						case 1:case 2:case 3:case 4:re = 1; break;
						default:printf("输入错误，请重新");
						}
					}
					if (aggregate_init(&T, choice) == OK)
						printf("初始化集合成功！");
					else
						printf("初始化集合失败！");
				}
			}
			getchar();
			break;
		case 19:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("请输入所要操作的成员的身份证号："); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("请输入所要操作的集合：1.好友集  2.粉丝集  3.关注人集  4.兴趣爱好集  0.Exit\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1:case 2:case 3:case 4:
						agg1 = aggregate(T, choice);
						if (agg1 == NULL)
						{
							printf("集合未初始化，不能进行操作！");
							re = 1; break;
						}
						operate_aggregate(F->HeadNode->lchild,T, choice);
						break;
					case 0:re = 1;  printf("已退出成功！"); break;
					default:printf("输入错误，");
					}
				}
			}
			getchar();
			break;
		case 20:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("A集合：所属成员的身份证号："); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T == NULL)
				{
					printf("没有找到成员%s！",id);
					getchar(); break;
				}
				printf("B集合：所属成员的身份证号："); scanf("%s", id);	getchar();
				T1 = SearchAVL(F->HeadNode->lchild, id, 2);
				if (T1 == NULL)
				{
					printf("没有找到成员%s！", id);
					getchar(); break;
				}
				re = 0;
				while (re == 0)
				{
					printf("请选择操作：1. common_friends  2. common_fans  3. common_concerns  4.common_hobbies  0.exit\n"); scanf("%d", &choice); getchar();
					switch (choice)
					{
					case 1: case 2:case 3:case 4:
						agg1 = aggregate(T, choice); agg2 = aggregate(T1, choice);
						search_common(agg1, agg2); printf("\n");
						break;
					case 0:re = 1; printf("已成功退出！"); break;
					default:printf("输入错误，");
					}
				}
			}
			getchar();
			break;
		case 21:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild == NULL)
				printf("该活动树为空树，判断失败！");
			else
			{
				printf("A集合：所属成员的身份证号："); scanf("%s", id);	getchar();
				T = SearchAVL(F->HeadNode->lchild, id,2);
				if (T == NULL)
					printf("没有找到成员%s，查找二度好友失败！",id);
				else if (T->data.friends == NULL)
					printf("好友集合未初始化，查找二度好友失败！");
				else
				{
					second_friends(F->HeadNode->lchild, T);
					printf("\n查找完毕！");
				}
			}
			getchar();
			break;
		case 22:
			if (head == NULL)
				printf("当前没有活动树！\n");
			else
			{
				j = 0;
				Traverse(head);
				printf("请输入要切换的AVL树的名字："); scanf("%s", name); getchar();
				F1 = ExAVL(head, name);
				if (F1 == NULL)
					printf("输入的名字不存在，切换失败！\n");
				else
				{
					F = F1;
					printf("切换成功！");
				}
			}
			getchar();
			break;
		case 23:
			if (SaveData(F) == OK)
				printf("数据写入文件成功！");
			else
				printf("数据写入文件失败！");
			getchar();
			break;
		case 24:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild != NULL)
				printf("当前活动树中已存有数据，不能录入数据！");
			else if (LoadData(F) == OK)
				printf("录入数据成功！");
			else
				printf("录入数据失败！");
			getchar();
			break;
		case 25:
			if (F == NULL)
				printf("当前没有活动树！\n");
			else  if (F->HeadNode->lchild != NULL)
				printf("当前活动树中已存有数据，不能随机生成数据！");
			else
			{
				printf("请输入数据规模："); scanf("%d", &choice); getchar();
				if (random(F->HeadNode, choice) == OK)
					printf("随机生成成功！");
				else
					printf("随机生成失败！");
			}
			getchar();
			break;
		default:
			printf("功能选择是无效的输入！\n");
			getchar();
			break;
		}
	}
	return 0;
}

/******************
函数名称：random
函数参数：当前AVL树的头指针，数据规模gross
函数功能：随机生成AVL树的成员
返回值：成功返回OK，失败返回ERROR
*******************/
int random(BSTNode *T, int gross)
{
	srand(time(NULL));
	int i=0,id;
	TElemType data;
	FILE *fp=NULL;
	printf("正在随机生成数据，请稍等。。。\n");
	char name[1000][20];//存储从文件里读入的名称
	if ((fp = fopen("name.txt", "r")) == NULL)
	{
		printf("name.txt打开失败！");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s", name[i]);
		if (strcmp(name[i], "#") == 0)break;
		i++;
	}
	for (; i < 1000; i++) strcpy(name[i], "#");
	for (i = 1; i <= gross; i++)
	{
		id = rand() % gross + 1;
		sprintf(data.id, "%d", id);
		strcpy(data.name,name[i-1]);
		data.friends = data.concern= data.fan =data.hobby = NULL;
		if (InsertAVL(T, data) == ERROR)i--;
	} 
	i = 0;
	if ((fp = fopen("hobby.txt", "r")) == NULL)
	{
		printf("hobby.txt打开失败！");
		return ERROR;
	}
	char hobby[60][20];
	while (!feof(fp))
	{
		fscanf(fp, "%s", hobby[i]);
		if (strcmp(hobby[i], "#") == 0)break;
		i++;	if (i >= 60)break;
	}
	for (; i < 60; i++) strcpy(hobby[i], "#");
	random1(T, T->lchild, gross, hobby);
	fclose(fp);
	return OK;
}
/******************
函数名称：random1
函数参数：当前AVL树的遍历指针F，当前结点T，数据规模gross，爱好集合hobby
函数功能：随机生成AVL树的成员
返回值：成功返回OK，失败返回ERROR
*******************/
int random1(BSTNode *F,BSTNode *T, int gross,char hobby[60][20])
{
	if (T == NULL)
		return OK;
	int j,k; char id[20];

	k = rand() % (gross/2);
	if (T->data.friends == NULL)
		aggregate_init(&T, 1);
	for (int i = 1; i <=k; i++)
	{
		j = rand() % gross + 1;
		sprintf(id, "%d", j);
		aggregate_insert(F->lchild,T->data.friends,1,id);
	}

	k = rand() % (gross/2);
	if (T->data.fan == NULL)
		aggregate_init(&T, 2);
	for (int i = 1; i <= k; i++)
	{
		j = rand() % gross + 1;
		sprintf(id, "%d", j);
		aggregate_insert(F->lchild, T->data.fan, 2, id);
	}

	k = rand() % (gross/2);
	if (T->data.concern == NULL)
		aggregate_init(&T, 3);
	for (int i = 1; i <= k; i++)
	{
		j = rand() % gross + 1;
		sprintf(id, "%d", j);
		aggregate_insert(F->lchild, T->data.concern, 3, id);
	}

	k = rand() % (gross/2);
	if (T->data.hobby == NULL)
		aggregate_init(&T, 4);
	if (k > 60)k= 60;
	for (int i = 1; i <= k; i++)
	{
		j = rand() % 60;
		strcpy(id, hobby[j]);
		aggregate_insert(F->lchild, T->data.hobby, 4, id);
	}
	random1(F,T->lchild, gross,hobby);
	random1(F,T->rchild, gross,hobby);
	return OK;
}
/******************
函数名称：LoadData
函数参数：文件指针fp，当前AVL树的遍历指针F
函数功能：将指定文件中的内容读入当前AVL树中
返回值：成功返回OK，失败返回ERROR
*******************/
int LoadData(Forest*F)
{
	FILE*fp1 = NULL, *fp2 = NULL, *fp3 = NULL, *fp4 = NULL, *fp5 = NULL;
	printf("正在录入name数据，请稍等。。。\n");
	if ((fp1 = fopen("newname.txt", "r")) == NULL)
	{
		printf("newname.txt打开失败！");
		return ERROR;
	}
	char id[20]; char name[20];
	fscanf(fp1, "%s", id);
	fscanf(fp1, "%s", name);
	while (!feof(fp1))
	{
		TElemType data;
		strcpy(data.name, name);strcpy(data.id, id);
		data.concern = data.fan = data.friends = data.hobby = NULL;
		InsertAVL(F->HeadNode, data);
		fscanf(fp1, "%s", id);
		fscanf(fp1, "%s", name);
	}
	fclose(fp1);
	int num = set_size(F->HeadNode->lchild);
	printf("正在录入friends数据，请稍等。。。\n");
	if ((fp2 = fopen("newfriends.txt", "r")) == NULL)
	{
		printf("newfriends.txt打开失败！");
		return ERROR;
	}
	BSTNode*T = NULL;
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp2, "%s", id);
		fscanf(fp2, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id,2);
		while (1)
		{
			fscanf(fp2, "%s", id);if(strcmp(id, "#") == 0)break;
			fscanf(fp2, "%s", name);
			aggregate_init(&T,1);
			aggregate_insert(F->HeadNode->lchild, T->data.friends, 1, id);
		}
	}
	fclose(fp2);
	printf("正在录入fan数据，请稍等。。。\n");
	if ((fp3 = fopen("newfan.txt", "r")) == NULL)
	{
		printf("newfan.txt打开失败！");
		return ERROR;
	}
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp3, "%s", id); 
		fscanf(fp3, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id, 2);
		while (1)
		{
			fscanf(fp3, "%s", id); if (strcmp(id, "#") == 0)break;
			fscanf(fp3, "%s", name);
			aggregate_init(&T,2);
			aggregate_insert(F->HeadNode->lchild, T->data.fan, 2, id);
		}
	}
	fclose(fp3);
	printf("正在录入concern数据，请稍等。。。\n");
	if ((fp4 = fopen("newconcern.txt", "r")) == NULL)
	{
		printf("newconcern.txt打开失败！");
		return ERROR;
	}
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp4, "%s", id);
		fscanf(fp4, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id, 2);
		while (1)
		{
			fscanf(fp4, "%s", id); if (strcmp(id, "#") == 0)break;
			fscanf(fp4, "%s", name);
			aggregate_init(&T,3);
			aggregate_insert(F->HeadNode->lchild, T->data.concern, 3, id);
		}
	}
	fclose(fp4);
	printf("正在录入hobby数据，请稍等。。。\n");
	if ((fp5 = fopen("newhobby.txt", "r")) == NULL)
	{
		printf("newhobby.txt打开失败！");
		return ERROR;
	}
	for (int i = 1; i <= num; i++)
	{
		fscanf(fp5, "%s", id);
		fscanf(fp5, "%s", name);
		T = SearchAVL(F->HeadNode->lchild, id, 2);
		while (1)
		{
			fscanf(fp5, "%s", id);if (strcmp(id, "#") == 0)break;
			fscanf(fp5, "%s", name);
			aggregate_init(&T,4);
			aggregate_insert(F->HeadNode->lchild, T->data.hobby, 4, id);
		}
	}
	fclose(fp5);
	return OK;
}
/******************
函数名称：SaveData2
函数参数：文件指针fp，当前AVL树的结点T
函数功能：将当前AVL树的内容存入指定文件
返回值：成功返回OK，失败返回ERROR
*******************/
int SaveData2(FILE *fp, BSTNode*T)
{
	if (T) {
		SaveData2(fp, T->lchild);

		fprintf(fp, "%s %s",T->data.id,T->data.name); 
		j++; if (j % 20 == 0)fprintf(fp, "\n");else fprintf(fp, " ");

		SaveData2(fp, T->rchild);
	}
	return OK;
}
/******************
函数名称：SaveData1
函数参数：文件指针fp，当前AVL树的结点T，集合选项choice
函数功能：将当前AVL树的内容存入指定文件
返回值：成功返回OK，失败返回ERROR
*******************/
int SaveData1(FILE *fp, BSTNode*T,int choice)
{
	if (T) 
	{
		SaveData1(fp, T->lchild, choice);

		fprintf(fp, "%s %s ", T->data.id, T->data.name);
		switch (choice)
		{
			case 1:j = 0;
				if (T->data.friends != NULL)
					SaveData2(fp, T->data.friends->lchild); 
				break;
			case 2:j = 0;
				if (T->data.fan != NULL)
					SaveData2(fp, T->data.fan->lchild);
				break;
			case 3:j = 0;
				if (T->data.concern != NULL)
					SaveData2(fp, T->data.concern->lchild);
				break;
			case 4:j = 0;
				if (T->data.hobby != NULL)
					SaveData2(fp, T->data.hobby->lchild);
				break;
		}
		fprintf(fp, "#\n");

		SaveData1(fp,T->rchild,choice);
	}
	return OK;
}
/******************
函数名称：SaveData
函数参数：文件指针fp，当前AVL树的遍历指针F
函数功能：将当前AVL树的内容存入指定文件
返回值：成功返回OK，失败返回ERROR
*******************/
int SaveData(Forest*F)
{
	FILE*fp1=NULL,*fp2=NULL, *fp3=NULL, *fp4=NULL, *fp5=NULL;
	BSTNode*T = NULL;
	printf("正在保存name数据，请稍等。。。\n");
	j = 0;
	if ((fp1 = fopen("newname.txt", "w")) == NULL)
	{
		printf("newname.txt打开失败！");
		return ERROR;
	}
	if(F==NULL)fprintf(fp1, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp1, "");
		else
		{
			if (SaveData2(fp1, T) == ERROR)
			{
				fclose(fp1);
				return ERROR;
			}
		}
	}
	fclose(fp1);
	printf("正在保存friends数据，请稍等。。。\n");
	if ((fp2 = fopen("newfriends.txt", "w")) == NULL)
	{
		printf("newfriends.txt打开失败！");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp2, "");
		else
		{
			if (SaveData1(fp2, T, 1) == ERROR)
			{
				fclose(fp2);
				return ERROR;
			}
		}
	}
	fclose(fp2);
	printf("正在保存fan数据，请稍等。。。\n");
	if ((fp3 = fopen("newfan.txt", "w")) == NULL)
	{
		printf("newfan.txt打开失败！");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp3, "");
		else
		{
			if (SaveData1(fp3, T, 2) == ERROR)
			{
				fclose(fp3);
				return ERROR;
			}
		}
	}
	fclose(fp3);
	printf("正在保存concern数据，请稍等。。。\n");
	if ((fp4 = fopen("newconcern.txt", "w")) == NULL)
	{
		printf("newconcern.txt打开失败！");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp4, "");
		else
		{
			if (SaveData1(fp4, T, 3) == ERROR)
			{
				fclose(fp4);
				return ERROR;
			}
		}
	}
	fclose(fp4);
	printf("正在保存hobby数据，请稍等。。。\n");
	if ((fp5 = fopen("newhobby.txt", "w")) == NULL)
	{
		printf("newhobby.txt打开失败！");
		return ERROR;
	}
	if (F == NULL)fprintf(fp2, "");
	else
	{
		T = F->HeadNode->lchild;
		if (T == NULL)fprintf(fp5, "");
		else
		{
			if (SaveData1(fp5, T, 4) == ERROR)
			{
				fclose(fp5);
				return ERROR;
			}
		}
	}
	fclose(fp5);
	return OK;
}
/******************
函数名称：Traverse
函数参数：森林的头结点head
函数功能：对所有AVL树进行中序遍历（同时输出序号和名称，形如1（李））
返回值：无
*******************/
void Traverse(Forest *head)
{
	Forest *p = head->next;
	if (p == NULL)
		printf("当前无树存在！\n");
	while (p)
	{
		printf("树的名字：%s 树的成员个数：%d\n", p->name, set_size(p->HeadNode->lchild));
		if (p->HeadNode->lchild == NULL)
			printf("该树为空树！");
		else
			TraverseAVL(p->HeadNode->lchild);
		printf("\n\n");
		p = p->next;
	}
	printf("遍历结束，");
}
/******************
函数名称：ExAVL
函数参数：森林的头结点head，名称name
函数功能：将活动树切换为名称为name的AVL树
返回值：成功返回指向切换后的树的遍历指针，失败返回NULL
*******************/
Forest *ExAVL(Forest *head, char name[20])
{
	Forest *q = head->next;
	while (q)
	{
		if (strcmp(q->name, name) == 0)
			break;
		q = q->next;
	}
	return q;
}

/******************
函数名称：operate_aggregate
函数参数：AVL树的根结点root，集合所属结点T，集合选项choice
函数功能：对指定集合进行销毁、增添、删除、修改、查找、遍历、统计规模的操作
返回值：返回OK
*******************/
int operate_aggregate(BSTNode*root, BSTNode*T, int choice)
{
	BSTNode*node = NULL,*T1=NULL;
	char s[100];
	switch (choice)
	{
	case 1:T1 = T->data.friends; break;
	case 2:T1 = T->data.fan; break;
	case 3:T1 = T->data.concern; break;
	case 4:T1 = T->data.hobby; break;
	}
	int op = 1, re = 0; char id[20], id2[20];
	while (op)
	{
		show1();
		scanf("%d", &op); getchar();
		switch (op)
		{
		case 0:
			printf("已退出对当前集合的操作！\n");
			break;
		case 1:
			if (DestroyAVL(T1->lchild) == OK)
			{
				switch (choice)
				{
				case 1:T->data.friends = NULL; break;
				case 2:T1 = T->data.fan = NULL; break;
				case 3:T1 = T->data.concern = NULL; break;
				case 4:T1 = T->data.hobby = NULL; break;
				}
				Delete(root, T->data.id, choice);
				printf("集合销毁成功！\n");
			}
			else
				printf("销毁失败！\n");
			break;
		case 2:
			printf("请输入要插入的成员的身份证号（若多成员则以空格断开）：");
			fgets(s, 100, stdin);
			for (int i = 0, j = 0; i < 100; i++)
			{
				if (s[i] == ' ' || s[i] == '\n')
				{
					id[j] = '\0'; j = 0;
					if (aggregate_insert(root, T1, choice, id) == OK)
						printf("成员%s插入成功！\n", id);
					else
						printf("成员%s插入失败！\n", id);
				}
				else
				{
					id[j] = s[i];  j++;
				}
			}
			break;
		case 3:
			printf("请输入要删除的成员的身份证号（若多成员则以空格断开）："); fgets(s, 100, stdin);
			for (int i = 0, j = 0; i < 100; i++)
			{
				if (s[i] == ' ' || s[i] == '\n')
				{
					id[j] = '\0'; j = 0;
					if (aggregate_remove(root, T1, choice, id) == OK)
						printf("成员%s删除成功！\n",id);
					else
						printf("成员%s不存在，删除失败！\n",id);
				}
				else
				{
					id[j] = s[i];  j++;
				}
			}
			break;
		case 4:
			printf("请输入修改前的成员的身份证号："); scanf("%s", id); getchar();
			if (SearchAVL(T1->lchild, id, 2) != NULL)
			{
				printf("请输入修改后的成员的身份证号："); scanf("%s", id2); getchar();
				if (SearchAVL(T1->lchild, id, 2) != NULL)
				{
					if (aggregate_remove(root, T1, choice, id) == OK)
					{
						aggregate_insert(root, T1, choice, id2);printf("修改成功！\n");
					}
				}
				else
					printf("不存在身份证号为%s的成员，修改失败！\n", id2);
			}
			else
				printf("不存在身份证号为%s的成员，修改失败！\n", id);
			break;
		case 5:
			printf("请输入要查找的成员的身份证号："); scanf("%s", id); getchar();
			node = SearchAVL(T1->lchild, id, 2);
			if (node == NULL)
				printf("不存在身份证号为%s的成员，查找失败！\n", id);
			else
				printf("查找成功！\n身份证号：%s  名称：%s\n", node->data.id, node->data.name);
			break;
		case 6:
			if (T1->lchild == NULL)
				printf("集合为空集！");
			else
			{
				j = 0;
				printf("先序遍历：\n");
				TraverseAVL2(T1->lchild);
				j = 0;
				printf("\n中序遍历：\n");
				TraverseAVL(T1->lchild);
			}
			printf("\n");
			break;
		case 7:
			printf("该集合中成员个数为：%d。\n", set_size(T1->lchild)); 
			break;
		default:
			printf("功能选择是无效的输入！\n");
			break;
		}
	}
	return OK;
}
/******************
函数名称：show1
函数参数：无
函数功能：显示关于集合操作的伪菜单界面
返回值：无
*******************/
void show1()
{
	printf("1. Destroy  2. Insert  3. Delete  4. Revise  5. Search  6. Traverse  7. Size 0. Exit\n");
}

/******************
函数名称：aggregate_remove
函数参数：当前AVL树的根结点T，所要进行删除的集合所属于的成员结点，集合选项choice，身份证号id
函数功能：将对应集合删除一个身份证号id的成员
返回值：成功返回OK，失败返回ERROR
*******************/
int aggregate_remove(BSTNode*T1, BSTNode*T, int choice, char id[20])
{
	BSTNode*node = NULL;
	if (choice == 4)
		node = SearchAVL(T->lchild, id, 2);
	else
		node = SearchAVL(T1, id, 2);
	if (node == NULL)
	{
		printf("没有找到符合条件的结点，");
		return ERROR;
	}
	if (T == NULL)
	{
		printf("该集合未初始化，");
		return ERROR;
	}
	switch (choice)
	{
	case 1:
		if (DeleteAVL(T, id) == OK)
		{
			DeleteAVL(node->data.friends, T->data.id);
			return OK;
		}
		else return ERROR;
	case 2:
		if (DeleteAVL(T, id) == OK)
		{
			DeleteAVL(node->data.concern, T->data.id);
			return OK;
		}
		else return ERROR;
	case 3:
		if (DeleteAVL(T, id) == OK)
		{
			DeleteAVL(node->data.fan, T->data.id);
			return OK;
		}
		else return ERROR;
	case 4://删除T的爱好集合中身份证号为id的结点，不需要反向删除
		if (DeleteAVL(T, id) == OK)return OK;
	}
	return ERROR;
}
/******************
函数名称：aggregate_insert
函数参数：AVL树的根结点，所要进行插入的集合所属于的成员结点，集合选项choice，身份证号id
函数功能：将对应集合插入一个身份证号id的成员
返回值：成功返回OK，失败返回ERROR
*******************/
int aggregate_insert(BSTNode*T1, BSTNode*T, int choice, char id[20])
{
	if (strcmp(T->data.id, id) == 0)return ERROR;
	BSTNode*node = NULL;
	if (choice == 4)//如果插入的时爱好集合，则将name存为0，在id中存入爱好
	{
		node = (BSTNode*)malloc(sizeof(BSTNode));
		strcpy(node->data.id, id); strcpy(node->data.name, "0");
		node->data.concern = NULL; node->data.friends = NULL;
		node->data.fan = NULL; node->data.hobby = NULL;
		node->lchild = node->rchild = NULL;
	}
	else//如果不是，则在AVL树中查找到身份证号为id的结点，以便实现反向添加
	{
		node = SearchAVL(T1, id, 2);
		if (node == NULL)
		{
			printf("没有找到符合条件的结点，");
			return ERROR;
		}
	}
	if (T == NULL)
	{
		printf("该集合未初始化，");
		return ERROR;
	}
	else if (SearchAVL(T->lchild, id, 2) != NULL)
		return ERROR;
	//在T的好友集合中插入node.data并在node的好友集合插入T.data
	if (InsertAVL(T, node->data) == OK&&InsertAVL2(node, choice, T->data) == OK)
		return OK;
	return ERROR;
}
/******************
函数名称：InsertAVL2
函数参数：AVL树的头结点，集合选项choice，数据结构data
函数功能：插入一个数据域为data的结点（仅用于完善集合，即在集合未初始化时，自行初始化集合）
返回值：成功返回OK，失败返回ERROR
*******************/
int InsertAVL2(BSTNode*T1, int choice, TElemType data)
{
	BSTNode*T = NULL;
	switch (choice)
	{
	case 1:
		if (T1->data.friends == NULL)//若集合没有初始化，则先初始化
			aggregate_init(&T1, 1);
		T = T1->data.friends->lchild;
		if (T == NULL)
		{
			T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
			T->BF = 0; T->data = data;
			T->lchild = NULL; T->rchild = NULL;
			T1->data.friends->lchild = T;
			return OK;
		}
		break;
	case 2:
		if (T1->data.concern == NULL)//若集合没有初始化，则先初始化
			aggregate_init(&T1, 3);
		T = T1->data.concern->lchild;
		if (T == NULL)
		{
			T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
			T->BF = 0; T->data = data;
			T->lchild = NULL; T->rchild = NULL;
			T1->data.concern->lchild = T;
			return OK;
		}
		break;
	case 3:
		if (T1->data.fan == NULL)//若集合没有初始化，则先初始化
			aggregate_init(&T1, 2);
		T = T1->data.fan->lchild;
		if (T == NULL)
		{
			T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
			T->BF = 0; T->data = data;
			T->lchild = NULL; T->rchild = NULL;
			T1->data.fan->lchild = T;
			return OK;
		}
		break;
	case 4:return OK;
	}

	BSTNode*pre = NULL, *current = T;
	while (current != NULL)
	{
		if (strcmp(current->data.id, data.id) == 0)
			return ERROR;
		pre = current;
		current = (strcmp(data.id, pre->data.id)>0) ? pre->rchild : pre->lchild;
	}
	current = (struct BSTNode*)malloc(sizeof(struct BSTNode)); current->BF = 0; current->data = data;
	current->lchild = NULL; current->rchild = NULL;
	if (strcmp(data.id, pre->data.id)>0)  pre->rchild = current;
	else pre->lchild = current;

	switch (choice)
	{
	case 1:
		T1->data.friends->lchild = Balance(T);
		if (T1->data.friends->lchild != NULL)
			return OK;
	case 2:
		T1->data.concern->lchild = Balance(T);
		if (T1->data.concern->lchild != NULL)
			return OK;
	case 3:
		T1->data.fan->lchild = Balance(T);
		if (T1->data.fan->lchild != NULL)
			return OK;
	}
	return ERROR;
}
/******************
函数名称：aggregate_destroy
函数参数：当前进行操作的集合所属的成员结点，集合选项choice
函数功能：销毁当前AVL树
返回值：成功返回OK，失败返回ERROR
*******************/
int aggregate_destroy(BSTNode*T, int choice)
{
	switch (choice)
	{
	case 1:
		if (T->data.friends == NULL)
			return ERROR;
		DestroyAVL(T->data.friends->lchild);
		T->data.friends = NULL;
		break;
	case 2:
		if (T->data.fan == NULL)
			return ERROR;
		DestroyAVL(T->data.fan->lchild);
		T->data.fan = NULL;
		break;
	case 3:
		if (T->data.concern == NULL)
			return ERROR;
		DestroyAVL(T->data.concern->lchild);
		T->data.concern = NULL;
		break;
	case 4:
		if (T->data.hobby == NULL)
			return ERROR;
		DestroyAVL(T->data.hobby->lchild);
		T->data.hobby = NULL;
		break;
	}
	return OK;
}
/******************
函数名称：Delete
函数参数：当前进行操作的AVL树的根结点，集合所属的成员身份证号，集合选项choice
函数功能：删除掉原来集合中所销毁的
返回值：成功返回OK，失败返回ERROR
*******************/
int Delete(BSTNode*F, char id[20], int choice)
{
	if (F == NULL)
		return OK;
	BSTNode*node = NULL;
	switch (choice)
	{
	case 1://反向删除F结点好友集中的id为T.data.id的成员
		if (F->data.friends == NULL)return OK;
		DeleteAVL(F->data.friends, id);
		break;
	case 2://反向删除F结点关注人集中的id为T.data.id的成员
		if (F->data.concern == NULL)return OK;
		DeleteAVL(F->data.concern, id); break;
	case 3://反向删除F结点粉丝集中的id为T.data.id的成员
		if (F->data.fan == NULL)return OK;
		DeleteAVL(F->data.fan, id); break;
	case 4:return OK;//爱好集合不需要反向删除
	}
	Delete(F->lchild, id, choice); Delete(F->rchild, id, choice);
	return OK;
}
/******************
函数名称：aggregate_init
函数参数：当前进行操作的集合所属的成员结点，集合选项choice
函数功能：初始化集合
返回值：成功返回OK，失败返回ERROR
*******************/
int aggregate_init(BSTNode**T, int choice)
{
	switch (choice)
	{
	case 1:
		if ((*T)->data.friends == NULL)//初始化好友集合
		{
			(*T)->data.friends = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.friends->BF = 0; (*T)->data.friends->lchild = NULL; (*T)->data.friends->rchild = NULL;
			strcpy((*T)->data.friends->data.id, (*T)->data.id); strcpy((*T)->data.friends->data.name, (*T)->data.name);
			(*T)->data.friends->data.hobby = NULL; (*T)->data.friends->data.friends = NULL;
			(*T)->data.friends->data.fan = NULL; (*T)->data.friends->data.concern = NULL;
			return OK;
		}
	case 2:
		if ((*T)->data.fan == NULL)//初始化粉丝集合
		{
			(*T)->data.fan = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.fan->BF = 0; (*T)->data.fan->lchild = NULL; (*T)->data.fan->rchild = NULL;
			strcpy((*T)->data.fan->data.id, (*T)->data.id); strcpy((*T)->data.fan->data.name, (*T)->data.name);
			(*T)->data.fan->data.hobby = NULL; (*T)->data.fan->data.friends = NULL;
			(*T)->data.fan->data.fan = NULL; (*T)->data.fan->data.concern = NULL;
			return OK;
		}
	case 3:
		if ((*T)->data.concern == NULL)//初始化关注人集合
		{
			(*T)->data.concern = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.concern->BF = 0; (*T)->data.concern->lchild = NULL; (*T)->data.concern->rchild = NULL;
			strcpy((*T)->data.concern->data.id, (*T)->data.id); strcpy((*T)->data.concern->data.name, (*T)->data.name);
			(*T)->data.concern->data.hobby = NULL; (*T)->data.concern->data.friends = NULL;
			(*T)->data.concern->data.fan = NULL; (*T)->data.concern->data.concern = NULL;
			return OK;
		}
	case 4:
		if ((*T)->data.hobby == NULL)//初始化好友集合
		{
			(*T)->data.hobby = (BSTNode*)malloc(sizeof(BSTNode));
			(*T)->data.hobby->BF = 0; (*T)->data.hobby->lchild = NULL; (*T)->data.hobby->rchild = NULL;
			strcpy((*T)->data.hobby->data.id, (*T)->data.id); strcpy((*T)->data.hobby->data.name, (*T)->data.name);
			(*T)->data.hobby->data.hobby = NULL; (*T)->data.hobby->data.friends = NULL;
			(*T)->data.hobby->data.fan = NULL; (*T)->data.hobby->data.concern = NULL;
			return OK;
		}
	}
	return ERROR;
}

/******************
函数名称：aggregate
函数参数：成员结点T和集合选项choice
函数功能：返回所需集合的头指针
返回值：所需集合的头指针
*******************/
BSTNode*aggregate(BSTNode *T, int choice)
{
	switch (choice)
	{
	case 1:return T->data.friends; break;
	case 2:return T->data.fan; break;
	case 3:return T->data.concern; break;
	case 4:return T->data.hobby; break;
	}
}
/******************
函数名称：search_common
函数参数：两个集合的头指针T1、T2
函数功能：输出T1和T2的交集
返回值：成功返回OK，失败返回ERROR
*******************/
int search_common(BSTNode*T1, BSTNode*T2)
{
	if (T1 == NULL || T2 == NULL)
	{
		printf("空集！");
		return OK;
	}

	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;
	//求T1和T2的集合的交集，并生成AVL树，T为AVL树的头结点
	set_intersection(T, T1->lchild, T2->lchild);
	j = 0;
	if (T->lchild == NULL)
		printf("空集！");
	else//若集合的交集非空，则遍历输出交集T
		TraverseAVL(T->lchild);
	return OK;
}
/******************
函数名称：second_friends
函数参数：遍历指针T1和所要查找的结点T
函数功能：输出和T是二度好友的结点的信息
返回值：成功返回OK，失败返回ERROR
*******************/
int second_friends(BSTNode*T1, BSTNode*T)
{
	if (T1 == NULL)
		return OK;
	second_friends(T1->lchild, T);

	if (set_member(T->data.friends->lchild, T1->data.id));
	else if (T1->data.friends == NULL);
	else if (strcmp(T1->data.id, T->data.id) != 0)
	{
		BSTNode*node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
		node->BF = 0; node->lchild = NULL; node->rchild = NULL;
		//求T1和T2的好友集合的交集，并生成AVL树，T为AVL树的头结点
		set_intersection(node, T->data.friends->lchild, T1->data.friends->lchild);
		j = 0;
		if (node->lchild != NULL)//若非空则T1为T的二度好友，输出T1的相关信息
			printf("身份证号：%s 姓名：%s\n", T1->data.id, T1->data.name);
	}

	second_friends(T1->rchild, T);
	return OK;
}

/******************
函数名称：set_subset
函数参数：AVL树的根结点T1、T2
函数功能：T1是否和T2相同
返回值：是返回OK，不是返回ERROR
*******************/
int set_equal(BSTNode*T1, BSTNode*T2)
{
	//如果T1是T2的子集且T2是T1的子集，则T1与T2相同
	if (set_subset(T1, T2) == OK&&set_subset(T2, T1) == OK)
		return OK;
	else return ERROR;
}
/******************
函数名称：set_subset
函数参数：AVL树的根结点T1、T2
函数功能：求T1是否是T2的子集
返回值：是返回OK，不是返回ERROR
*******************/
int set_subset(BSTNode*T1, BSTNode*T2)
{
	if (T1 == NULL)return OK;

	if (set_member(T2, T1->data.id)==OK)
	{
		if (!set_subset(T1->lchild, T2))return ERROR;
		if (!set_subset(T1->rchild, T2))return ERROR;
		return OK;
	}
	else return ERROR;
}
/******************
函数名称：set_member
函数参数：AVL树的根结点T，身份证号id
函数功能：求身份证号为id的成员是否输入结点T的某集合
返回值：是返回OK，不是返回ERROR
*******************/
int set_member(BSTNode*T, char id[20])
{
	if(T==NULL)
		return ERROR;
	if (SearchAVL(T, id,2) != NULL)return OK;
	return ERROR;
}

/******************
函数名称：set_intersection
函数参数：所要进行操作的两个集合所属于的两个成员结点T1、T2、T3
函数功能：将存在于T3且存在于T2的结点添加到T1中
返回值：成功返回OK，失败返回ERROR
*******************/
int set_intersection(BSTNode*T1, BSTNode*T2, BSTNode*T3)
{
	if (T3 == NULL||T2==NULL)
		return OK;
	if (SearchAVL(T2, T3->data.id,2) != NULL)
	{
		TElemType data;
		strcpy(data.id,T3->data.id); strcpy(data.name, T3->data.name);
		data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
		InsertAVL(T1, data);
	}
	set_intersection(T1, T2, T3->lchild);
	set_intersection(T1, T2, T3->rchild);
	return OK;
}
/******************
函数名称：set_intersection1
函数参数：所要进行操作的两个集合头指针T1、T2
函数功能：求两集合的交集
返回值：成功返回OK，失败返回ERROR
*******************/
int set_intersection1(BSTNode*T1, BSTNode*T2)
{
	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;

	if (T1 == NULL || T2 == NULL)return ERROR;
	set_intersection(T, T1->lchild, T2->lchild);

	j = 0;
	if (T->lchild == NULL)
		printf("交集为空集！");
	else
		TraverseAVL(T->lchild);
	return OK;
}
/******************
函数名称：set_union
函数参数：所要进行操作的两个集合所属于的两个成员结点T1、T2
函数功能：将存在于T2而不存在于T1的结点添加到T1中
返回值：成功返回OK，失败返回ERROR
*******************/
int set_union(BSTNode*T1, BSTNode*T2)
{
	if (T2 == NULL)
		return OK;
	if (SearchAVL(T1, T2->data.id,2) == NULL)
	{
		TElemType data;
		strcpy(data.id, T2->data.id); strcpy(data.name, T2->data.name);
		data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
		InsertAVL(T1, data);
	}
	set_union(T1, T2->lchild);
	set_union(T1, T2->rchild);
	return OK;
}
/******************
函数名称：copy
函数参数：所要进行操作的两个集合所属于的两个成员结点T1、T2
函数功能：将存在于T2的结点添加到T1中
返回值：成功返回OK，失败返回ERROR
*******************/
void copy(BSTNode*T1, BSTNode*T2)
{
	if (T2 == NULL)
		return;
	TElemType data;
	strcpy(data.id,T2->data.id); strcpy(data.name, T2->data.name);
	data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
	InsertAVL(T1, data);

	copy(T1, T2->lchild);
	copy(T1, T2->rchild);
}
/******************
函数名称：set_union1
函数参数：所要进行操作的两个集合头指针T1、T2
函数功能：求两集合的并集
返回值：成功返回OK，失败返回ERROR
*******************/
int set_union1(BSTNode*T1, BSTNode*T2)
{
	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;

	if (T1 == NULL || T2 == NULL)return ERROR;
	copy(T, T1->lchild);
	set_union(T, T2->lchild);

	j = 0;
	if (T->lchild == NULL)
		printf("并集为空集！");
	else
		TraverseAVL(T->lchild);
	return OK;
}
/******************
函数名称：set_diffrence
函数参数：所要进行操作的两个集合所属于的两个成员结点T1、T2、T3
函数功能：将存在于T3而不存在于T2的结点添加到T1中
返回值：成功返回OK，失败返回ERROR
*******************/
int set_diffrence(BSTNode*T1, BSTNode*T2, BSTNode*T3)
{
	if (T3 == NULL || T2 == NULL)
		return OK;
	if (SearchAVL(T2, T3->data.id,2) == NULL)
	{
		TElemType data;
		strcpy(data.id, T3->data.id); strcpy(data.name, T3->data.name);
		data.concern = NULL; data.fan = NULL; data.friends = NULL; data.hobby = NULL;
		InsertAVL(T1, data);//将data插入到T1中
	}
	set_diffrence(T1, T2, T3->lchild);
	set_diffrence(T1, T2, T3->rchild);
	return OK;
}
/******************
函数名称：set_diffrence1
函数参数：所要进行操作的两个集合的头指针T1、T2
函数功能：求两集合的差集
返回值：成功返回OK，失败返回ERROR
*******************/
int set_diffrence1(BSTNode*T1, BSTNode*T2)
{
	BSTNode*T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
	T->BF = 0; T->lchild = NULL; T->rchild = NULL;

	if (T1 == NULL || T2 == NULL)return ERROR;
	set_diffrence(T, T1->lchild, T2->lchild); set_diffrence(T, T2->lchild, T1->lchild);

	j = 0;
	if (T->lchild == NULL)
		printf("差集为空集！");
	else
		TraverseAVL(T->lchild);
	return OK;
}
/******************
函数名称：set_size
函数参数：当前AVL树的根结点
函数功能：求集合的规模
返回值：成功返回集合规模
*******************/
int set_size(BSTNode*T)
{
	if (T == NULL)
		return 0;
	else
		return set_size(T->lchild) + set_size(T->rchild) + 1;
}

/******************
函数名称：TraverseAVL
函数参数：AVL树的根结点
函数功能：对当前AVL树进行中序遍历（同时输出序号和名称，形如1（李））
返回值：无
*******************/
void TraverseAVL(BSTNode*T)
{
	if (T)
	{
		TraverseAVL(T->lchild);
		printf("%s（%s）", T->data.name, T->data.id);
		j++; if(j % 10 == 0)printf("\n"); else printf(" ");
		TraverseAVL(T->rchild);
	}
	return;
}
/******************
函数名称：TraverseAVL2
函数参数：AVL树的根结点
函数功能：对当前AVL树进行先序遍历（同时输出序号和名称，形如1（李））
返回值：无
*******************/
void TraverseAVL2(BSTNode*T)
{
	if (T)
	{
		printf("%s（%s）", T->data.name, T->data.id);
		j++; if(j % 10 == 0 )printf("\n"); else printf(" ");
		TraverseAVL2(T->lchild);
		TraverseAVL2(T->rchild);
	}
	return;
}

/******************
函数名称：LL
函数参数：AVL树的根结点
函数功能：插入旋转根的左孩子的左子树而导致失衡的情况需要进行RR旋转
返回值：旋转后新的根结点
*******************/
BSTNode*LL(BSTNode*root)
{
	BSTNode*newroot = root->lchild;
	root->lchild = newroot->rchild;
	newroot->rchild = root;
	if (newroot->BF == 1)
	{
		root->BF = 0;
		newroot->BF = 0;
	}
	else
	{
		root->BF = 1;
		newroot->BF = -1;
	}
	return newroot;
}
/******************
函数名称：RR
函数参数：AVL树的根结点
函数功能：插入旋转根的右孩子的右子树而导致失衡的情况需要进行RR旋转
返回值：旋转后新的根结点
*******************/
BSTNode*RR(BSTNode*root)
{
	BSTNode*newroot = root->rchild;
	root->rchild = newroot->lchild;
	newroot->lchild = root;
	if (newroot->BF == -1)
	{
		root->BF = 0;
		newroot->BF = 0;
	}
	else
	{
		root->BF = -1;
		newroot->BF = 1;
	}
	return newroot;
}
/******************
函数名称：LR
函数参数：AVL树的根结点
函数功能：插入旋转根的左孩子的右子树而导致失衡的情况需要进行LR旋转
返回值：旋转后新的根结点
*******************/
BSTNode*LR(BSTNode*root)
{
	BSTNode*root1 = root->lchild;
	BSTNode*newroot = root1->rchild;
	root->lchild = newroot->rchild;
	root1->rchild = newroot->lchild;
	newroot->lchild = root1;
	newroot->rchild = root;
	switch (newroot->BF) //改变平衡因子
	{
	case 0:
		root->BF = 0;
		root1->BF = 0;
		break;
	case 1:
		root->BF = -1;
		root1->BF = 0;
		break;
	case -1:
		root->BF = 0;
		root1->BF = 1;
		break;
	}
	newroot->BF = 0;
	return newroot;
}
/******************
函数名称：RL
函数参数：AVL树的根结点
函数功能：插入旋转根的右孩子的左子树而导致失衡的情况需要进行RL旋转
返回值：旋转后新的根结点
*******************/
BSTNode*RL(BSTNode*root)
{
	BSTNode*root1 = root->rchild;
	BSTNode*newroot = root1->lchild;
	root->rchild = newroot->lchild;
	root1->lchild = newroot->rchild;
	newroot->rchild = root1;
	newroot->lchild = root;
	switch (newroot->BF)
	{
	case 0:
		root->BF = 0;
		root1->BF = 0;
		break;
	case 1:
		root->BF = 0;
		root1->BF = -1;
		break;
	case -1:
		root->BF = 1;
		root1->BF = 0;
		break;
	}
	newroot->BF = 0;
	return newroot;
}

/******************
函数名称：DeleteAVL
函数参数：AVL树的头结点，所要删除的结点的身份证号
函数功能：删除名称为name的结点
返回值：成功返回OK，失败返回ERROR
*******************/
int DeleteAVL(BSTNode*T1, char id[20])
{
	if (T1 == NULL)return ERROR;
	BSTNode*T = T1->lchild;		
	BSTNode*node = NULL;
	node = SearchAVL(T, id, 2); 
	if (node == NULL||T==NULL)//所要查找的结点不存在或者当前AVL树为空树则返回ERROR
	{
		return ERROR;
	}
	BSTNode*temp1=NULL,*temp2=NULL;
	if (node->lchild != NULL&&node->rchild != NULL)
	{
		temp1 = node->lchild; temp2 = node;
		while (temp1->rchild != NULL)
		{
			temp2 = temp1;
			temp1 = temp1->rchild;
		}
		if (temp1->lchild == NULL)
		{
			if (temp2 != node)
			{
				temp1->lchild = node->lchild; temp1->rchild = node->rchild;
				temp2->rchild = NULL;
			}	
			else
				temp1->rchild = node->rchild;
		}
		if (node == T)//如果要删除的结点为根结点，修改根结点
			T = temp1;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);//调用函数用prenode存储所要删除结点的双亲结点
			if (strcmp(temp1->data.id, prenode->data.id) > 0)
				prenode->rchild = temp1;
			else
				prenode->lchild = temp1;
		}	 
		node->lchild = NULL; node->rchild = NULL;
		free(node);
	}
	else if (node->lchild == NULL&&node->rchild == NULL)
	{
		if (node == T)
			T = NULL;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);
			if (strcmp(node->data.id, prenode->data.id) > 0)
				prenode->rchild = NULL;
			else
				prenode->lchild = NULL;
		}
	}
	else if (node->lchild == NULL&&node->rchild != NULL)
	{
		if (node == T)
			T = T->rchild;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);
			if (strcmp(node->data.id, prenode->data.id) > 0)
				prenode->rchild = node->rchild;
			else
				prenode->lchild = node->rchild;
		}
	}
	else if (node->lchild != NULL&&node->rchild == NULL)
	{
		if (node == T)
			T = T->lchild;
		else
		{
			BSTNode*prenode = Parent(T, node->data.id);
			if (strcmp(node->data.id, prenode->data.id) > 0)
				prenode->rchild = node->lchild;
			else
				prenode->lchild = node->lchild;
		}
	}
	
	T1->lchild=Balance(T);
	return OK;
}
/******************
函数名称：InsertAVL
函数参数：AVL树的头结点，数据结构data
函数功能：插入一个数据域为data的结点
返回值：成功返回OK，失败返回ERROR
*******************/
int InsertAVL(BSTNode*T1, TElemType data)
{
	if (T1 == NULL)
	{
		printf("未初始化，");
		return ERROR;
	}
	BSTNode*T = T1->lchild;
	if (T == NULL)//插入前为空树
	{
		T = (struct BSTNode*)malloc(sizeof(struct BSTNode));
		T->BF = 0; T->data = data;
		T->lchild = NULL; T->rchild = NULL;
		T1->lchild = T;
		return OK;
	}
	BSTNode*pre = NULL, *current = T;
	while (current != NULL)//查找到所要插入的位置，并用pre保存所要插入位置的双亲结点
	{
		if (strcmp(current->data.id,data.id)==0)
			return ERROR;
		pre = current;
		current = (strcmp(data.id, pre->data.id)>0) ? pre->rchild : pre->lchild;
	}
	current = (struct BSTNode*)malloc(sizeof(struct BSTNode)); current->BF = 0; current->data = data; 
	current->lchild = NULL; current->rchild = NULL;
	if (strcmp(data.id,pre->data.id)>0)  pre->rchild = current;
	else pre->lchild = current;

	T1->lchild = Balance(T);
	if (T1->lchild != NULL)
		return OK;
	else return ERROR;
}
/******************
函数名称：Balance
函数参数：AVL树的根结点
函数功能：将插入新结点后的AVL树调整至平衡
返回值：成功返回新的根结点
*******************/
BSTNode *Balance(BSTNode *T)
{
	BSTNode *root = NULL;
	if (T == NULL)return T;
	T->lchild=Balance(T->lchild);//将T的左子树调整至AVL树 
	T->rchild=Balance(T->rchild);//将T的右子树调整至AVL树
	T->BF = Depth(T->lchild) - Depth(T->rchild);//赋值平衡因子
	if (T->BF == 0 || T->BF == -1 || T->BF == 1)
		return T;
	if (T->BF == 2)
	{
		int BF = T->lchild->BF;
		if (BF == -1)
			root = LR(T);
		else if (BF == 1)
			root = LL(T);
		else  //删除时选用
			root = LL(T);
	}
	else if (T->BF == -2)
	{
		int BF = T->rchild->BF;
		if (BF == -1)
			root = RR(T);
		else if (BF == 1)
			root = RL(T);
		else	 //删除时选用
			root = RR(T);
	}
	return root;
}
/******************
函数名称：Depth
函数参数：AVL树的根结点
函数功能：返回AVL树的深度
返回值：返回AVL树的深度
*******************/
int Depth(BSTNode *T)
{
	int deep = 0;
	if (T)
	{
		int leftdeep = Depth(T->lchild);
		int rightdeep = Depth(T->rchild);
		deep = leftdeep >= rightdeep ? leftdeep + 1 : rightdeep + 1;
	}
	return deep;
}
/******************
函数名称：Parent
函数参数：AVL树的根结点，序号id
函数功能：寻找双亲结点
返回值：如果查找到返回结点指针，否则返回NULL
*******************/
BSTNode*Parent(BSTNode *T, char id[20])
{
	if (T == NULL)return NULL;
	if ((T->lchild != NULL && strcmp(id, T->lchild->data.id) == 0) || (T->rchild != NULL && strcmp(id, T->rchild->data.id) == 0))
		return T;
	else {
		BSTNode * temp = NULL;
		if (strcmp(id, T->data.id)>0)
			temp = Parent(T->rchild, id);
		if (strcmp(id, T->data.id)<0)
			temp = Parent(T->lchild, id);
		return temp;
	}
}
/******************
函数名称：SearchAVL
函数参数：当前AVL树的根结点，所要查找的结点的名称，功能选项choice
函数功能：查找名称为name的结点或身份证号为name的结点
返回值：成功返回结点指针，失败返回NULL
*******************/
BSTNode*SearchAVL(BSTNode*T, char name[20],int choice)
{
	if (T == NULL)
		return NULL;
	if (choice == 2 && strcmp(T->data.id,name) == 0)//按照ID查找，唯一确定
		return T;
	if (choice == 1 && strcmp(T->data.name, name) == 0)//按照name查找，不唯一确定
	{
		printf("请问所要进行操作的是ID为：%s的用户吗？\n", T->data.id);
		printf("Y or N?（选择N后将继续进行查找）");
		char c; scanf("%c", &c); getchar(); int re = 0;
		while (re == 0)
		{
			switch (c)
			{
			case 'Y':case 'y':
				re = 1;return T; break;
			case 'N':case 'n':
				re = 1;break;
			default:
				re = 0;
				printf("输入错误，请重新选择Y or N?（选择N后将继续进行查找）"); scanf("%c", &c); getchar();
			}
		}
	}
	BSTNode * temp=NULL;
	temp = SearchAVL(T->rchild, name,choice);
	if (temp==NULL)
		temp = SearchAVL(T->lchild, name,choice);
	return temp;
}
/******************
函数名称：DestroyAVL
函数参数：当前AVL树的根结点
函数功能：递归销毁当前AVL树
返回值：成功返回OK，失败返回ERROR
*******************/
int DestroyAVL(BSTNode*T)
{
	if (T == NULL) {
		return OK;
	}
	DestroyAVL(T->lchild);
	DestroyAVL(T->rchild);
	free(T);	T = NULL;
	return OK;
}
/******************
函数名称：DestroyAVL1
函数参数：整个森林头指针head，遍历指针F
函数功能：销毁当前F所指向的AVL树
返回值：成功返回OK，失败返回ERROR
*******************/
int DestroyAVL1(Forest *head, Forest *F)
{
	Forest *p = head;
	Forest *q = p;
	while (p != F)
	{
		q = p;
		p = p->next;
	}
	q->next = p->next;
	if (DestroyAVL(p->HeadNode->lchild) == ERROR)//递归销毁AVL树
		return ERROR;
	free(p->HeadNode);
	p->HeadNode = NULL;
	free(p);
	F = NULL;
	return OK;
}
/******************
函数名称：InitAVL
函数参数：整个森林头指针head，遍历指针F
函数功能：初始化一颗空的AVL树
返回值：成功返回OK，失败返回ERROR
*******************/
int InitAVL(Forest *head, Forest **F)
{
	Forest *q = head;
	char name[20];
	printf("请输入该AVL树的名字（20个字符以内）："); scanf("%s", name); getchar();
	while (q->next)
	{
		q = q->next;
		if (strcmp(q->name, name) == 0)
			break;
	}
	if (strcmp(q->name, name) == 0)
	{
		printf("该名字已被使用，");
		return ERROR;
	}
	q->next = (Forest *)malloc(sizeof(Forest));
	(*F) = q->next;
	strcpy((*F)->name, name);
	(*F)->HeadNode = (BSTNode*)malloc(sizeof(BSTNode));//对当前指针F进行初始化，并令头结点的左孩子结点为AVL树的根结点，右孩子始终指向NULL
	(*F)->HeadNode->BF = 0; (*F)->HeadNode->lchild = NULL; (*F)->HeadNode->rchild = NULL;
	memset((*F)->HeadNode->data.id, '0', 20); memset((*F)->HeadNode->data.name, '0', 20);
	(*F)->HeadNode->data.hobby = NULL; (*F)->HeadNode->data.friends = NULL;
	(*F)->HeadNode->data.fan = NULL; (*F)->HeadNode->data.concern = NULL;
	(*F)->next = NULL;
	return OK;
}

/******************
函数名称：show
函数参数：遍历指针F
函数功能：显示伪菜单界面
返回值：无
*******************/
void show(Forest *F)
{
	system("cls");
	printf("\n\n");
	printf("\t\t\t\tMenu for Self-balancing Binary Search Tree\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t1. InitAVL\t\t2. DestroyAVL\n");
	printf("\t\t\t\t3. SearchAVL\t\t4. InsertAVL\n");
	printf("\t\t\t\t5. DeleteAVL\t\t6. TraverseAVL\n");

	printf("\t\t\t\t7. set_init\t\t8. set_destroy\n");
	printf("\t\t\t\t9. set_insert\t\t10. set_remove\n");
	printf("\t\t\t\t11. set_intersection\t12. set_union\n");
	printf("\t\t\t\t13. set_diffrence\t14. set_size\n");
	printf("\t\t\t\t15. set_member\t\t16. set_subset\n");
	printf("\t\t\t\t17. set_equal\t\t18. init_aggregate\n");
	printf("\t\t\t\t19. operate_aggregate\t20. search_common\n");
	printf("\t\t\t\t21. second_friends\t22. ExAVL\n");
	printf("\t\t\t\t23. SaveData\t\t24. LoadData\n");
	printf("\t\t\t\t25. Random\t\t0. Exit\n");
	if (F == NULL)
		printf("----------------------------------------------当前没有活动树-----------------------------------------------------------");
	else
		printf("----------------------------------------------当前对树 %s 进行操作---------------------------------------------", F->name);
	printf("\n请选择你的操作[0~25]:");
}