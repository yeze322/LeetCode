#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
public:
    void recoverTree(TreeNode *root) {
		last = new TreeNode(INT_MIN);
        inorder(root);
    }
private:
    TreeNode *last;
	TreeNode *up;
	TreeNode *down;
    void inorder(TreeNode *node){
        if(node==NULL)
            return;
        inorder(node->left);
		int lastval=last->val;
		int thisval=node->val;
		if(thisval<lastval){
			node->val=lastval;
			last->val=thisval;
		}//swap
		last=node;
        inorder(node->right);
    }
};
int main()
{
	TreeNode *root = new TreeNode(2);
	root->left = new TreeNode(3);
	root->right = new TreeNode(1);
	Solution t;
	t.recoverTree(root);
	return 0;
}
