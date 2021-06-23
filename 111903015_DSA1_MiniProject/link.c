#include <stdio.h>
#include <stdlib.h>
#include "link.h"

//INITIALISATION OF LINKED LIST
void init(largeno *l) {
	l->head = NULL;
	l->tail = NULL;
	l->deci = 0;
	l->sign = POSITIVE;
}
//ADDING DIGITS IN THE LINKED LIST
void add_Digit(largeno *l, int x) {
	if( x < 0 || x > 9)
		return;
	node *temp = (node *)malloc(sizeof(node));

	if(temp == NULL)
		return;

	temp->data = x;
	temp->next = NULL;
	if((l->head == NULL) && (l->tail == NULL)) {
		temp->prev = NULL;
		l->head = temp;
		l->tail = temp;
		return;
	}
	temp->prev = l->tail;
	l->tail->next = temp;
	l->tail = temp;
	return;
}
//LENGTH OF LIST
int length(largeno l) {
	node *p;
       	p = l.head;
	int count = 0;
	while(p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}
//ADDING ELEMENTS TO EXTREME LEFT
void append_left(largeno *l, int n) {
	if(n < 0 || n > 9)
		return;
	node *temp = (node *)malloc(sizeof(node));
	if(!temp)
		return;
	temp->data = n;
	temp->prev = NULL;
	if((l->head == NULL) && (l->tail == NULL)){
		temp->next = NULL;
		l->head = l->tail = temp;
		return;
	}
	temp->next = l->head;
	l->head->prev = temp;
	l->head = temp;
	return;
}
//REMOVES ELEMENT
void removes(largeno *l, int pos){
	int i;
	node *p, *temp;
	/* handle errors on position */
	if(pos < 0 || pos >= length(*l))
		return;

	p = l->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(l->head == NULL) {
		return;
	}
	if(length(*l) == 1) {
		l->head = l->tail = p = NULL;
		return;
	}
	if(pos == 0) {
		p->next->prev = NULL;
		l->head = p->next;
		free(p);
		return;
	}
	if(pos == length(*l) - 1) {
		temp = p->next;
		p->next = NULL;
		l->tail = p;
		free(temp);
		return;
	}

	temp = p->next;
	p->next = p->next->next;
	temp->next->prev = p;
	free(temp);
	return;
}
//Function to remove extra zeroes on left of number.
void zero_remove(largeno *l) {
	node *p = l->head;
	int i, len = length(*l);
	for(i = 0; i < len - l->deci -1; i++) {
		if(p->data == 0) {
			l->head = p->next;
			p->next = NULL;
			l->head->prev = NULL;
			free(p);
			p = l->head;
		}else {
			break;
		}
	}
	p = l->tail;
	int decimal = l->deci;
	for(i = 0; i < decimal - 1; i++) {
		if(p->data == 0) {
			l->tail = p->prev;
			p->prev = NULL;
			l->tail->next = NULL;
			free(p);
			p = l->tail;
			l->deci--;

		}else {
			break;
		}
	}
	return;
}
void print(largeno l) {
	node *p;
	int pos = 0;
	zero_remove(&l);
	p = l.head;
	if(l.sign == NEGATIVE) {
		printf("-");
		l.sign = POSITIVE;
	}
	while(p != NULL) {
		pos++;
		if(pos == (length(l) - l.deci + 1))
			printf(".");
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}
