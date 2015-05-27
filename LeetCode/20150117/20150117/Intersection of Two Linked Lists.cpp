#include<stack>
#include<iostream>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		int count=0;
		ListNode *p=headA;
		ListNode *q=headB;
		while(headA!=nullptr)
		{
			count++;
			headA=headA->next;
		}
		while(headB!=nullptr)
		{
			count--;
			headB=headB->next;
		}
		headA=p;headB=q;
		if(count>0)//A is longer
			while(count--)
				headA=headA->next;
		else//B is longer
			while(count++)
				headB=headB->next;
		while(headA!=nullptr&&headB!=nullptr&&headA!=headB)
		{
			headA=headA->next;
			headB=headB->next;
		}
		return (headA==nullptr?headA:headB);
	}
};

class Solutionbad {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		stack<ListNode*> chain1,chain2;
		while(headA!=NULL)
		{
			chain1.push(headA);
			headA=headA->next;
		}
		while(headB!=NULL)
		{
			chain2.push(headB);
			headB=headB->next;
		}
		ListNode* record=nullptr;
		while(!chain1.empty()&&!chain2.empty()&&chain1.top()==chain2.top())
		{
			record=chain1.top();
			chain1.pop();
			chain2.pop();
		}
		return record;
	}
};