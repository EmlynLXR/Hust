#include<iostream>
#include<cstdlib>
#include <fstream>
#include <string>
using namespace std;
const int max = 10;
int root[max + 1][max + 1] = { 0 };
double p[max + 1] = { 0 };
double q[max + 1] = { 0 };
double e[max + 2][max + 2] = { 0 };
double w[max + 2][max + 2] = { 0 };
void CONSTRUCT_OPTIMAL_BST(int i, int j, int croot);
void OPTIMAL_BST(double p[max + 1], double q[max + 1]);
int n;
int main()
{
	string infilename = "infile.txt";
	string outfilename = "outfile.txt";
	ifstream infile;
	infile.open(infilename, ios::in);
	if (!infile.is_open())
		cout << "Can not open" << infilename << endl;
	ofstream outfile;
	outfile.open(outfilename, ios::out);
	if (!outfile.is_open())
		cout << "Can not open" << outfilename << endl;
	int total;
	infile >> total;
	while (total)
	{
		total--;

		int n;
		infile >> n;
		::n = n;
		for (int i = 0; i < n + 1; i++)
			infile >> p[i];
		for (int i = 0; i < n + 1; i++)
			infile >> q[i];

		OPTIMAL_BST(p, q);
		cout << "e:" << endl;
		for (int i = 1; i < n + 2; i++)
		{
			for (int j = 0; j < n +1 ; j++)
			{
				outfile << e[i][j] << '\t';
				cout << e[i][j] << '\t';
			}
			outfile << endl;
			cout << endl;
		}
		cout << endl;
		cout << "w:" << endl;
		for (int i = 1; i < n + 2; i++)
		{
			for (int j = 0; j < n + 1; j++)
			{
				outfile << w[i][j] << '\t';
				cout << w[i][j] << '\t';
			}
			outfile << endl;
			cout << endl;
		}
		cout << endl;
		cout << "root:" << endl;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				outfile << root[i][j] << '\t';
				cout << root[i][j] << '\t';
			}
			outfile << endl;
			cout << endl;
		}
		cout << endl;
		CONSTRUCT_OPTIMAL_BST(1, n, 0);

		cout << "Test run out" << endl;
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}
void OPTIMAL_BST(double p[max + 1], double q[max + 1])
{
	for (int i = 1; i <= n + 1; i++)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int l = 1; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			e[i][j] = 999;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= j; r++)
			{
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}
void CONSTRUCT_OPTIMAL_BST(int i, int j,int croot)
{
	int node = root[i][j];//子树根节点
	if (node == root[1][n])//是整个树的根节点
	{
		cout << "k" << node << "是根" << endl;
		CONSTRUCT_OPTIMAL_BST(i, node - 1, node);
		CONSTRUCT_OPTIMAL_BST(node + 1, j, node);
		return;
	}
	if (j < i-1)//不存在
		return;
	else if (j == i-1)//虚拟节点
	{
		if (j < croot)cout << "d" << j << "是" << "k" << croot << "的左孩子" << endl;
		else cout << "d" << j << "是" << "k" << croot << "的右孩子" << endl;
		return;
	}
	else//真实节点
	{
		if (node < croot)cout << "k" << j << "是" << "k" << croot << "的左孩子" << endl;
		else cout << "k" << j << "是" << "k" << croot << "的右孩子" << endl;
	}
	CONSTRUCT_OPTIMAL_BST(i, node - 1, node);
	CONSTRUCT_OPTIMAL_BST(node + 1, j, node);
}