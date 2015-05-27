#include "Single.h"


/* constructor */
void list_init(List *list, void (*destroy)(void *data));
/* destructor */
void list_destroy(List *list);
/* insert, success return  else return -1, complexity O(1) */
int list_ins_next(List *list,Node *element,const void *data);
/* remove, success return 0 else return -1, complexity O(1) */
int list_rem_next(List *list,Node *element, void **data){

}

/* return elements' number */
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