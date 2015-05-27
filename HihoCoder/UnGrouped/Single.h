#ifndef _SINGLE_H_
#define _SINGLE_H_

#include "common.h"
using std::vector;
class Node{
public:
	void *data;
	Node *next;
	Node(void *data_ptr = NULL,Node *next_ptr = NULL): data(data_ptr),next(next_ptr){}
};

class List{
public:
	List();
	~List();
	int list_ins_head(Node*);
	int list_ins_head(void *data);
	int list_ins_tail(Node*);
	int list_ins_tail(void *data);
	int list_remove_next(Node *);
	int list_remove_bydata(void *);
	int size;
	Node *head;
	Node *tail;
private:
	vector<Node*> remember_to_delete;
};

List::List(){
	size = 0;
	head = new Node();
	tail = head;
}

List::List(){
	Node *temp;
	while(head){
		temp = head;
		head = head->next;
		delete(temp);
	}

}
List::~List(){
	for(vector<Node*>::iterator i = remember_to_delete.begin();i!=remember_to_delete.end();++i){
		delete(*i);
	}
	size = 0;
	head = NULL;
	tail = NULL;
}
/* insert, success return 1 else return 0, complexity O(1) */
int List::list_ins_head(Node *element){
	if (head == NULL||element == NULL)
		return false;
	element->next = head->next;
	head->next = element;
	size += 1;
	if(tail == head)
		tail = element;
	return true;
}

int List::list_head(void *data){
	if (head == NULL)
		return false;
	Node *new_node = new Node(data,head->next);
	remember_to_delete.push_back(new_node);
	head->next = new_node;
	size += 1;
	if(tail == head)
		tail = new_node;
	return true;
}
int List::list_ins_tail(Node *element){
	if (head == NULL||element == NULL)
		return false;
	element->next = NULL;
	tail->next = element;
	tail = element;
	size += 1;
}
int List::list_ins_tail(void *data){
	if(head == NULL)
		return false;
	Node *new_node = new Node(data,NULL);
	remember_to_delete.push_back(new_node);
	tail->next = element;
	tail = element;
	size += 1;
}

/* remove, success return 0 else return -1, complexity O(1) */
int list_rem_next(List *list,Node *element, void **data);
int list_size(const List *list){
	return list->size;
}

/* return head node (pointer) */
Node* list_head(const List *list){
	return list->head;
}

/* return tail node (pointer) */
Node* list_tail(const List *list){
	return list->tail;
}

/* macro, judge if the node is head node */
int list_is_head(List *list,const Node *element){
	if (element == list->head)
		return 1;
	else
		return 0;
}

/* macro, judge if the node is tail node */
int list_is_tail(List *list, const Node *element){
	if (element == list->tail)
		return 1;
	else
		return 0;
}

/* macro, return data saved in element */
void* list_data(const Node *element){
	return element->data;
}

/* marco, return next node (pointer) */
Node* list_next(const Node *element){
	return element->next;
}

#endif // !_SINGLE_H_