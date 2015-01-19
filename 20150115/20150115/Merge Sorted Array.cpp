class Solution {
public:
	void merge(int A[], int m, int B[], int n) {
		int tail=m+n-1;
		int atail=m-1,btail=n-1;//RA.没有考虑空数组的情况
		bool increase=0;
		if(atail==-1||btail==-1)
		{
			if(atail==-1&&btail==-1)
				return;//problem is when atail or btail ==-1, bool error
		}
		else
			increase=(A[0]<=A[atail]&&B[0]<=B[btail]);
		while(tail>=0)
		{
			if(atail<0||btail<0)
			   A[tail--]=(atail<0?B[btail--]:A[atail--]);
			else if((A[atail]>B[btail]))//不用选择是递增还是递减
			   A[tail--]=(increase?A[atail--]:B[btail--]);
			else
			   A[tail--]=(increase?B[btail--]:A[atail--]);
		}
	}
};
//我觉得这道题目的意义在于自动排序。不传入递增还是递减你怎么判断是增还是减法。
int main()
{
	Solution tst;
	int A[10]={};
	int B[5]={1,2,3,4,5};
	tst.merge(A,0,B,5);
	return 0;
}