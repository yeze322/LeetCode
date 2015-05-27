#include<vector>
using namespace std;
class Solution {
public:
    int majorityElement(vector<int> &num) {
        int flag=num[0],count=0;
		for(int i=1;i<num.size();i++)
		{
			while(i<num.size()&&num[i]==flag)
			{
				count++;
				i++;
			}
			count--;
			if(count<0)
			{
				flag=num[i];
				count=0;
			}
		}
		return flag;
    }
};

int main()
{
	int a[7]={-1,100,2,100,100,4,100};
	vector<int> num;
	for(int i=0;i<7;i++)
	{
		num.push_back(a[i]);
	}
	Solution he;
	int majority=he.majorityElement(num);
	return 0;
}
