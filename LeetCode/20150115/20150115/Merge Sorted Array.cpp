class Solution {
public:
	void merge(int A[], int m, int B[], int n) {
		int tail=m+n-1;
		int atail=m-1,btail=n-1;//RA.û�п��ǿ���������
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
			else if((A[atail]>B[btail]))//����ѡ���ǵ������ǵݼ�
			   A[tail--]=(increase?A[atail--]:B[btail--]);
			else
			   A[tail--]=(increase?B[btail--]:A[atail--]);
		}
	}
};
//�Ҿ��������Ŀ�����������Զ����򡣲�����������ǵݼ�����ô�ж��������Ǽ�����
int main()
{
	Solution tst;
	int A[10]={};
	int B[5]={1,2,3,4,5};
	tst.merge(A,0,B,5);
	return 0;
}