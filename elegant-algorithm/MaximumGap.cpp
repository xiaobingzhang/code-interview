// MaximumGap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include  <vector>
using namespace std;
/*
suppose there are N elements and they are range from A to B
so the maximum gap will be no smaller than ceiling[(B-A)/(N-1)]
let the length of a bucket to be len = ceiling[(B-A)/(N-1)], then we will have
at most num = (B-A)/len + 1 of bucket

for any number K in the array, we can easily find out which bucket
it belongs by calculating loc = (K -A)/len and therefore maintain the max and min elements
in each bucket

since the max dif between elements in the same buckets will be at most len - 1;
so the final answer will not be taken from two elements in the same buckets;

for each no-empty buckets p,find the next non-empty buckets q,then q.min - p.max could be the potential answer to the question.
Return the maximum of all those values;
*/


int maximumGap(vector<int> &num)
{
	if (num.size()  < 2) return 0;
	int A = num[0];
	int B = num[0];
	for (vector<int>::iterator iter = num.begin(); iter != num.end(); iter++)
	{
		A = min(A, *iter);
		B = max(B, *iter);
	}
	int len = ceil((double)(B - A) / (num.size() - 1));
	vector< vector<int> > buckets((B - A) / len + 1);
	for (vector<int>::iterator iter = num.begin(); iter != num.end(); iter++)
	{
		int x = *iter;
		int  i = (x - A) / len;
		if (buckets[i].empty())
		{
			buckets[i].reserve(2);
			buckets[i].push_back(x);
			buckets[i].push_back(x);
		}
		else
		{
			if (x < buckets[i][0])buckets[i][0] = x;
			if (x > buckets[i][1])buckets[i][1] = x;
		}
	}
	int gap = 0;
	int prev = 0;
	for (int i = 1; i < buckets.size(); i++)
	{
		if (buckets[i].empty())continue;
		gap = max(gap, buckets[i][0] - buckets[prev][1]);
		prev = i;
	}
	return gap;
}
int _tmain(int argc, _TCHAR* argv[])
{
	vector<int>  num;
	num.push_back(1);
	num.push_back(1);
	num.push_back(1);
	num.push_back(1);
	num.push_back(1);
	num.push_back(5);
	num.push_back(5);
	num.push_back(5);
	num.push_back(5);
	num.push_back(5);
	cout << maximumGap(num);
	return 0;
}

