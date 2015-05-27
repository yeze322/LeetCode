#include <vector>
using std::vector;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	vector<int> rightSideView(TreeNode *root) {
		vector<int> right_vec;
		if(root==NULL)
			return right_vec;
		vector<TreeNode*> temp_node;
		vector<TreeNode*> this_level(1,root);

		while(!this_level.empty()){
			temp_node.clear();
			right_vec.push_back(((*this_level.end())-1)->val);
			for(int i=0;i<this_level.size();i++)
			{
				TreeNode *temp = this_level[i];
				if(temp->left)
					temp_node.push_back(temp->left);
				if(temp->right)
					temp_node.push_back(temp->right);
			}
			this_level = temp_node;
		}

		return right_vec;
	}
};