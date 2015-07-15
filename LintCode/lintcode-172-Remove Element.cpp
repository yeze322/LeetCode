#include <string>
#include <vector>
#include <time.h>

using namespace std;
class Solution {
public:
	/**
	*@param A: A list of integers
	*@param elem: An integer
	*@return: The new length after remove
	*/

	/*
	Three versions for this question.
	Key point is how to simplified it.
	In theory, solution is better, but the performance indicates that soluton0 is better than the first one.
	It may caused by small test cases.

	!!!:
	After test, I have to admit, the version with an extra while() loop is not a good method......
	time is nearly the same, but it's not concise at all.
	*/

	int removeElement(vector<int> &A, int elem) {
		// write your code here
		int SIZE = A.size();
		int count = 0;
		int visit = 0;
		int write = 0;

		while (visit < SIZE && A[visit] != elem) visit++;
		write = visit;
		for (; visit < SIZE; visit++){
			if (A[visit] == elem) count++;
			else A[write++] = A[visit];
		}
		return SIZE - count;
	}
	int removeElement0(vector<int> &A, int elem) {
		// write your code here
		const int SIZE = A.size();
		int write = 0;
		int count = 0;

		for (int i = 0; i < SIZE; i++){
			if (A[i] == elem) count++;
			else{
				if (write != i) A[write] = A[i];
				write++;
			}
		}
		return SIZE - count;
	}
	int removeElement1(vector<int> &A, int elem) {
		// write your code here
		const int SIZE = A.size();
		int write = 0;
		int count = 0;
		for (int i = 0; i < SIZE; i++){
			if (A[i] != elem){
				A[write++] = A[i];
			}
			else{
				count++;
			}
		}
		return SIZE - count;
	}
	int removeElement2(vector<int> &A, int elem) {
		// write your code here
		int len = A.size();
		while (true){
			auto iter = find(A.begin(), A.end(), elem);
			if (iter == A.end()) return len;
			A.erase(iter);
			len--;
		}
	}
};



int main(){
	Solution t;
	vector<int> hehe = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 4, 0, 2, 0, 4, 4, 0, 4, 4, 4, 0, 2, 0, 4, 4, };
	vector<vector<int>> list(10000, hehe);
	clock_t t1 = clock();
	for (auto x : list){
		t.removeElement(x, 4);
	}
	clock_t t2 = clock();
	for (auto x : list){
		t.removeElement0(x, 4);
	}
	clock_t t3 = clock();
	return 0;
}