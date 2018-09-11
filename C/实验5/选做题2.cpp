/*#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define n 8
int queen[n][n];
int board[n][n];
void putqueen(int);
int check(int board[n][n], int);
void show();
int main()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			board[i][j] = 0;
	putqueen(-1);
	system("pause");
}
void putqueen(int i)
{
	i++;
	if (i == n-1) show();
	int j = 0;
	for (j = 0; j < n; j++)
	{
		board[i][j] = 1;
		if (check(board, i) == 0) break;
	}
	if (check(board, i) == 1)putqueen(i);

}
int check(int board[n][n], int z)
{
	int i = 0, j = 0, k = 0, m = 0;
	for (i = 0; i < z; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (m = i+1; m < z; m++)
			{
				for (k = 0; k < n; k++)
				{
					if (board[i][j]==1&&board[m][z]==1&&(i==m||j==z))return 0;
					if (board[i][j] == 1 && board[m][z] == 1 && (abs(i-m)==abs(j-z)))return 0;
				}
			}
		}
	}
	return 1;
}
void show()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%6d", board[i][j]);
		printf("\n");
	}
	printf("\n");
}*/
#include <stdio.h>
#include<stdlib.h>
int c[20], n = 8, cnt = 0;
void print() {
	for (int i = 0; i<n; ++i) {
		for (int j = 0; j<n; ++j) {
			if (j == c[i]) printf( "1 ");
			else printf( "0 ");
		}
		printf("\n");
	}
	printf("\n");
}
void search(int r) {
	if (r == n) {
		print();
		cnt++;
		return;
	}
	for (int i = 0; i<n; i++) 
	{
		c[r] = i;
		int ok = 1;
		for (int j = 0; j<r; j++)
			if (c[r] == c[j] || r - j == c[r] - c[j] || r - j == c[j] - c[r]) 
			{
				ok = 0;
				break;
			}
        if (ok) search(r + 1);
	}
}
int main() {
	search(0);
	printf("%d\n",cnt);
	system("pause");
	return 0;
}