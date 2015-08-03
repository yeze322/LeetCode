#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	/*
	* @param numbers : An array of Integer
	* @param target : target = numbers[index1] + numbers[index2]
	* @return : [index1+1, index2+1] (index1 < index2)
	*/
	vector<int> twoSum(vector<int> &nums, int target) {
		// write your code here
		unordered_map<int, vector<int>> map;
		for (int i = 0; i < nums.size(); i++){
			if (map.find(nums[i]) == map.end()){
				map[nums[i]].push_back(i);
			}
			else{
				map[nums[i]] = { i };
			}
		}
		for (int i : nums){
			auto num1Iter = map.find(i);
			if (num1Iter == map.end())
				continue;
			auto num2Iter = map.find(target - i);
			if (num2Iter != map.end() && num2Iter != num1Iter){
				vector<int> ret;
				ret.push_back(num1Iter->second[0] + 1);
				ret.push_back(num2Iter->second[0] + 1);
				sort(ret.begin(), ret.end());
				return ret;
			}
		}
		return{ 0, 0 };
	}
};

int main(){
	Solution t;
	auto ret = t.twoSum(vector<int>{ 1, 0, -1 }, 0);
	return 0;
}