#include<iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
//solution 1 ___ use two pointer, their distance is n, when the fast one arrived the end of list, delete the slow one.
public:
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		ListNode *realhead=new ListNode(0);
		realhead->next=head;
		ListNode *fast=realhead,*slow=realhead;
		int count=n;
		while(count--)
		{
			if(fast==NULL)//n>length, return
			{
				delete(realhead);
				realhead==NULL;
				return head;
			}
			fast=fast->next;
		}
		while(fast->next!=NULL)//fast move to the last node
		{
			fast=fast->next;
			slow=slow->next;
		}
		ListNode *record=slow->next->next;
		delete(slow->next);
		slow->next=record;

		record=realhead->next;
		delete(realhead);
		realhead=NULL;
		return record;
		//return realhead->next;
	}
};
