#include <stdio.h>
#include <stdlib.h>
#include "xor-list.h"

int next(struct Xorlist* l){
	if((l->p1) == (l->tail)){
		fprintf (stderr, "next Errror message: there isn't Node with this number \n");
		return 1;
	}
	
	struct Node *tmp = l->p1;
	l->p1 = l->p2;
	l->p2 = xor_ptr(tmp, l->p2->ptr);
	++(l->curr_pos);
	return 0;
}

int prev(struct Xorlist* l){
	if(l->p1 == l->head){
		fprintf (stderr, "prev Errror message: there isn't Node with this number \n");
		return 1;
	}
	
	struct Node *tmp = l->p2;
	l->p2 = l->p1;
	l->p1 = xor_ptr(tmp, l->p1->ptr);
	--(l->curr_pos);
	return 0;
}

int move_to(struct Xorlist* l, long long pos){
	// находимся к нужном Node
	if(l->curr_pos == (pos - 1)){
		return 0;
	}
	
	long long dist_from_h = pos - 1;
	long long dist_from_t = l->size - pos;
	
	/* dist_from_c = abs(l->curr_pos - (pos - 1)) */
	long long dist_from_c = (l->curr_pos > (pos - 1)) ? 
				l->curr_pos - (pos - 1) : (pos - 1) - l->curr_pos;
	
	/* min(a, b, c) */
	if(dist_from_h > dist_from_t){
		if(dist_from_c > dist_from_t){
			l->curr_pos = l->size - 1;
			l->p1 = l->tail;
			l->p2 = NULL;
			while(l->curr_pos != (pos - 1)){prev(l);}
		}
		else if((dist_from_c <= dist_from_t)){
			while(l->curr_pos != (pos - 1)) {(l->curr_pos > (pos - 1)) ? prev(l) : next(l);} 
		}
	}
	else if(dist_from_h <= dist_from_t){
		if(dist_from_c > dist_from_h){
			l->curr_pos = 0;
			l->p1 = l->head;
			l->p2 = l->head->ptr;
			while(l->curr_pos != (pos - 1)){next(l);}
		}
		else if(dist_from_c <= dist_from_t){
			while(l->curr_pos != (pos - 1)) {(l->curr_pos > (pos - 1)) ? prev(l) : next(l);} 
		}
	}
	return 0;
}


int insert(struct Xorlist* l, long long pos, long long data){
	if(((pos - 1) > l->size) || ((pos - 1) < 0)){
		fprintf (stderr, "insert Errror message: there isn't Node with this number \n");
		return 1;
	}
	
	struct Node *new_node = malloc(sizeof(struct Node));
	new_node->data = data;
	
	
	if(l->size == 0){
		l->p1 = new_node;
		l->p1->ptr = NULL;
		l->p2 = NULL;
		l->curr_pos = 0;
		
		l->head = l->p1;
		l->tail = l->p1;
	}
	/* infront */
	else if((pos - 1) == 0){
		new_node->ptr = xor_ptr(NULL, l->head);
		l->head->ptr = xor_ptr(new_node, l->head->ptr);
		l->head = new_node;
		
		l->p1 = l->head;
		l->p2 = l->head->ptr;
		l->curr_pos = 0;
	}
	/* to the end */
	else if((pos - 1) == l->size){
		new_node->ptr = xor_ptr(l->tail, NULL);
		l->tail->ptr = xor_ptr(new_node, l->tail->ptr);
		l->tail = new_node;
		
		l->p1 = l->tail;
		l->p2 = NULL;
		
		// т.к. size еще не увеличен
		l->curr_pos = l->size;
	}
	else{
		/* insert between p1 and p2 */
		move_to(l, pos - 1);
		new_node->ptr = xor_ptr(l->p1, l->p2);
		/* tmp1 - Node before p1 */
		struct Node *tmp1 = xor_ptr(l->p1->ptr, l->p2);
		/* tmp2 - Node after p2*/
		struct Node *tmp2 = xor_ptr(l->p2->ptr, l->p1);
		
		l->p1->ptr = xor_ptr(tmp1, new_node);
		l->p2->ptr = xor_ptr(tmp2, new_node);
		
		l->p1 = new_node;
		l->curr_pos = pos - 1;
	}	
	
	++(l->size);
	return 0;
}

int erase(struct Xorlist* l, long long pos){
	if ((pos > l->size) || ((pos -1) < 0)){
		fprintf (stderr, "erase Errror message: there isn't Node with this number \n");
		return 1;
	}

	if(l->size == 1){
		free(l->head);
		l->p1 = l->p2 = l->head = l->tail = NULL;
		l->curr_pos = -1;
	}
	/* from the beginning  */
	else if((pos - 1) == 0){
		l->p1 = l->head->ptr;
		l->p2 = xor_ptr(l->head, l->p1->ptr);
		free(l->head);
		l->p1->ptr = xor_ptr(NULL, l->p2);
		l->head = l->p1;
		l->curr_pos = 0;
	}
	/* from the end */
	else if(pos == l->size){
		l->p2 = l->tail->ptr;
		l->p1 = xor_ptr(l->tail, l->p2->ptr);
		free(l->tail);
		l->p2->ptr = xor_ptr(NULL, l->p1);
		l->tail = l->p2;
		
		l->p1 = l->tail;
		l->p2 = NULL;
		l->curr_pos = l->size - 2;
	}
	else{
		move_to(l, pos);
		//Node before p1
		struct Node *tmp = xor_ptr(l->p1->ptr, l->p2);
		tmp->ptr = xor_ptr(xor_ptr(tmp->ptr, l->p1), l->p2);
		l->p2->ptr = xor_ptr(xor_ptr(l->p2->ptr, l->p1), tmp);
		free(l->p1);
		l->p1 = tmp;
	}
	--(l->size);
	return 0;
}
void delete_xor_list(struct Xorlist* l){
	while(l->size != 0){
		erase(l, 1);
	}
}
void print_xor_list(struct Xorlist* l){
	if(l->size <= 0){
		printf("xor list is empty\n");
		return;
	}
	
	move_to(l, 1);

	while(l->curr_pos < (l->size - 1)){
		printf("%Ld ", l->p1->data);
		next(l);
	}
	printf("%Ld\n", l->p1->data);
}
void init_xor_list(struct Xorlist* l){
	l->p1 = l->p2 = l->head = l->tail = NULL;
	l->size = 0;
	l->curr_pos = -1;
}
struct Node *xor_ptr(struct Node *a, struct Node *b){
	return (struct Node *)((__intptr_t) (a) ^ (__intptr_t) (b));
}
