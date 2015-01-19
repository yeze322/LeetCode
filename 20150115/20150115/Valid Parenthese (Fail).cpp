#include<iostream>
#include<string>
using namespace std;
class Solutionfail {//没那么简单。本函数能够保证匹配但不能保证完全匹配，见0116
public:
	bool isValid(string s) {
		int len=s.length();
		int these[3]={0};
		char lastone;
		for(int i=0;i<len;i++)
		{
			switch(s[i])
			{
			case '(':
				these[0]++;	break;
			case ')':
				if(these[0])
					these[0]--;
				else
					return false;
				//************
			case '[':
				these[1]++; break;
			case ']':
				if(these[1])
					these[1]--;
				else
					return false;
				//**************
			case '{':break;
				these[2]++; break;
			case '}':			
				if(these[2])
					these[2]--;
				else
					return false;
			}	
			lastone=s[i];
		}
		if(!(these[0]||these[1]||these[2]))
			return true;
		return false;
	}
};


int main()
{
	string st="1234";
	int a=st.length();
	Solution student;
	return 0;
}
