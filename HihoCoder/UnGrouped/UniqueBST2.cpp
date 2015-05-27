#include <vector>
#include <iostream>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<TreeNode *> generateTrees(int n) {
		return createTree(n,1);
	}
private:
	vector<TreeNode *> createTree(int node_num, int start){
		vector<TreeNode*> ret;
		if(node_num==0){
			ret.push_back(NULL);
			return ret;
		}
		if(node_num==1){
			TreeNode *root = new TreeNode(start);
			ret.push_back(root);
			return ret;
		}//add n=1 to reduce recursive times.
		for(int i=1;i<node_num+1;i++){
			vector<TreeNode*> treeLeft = createTree(i-1,start);
			vector<TreeNode*> treeRight =  createTree(node_num-i,start+i);
			for(auto pLeft=treeLeft.begin();pLeft!=treeLeft.end();++pLeft){
				for(auto pRight=treeRight.begin();pRight!=treeRight.end();++pRight){
					TreeNode *root = new TreeNode(start+i-1);
					root->left = *pLeft;
					root->right = *pRight;
					ret.push_back(root);
				}
			}
		}
		return ret;
	}
};

int main()
{
	Solution t;
	vector<TreeNode*> ret;
	ret = t.generateTrees(1);
	ret = t.generateTrees(2);
	ret = t.generateTrees(3);
	ret = t.generateTrees(4);
	return 0;
}
