#include <string>
#include <vector>
#include <time.h>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*
Example
A = [1, 2, 3, empty, empty], B = [4, 5]

After merge, A will be filled as [1, 2, 3, 4, 5]
*/
class Solution {
public:
	/**
	* @param A: sorted integer array A which has m elements,
	*           but size of A is m+n
	* @param B: sorted integer array B which has n elements
	* @return: void
	*/
	void mergeSortedArray(int A[], int m, int B[], int n) {
		// write your code here
		int indexA = m - 1, indexB = n - 1;
		int write = m + n - 1;
		while (indexA >= 0 && indexB >= 0){
			while (indexA >= 0 && A[indexA] > B[indexB]){
				A[write--] = A[indexA--];
			}
			while (indexB >= 0 && A[indexA] <= B[indexB]){
				A[write--] = B[indexB--];
			}
		}
		if (indexB >= 0){
			memcpy(A, B, (indexB + 1)*sizeof(int));
		}
	}
};

int main(){
	Solution t;
	int A[] = { 9, 10, 11, 12, 13 };
	int B[] = { 4, 5, 6, 7 };
	t.mergeSortedArray(A, 5, B, 4);
	return 0;
}