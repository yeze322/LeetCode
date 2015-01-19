class Solution {
public:
    int singleNumber1(int A[], int n) {
        while(--n)
            A[n-1]=A[n]^A[n-1];
        return A[0];
    }
	int singleNumber2(int A[], int n) {
        for(int i=1;i<n;i++)
            A[0]=A[0]^A[i];
        return A[0];
    }
};