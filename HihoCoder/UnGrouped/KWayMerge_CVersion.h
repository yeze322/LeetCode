#include<stdio.h>
#include<stdlib.h>
struct ListNode {
	int val;
	struct ListNode *next;
};

void MIN_HEAP_SORT(struct ListNode **lists, int index_i,int size)
{
	int left = index_i*2 + 1;
	int right= index_i*2 + 2;
	if(left>=size)
		return;
	int min;
	if(right>=size)
		min = left;
	else
		min = lists[left]->val<lists[right]->val?left:right;
	if(lists[index_i]->val>lists[min]->val){
		struct ListNode *temp = lists[index_i];
		lists[index_i] = lists[min];
		lists[min] = temp;
		MIN_HEAP_SORT(lists,min,size);
	}
}

void BuildHeap(struct ListNode **lists,int size)
{
	for(int i=(size-1)/2;i>=0;--i){
		MIN_HEAP_SORT(lists,i,size);
	}
}

struct ListNode *mergeKLists(struct ListNode *lists[], int k) {
	if(k==0)
		return NULL;//1
	struct ListNode *head = (struct ListNode*)calloc(1,sizeof(struct ListNode));
	struct ListNode *int_max = (struct ListNode*)calloc(1,sizeof(struct ListNode));
	int_max->val = INT_MAX;
	int_max->next = NULL;
	struct ListNode *travel = head;
	for(int i=0;i<k;++i){
		if(lists[i]==NULL)
			lists[i] = int_max;
	}//remove thos NULL ptr
	BuildHeap(lists,k);//3
	while(lists[0]!=int_max){
		travel->next = lists[0];
		travel = lists[0];
		lists[0] = lists[0]->next;
		if(lists[0]==NULL)
			lists[0] = int_max;
		MIN_HEAP_SORT(lists,0,k);
	}
	travel->next = NULL;
	return head->next;
}