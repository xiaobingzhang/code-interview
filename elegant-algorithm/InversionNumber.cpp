// InversionNumber.cpp : Defines the entry point for the console application.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
using namespace std;


#define UINT_MAX	(~0U)//4294967295
using u_int = unsigned int;

void merger(vector<u_int>& A, int p, int q, int r, long long & count){
	int n1 = q - p + 1;
	int n2 = r - q;
	vector<u_int> L(n1 + 1);
	vector<u_int> R(n2 + 1);

	for (size_t i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}
	for (size_t i = 0; i < n2; i++){
		R[i] = A[q + 1 + i];
	}

	L[n1] = UINT_MAX;
	R[n2] = UINT_MAX;
	u_int i = 0, j = 0;
	for (int k = p; k <= r; k++){
		if (L[i] <= R[j]){
			A[k] = L[i];
			i++;
		}
		else{
			A[k] = R[j];
			j++;
			count += (n1 - i);
		}
	}
}

long long  merge_sort(vector<u_int>& A, int p, int r){
	long long  count = 0;
	if (p < r){
		int q = (r - p) / 2 + p;
		count += merge_sort(A, p, q);
		count += merge_sort(A, q + 1, r);
		merger(A, p, q, r, count);
	}
	return count;
}
int main()
{
	vector<u_int> A;
	int n;
	cin >> n;
	int t = n;
	while (t--)
	{
		u_int temp;
		cin >> temp;
		A.push_back(temp);
	}
	long long cnt = merge_sort(A, 0, n - 1);

	cout << cnt << endl;

	return 0;
}




