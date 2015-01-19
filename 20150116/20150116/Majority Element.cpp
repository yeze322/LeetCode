#include<algorithm>
#include<vector>

using namespace std;
class Solution1 {
public:
	int majorityElement(vector<int> &num) {
		//qqsort(num,0,num.size()-1);
		sort(num.begin(),num.end());
		return num[num.size()/2];
	}
	void qqsort(vector<int> &num,int begin,int end)
	{
		if(begin>=end)
			return;
		int i=begin,j=end;
		int flag=num[i];
		while(i<j)
		{
			while(i<j&&num[j]>=flag)
				j--;
			num[i]=num[j];
			while(i<j&&num[i]<=flag)
				i++;
			num[j]=num[i];
		}
		num[i]=flag;
		qqsort(num,begin,i-1);
		qqsort(num,i+1,end);
	}

};
class Solution {
public:
	int majorityElement(vector<int> &num) {
		int *i=&num[0],*j=&num[num.size()-1];
		qqsort(num,i,j);
		//sort(num.begin(),num.end());
		return num[num.size()/2];
	}//快排不行。明天重写一个更加好的
	void qqsort(vector<int> &num,int *begin,int *end)
	{
		if(begin>=end)
			return;
		int *i=begin,*j=end;
		int flag=*i;
		while(i<j)
		{
			while(i<j&&*j>=flag)
				j--;
			*i=*j;
			while(i<j&&*i<=flag)
				i++;
			*j=*i;
		}
		*i=flag;
		qqsort(num,begin,i-1);
		qqsort(num,i+1,end);
	}

};
int main()
{
	Solution yeze;
	vector<int> number;
	int a[10]={1,54,2,54,2,1,5,46,4,34};
	for(int i=0;i<10;i++)
		number.push_back(a[i]);
	yeze.majorityElement(number);
	return 0;
}
