#include<iostream>
#include<string>
#include <fstream>
#include <string>
using namespace std;
const int max=20;
string add_zero(string x);
string delete_zero(string x);
string sub(string x, string y);
string add(string x, string y);
string mul(string x, string y);

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
	int n;
	infile >> n;
	while (n)
	{
		n--;
		int op;
		string x, y;
		string result;
		infile >> x >> y >> op;
		switch (op)
		{
		case 1:
			result = add(x, y);
			cout << result << endl;
			outfile << result << endl;
			break;
		case 2:
			result = sub(x, y);
			cout << result << endl;
			outfile << result << endl;
			break;
		case 3:
			result = mul(x, y);
			cout << result << endl;
			outfile << result << endl;
			break;
		}
	}
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}
string add_zero(string x)
{
	string result = "";
	if (x[0] == '-')
		result = x.substr(1, x.size());
	else result = x;
	int i = 0;
	for (i = 0; i < result.size(); i++)
	{
		if (result[i] != '0')
			break;
	}
	result = result.substr(i, result.size());
	if ((result.size()) % 2 != 0 && result.size() != 1)
		result = "0" + result;
	result = x[0] == '-' ? '-' + result : result;
	return result;
}
string delete_zero(string x)
{
	string result = "";
	if (x[0] == '-')
		result = x.substr(1, x.size());
	else result = x;
	int i = 0;
	for (i = 0; i < result.size(); i++)
	{
		if (result[i] != '0')
			break;
	}
	result = result.substr(i, result.size());
	result = x[0] == '-' ? '-' + result : result;
	return result;
}
string sub(string x, string y)
{
	bool sign = 0;
	if (x[0] == '-'&&y[0] == '-')
	{
		x = x.substr(1, x.size());
		y = y.substr(1, y.size());
		return sub(y, x);
	}
	else if (x[0] == '-'&&y[0] != '-')
	{
		sign = 1;
		x = x.substr(1, x.size());
		x = delete_zero(x);
		y = delete_zero(y);  //去0
		return "-" + add(x, y);
	}
	else if (x[0] != '-'&&y[0] == '-')
	{
		y = y.substr(1, y.size());
		return add(x, y);
	}
	else
	{
		x = delete_zero(x);
		y = delete_zero(y);  //去0
		if (x.size() < y.size() ||(x.size() == y.size() && x < y))
		{
			sign = 1;
			swap(x, y);
		}
	}

	x = add_zero(x);
	y = add_zero(y);  //补0
	if (x == "" && y[0] == '-') return (y.substr(1, y.size()));
	else if (x == ""&&y == "") return"0";
	else if (x == "")return sign ? '-' + y : y;
	else if (y == "")return sign ? '-' + x : x;

	string c(x.size() - y.size(), '0');
	y = c + y;	  //补齐

	string sum;
	int a = 0;	//来自低位的借位
	for (int i = x.size() - 1; i >= 0; i--)
	{
		x[i] = a ? x[i] - 1 : x[i];
		a = x[i] >= y[i] ? 0 : 1;
		int s = (x[i] - '0') - (y[i] - '0');
		if (s < 0)
			sum.push_back((s + 10) + '0');
		else
			sum.push_back(s + '0');
	}
	if (sign != 0)
		sum.push_back('-');

	string result(sum.rbegin(), sum.rend());
	if (result == "" || (result.size() == 1 && sign != 0)) return "0";
	result = delete_zero(result);
	return result;
}
string add(string x, string y)
{
	if (x == "0"&&y == "0") return"0";
	else if (x == "0")return y;
	else if (y == "0")return x;

	bool sign = 0;
	if (x[0] == '-'&&y[0] == '-')
	{
		sign = 1;
		x = x.substr(1, x.size());
		y = y.substr(1, y.size());
		if (x.size() < y.size()) swap(x, y);
	}
	else if (x[0] == '-')
		return sub(y, x.substr(1, x.size()));
	else if (y[0] == '-')
		return sub(x, y.substr(1, y.size()));

	if (x.size() <= y.size()) swap(x, y);
	x = add_zero(x);
	y = add_zero(y);
	string c(x.size() - y.size(), '0');
	y = c + y;

	string sum;
	int a = 0;	//来自底位的进位
	for (int i = x.size() - 1; i >= 0; i--)
	{
		int s = (x[i] - '0') + (y[i] - '0') + a;
		if (s > 9)
		{
			sum.push_back((s - 10) + '0');
			a = 1;
		}
		else {
			sum.push_back(s + '0');
			a = 0;
		}
	}
	if (a != 0)
		sum.push_back(a + '0');

	string result(sum.rbegin(), sum.rend());
	if (x[0] == '-'&&y[0] == '-')
		result = "-" + result;
	result = delete_zero(result);
	return result;
}
string mul(string x, string y)
{
	if (x == "0" || y == "0")return "0";
	bool sign = (x[0] == '-') ^ (y[0] == '-');
	if (x[0] == '-') x = x.substr(1, x.length());
	if (y[0] == '-') y = y.substr(1, y.length());

	x = delete_zero(x);
	y = delete_zero(y);
	if (x.size() < y.size()) swap(x, y);
	x = add_zero(x);
	y = add_zero(y);

	string c(x.size() - y.size(), '0');
	y = c + y;

	string result = "";

	int m = x.size();
	int m2 = m / 2;
	if (m == 0)return "";
	else if (m == 1)
	{
		int r = (x[0] - '0')*(y[0] - '0');
		string str1 = to_string(r);
		result += str1;
		if (sign == 1)
			result = "-" + result;
		return result;
	}
	string A, B, C, D;
	if (2 * m2 == m)
	{
		A = x.substr(0, m2);
		B = x.substr(m2, m - m2);
		C = y.substr(0, m2);
		D = y.substr(m2, m - m2);
	}
	else
	{
		A = x.substr(0, m2 + 1);
		B = x.substr(m2 + 1, m - m2);
		C = y.substr(0, m2 + 1);
		D = y.substr(m2 + 1, m - m2);
	}

	string AC = mul(A, C);
	string BD = mul(B, D);
	string AB = sub(A, B);
	string DC = sub(D, C);
	string M = mul(AB, DC);
	M = add(M, AC);
	M = add(M, BD);
	string W0 = (AC == "0") ? AC : AC + string(m, '0');
	string W1 = (M == "0") ? M : M + string(m2, '0');
	result = add(W0, W1);
	result = add(result, BD);
	if (sign == 1)
		result = "-" + result;
	result = delete_zero(result);
	return result;
}
