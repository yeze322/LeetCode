#include<stack>
#include<string>
using namespace std;
class Solution {
public:
	string convertToTitle(int n) {
		stack<char> save;
		while(--n>=0)
		{
			save.push(n%26+'A');
			n=n/26-1;
		}
		string num26;
		while(!save.empty())
		{
			num26.push_back(save.top());
			save.pop();
		}
		return num26;
	}
	string convertToTitle1(int n) {
		string r;
		for (; n > 0; n /= 26)
			r = char(--n % 26 + 'A') + r;
		return r;
	}
};

int main()
{
	Solution yy;
	string i=yy.convertToTitle1(266);
	return 0;
}
