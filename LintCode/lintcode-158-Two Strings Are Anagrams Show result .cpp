#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
	/**
	* @param s: The first string
	* @param b: The second string
	* @return true or false
	*/
	bool anagram(string s, string t) {
		// write your code here
		vector<int> hash(255);
		for (auto ch : s) hash[ch]++;
		for (auto ch : t) hash[ch]--;
		for (auto num : hash){
			if (num) return false;
		}
		return true;
	}
};

class Solution2 {
public:
	/**
	* @param s: The first string
	* @param b: The second string
	* @return true or false
	*/
	bool anagram(string s, string t) {
		// write your code here
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		return s == t;
	}
};
int main(){
	Solution t;
	auto ret = t.anagram("abcs", "scab");
}