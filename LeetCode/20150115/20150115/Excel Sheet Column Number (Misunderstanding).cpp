#include<iostream>
using namespace std;
//本质是一个26进制的问题

class Solution {
public:
    int titleToNumber(string s) {
        int num=0,i=0;
        while(i<s.length())
        {
            num=num*26+s[i]-'A'+1;
            i++;
        }
        return num;
    }
};

int main()
{
	string a="Z";
	Solution yee;
	int trans=yee.titleToNumber(a);
	//char ch2=a[6];//不允许越界访问
	return 0;
}