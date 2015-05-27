#include <string>
#include <unordered_set>
#include <stack>
#include <deque>
using namespace std;

class Solution {
public:
	vector<string> wordBreak(string s, unordered_set<string> &dict) {
		line = &s;
		len = s.length();
		mark_prvshead = new vector<int> [len+1];
		bool can = false;
		deque<int> point_cut(1,0);
		for(int tail=1;tail<len+1;tail++){
			bool found = false;
			for(auto iter = point_cut.begin();iter!=point_cut.end();iter++){
				int head = *iter;
				string word = s.substr(head,tail-head);
				auto ptr_find = dict.find(word);
				if(ptr_find!=dict.end()){
					mark_prvshead[tail].push_back(head);
					found = true;
				}
			}
			if(found)
				point_cut.push_front(tail);

		}
		if(point_cut[0]==len)
			bottom_to_top(len,"");
		return sentence;
	}
	void bottom_to_top(int tail,string suffix){
		auto vec = mark_prvshead[tail];
		for(auto ptr = vec.begin();ptr!=vec.end();ptr++){
			string word= line->substr(*ptr,tail-*ptr);
			if(*ptr==0)
				sentence.push_back(word + suffix);
			else
				bottom_to_top(*ptr," "+ word + suffix);
		}
	}

private:
	int len;
	vector<int> *mark_prvshead;
	string *line;
	unordered_set<string> *diction;
	vector<string> sentence;
};

class Solution2{
public:
	// compare if the suffix is contained in the word
	bool stringSuffComp(const string& suff, const string& word){

		if (suff.length() > word.length()) return false;

		for (int i = suff.length() - 1, j = word.length() - 1; i >= 0 && j >= 0; i--, j--){

			if (suff[i] != word[j]) return false;
		}
		return true;
	}

	// check if any suffix of s is not contained in the dict
	// only check those suffix that is shorter than the minimum length of the words in dict
	bool checkSuffix(string* s, unordered_set<string> &dict){

		string suff;
		unordered_set<string>::iterator j = dict.begin();
		// Record the minimum length of the words, help check the suffix
		int suffLen = (*s).length();
		while (j != dict.end()){

			if ((*j).length() < suffLen) suffLen = (*j).length();
			j++;
		}

		j = dict.begin();
		// check if the suffix of string is contained as the suffix of each word
		for (int i = (*s).length() - 1; i >= (*s).length() - suffLen; i--){

			if (i < 0) break;
			suff = (*s).substr(i);
			bool found = false;
			while (j != dict.end()){

				if (stringSuffComp(suff, (*j))) { 
					found = true; 
					break;
				}
				j++;
			}
			if (!found) return false;
		}
		return true;
	}

	vector<string> wordBreak(string s, unordered_set<string> &dict) {

		stack<int> nodes;                       // when we have a guess, put idx of that word into this record
		stack<string> str_nodes;                // record the sentence that is matched so forth
		vector<string> res;
		string* ans = new string("");
		int i = 0, j = 1;                       // start and end pos of current word search
		bool finish = false;

		if (!checkSuffix(&s, dict)) return res; // branch-cutting? get rid of the cases that would fail but exetremely costy

		while (!finish){

			for (; j <= s.length(); j++){
				// search possible current word
				if (dict.find(s.substr(i, j - i)) == dict.end()) continue;
				else if (j == s.length()){
					// a match here, and we have a new sentence with space
					*ans += s.substr(i, j - i);
					res.push_back(*ans);
					ans = new string("");
					if (nodes.size()) break;
				}
				else{
					// a matched word, but not reach the end of original string 
					str_nodes.push(string(*ans));
					*ans += s.substr(i, j - i) + " ";
					nodes.push(j);
					nodes.push(i);

					i = j;
					continue;
				}
			}
			// the last guess is not a good one, pop out and retry
			if (nodes.size()){
				*ans = str_nodes.top(); str_nodes.pop();
				i = nodes.top(); nodes.pop();
				j = nodes.top(); nodes.pop();
				j++;
			}
			else break;
		}
		return res;
	}
};

int main()
{
	string a[]={"aaaa","aa","a"};

	unordered_set<string> diction(a,a+sizeof(a)/sizeof(string));
	string s = "aaaaaaaaaaaaaaaaa";
	Solution2 t;
	auto ret = t.wordBreak(s,diction);
	return 0;
}