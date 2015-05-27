#include<iostream>
#include<stack>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class SolutionSTK {//用栈实现
public:
	void reorderList(ListNode *head) {
		if(head==NULL||head->next==NULL||head->next->next==NULL)
			return;
		stack<ListNode*> half;
		ListNode *fast=head->next,*slow=head;
		while(fast!=NULL&&fast->next!=NULL)
		{
			fast=fast->next->next;
			slow=slow->next;
		}
		ListNode *record=slow->next;
		slow->next=NULL;//cut the chain
		while(record!=NULL)
		{
			half.push(record);
			record=record->next;
		}
		fast=head;
		while(!half.empty())
		{
			record=fast->next;
			fast->next=half.top();
			half.top()->next=record;
			half.pop();
			fast=record;
		}
	}
};

class Solution {//尝试在O(1)空间实现
public:
	void reorderList(ListNode *head) {
		if(head==NULL||head->next==NULL||head->next->next==NULL)
			return;
		ListNode *fast=head->next,*slow=head;
		while(fast!=NULL&&fast->next!=NULL)
		{
			fast=fast->next->next;
			slow=slow->next;
		}
		ListNode *record=slow->next;
		slow->next=NULL;//cut the chain

		ListNode *q=record->next,*r;
		record->next=NULL;
		//reverse
		while(q!=NULL)
		{
			r=q->next;
			q->next=record;
			record=q;
			q=r;
		}
		fast=head;
		while(record!=NULL)
		{
			q=fast->next;
			r=record->next;
			fast->next=record;
			record->next=q;
			fast=q;
			record=r;
		}
	}
};

int main()
{
	ListNode *head=new ListNode(0);
	ListNode *move=head;
	for(int i=0;i<2;i++)
	{
		move->next=new ListNode(i+1);
		move=move->next;
	}
	Solution yy;
	yy.reorderList(head->next);
	return 0;
}
