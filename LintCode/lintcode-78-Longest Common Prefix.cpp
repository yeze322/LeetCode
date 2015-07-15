#include <string>
#include <vector>
using namespace std;
/*
Example
For strings "ABCD", "ABEF" and "ACEF", the LCP is "A"

For strings "ABCDEFG", "ABCEFG" and "ABCEFA", the LCP is "ABC"
*/
class Solution {
public:
	/**
	* @param strs: A list of strings
	* @return: The longest common prefix
	*/
	string longestCommonPrefix(vector<string> &strs) {
		// write your code here
		int size = strs.size();
		if (size == 0) return "";
		vector<int> mark(size);
		int index = 0;
		string ret;
		string standard = strs[0];
		while (true){
			for (auto str : strs){
				if (index >= str.size() || str[index] != standard[index]) return ret;
			}
			ret.push_back(standard[index]);
			index++;
		}
	}
};

int main(){
	vector<string> in1 = { "ABCDEFG", "ABCEFG", "ABCEFA", };
	Solution t;
	auto ret = t.longestCommonPrefix(in1);
	return 0;
}