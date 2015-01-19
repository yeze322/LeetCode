#include<iostream>
using namespace std;
class Solution {
public:
    int removeDuplicates(int A[], int n) {
       if(!n)
			return 0;
		int index_new=0,i=1;
		while(i<n)
		{
			while(A[i]==A[index_new])//==A[i-1]
				i++;
			if(i>=n)
				return index_new+1;
			A[++index_new]=A[i++];
		}
		return index_new+1;
    }
};

int main()
{
	int a[10]={0,1,2,3,4,5,6,7,9,9};
	Solution yy;
	int count=yy.removeDuplicates(a,0);
	return 0;
}
