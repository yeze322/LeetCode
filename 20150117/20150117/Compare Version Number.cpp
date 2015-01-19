#include<string>
using namespace std;
class Solution {
public:
	int compareVersion(string version1, string version2) {
		unsigned int i=0,j=0;
		return cmp(version1,version2,i,j);
	}
	int cmp(string a,string b,unsigned int i,unsigned int j)
	{
		if(i>=a.size()&&j>=b.size())
			return 0;
		int num1=0,num2=0;
		while(i<a.length()&&a[i]!='.')
			num1=num1*10+a[i++]-'0';
		while(j<b.length()&&b[j]!='.')
			num2=num2*10+b[j++]-'0';
		i++;j++;
		if(num1<num2)
			return -1;
		else if(num1>num2)
			return 1;
		else return cmp(a,b,i,j);
	}
};

int main()
{
	Solution yy;
	string a="1.4";
	string b="1.5";
	int flag = yy.compareVersion(a,b);
	return 0;
}
