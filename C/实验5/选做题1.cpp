#include<stdio.h>
#include<stdlib.h>
void strnins(char[], char[], int);
int main()
{
	int n,i=0; 
	//char *s1 = "hustoadha", *s2 = "nasodas";未给指针分配内存
	//char s1[] = "hustoadha", s2[] = "nasodas";
	char c,s1[100], s2[100];
	printf("输入字符串s1:");
	while ((c=getchar()) != '\n')s1[i++]=c;
	s1[i] = '\0';
	i = 0;
	printf("输入字符串s2:");
	while ((c = getchar()) != '\n')s2[i++]=c;
	s2[i] = '\0';
	printf("输入n:");
	scanf_s("%d", &n);
	strnins(s1, s2, n);
	system("pause");
}
void strnins(char s[], char t[], int n)
{
	int i = 0, j = 0, k;
	while (s[i] != '\0')i++;
	while (t[j] != '\0')j++;
	if (i<n)
		printf("n is too big!!!\n");
	else
	{
		for (i = n - 1, k = 0; i < j + n - 1 ; i++, k++)s[i] = t[k];
		s[i] = '\0';
		printf("结果为：");
		printf("%s\n", s);
	}
}