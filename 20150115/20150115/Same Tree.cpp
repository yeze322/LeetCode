#include<iostream>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	bool isSameTree(TreeNode *p, TreeNode *q) {
		//NULL?
		if(p==NULL||q==NULL){
			if(p==NULL&&q==NULL)
				return 1;
			else
				return 0;
		}

		if(p->val!=q->val)
			return 0; 
		else
			return isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
	}
};