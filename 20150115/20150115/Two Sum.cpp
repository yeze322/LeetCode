#include<string>
#include<iostream>
using namespace std;
#include<vector>
using std::vector;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        cout<<numbers[0]<<numbers[5];
    }
};
typedef struct student
{
	//int a[10];
	//int data;
	int score;
}stu,*pstu;
void randscore(stu &peo)
{
	peo.score=rand()%100;
}

int comparestu(const void* left,const void* right)
{
	stu sleft=*(pstu)left;
	stu sright=*(pstu)right;
	int sum_left=sleft.score;
	int sum_right=sright.score;
	if(sum_left<sum_right)
		return 1;
	else
		return (sum_left==sum_right?0:-1);
}


int main()
{
	stu class21[10];
	for(int i=0;i<10;i++)
		randscore(class21[i]);
	qsort(&class21,10,sizeof(stu),&comparestu);

	string number="1.2";
	int len=number.length();
	Solution today;
	vector<int> vec;
	int a[6]={1,2,3,4,5,6};
	for(int i=0;i<6;i++)
		vec.push_back(a[i]);
	//Solution::twoSum(a,5);
	for(vector<int>::size_type ix=0;ix!=vec.size();++ix)
		vec[ix]=0;
		//vec.at(5)=1;
	return 0;
}
