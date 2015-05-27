#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    int trap(vector<int>& height) {
		int size = height.size();
        if(size<=2)
            return 0;
        vector<int> peak;
        if(height[0]>=height[1])
            peak.push_back(0);
        for(int i=1;i<size-1;i++){
            int mid = height[i];
            if(height[i-1]<=mid&&mid>=height[i+1])
                peak.push_back(i);
        }
		if(height[size-1]>=height[size-2])
			peak.push_back(size-1);
        int water = 0;
        for(int i=0;i<(int)peak.size()-1;i++){
            int left_index = peak[i];
            int right_index = peak[i+1];
            int wall_height = min(height[left_index],height[right_index]);
            int liter = 0;
            for(int loop=left_index+1;loop<right_index;loop++){
                liter += max(0,wall_height-height[loop]);
            }
			water += liter;
        }
        return water;
    }
};

int main()
{
	int a[] = {2,0,2};
	vector<int> height(a,a+sizeof(a)/sizeof(int));
	Solution t;
	t.trap(height);
	return 0;
}
