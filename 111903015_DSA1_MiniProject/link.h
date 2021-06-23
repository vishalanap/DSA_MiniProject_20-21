#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED

#define POSITIVE 1
#define NEGATIVE -1

//Structures for storing long numbers in the form of linked lists.

typedef struct node{
	int data;
	struct node *prev;
	struct node *next;
}node;

typedef struct largeno{
	int sign;
	int deci;
	node *head;
    node *tail;
}largeno;

void init(largeno *l);
void add_Digit(largeno *l, int x);
void print(largeno l);
void destroy(largeno *l);
void append_left(largeno *l, int n);
int length(largeno l);
void removes(largeno *l, int pos);
void zero_remove(largeno *l);

#endif // LINK_H_INCLUDED
