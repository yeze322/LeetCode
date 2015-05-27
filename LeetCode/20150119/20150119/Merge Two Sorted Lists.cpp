#include<iostream>
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		if(!l1||!l2)
			return l1?l1:l2;
		bool increase,judge;
		ListNode *head=new ListNode(0);
		ListNode *stick=head;
		ListNode *a=l1,*b=l2;
		//judge if the tow lists are increase
		while(a->next&&a->next->val!=l1->val)
			a=a->next;
		while(b->next&&b->next->val!=l2->val)
			b=b->next;
		increase=(l1->val<=a->val)&&(l2->val<=b->val);
		//now stick
		while(l1&&l2)
		{
			judge=(l1->val>=l2->val)^increase;
			stick->next=judge?l1:l2;
			judge?l1=l1->next:l2=l2->next;
			stick=stick->next;
		}
		stick->next=(l1?l1:l2);
		//return head->next;
		stick=head->next;
		delete(head);head=NULL;
		return stick;
	}
};