#include<vector>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode *sortedArrayToBST(vector<int> &num) {
		return createBST(num,0,num.size());
	}
private:
	TreeNode* createBST(vector<int> &num,int head,int tail){
		if(head>=tail)
			return NULL;
		if(head==(tail-1))
			return new TreeNode(num[head]);
		int cut=(head+tail)/2;
		TreeNode *root = new TreeNode(num[cut]);
		root->left = createBST(num,head,cut);
		root->right = createBST(num,cut+1,tail);
		return root;
	}
};

int main()
{
	vector<int> num;
	num.push_back(1);
	num.push_back(3);
	Solution t;
	auto ret = t.sortedArrayToBST(num);
	return 0;
}
