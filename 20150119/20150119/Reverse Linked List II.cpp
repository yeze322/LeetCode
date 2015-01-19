#include<stdio.h>
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class SolutionAC {
public:
	ListNode *reverseBetween(ListNode *head, int m, int n) {//不让取空间！ER.实际上是自己不会用构造函数
		ListNode *start=new ListNode(0);//create a real head myself
		start->next=head;//head here means the first node! Misunderstaning.
		ListNode *startrecord=start;
		for(int i=0;i<m-1;i++)
			start=start->next;
		ListNode *p,*q,*r;
		p=start->next;
		q=p->next;
		if(q==NULL)
			return head;
		r=q->next;
		for(int i=m;i<n;i++)
		{
			q->next=p;
			p=q;
			q=r;
			if(r==NULL)
				break;
			r=r->next;
		}
		start->next->next=q;
		start->next=p;
		start=startrecord->next;
		delete(startrecord);
		startrecord=NULL;
		return start;
	}
};


class Solutionexodia {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        ListNode ** sub_head = &head;
        ListNode * oper0 = head, * oper1 = head, * oper2 = head; 
        for (int i =0; i < m-1; i++) {
            sub_head = &((*sub_head)->next);
        }
        oper0 = *sub_head;
        oper1 = oper0;
        oper2 = oper1->next;
        for( int i = 0; i < n-m; i++) {
            oper0 = oper1;
            oper1 = oper2; 
            oper2 = oper2->next;
            oper1->next = oper0; 
            }
        (*sub_head)->next = oper2;
        *sub_head = oper1;
        return head;
    }
};


//class SolutionGiveUp {//想不加头结点，不过这么做太让人困惑了PASS
//public:
//	ListNode *reverseBetween(ListNode *head, int m, int n) {//不让取空间！ER
//		ListNode *start=head;
//		ListNode *headcpy=head;
//		for(int i=1;i<m;i++)
//			start=start->next;
//		ListNode *startcpy=start;
//		ListNode *p,*q,*r;
//		m==1?p=start:p=start->next;
//		ListNode *startrecord=p;
//		q=p->next;
//		if(q==NULL)
//			return head;
//		r=q->next;
//		for(int i=m;i<n;i++)
//		{
//			q->next=p;
//			p=q;
//			q=r;
//			if(r==NULL)
//				break;
//			r=r->next;
//		}
//		startrecord->next=q;
//		if(start==head)
//			return p;
//		startcpy->next=p;
//		return head;
//	}
//};

int main()
{
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int k=8;
	ListNode *ls[10];
	ListNode *head=&ListNode(0);
	for(int i=0;i<k;i++)
	{
		ls[i]=new ListNode(i);
		ls[i]->val=i+1;
		//ls[i-1].next=&ls[i];
	}
	head->next=ls[0];
	//ls[k]->next=NULL;
	//ls[k]->val=a[k];


	SolutionAC yy;
	ListNode *newnode=yy.reverseBetween(ls[0],2,5);
	return 0;
}
