#include<string>
using namespace std;
class Solution {
public:
    int removeElement(int A[], int n, int elem) {
		int count=n,j=0;
        for(int i=0;i<n;i++)
        {
           if(A[i]!=elem)
                A[j++]=A[i];
        }
        return j;
       /* int count=n,j=0;
        for(int i=0;i<n;i++)
        {
            while(A[i]==elem)
			{
				count--;
                i++;
			}
            if(i==n)
				break;
			A[j++]=A[i];
        }
        return count;*/
    }
};

int main()
{
	string s;
	int A[11]={2,1,3,0,1,1,0,3,3,1,3};
	Solution yy;
	int len=yy.removeElement(A,11,3);
	return 0;
}
