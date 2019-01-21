#include<iostream>
#include<cstdlib>
#include <fstream>
#include <string>
using namespace std;


const int n = 10;
const int MAX = 0x7fffffff;
double adjacency[n][n] = { 0 };
int path[n][n] = { 0 };

void FLOTD_WARSHALL(int num)
{
	int temp;
	 for(int k=0;k< num;k++)
		 for(int i=0;i< num;i++)
			 for (int j = 0; j < num; j++)
			 {
				 temp = (adjacency[i][k] == MAX || adjacency[k][j] == MAX) ? MAX : (adjacency[i][k] + adjacency[k][j]);
				 if (temp < adjacency[i][j])
				 {
					 adjacency[i][j] = temp;
					 path[i][j] = path[k][j];
				 }
			 }
}
int main()
{
	string infilename = "infile.txt";
	string outfilename = "outfile.txt";
	ifstream infile;
	infile.open(infilename, ios::in);
	if (!infile.is_open())
		cout << "Can not open " << infilename << endl;
	ofstream outfile;
	outfile.open(outfilename, ios::out);
	if (!outfile.is_open())
		cout << "Can not open " << outfilename << endl;
	int total;
	infile >> total;
	while (total)
	{
		total--;

		//初始化
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)adjacency[i][j] = 0;
				else adjacency[i][j] = MAX;
			}
		}
		//输入邻接矩阵
		int num;
		infile >> num;
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				infile >> adjacency[i][j];
			}
		}
		//初始化path
		for (int i = 0; i < num; i++)
			for (int j = 0; j < num; j++)
			{
				if (adjacency[i][j] != MAX && i != j)
					path[i][j] = i + 1;
			}

		FLOTD_WARSHALL(num);
		//输出矩阵
		cout << "D(n):" << endl;
		outfile << "D(n):" << endl;
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if (adjacency[i][j] == MAX)
				{
					outfile << "MAX" << '\t';
					cout << "MAX" << '\t';
				}
				else
				{
					outfile << adjacency[i][j] << '\t';
					cout << adjacency[i][j] << '\t';
				}

			}
			cout << endl;
			outfile << endl;
		}
		cout << "path(n):" << endl;
		outfile << "path(n):" << endl;
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if (path[i][j] == MAX)
				{
					outfile << "MAX" << '\t';
					cout << "MAX" << '\t';
				}
				else
				{
					outfile << path[i][j] << '\t';
					cout << path[i][j] << '\t';
				}
			}
			cout << endl;
			outfile << endl;
		}
		cout << "Test run out" << endl;
	}
	
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}