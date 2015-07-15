#include <string>
#include <vector>
using namespace std;

class Solution {
public:
	/**
	* @param A, B: Two string.
	* @return: the length of the longest common substring.
	*/
	int longestCommonSubstring(string &A, string &B) {
		// write your code here
		int lenA = A.size();
		int lenB = B.size();
		vector<int> mark(lenA + 1);
		int max = 0;
		for (auto chB : B){
			for (int i = lenA - 1; i>-1; i--){
				if (A[i] == chB){
					mark[i + 1] = mark[i] + 1;
					max = mark[i + 1] > max ? mark[i + 1] : max;
				}
				else{
					mark[i + 1] = 0;
				}
			}
		}
		return max;
	}
};