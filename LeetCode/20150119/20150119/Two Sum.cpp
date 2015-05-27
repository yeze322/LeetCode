#include<algorithm>
#include <vector>
using namespace std;
class Solution{
public:
	vector<int> twoSum(vector<int> &numbers, int target) {

	}
	int vecsearch(vector<int> n,int top,int end,int find)
	{//assuming giving an ascending 
		int mid;
		while(top<=end)
		{
			mid=(top-end)/2+end;
			if(n[mid]==find)
				return mid;
			else if(n[mid]<find)
				top=mid+1;
			else
				end=mid-1;
		}
		return -1;
	}

};
int bs(const void *a,const void *b)
{
	return (*(int*)a-*(int*)b);
}


int main()
{
	Solution ss;
	int a[10]={1,2,3,4,5,6,7,8,10,9};
	qsort(&a,10,sizeof(int),bs);
	vector<int> num;
	for(int i=0;i<10;i++)
		num.push_back(a[i]);
	int index=ss.vecsearch(num,0,num.size(),7);

	return 0;
}
