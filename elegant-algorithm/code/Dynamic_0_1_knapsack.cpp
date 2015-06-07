// Dynamic_0_1_knapsack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;
int knapsack0_1(const vector<int> & v, const vector<int> & w, int W){
	int len = v.size();
	vector<vector<int> > dp(len + 1, vector<int>(W + 1, 0));
	for (int i = 1; i <= len; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			if (w[i - 1] <= j){
				if (v[i - 1] + dp[i - 1][j - w[i - 1]] > dp[i - 1][j]){
					dp[i][j] = v[i - 1] + dp[i - 1][j - w[i - 1]];
				}else{
					dp[i][j] = dp[i - 1][j];
				}
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	for each (vector<int> ret in dp)
	{
		for each (int var in ret){
			cout << var << " ";
		}
		cout << endl;
	}
	/////////////print ret/////////////////////
	vector<int> ret;
	int j = W;
	for (int i = len; i > 0; i--)
	{
		if (dp[i][j] > dp[i - 1][j])
		{
			ret.push_back(i - 1);
			j = j - w[i - 1];
		}
	}
	for (int i = ret.size() - 1; i >= 0; i--)
	{
		cout << ret[i] << "  ";
	}
	/////////////////////////////////////
	cout << endl;
	return dp[len][W];
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int>  v;
	vector<int>  w;
	/*
	v.push_back(60);
	w.push_back(10);
	v.push_back(100);
	w.push_back(20);
	v.push_back(120);
	w.push_back(30);
	*/
	v.push_back(2);
	w.push_back(1);
	v.push_back(1);
	w.push_back(4);
	v.push_back(4);
	w.push_back(2);
	v.push_back(3);
	w.push_back(3);
	int W = 8;
	int max = knapsack0_1(v, w, W);
	cout << max << endl;
	return 0;
}

