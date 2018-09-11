#include<stdio.h>
#include<stdlib.h>
#define N 5
#define M 5
float avg1[N], sum1[N];//每个同学的平均分
float avg2[M], sum2[M];//每门课程的平均分
char name[N][10];
char course[M][10];
int score[N][M];
void avg_stu(char name[N][10],int score[N][M]);
void avg_course(char course[M][10],int score[N][M]);
void num_low_avg(char name[N][10], char course[M][10], int score[N][M]);
void num(char name[N][10], char course[M][10], int score[N][M]);
int main()
{
	int i = 0, j = 0; 
	for (i = 0; i<M; i++)
		scanf("%s ", *(course + i));
	for (i = 0; i < N; i++)
	{
		scanf("%s ", *(name + i));
		for (j = 0; j < M; j++)
			scanf("%d", *(score + i) + j);
	}
	avg_stu(name, score);
	avg_course(course, score);
	num_low_avg(name, course, score);
	num(name, course, score);
	system("pause");
}
void avg_stu(char name[N][10], int score[N][M])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			sum1[i] = sum1[i]+ *(*(score + i) + j);
		}
		avg1[i] = sum1[i] / M;
	}
	for (int i = 0; i < N; i++)
	{
		printf("Average score of %s is %.2f\n",*(name + i), avg1[i]);
	}
}
void avg_course(char course[M][10], int score[N][M])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sum2[i] = sum2[i] + *(*(score + j) + i);
		}
		avg2[i] = sum2[i] / M;
	}
	for (int i = 0; i < N; i++)
	{
		printf("Average score of %s is %.2f\n", *(course + i), avg2[i]);
	}
}
void num_low_avg(char name[N][10], char course[M][10], int score[N][M])
{
	int count[M] = {0};
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (score[j][i] < avg2[i])count[i]++;
		}
	}
	for (int i = 0; i < M; i++)
		printf("Number of students lower than avg of %s is %d\n", *(course + i), count[i]);
}
void num(char name[N][10], char course[M][10], int score[N][M])
{
	int count1[M] = { 0 }, count2[M] = { 0 };
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (score[j][i] < 60)count1[i]++;
			if (score[j][i] > 90)count2[i]++;
		}
	}
	for (int i = 0; i < M; i++)
		printf("Number of students %s fail is %d\n", *(course + i), count1[i]);
	for (int i = 0; i < M; i++)
		printf("Number of students %s perfect is %d\n", *(course + i), count2[i]);
}
