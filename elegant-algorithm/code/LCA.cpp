// LCA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

struct node {
	int val;
	node *left, *right;
	node(int x) :val(x), right(NULL), left(NULL){}
};

node* newNode(int k)
{
	node *temp = new node(k);
	return temp;
}
bool findPath(node* root, vector<int> &path, int k){
	if (root == NULL){
		return false;
	}
	path.push_back(root->val);
	if (root->val == k){
		return true;
	}
	if ((root->left && findPath(root->left, path, k)) || (root->right && findPath(root->right, path, k))){
		return true;
	}
	path.pop_back();
	return false;
}

int findLCA(node *root, int n1, int n2)
{
	// to store paths to n1 and n2 from the root
	vector<int> path1, path2;

	// Find paths from root to n1 and root to n1. If either n1 or n2
	// is not present, return -1
	if (!findPath(root, path1, n1) || !findPath(root, path2, n2))
		return -1;

	/* Compare the paths to get the first different value */
	int i;
	for (i = 0; i < path1.size() && i < path2.size(); i++){
		if (path1[i] != path2[i]){
			break;
		}
	}

	return path1[i - 1];
}

node* findLCARec(node *root, int n1, int n2){
	if (!root){
		return NULL;
	}
	// If either n1 or n2 matches with root's key, report
	// the presence by returning root (Note that if a key is
	// ancestor of other, then the ancestor key becomes LCA
	if (root->val == n1 || root->val == n2){
		return root;
	}
	// Look for keys in left and right subtrees
	node *left_lca = findLCARec(root->left, n1, n2);
	node *right_lca = findLCARec(root->right, n1, n2);
	// If both of the above calls return Non-NULL, then one key
	// is present in once subtree and other is present in other,
	// So this node is the LCA
	if (left_lca && right_lca){
		return root;
	}
	// Otherwise check if left subtree or right subtree is LCA
	return (left_lca != NULL) ? left_lca : right_lca;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Let us create the Binary Tree shown in above diagram.
	/*node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);
	cout << "LCA(4, 5) = " << findLCA(root, 4, 5);
	cout << "\nLCA(4, 6) = " << findLCA(root, 4, 6);
	cout << "\nLCA(3, 4) = " << findLCA(root, 3, 4);
	cout << "\nLCA(2, 4) = " << findLCA(root, 2, 4);*/
	node * root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);
	cout << "LCA(4, 5) = " << findLCARec(root, 4, 5)->val;
	cout << "\nLCA(4, 6) = " << findLCARec(root, 4, 6)->val;
	cout << "\nLCA(3, 4) = " << findLCARec(root, 3, 4)->val;
	cout << "\nLCA(2, 4) = " << findLCARec(root, 2, 4)->val;
	return 0;
	return 0;
}

