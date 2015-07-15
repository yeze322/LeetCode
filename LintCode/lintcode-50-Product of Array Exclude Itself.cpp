#include <string>
#include <vector>
#include <time.h>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
	/**
	* @param A: Given an integers array A
	* @return: A long long array B and B[i]= A[0] * ... * A[i-1] * A[i+1] * ... * A[n-1]
	*/
	vector<long long> productExcludeItself(vector<int> &nums) {
		// write your code here
		int size = nums.size();
		if (size == 1) return{ 1 }; // 3
		if (size == 0) return{};
		vector<long long> left(size), right(size);
		long long product = 1;// 1
		for (int i = 0; i<size; i++){
			product *= nums[i];
			left[i] = product;
		}
		product = 1;
		for (int i = size - 1; i>-1; i--){
			product *= nums[i];
			right[i] = product;
		}
		vector<long long> ret(size);
		ret[0] = right[1];// 2
		ret[size - 1] = left[size - 2];
		for (int i = 1; i<size - 1; i++){
			ret[i] = left[i - 1] * right[i + 1];
		}
		return ret;
	}
};


int main(){
	Solution t;
	vector<int> in1 = { 1, 2, 3 };
	t.productExcludeItself(in1);
	return 0;
}