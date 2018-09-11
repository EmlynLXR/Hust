#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void sort(int t[], char s[][100], int n);
int binarySearch(int a[], int n, int key);
int main()
{
	char s[100][100];
	int t[100];
	int n, i = 0, j = 0; scanf_s("%d", &n);
	getchar();
	char c;
	for (; i < n; i++)
	{
		j = 0;
		while ((c = getchar()) != ' ')
			s[i][j++] = c;
		s[i][j] = '\0';
		scanf_s("%d", &t[i]);
		getchar();
	}
	s[i][j] = '\0';
	sort(t, s, n);
	for (int k = 0; k < n; k++)
		printf("%-20s %d\n", s[k], t[k]);
	printf("\n");
	int N, key[100]; scanf_s("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf_s("%d", &key[i]);
		getchar();
	}
	for (i = 0; i < N; i++)
	{
		if ((binarySearch(t, n, key[i])) == (-1))printf("Not found!\n");
		else printf("%-20s %d\n", s[binarySearch(t, n, key[i])], key[i]);
	}
	system("pause");
	return 0;
}
int binarySearch(int t[], int N, int key)
{
	int low = 0;
	int high = N - 1;
	int mid;
	int midVal;
	while (low <= high)
	{
		mid = (low + high) / 2;
		midVal = t[mid];
		if (midVal<key)
			high = mid - 1;
		else if (midVal>key)
			low = mid + 1;
		else return mid;
	}
	return -1;
}
void sort(int t[], char s[][100], int n)
{
	int i, j, k, temp1; char temp2[100];
	for (i = 0; i<n; i++)
		for (j = 0; j<n - i - 1; j++)
			if (t[j] < t[j + 1])
			{
				temp1 = t[j];
				t[j] = t[j + 1];
				t[j + 1] = temp1;
				strcpy_s(temp2, s[j]);
				strcpy_s(s[j], s[j + 1]);
				strcpy_s(s[j + 1], temp2);
			}
}
