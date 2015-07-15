#include <vector>
#include <cstring>
using namespace std;
class Solution {
public:
	/**
	* Returns a index to the first occurrence of target in source,
	* or -1  if target is not part of source.
	* @param source string to be scanned.
	* @param target string containing the sequence of characters to match.
	*/
	int strStr(const char *source, const char *target) {
		// write your code here
		if (source == NULL || target == NULL) return -1;
		vector<int> next = calcNext(target);
		int len_src = strlen(source);
		int len_tgt = strlen(target);
		int i = 0, j = 0;
		while (i<len_src && j<len_tgt){
			if (source[i] == target[j]){
				i++;
				j++;
			}
			else if (j == 0){
				i++;
			}
			else{
				j = next[j - 1];
			}
		}
		if (j == len_tgt) return i - len_tgt;
		else return -1;
	}
private:
	vector<int> calcNext(const char *s){
		int len = strlen(s);
		vector<int> next(len);
		for (int i = 1; i<len; i++){
			if (s[i] == s[next[i - 1]]) next[i] = next[i - 1] + 1;
			else next[i] = s[0] == s[i];
		}
		return next;
	}
};