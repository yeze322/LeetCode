#include <unordered_map>
#include <vector>
#include <memory>
#include <thread>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		sum3(nums, 0);
		return ret;
	}
	void sum3(vector<int>& nums, int target){
		int size = nums.size();
		int i = 0;
		while (i < size){
			int a = nums[i];
			int target2 = target - a;
			int j = i + 1;
			int k = size - 1;
			while (j < k){
				int b = nums[j];
				int c = nums[k];
				int sum2 = b + c;
				if (sum2 == target2){
					ret.push_back({ a, b, c });
					while (j < k && b == nums[j])
						j++;
					while (j < k && c == nums[k])
						k--;
				}
				else if (sum2 < target2){//increase
					while (j<k && b == nums[j])
						j++;
				}
				else if (sum2 > target2){
					while (j < k && c == nums[k])
						k--;
				}
			}
			while (i < size &&a == nums[i])
				i++;
		}
	}
private:
	vector<vector<int>> ret;
};

int main(){
	vector<int> nums{ -2, 10, -14, 11, 5, -4, 2, 0, -10, -10, 5, 7, -11, 10, -2, -5, 2, 12, -5, 14, -11, -15, -5, 12, 0, 13, 8, 7, 10, 6, -9, -15, 1, 14, 11, -9, -13, -10, 6, -8, -5, -11, 6, -9, 14, 11, -7, -6, 8, 3, -7, 5, -5, 3, 2, 10, -6, -12, 3, 11, 1, 1, 12, 10, -8, 0, 8, -5, 6, -8, -6, 8, -12, -14, 7, 9, 12, -15, -12, -2, -4, -4, -12, 6, 7, -3, -6, -14, -8, 4, 4, 9, -10, -7, -4, -3, 1, 11, -1, -8, -12, 9, 7, -9, 10, -1, -14, -1, -8, 11, 12, -5, -7 };
	vector<int> num2{ -1, 0, 1, 2, -1, -4 };
	Solution t;
	auto ret = t.threeSum(num2);
	return 0;
}