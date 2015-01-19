#include<stdio.h>


class Solution {
private:
	struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};public:
	int maxDepth(TreeNode *root) {
		if(root==NULL)
			return 0;
		int a=maxDepth(root->left),b=maxDepth(root->right);
		return (a>b?a:b)+1;
	}

};