#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

/* ATTENTION: index calculated from 1, not 0 */
struct course_t{
	int indegree;
	vector<int> nextIndex;
	course_t():indegree(0){};
};
class CourseSet{
public:
	void inputCourse();
	void createCourse();
	bool judgeNoCircle();
	void printCorrect(bool);
private:
	int courseNum;
	vector<course_t> courses;
};

void CourseSet::inputCourse(){
	int relationNum;
	cin>>courseNum>>relationNum;
	createCourse();
	int left,right;
	for(int i=0;i<relationNum;i++){
		scanf("%d %d",&left,&right);
		courses[right].indegree++;
		courses[left].nextIndex.push_back(right);
	}
}

void CourseSet::createCourse(){
	courseNum++;
	courses = vector<course_t>(courseNum);
}

bool CourseSet::judgeNoCircle(){
	vector<int> zero;
	for(int i=0;i<courses.size();i++){
		if(courses[i].indegree == 0){
			zero.push_back(i);
			courseNum--;
		}
	}
	while(!zero.empty()){
		vector<int> nextLevel;
		for(auto x:zero){
			vector<int>& nextIndex = courses[x].nextIndex;
			for(auto x : nextIndex){
				int& indegree = courses[x].indegree;
				indegree--;
				if(indegree == 0){
					courseNum --;
					nextLevel.push_back(x);
				}
			}
		}
		zero = nextLevel;
	}
	return  courseNum==0;
}

void CourseSet::printCorrect(bool judge){
	if(judge)
		printf("Correct\n");
	else
		printf("Wrong\n");
}

int main()
{
	freopen("input.txt","r",stdin);
	int groupN;
	cin>>groupN;
	for(int i=0;i<groupN;i++){
		CourseSet course;
		course.inputCourse();
		bool judge = course.judgeNoCircle();
		course.printCorrect(judge);
	}
	return 0;
}