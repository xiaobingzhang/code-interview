#include "stdafx.h"
#include <vector>
#include<string>
#include <iostream>
using namespace std;

vector<int> compute_prefix_function(string P){
	int m = P.size();
	vector<int> next(m);
	next[0] = -1;
	int k = -1;
	for (int i = 1; i < m; i++){
		while (k > -1 && P[k + 1] != P[i])
		{
			k = next[k];
		}
		if (P[k + 1] == P[i]){
			k++;
		}
		next[i] = k;
	}
	return next;
}


void kmp_match(string T, string P, int &count){
	int m = P.size();
	int n = T.size();
	vector<int> next;
	next = compute_prefix_function(P);
	int k = -1;
	for (int i = 0; i < n; i++){
		while (k > -1 && P[k + 1] != T[i])
		{
			k = next[k];
		}
		if (P[k + 1] == T[i]){
			k++;
		}
		if (k == m - 1){
			count++;
			k = next[k];
		}
	}
}
int main()
{

	int count;
	cin >> count;
	while (count--){
		int ret = 0;
		string T;
		string P;
		cin >> P >> T;
		kmp_match(T, P, ret);
		cout << ret << endl;
	}

	cout << endl;
	return 0;
}

