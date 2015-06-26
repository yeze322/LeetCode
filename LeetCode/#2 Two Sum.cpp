class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> map;
        for(int i=0;i<nums.size();i++){
            auto iter = map.find(target - nums[i]);
            if(iter != map.end()){
                return {iter->second + 1, i+1};
            }
            map.emplace(nums[i],i);
        }
    }
};

class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> copyNums = nums;
        sort(copyNums.begin(), copyNums.end());
        int head = 0;
        int tail = copyNums.size() - 1;
        int numHead, numTail;
        while (head<tail){
            numHead = copyNums[head];
            while (head<tail && numHead + copyNums[tail] > target)
                tail--;
            if (numHead + copyNums[tail] == target)
                break;
            numTail = copyNums[tail];
            while (head<tail && copyNums[head] + numTail < target)
                head++;
            if (copyNums[head] + numTail == target)
                break;
        }
        auto iter1 = find(nums.begin(), nums.end(), copyNums[head]);
        auto iter2 = find(nums.begin(), nums.end(), copyNums[tail]);
        if (iter1 == iter2){
            iter2 = find(iter1+1,nums.end(),copyNums[tail]);
        }
        return __makeRetVal(iter1-nums.begin(),iter2 - nums.begin());
    }
private:
    vector<int> __makeRetVal(int x, int y){
        return{ min(x, y) + 1, max(x, y) + 1 };
    }
};