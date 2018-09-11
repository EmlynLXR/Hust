#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

bool aush = 0;
bool falg = 0;

#define N 4
//#define N 6000000
typedef struct INFO
{
	char name[10];
	int num[5];
}INFO;
int pm[N] = {0};
struct INFO shop[2 * N];
//之前对结构数组的声明
//struct INFO shop[2 * N] = { {"PEN",35,56,70,25,0},{"BOOK",12,30,25,5,0},{"BAG",30,50,30,0,0},{"TempValue",15,20,30,2,0},
//{"BOOK",12,28,20,15,0},{"PEN",35,50,30,24,0},{"BAG",30,50,30,0,0},{"TempValue",15,20,30,2,0}};
char s1[10] = "SHOP1",s2[10] = "SHOP2";
char BNAME[10] = "LXR", BPASS[10] = "2333";

void menu_0();
void menu_1();
int search();
int modify();
void apr_c();
void outputall();
int str_num(char *);
extern "C" void apr(struct INFO*shop,int num,int n);
extern "C" void rank(struct INFO*shop, int*pm,int num,int n);
int main(int argc, char *argv[])
{
	shop[0] = { "PEN",35,56,70,25,0 };
	shop[1] = { "BOOK", 12, 30, 25, 5, 0 };
	shop[2] = { "BAG", 30, 50, 30, 0, 0 };
	shop[N + 0] = { "BOOK",12,28,20,15,0 };
	shop[N + 1] = { "PEN", 35, 50, 30, 24, 0 };
	shop[N + 2] = { "BAG", 30, 50, 30, 0, 0 };
	for(int i=3;i<N;i++)
		shop[i] = { "TempValue", 15, 20, 30, 2, 0 };
	for (int i = N+3; i<2*N; i++)
		shop[i] = { "TempValue", 15, 20, 30, 2, 0 };


	char name[10], pass[10];
	while (aush != 1)
	{
		printf("Input the name （if enter q,exit!）："); fgets(name, 10, stdin);
		if (name[0] == 'q'&&name[1] == '\n')
		{
			printf("Welcome to use next time！"); getchar();
			return 0;
		}
		if (name[0] == '\n')
		{
			aush = 1;
			break;
		}
		printf("Input the password：");  fgets(pass, 10, stdin);
		for (int i = 0; i < 10; i++)
		{
			if (name[i] == '\n')
			{
				for (int j = i; j < 10; j++)
					name[j] = '\0';
				break;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (pass[i] == '\n')
			{
				for (int j = i; j < 10; j++)
					pass[j] = '\0';
				break;
			}
		}
		if (strcmp(BNAME, name) == 0 && strcmp(BPASS, pass) == 0)
		{
			aush = 1;
			break;
		}
		printf("Login Fail！\n");
	}

	if (name[0] == '\n')
	{
		aush = 0;
		menu_0();
	}
	else
	{
		printf("Login Success！\n");
		menu_1();
	}	
	return(0);
}
void menu_0()
{
	int op = 1;
	while (op != 6)
	{
		printf("\n----------------------------\n");
		printf("1=Search information\n");
		printf("6=Exit\n");
		printf("----------------------------\n");
		scanf("%d", &op); getchar();
		switch (op)
		{
		case 1:
			search();
			break;
		case 6:
			printf("Success exit！\n");
			getchar();break;
		case 2:case 3:case 4:case 5:
			printf("You have no access！\n");
			break;
		default:
			printf("Error input！\n");
		}
	}
}
void menu_1()
{
	clock_t start, end;
	int op = 0;
	int flag = 0;
	while (op != 6)
	{
		printf("\n----------------------------\n");
		printf("1=Search information\n");
		printf("2=Modify product information\n");
		printf("3=Calculate the APR\n");
		printf("4=Calculate the ranking\n");
		printf("5=Output all information\n");
		printf("6=Exit\n");
		printf("----------------------------\n");
		scanf("%d", &op); getchar();
		switch (op)
		{
		case 1:	
			while(search());
			break;
		case 6:
			printf("Success exit！\n");
			getchar(); break;
		case 2:
			while(modify());
			break;
		case 3:
			//用于检验C语言程序和汇编语言的效率
			/*start = clock();
			apr_c();
			end = clock();
			printf("The time was: %lfms\n", difftime(end, start));
			start = clock();
			apr(shop, sizeof(INFO), N);
			end = clock();
			printf("The time was: %lfms\n", difftime(end, start));	
			*/
			apr(shop, sizeof(INFO), N);
			break;
		case 4:
			rank(shop, pm,sizeof(INFO),N);
			break;
		case 5:
			outputall();
			break;
		default:
			printf("Error input！\n");
		}
	}
}
void apr_c()
{
	int a, b;
	int i, j;
	for (i = 0; i < 2*N; i++)
	{
		a = shop[i].num[1] * shop[i].num[3];
		b = shop[i].num[0] * shop[i].num[2];
		a = a - b;
		a = a* 100;
		if(b!=0)
			a = a / b;
		shop[i].num[4] = a;
	}
	for (i = 0; i < N; i++)
	{
		for (j = N; j < 2 * N; j++)
		{
			if (strcmp(shop[i].name, shop[j].name) == 0)
				break;
		}
		a = shop[i].num[4];
		b = shop[j].num[4];
		a = (a + b) / 2;
		shop[i].num[4] = a;
		shop[j].num[4] = a;
	}
}
int search()
{
	int f = 0;
	int i;
	char name[10];
	printf("Input the name of commodity："); fgets(name, 10, stdin);
	if (name[0] == '\n')return 0;
	for (i = 0; i < 10; i++)
	{
		if (name[i] == '\n')
		{
			for (int j = i; j < 10; j++)
				name[j] = '\0';
			break;
		}
	}
	for (i = 0; i < 2 * N; i++)
	{
		if (strcmp(name, shop[i].name) == 0)
		{
			if (f == 0)
			{
				printf("Successful Search！\n");
				printf("%s：\n",s1);
				f = 1;
			}
			else
			{
				printf("%s：\n",s2);
				f = 2;
			}
			printf("%s：\n\t", shop[i].name);
			for (int j = 0; j < 5; j++)
				printf("%d\t", shop[i].num[j]);
			printf("\n");
			if (f == 2)break;
		}
	}
	if (i == 2 * N)
	{
		printf("Unsuccessful Search！\n");
		return 1;
	}
	return 0;
}
int str_num(char *str)
{
	int a = 0,i;
	if (str[0] == '\n')return -2;
	for (i = 0; str[i] != '\n'; i++)
	{
		if (str[i] > '9' || str[i] < '0')return -1;
		a =10*a + str[i]-'0';
	}
	return a;
}
int modify()
{
	int f = 0;
	int i;
	char input[5];
	char shop_name[10];
	char name[10];
	
	printf("Input the name of shop："); fgets(shop_name, 10, stdin);
	if (shop_name[0] == '\n')return 0;
	for (i = 0; i < 10; i++)
	{
		if (shop_name[i] == '\n')
		{
			for (int j = i; j < 10; j++)
				shop_name[j] = '\0';
			break;
		}
	}
	if (strcmp(shop_name, s1) == 0)
		f = 1;
	else if (strcmp(shop_name, s2) == 0)
		f = 2;
	else
	{
		printf("Unsuccessful Search！\n");
		return 1;
	}

	printf("Input the name of commodity："); fgets(name, 10, stdin);
	for (i = 0; i < 10; i++)
	{
		if (name[i] == '\n')
		{
			for (int j = i; j < 10; j++)
				name[j] = '\0';
			break;
		}
	}

	for (i = (f - 1)*N; i < f*N; i++)
	{
		if (strcmp(name, shop[i].name) == 0)
		{
			printf("Successful Search！\n");
			if (f == 1)
				printf("%s：",s1);
			else 
				printf("%s：",s2);
			printf("%s\n", shop[i].name);

			while (1)
			{
				printf("sale price=%d/sale price=", shop[i].num[0]); fgets(input, 10, stdin);
				f = str_num(input);
				if (f == -2)break;
				if (f != -1)
				{
					shop[i].num[0] = f;
					break;
				}
			}
			while (1)
			{
				printf("stock=%d/stock=", shop[i].num[1]); fgets(input, 10, stdin);
				f = str_num(input);
				if (f == -2)break;
				if (f != -1)
				{
					shop[i].num[1] = f;
					break;
				}
			}
			while (1)
			{
				printf("sold=%d/sold=", shop[i].num[2]); fgets(input, 10, stdin);
				f = str_num(input);
				if (f == -2)break;
				if (f != -1)
				{
					shop[i].num[2] = f;
					break;
				}
			}
			printf("\n");
			break;
		}
	}
	if (i == f*N)
	{
		printf("Unsuccessful Search！\n");
		return 1;
	}
	return 0;
}
void outputall()
{
	printf("%s:stock price,sale price,stockr,sold,profit margins\n",s1);
	for (int i = 0; i < 2*N; i++)
	{
		if (i == N )printf("\n%s:stock price,sale price,stockr,sold,profit margins/profit rank\n",s2);
		printf("%s：\n\t",shop[i].name);
		for (int j = 0; j < 5; j++)
			printf("%d\t", shop[i].num[j]);
		printf("\n");
	}
}  