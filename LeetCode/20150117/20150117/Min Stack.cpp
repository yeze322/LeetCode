#include<stack>
using namespace std;
//错误原因——等于没写，那么当有相等的数出栈，会导致minstack中的记录也出栈！
class MinStackRA {
public:
	void push(int x) {
		if(data.empty()&&mins.empty())
			mins.push(x);
		data.push(x);
		if(x<mins.top())
			mins.push(x);
	}
	void pop() {
		if(data.top()==mins.top())
			mins.pop();
		data.pop();
	}
	int top() {
		/*if(data.empty())
			return -1;*/
		return data.top();
	}

	int getMin() {
		/*if(mins.empty())
			return -1;*/
		return mins.top();
	}
private:
	stack<int> data;
	stack<int> mins;
};
class MinStackAC {
public:
	void push(int x) {
		if(data.empty()||x<=mins.top())
			mins.push(x);
		data.push(x);
	}
	void pop() {
		if(data.top()==mins.top())
			mins.pop();
		data.pop();
	}
	int top() {
		return data.top();
	}

	int getMin() {
		return mins.top();
	}
private:
	stack<int> data;
	stack<int> mins;
};
int main()
{
	MinStackAC minstack;
	int a[10]={10,2,8,7,5,1,4,9,7};
	minstack.push(2147483646);
	minstack.push(1);
	minstack.push(0);
	minstack.getMin();
	minstack.pop();
	minstack.getMin();
	
	return 0;
}