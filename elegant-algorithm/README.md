# Elegant-algorithm

##KMP
```cpp
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

```

##Quick Sort

```cpp
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

```
##Permutation
```cpp
bool isSwap(const vector<int> &v,int begin,int end){
	for (int i = begin; i < end;i++){
		if (v[i] == v[end]){
			return false;
		}
	}
	return true;
}
void allPermutation( vector<int> &v, int l, int len){
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
				allPermutation(v, l + 1, len);
				swap(v[l], v[i]);
			}
			
		}
	}
}
```
##SubSet
```cpp
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
```

##Inversion Number
```cpp
///base on the merger sort
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
			count += (n1 - i);//This is important
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
```
##sqrt

```cpp
int mySqrt(int x) {
	double mid;
	unsigned l = 0, r = (x - 1) / 2 + 1;
	while (l <= r){
		mid = (r - l) / 2 + l;
		if (mid * mid == x){
			return mid;
		}
		else if (mid * mid > x){
			r = mid - 1;
		}
		else{
			l = mid + 1;
		}
	}
	return r;
}
```

##Binary Search

```cpp
int binary_search(int A[], int n, int x){
	int l = 0, r = n - 1;
	while (l <= r){
		int m = (r - l) / 2 + l;
		if (A[m] == x){
			return m;
		}
		if (A[m] < x){
			l = m + 1;
		}
		else{
			r = m - 1;
		}
	}
	return -1;
}
```
##Tree
```cpp
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
```
##MaxDepth
```cpp
int maxDepthRecursive(TreeNode *root) {
	int ret = 0;
	if (root != NULL){
		ret = max(maxDepthRecursive(root->left), maxDepthRecursive(root->right)) + 1;
	}
	return ret;
}
```
```cpp
int maxDepthIterQueue(TreeNode *root){
	if (root == NULL){
		return 0;
	}
	queue<TreeNode *> q;
	q.push(root);
	int count = 1;
	int depth = 0;
	while (!q.empty())
	{
		TreeNode * tmp = q.front();
		q.pop();
		count--;
		if (tmp->left){
			q.push(tmp->left);
		}

		if (tmp->right){
			q.push(tmp->right);
		}
		if (count == 0){
			depth++;
			count = q.size();
		}
	}
	return depth;
}
```

```cpp
int maxDepthIterStack(TreeNode *root){
	if (!root) return 0;
	stack<TreeNode*> s;
	s.push(root);
	int maxDepth = 0;
	TreeNode *prev = NULL;
	while (!s.empty()) {
		TreeNode *curr = s.top();
		if (!prev || prev->left == curr || prev->right == curr) {
			if (curr->left)
				s.push(curr->left);
			else if (curr->right)
				s.push(curr->right);
		}
		else if (curr->left == prev) {
			if (curr->right)
				s.push(curr->right);
		}
		else {
			cout << s.top()->val << "-->" << endl;
			s.pop();
		}
		prev = curr;
		if (s.size() > maxDepth)
			maxDepth = s.size();
	}
	return maxDepth;
}

```
##Minimum Depth 
```cpp
int minDepth(TreeNode *root){
	if (root == NULL){
		return 0;
	}
	queue<TreeNode *> q;
	q.push(root);
	int count = 1;
	int depth = 1;
	while (!q.empty())
	{
		TreeNode * tmp = q.front();
		q.pop();
		count--;
		if (!tmp->left && !tmp->right){
			return depth;
		}
		if (tmp->left){
			q.push(tmp->left);
		}

		if (tmp->right){
			q.push(tmp->right);
		}
		if (count == 0){
			depth++;
			count = q.size();
		}
	}
	return depth;
}
```

##Preorder
```cpp
vector<int> preorderTraversal(TreeNode *root) {
	vector<int> ret;
	if (!root) return  ret;

	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		TreeNode * node = s.top();
		s.pop();
		ret.push_back(node->val);
		if (node->right){
			s.push(node->right);
		}
		if (node->left){
			s.push(node->left);
		}
	}
	return ret;
}

```

##Inorder

```cpp
//Binary Tree Inorder Traversal
vector<int> inorderTraversal(TreeNode *root) {
	vector<int> ret;
	if (!root) return  ret;

	stack<TreeNode*> s;

	while (root != NULL || !s.empty())
	{
		if (root != NULL){
			s.push(root);
			root = root->left;
		}
		else{
			root = s.top();
			s.pop();
			ret.push_back(root->val);
			root = root->right;
		}
	}
	return ret;
}


```

##Postorder
```cpp
//	Binary Tree Postorder Traversal
vector<int> postorderTraversal(TreeNode *root) {
	vector<int> ret;

	if (!root) return  ret;

	stack<TreeNode*> s;
	s.push(root);
	TreeNode *prev = NULL;

	while (!s.empty()) {
		TreeNode *curr = s.top();
		if (!prev || prev->left == curr || prev->right == curr) {
			if (curr->left)
				s.push(curr->left);
			else if (curr->right)
				s.push(curr->right);
		}
		else if (curr->left == prev) {
			if (curr->right)
				s.push(curr->right);
		}
		else {
			ret.push_back(s.top()->val);
			s.pop();
		}
		prev = curr;
	}
	return ret;
}
```
##Level Order Traversal 
```cpp
//Binary Tree Level Order Traversal 
vector<vector<int> > levelOrder(TreeNode *root) {
	vector<vector<int> > ret;
	if (root == NULL){
		return ret;
	}
	queue<TreeNode *> q;
	q.push(root);
	int count = 1;
	vector<int> levelVec;
	while (!q.empty())
	{

		TreeNode * tmp = q.front();
		levelVec.push_back(tmp->val);
		q.pop();
		count--;
		if (tmp->left){
			q.push(tmp->left);
		}

		if (tmp->right){
			q.push(tmp->right);
		}
		if (count == 0){
			ret.push_back(levelVec);
			levelVec.clear();
			count = q.size();
		}
	}
	reverse(ret.begin(), ret.end());
	return ret;
}
```

##Level Order Traversal
```cpp
//Binary Tree Level Order Traversal II T
vector<vector<int> > levelOrderBottom(TreeNode *root) {
	vector<vector<int> > ret;
	if (root == NULL){
		return ret;
	}
	queue<TreeNode *> q;
	q.push(root);
	int count = 1;
	vector<int> levelVec;
	while (!q.empty())
	{

		TreeNode * tmp = q.front();
		levelVec.push_back(tmp->val);
		q.pop();
		count--;
		if (tmp->left){
			q.push(tmp->left);
		}

		if (tmp->right){
			q.push(tmp->right);
		}
		if (count == 0){
			ret.push_back(levelVec);
			levelVec.clear();
			count = q.size();
		}
	}
	//reverse(ret.begin,ret.end());
	return ret;
}
```
##Construct Binary Tree from Preorder and Inorder Traversal
```cpp
/*
Construct Binary Tree from Preorder and Inorder Traversal
*/

TreeNode * buildTreePI(vector<int> &preorder, int  pbegin, int pend, vector<int> &inorder, int ibegin, int iend){
	if (pbegin > pend || ibegin > iend){
		return NULL;
	}
	int pivot = preorder[pbegin];
	int i = ibegin;
	for (; i < iend; i++)
	{
		if (inorder[i] == pivot){
			break;
		}
	}
	TreeNode * root = new TreeNode(pivot);
	root->left = buildTreePI(preorder, pbegin + 1, i - ibegin + pbegin, inorder, ibegin, i - 1);
	root->right = buildTreePI(preorder, i - ibegin + pbegin + 1, pend, inorder, i + 1, iend);
	return root;

}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
	int  pbegin = 0;
	int pend = preorder.size() - 1;
	int ibegin = 0;
	int iend = inorder.size() - 1;
	TreeNode * root = buildTreePI(preorder, pbegin, pend, inorder, ibegin, iend);
	return root;
}


```
##Construct Binary Tree from Inorder and Postorder Traversal
```cpp
/*Construct Binary Tree from Inorder and Postorder Traversal*/

TreeNode * buildTreeIP(vector<int> & inorder, int is, int ie,
	vector<int> & postorder, int ps, int pe) {
	if (ps > pe || is > ie) {
		return NULL;
	}
	int pivot = postorder[pe];
	int i = is;
	for (; i < ie; i++) {
		if (inorder[i] == pivot) {
			break;
		}
	}
	TreeNode *rootNode = new TreeNode(pivot);
	rootNode->left = buildTreeIP(inorder, is, i - 1, postorder, ps, ps + i - is - 1);
	rootNode->right = buildTreeIP(inorder, i + 1, ie, postorder, ps + i - is, pe - 1);
	return rootNode;
}


TreeNode *buildTree1(vector<int> &inorder, vector<int> &postorder){
	int is = 0;
	int ie = inorder.size() - 1;
	int ps = 0;
	int pe = postorder.size() - 1;
	TreeNode *root = buildTreeIP(inorder, is, ie, postorder, ps, pe);
	return root;
}
```
##MaximumGap
**非常喜欢这个题目的解法桶排序的第一次应用**
```cpp
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
```
#Queue and Stack
```cpp
//两个栈生成一个队列
template <typename T>
class Queue{
public :
	Queue(){}
	~Queue(){}
	void appendTail(const T& item);
	T deleteHead();
private :
	// s1主要负责进行数据的push操作
	stack<T> m_stack1;
	//s2负责数据的pop操作
	stack<T> m_stack2;

};


template<typename T>
void Queue<T>::appendTail(const T & item){
	m_stack1.push(item);
}

template<typename T>
T  Queue<T>::deleteHead(){
	/*如果当前的s2栈中没有数据,则把s1中的所有数据全部逆序导入到s1中
	*/
	if (m_stack2.empty()){
		while (m_stack1.size() > 0)
		{
			T &data = m_stack1.top();
			m_stack1.pop();
			m_stack2.push(data);
		}
	}
	if (m_stack2.size() == 0)
		throw new exception("队列为空");
	T ret = m_stack2.top();
	m_stack2.pop();
	return ret;
}
//////////////////////////////

//两个队列生成一个栈
template <typename T>
class Stack{
public:
	Stack();
	~Stack();
	void push(const T& item);
	T pop();
private:
	queue<T> q1;
	queue<T> q2;

};
template <typename T>
void pushHead(const T& item){
	if (q1.size() > 0){
		q1.push(item);
	}
	else if (q2.size() > 0){
		q2.push(item);
	}
	else{
		q1.push(item);
	}
}
template <typename T>
T popStack(){
	if (q1.empty()){
		while (q2.size()>1)
		{
			q1.push(q2.front());
			q2.pop();
		}
		T &data = q2.front();
		q2.pop();
		return data;
	}
	else{
		while (q1.size()>1)
		{
			q2.push(q1.front());
			q1.pop();
		}
		T &data = q1.front();
		q1.pop();
		return data;
	}
}

```

##[Trap Water](https://leetcode.com/problems/trapping-rain-water/)
```cpp
int trap(int A[], int n) {
	int all = 0;
	int block = 0;
	int l = 0;
	int r = n - 1;
	int curLevel = 0;
	while (l <= r){
		if (min(A[l], A[r]) > curLevel){
			all += (min(A[l], A[r]) - curLevel) *(r - l + 1);
			curLevel = min(A[l], A[r]);
		}
		if (A[l] < A[r]){
			block += A[l++];
		}
		else{
			block += A[r--];
		}
	}
	return all - block;
}

int trap1(int A[], int n) {
	int leftMax = 0, rightMax = 0;
	int l = 0;
	int r = n - 1;
	int ret = 0;
	while (l <= r)
	{
		leftMax = max(A[l], leftMax);
		rightMax = max(A[r], rightMax);
		if (leftMax < rightMax){
			ret += (leftMax - A[l]);
			l++;
		}
		else{
			ret += (rightMax - A[r]);
			r--;
		}
	}
	return ret;
}
```
##[LargestRectangleArea](https://leetcode.com/problems/largest-rectangle-in-histogram/)
**非常巧妙的思想**
```cpp
int largestRectangleArea(vector<int> &height) {
	int maxArea = 0;
	stack<int> s;
	int temp = 0;
	int i = 0;
	while (i < height.size()){
		if (s.empty() || height[i] >= height[s.top()]){
			s.push(i++);
		}
		else{
			temp = s.top();
			s.pop();
			maxArea = max(maxArea, height[temp] * (s.empty() ? i : i - s.top() - 1));
		}
	}
	while (!s.empty())
	{
		temp = s.top();
		s.pop();
		maxArea = max(maxArea, height[temp] * (s.empty() ? i : i - s.top() - 1));
	}
	return maxArea;
}
```
##LIS(longest increase Subsequence)

```cpp
int lis(const vector<int> &num){
    auto len = num.size();
    vector<int> dp(len,1);
    int lis = 0;
    /////
    int lastIndex = 0;
    /////
    for(int i = 0; i < num.size(); i++){
        for(int j = 0; j < i; j++){
            if(num[j] < num[i] && dp[i] < dp[j] + 1){
                dp[i] = dp[j] + 1;
            }
        }
        if(dp[i] < lis){
            ///////in order to print///////
            lastIndex = i;
            ///////////////
            lis = dp[i];
        }
    }
    printSubsequence(num,dp,lastIndex,lis);
    return lis;
}

//////逆序输出///////
void printSubsequence(const vector<int> &num,const vector<int> &dp,int lastIndex,int lis){
    int temp = lis;
    for(;lastIndex >=0 ; --lastIndex){
        if(dp[lastIndex] == temp){
            cout<<num[lastIndex]<<"->";
            temp -- ;
        }
    }
    cout<<endl;
}
```


```cpp
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
```

##最大子数组和以及乘积
```cpp
//最大子数组乘积
int maxProduct(int A[], int n) {
	int cur_max = A[0];
	int cur_min = A[0];
	int ret = A[0];
	for (int i = 1; i < n; i++){
		int temp = cur_max;
		cur_max = max(A[i], max(A[i] * cur_max, A[i] * cur_min));
		cur_min = min(A[i], min(A[i] * temp, A[i] * cur_min));
		ret = cur_max>ret ? cur_max : ret;
	}
	return ret;
}
//最大子数组之和
int maxSubArray(int A[], int n) {
	int maxEndHere = A[0];
	int maxSoFar = A[0];
	for (int i = 1; i < n; i++){
		maxEndHere = max(maxEndHere + A[i], A[i]);
		maxSoFar = max(maxSoFar, maxEndHere);
	}
	return maxSoFar;
}
```
##[Minimum Window Substring ](https://leetcode.com/problems/minimum-window-substring/)
**非常通用的思想**
```cpp
string minWindow(string S, string T) {
	int appeared[256] = { 0 };
	int expected[256] = { 0 };
	int count = 0;
	int minStart = 0;
	int minEnd = INT_MAX;
	int start = 0;

	for (int i = 0; i < T.size(); i++){
		expected[T[i]] ++;
	}
	for (int end = 0; end < S.size(); end++)
	{
		if (expected[S[end]] > 0)
		{
			appeared[S[end]]++;
			if (expected[S[end]] >= appeared[S[end]]){
				count++;
			}
		}
		if (count == T.size()){
			while (expected[S[start]] < appeared[S[start]] || expected[S[start]] == 0)
			{
				appeared[S[start]] --;
				start++;
			}
			if ((minEnd - minStart)>(end - start)){
				minEnd = end;
				minStart = start;
			}
		}
	}
	if (minEnd == INT_MAX){
		return "";
	}
	return S.substr(minStart, minEnd - minStart + 1);
}
```
##[Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

```cpp
int maxArea(vector<int> &height) {
	int ret = 0;
	int i = 0, j = height.size() - 1;
	while (i < j)
	{
		int tmp = min(height[i], height[j])*(j - i);
		if (height[i] < height[j]){
			i++;
		}
		else{
			j--;
		}
		ret = max(tmp, ret);
	}
	return ret;

```

##[LRU Cache](https://leetcode.com/problems/lru-cache/)
```cpp
struct LRUCacheEntry{
	int key;
	int value;
	LRUCacheEntry *pre;
	LRUCacheEntry *next;
};

class LRUCache{

private:
	LRUCacheEntry *head;
	LRUCacheEntry *tail;
	LRUCacheEntry *t;
	map<int, LRUCacheEntry *> _map;
	vector< LRUCacheEntry *> freeEntry;

	void detach(LRUCacheEntry *node){
		node->pre->next = node->next;
		node->next->pre = node->pre;
	}

	void attach(LRUCacheEntry *node){
		node->next = head->next;
		node->pre = head;
		head->next->pre = node;
		head->next = node;

	}
public:
	LRUCache(int capacity) {
		t = new LRUCacheEntry[capacity];
		for (int i = 0; i < capacity; i++){
			freeEntry.push_back(t + i);
		}
		head = new LRUCacheEntry();
		tail = new LRUCacheEntry();

		head->pre = nullptr;
		tail->next = nullptr;
		head->next = tail;
		tail->pre = head;
	}
	~LRUCache(){
		delete[] t;
		delete head;
		delete tail;
	}
	int get(int key) {
		LRUCacheEntry *node = _map[key];
		if (node){
			detach(node);
			attach(node);
			return node->value;
		}
		return -1;
	}

	void set(int key, int value) {
		LRUCacheEntry *node = _map[key];
		if (node){
			detach(node);
			node->value = value;
			attach(node);
		}
		else{
			if (freeEntry.empty()){
				node = tail->pre;
				detach(node);
				_map.erase(node->key);

			}
			else{
				node = freeEntry.back();
				freeEntry.pop_back();
			}
			node->key = key;
			node->value = value;
			_map[key] = node;
			attach(node);
		}
	}
};
```
