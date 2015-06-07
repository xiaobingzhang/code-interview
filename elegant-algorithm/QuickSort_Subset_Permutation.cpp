// QuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int quick_sort_partition(int A[], int p, int r){
	int x = A[r];//
	int i = p - 1;//
	for (int j = p; j < r; j++){
		if (A[j] < x){
			swap(A[++i], A[j]);
		}
	}
	swap(A[++i], A[r]);
	return i;
}


void quick_sort(int A[], int p, int r){
	int q;
	if (p < r){
		q = quick_sort_partition(A, p, r);
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}


//全组合

bool isSwap(const vector<int> &v,int begin,int end){
	for (int i = begin; i < end;i++){
		if (v[i] == v[end]){
			return false;
		}
	}
	return true;
}
void allRange( vector<int> &v, int l, int len){
	if (l == len - 1){
		for (int a : v){
			cout << a << " ";
		}
		cout << endl;
	}
	else{
		for (int i = l; i < len; i++){
			if (isSwap(v,l,i)){
				swap(v[l], v[i]);
				allRange(v, l + 1, len);
				swap(v[l], v[i]);
			}
			
		}
	}
}
//子集
vector<vector<int> > subsets(vector<int> &S) {
	sort(S.begin(), S.end());
	vector<vector<int>> ret;
	int count = S.size();
	for (int i = 0; i < (1 << count); i++)
	{
		vector<int> tmp;
		for (int j = 0; j < count; j++)
		{
			if ((i >> j) & 1 == 1){
				tmp.push_back(S[j]);
			}
		}
		ret.push_back(tmp);
	}
	return ret;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> v = { 1, 2, 2 };
	allRange(v,0,3);
	//int A[10] = { 8, 7, 2, 1, 9, 0, 3, 6, 5, 4 };
	//for (size_t i = 0; i < 10; i++){
	//	std::cout << A[i] << " ";
	//}
	//cout << endl;
	//quick_sort(A, 0, 9);
	//for (size_t i = 0; i < 10; i++){
	//	std::cout << A[i] << " ";
	//}
	return 0;
}

