#include<stack>
#include<string>
using namespace std;
extern int a[];
class Solution {
public:
    bool isValid(string s) {
        stack<char> left;
		for(int i=0;i<s.length();i++)
		{
			char ch=s[i];
			if(ch=='('||ch=='['||ch=='{')
			{
				left.push(ch);
				continue;
			}
			//else ch==),],}
			if(left.empty())
				return false;
			//now left!=empty ch = ) ] }
			if(ch-left.top()<=2)//match via ascii
				left.pop();//here cause WA,else means nomatch must return false
			else
				return false;
		}
		return left.empty();
    }
};