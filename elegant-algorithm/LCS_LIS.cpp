// LCS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int lcs(const string &x, const string & y){
	unsigned int m = x.size();
	unsigned int n = y.size();

	vector<vector<int> >  c(m + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			if (x[i - 1] == y[j - 1]){
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] > c[i][j - 1]){
				c[i][j] = c[i - 1][j];
			}
			else{
				c[i][j] = c[i][j - 1];
			}
		}
	}

	/*for (int i = 0; i <= m; i++){
		for (int j = 0; j <= n; j++){
		cout << c[i][j] << "->";
		}
		cout << endl;
		}*/
	return c[m][n];
}

void printLis(const vector<int> &num, const vector<int> &dp, int lis, int lastindex){
	int temp = lis;
	for (; lastindex >= 0; lastindex--){
		if (dp[lastindex] == temp){
			cout << num[lastindex] << "-->";
			temp--;
		}
	}
	cout << endl;
}

int lis(const vector<int> num){
	unsigned int len = num.size();

	vector<int> dp(len, 1);

	int lis = 0;
	///////////////////////
	int lastindex = 0;
	///////////////////////

	for (int i = 0; i < len; i++){
		for (int j = 0; j < i; j++){
			if (num[i] > num[j] && dp[i] < dp[j] + 1){
				dp[i] = dp[j] + 1;
			}
		}
		if (dp[i] > lis){
			////////////////////////////////
			lastindex = i;
			////////////////////////////////
			lis = dp[i];
		}
	}
	printLis(num, dp, lis, lastindex);
	return lis;

}
//¶þ·Ö²éÕÒ

int binarysearch(const vector<int> &num, int key){
	int  l = 0, r = num.size() - 1;
	int  mid;
	while (l <= r)
	{
		mid = (r - l) / 2 + l;
		if (num[mid] > key){
			r = mid - 1;
		}
		else if (num[mid] < key)
		{
			l = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return l;
}

//
int _Best_LIS(const vector<int> &num){
	int len = 1;
	vector<int> LIS;
	LIS.push_back(num[0]);
	int pos = 0;
	for (int i = 1; i < num.size(); i++){
		if (num[i] > LIS[len - 1]){
			LIS.push_back(num[i]);
			++len;
		}
		else
		{
			pos = binarysearch(LIS, num[i]);
			LIS[pos] = num[i];
		}
	}
	return len;
}
int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> num;
	num.push_back(10);
	num.push_back(22);
	num.push_back(9);
	num.push_back(33);
	num.push_back(21);
	num.push_back(50);
	num.push_back(31);
	num.push_back(60);
	num.push_back(80);
	int lislen = lis(num);
	int lislen2 = _Best_LIS(num);

	cout << "longest increase sequence length is " << lislen << endl;
	cout << "longest increase sequence length is " << lislen2 << endl;
	string a = "ABCBDAB";
	string b = "BDCABA";
	int s = lcs(a, b);
	cout << s << endl;
	cout << "ssssssss" << endl;
	return 0;
}

