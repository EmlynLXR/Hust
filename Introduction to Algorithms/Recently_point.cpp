#include <iostream>
#include <fstream>
#include <string>
#include<math.h>
#include<algorithm>
#include<stdlib.h>
#include <vector>
using namespace std;

const int PointNum = 100;
const double MAX = 0x7fffffff;

struct POINT {
	double x, y;
};
struct ClosePoint {
	struct POINT A;
	struct POINT B;
	double distance;
};
vector<struct ClosePoint> close;
double point_distence(POINT x, POINT y)
{
	return sqrt(pow((x.x - y.x), 2) + pow((x.y - y.y), 2));
}
bool myfunction(POINT x, POINT y)
{
	return x.y < y.y;
}	 //按y升序排序
int AlreadyIn(POINT x, POINT y)
{
	if (close.empty())
		return 0;
	for (auto iter = close.cbegin(); iter != close.cend(); iter++)
	{
		if(((*iter).A.x==x.x&&(*iter).A.y==x.y)&& (((*iter).B.x == y.x && (*iter).B.y == y.y)))
			return 1;
		if (((*iter).B.x == x.x && (*iter).B.y == x.y) && (((*iter).A.x == y.x && (*iter).A.y == y.y)))
			return 1;
	}
	return 0;

}
double closestPoints(POINT point[], int left, int right);
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

		int n;
		infile >> n;
		POINT point[PointNum] = { 0,0 };
		int x, y;
		for (int i = 0; i < n; i++)
		{
			infile >> x >> y;
			point[i].x = x;
			point[i].y = y;
		}
		sort(point, point + n, myfunction);
		cout << "输入的点对根据y坐标升序排序后的结果如下：" << endl;
		for (int i = 0; i < n; i++)
			cout << '(' << point[i].x << ',' << point[i].y << ") ";
			
		cout << endl;
		double distance = closestPoints(point, 0, n - 1);

		cout << "最小距离点对为：" << endl;
		for (auto iter = close.cbegin(); iter != close.cend(); iter++)
		{
			cout << "(" << (*iter).A.x << "," << (*iter).A.y << "),(" << (*iter).B.x << "," << (*iter).B.y << ")" << endl;
			outfile << (*iter).A.x << ' ' << (*iter).A.y << ' ' << (*iter).B.x << ' ' << (*iter).B.y << ' ' << endl;
		}
		outfile << endl;

		if (distance == MAX)
			cout << "最小距离为：MAX" << endl;
		else
			cout << "最小距离为：" << distance << endl;      //输出点对的最小问题 
		cout << endl;
		close.clear();

	}
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}
double closestPoints(POINT point[],int left,int right)
{
	double min = MAX;
	double distance = 0;
	if (right - left < 1)	  //一个点则返回MAX
	{
		return min;
	}
	else if(right - left == 1)	  //一对点则直接求解
	{
		distance = point_distence(point[left], point[right]);
		if (distance < min)
		{
			min = distance;
			//更新closepoint
			if (AlreadyIn(point[left], point[right]) == 0)
			{
				ClosePoint closepoint = { point[left],point[right] ,min };
				if (close.empty())
					close.push_back(closepoint);
				else
				{
					if (min == close[0].distance)
						close.push_back(closepoint);
					else if (min < close[0].distance)
					{
						close.clear();
						close.push_back(closepoint);
					}
				}
			}
		}
		return min;
	}
	else
	{
		int mid = (right + left) / 2;
		double dleft = closestPoints(point, left, mid);	//递归判断左半部分
		double dright = closestPoints(point, mid + 1, right);	 //递归判断右半部分

		//在跨越分割线的点对找寻最小点对
		for(int i=mid; i>=0 ;i--)
			for (int j = mid + 1; j <= right ; j++)
			{
				if ((point[j].y - point[i].y) >= min)
					break;
				else
				{
					double dis = point_distence(point[i], point[j]);
					//更新closepoint
					ClosePoint closepoint = { point[i], point[j] ,dis };
					if (close.empty())
						close.push_back(closepoint);
					else
					{
						if (dis == close[0].distance&&AlreadyIn(point[i], point[j])==0)
							close.push_back(closepoint);
						else if (dis < close[0].distance)
						{
							close.clear();
							close.push_back(closepoint);
						}
					}
				}
			}
		return close[0].distance;
	}
}