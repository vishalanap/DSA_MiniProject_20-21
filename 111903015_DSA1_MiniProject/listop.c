#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "link.h"
#include "listop.h"

//Function to equalise the number of digits after decimal point.
void decimal_equal(largeno *a, largeno *b) {
	int i;
	if(a->deci > b->deci) {
		int diff = a->deci - b->deci;
		for(i = 0; i < diff; i++) {
			add_Digit(b, 0);
			b->deci++;
		}
	}
	else if(b->deci > a->deci) {
		int diff = b->deci - a->deci;
		for(i = 0; i < diff; i++) {
			add_Digit(a, 0);
			a->deci++;
		}
	}
}

//Function to make both of the numbers of same length
void length_equal(largeno *a, largeno *b) {
	int gap;
	gap = length(*a) - length(*b);
	if(gap > 0) {
		int i = 0;
		while(i < gap) {
			append_left(b, 0);
			i++;
		}
	}
	else if(gap < 0) {
		int i = 0;
		gap = -gap;
		while(i < gap) {
			append_left(a, 0);
			i++;
		}
	}
}

//checks whether the number is zero or not.
//Returns 0 if it is zero number.
int zero_number(largeno a) {
	int i, f = 0;
	node *p = a.head;
	for(i = 0; i < length(a); i++) {
		if(p->data != 0)
			f = 1;
		 p = p->next;
	}
	return f;
}

//Make a copy of number into another number i.e. to copy a into b
void copies(largeno *a,largeno *b) {
	int i, num, len;
	len = length(*a);
	node *t1 = a->head;
	for(i = 0; i < len; i++) {
		num = t1->data;
		add_Digit(b, num);
		t1 = t1->next;
	}
	b->deci = a->deci;
	b->sign = a->sign;
	return;
}

//Function for finding the bigger number among the numbers of equal length.
int compare_equal(largeno a, largeno b) {
	length_equal(&a, &b);
	decimal_equal(&a, &b);
	node *p, *q;
	int len;
	int i;
	len = length(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++) {
		if(p->data > q->data)
			return 1;  //for number a greater than number b.
		else if(p->data < q->data)
			return -1;  //for a is less than b.
		p = p->next;
		q = q->next;
	}
	return 0;    //for both numbers are equal.
}
