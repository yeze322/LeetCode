#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
	/**
	* @param points an array of point
	* @return an integer
	*/
	int maxPoints(vector<Point>& points) {
		// Write your code here
		int size = points.size();
		if (size <= 2) return size;
		vector<double> kLists;
		unordered_map<double, int> counter;
		int max = 0;
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++){
				if (i == j) continue;
				double k = calcuK(points[i], points[j]);
				if (counter.find(k) != counter.end())
					counter[k]++;
				else
					counter.emplace(k, 1);
			}
			for (auto iter = counter.begin(); iter != counter.end(); ++iter){
				max = iter->second+1 > max ? iter->second+1 : max;
			}
			counter.clear();
		}
		return max;
	}
private:
	double calcuK(const Point& a, const Point& b){
		int denominator = b.y - a.y;
		int numerator = b.x - a.x;
		if (numerator == 0) return INT_MAX;
		return (double)denominator/numerator;
	}
};


int main(){
	vector<Point> input{ { 1, 2 }, { 3, 6 }, { 0, 0 }, { 1, 3 } };
	vector<Point> input2{ { 0, 0 }, { 1, 1 }, { 1, -1 } };
	Solution t;
	t.maxPoints(input);
	t.maxPoints(input2);
	return 0;
}