#include <vector>
#include <unordered_map>
using namespace std;
/*
HINT:
1. use union find set.
2. I tried to use unordered_set, but found that C++ don't support HASH a vector<>;
*/
class Solution {
public:
	/**
	* @param strs: A list of strings
	* @return: A list of strings
	*/
	struct INDEX{
		vector<string> ret;
		vector<int> index;
		INDEX(vector<int>& input, string& str) :index(input), ret({str}){}
	};
	vector<string> anagrams(vector<string> &strs) {
		vector<INDEX> index;
		for (auto str : strs){
			vector<int> hashStr(26);
			for (auto ch : str) hashStr[ch - 'a']++;
			if (index.empty()) index.push_back(INDEX(hashStr,str));
			else{
				bool repeated = false;
				for (auto &vec : index){
					if (vec.index == hashStr){
						vec.ret.push_back(str);
						repeated = true;
						break;
					}
				}
				if (!repeated)
					index.push_back(INDEX(hashStr,str));
			}
		}
		vector<string> ret;
		for (auto ele : index){
			if (ele.ret.size() > 1){
				ret.insert(ret.end(),ele.ret.begin(), ele.ret.end());
			}
		}
		return ret;
	}
};

int main(){
	vector<string> input = { "lint", "intl", "inlt", "code", };
	vector<string> in2 = { "tea", "", "eat", "", "tea", "" };
	Solution t;
	auto ret = t.anagrams(input);
	auto ret2 = t.anagrams(in2);
	return 0;
}