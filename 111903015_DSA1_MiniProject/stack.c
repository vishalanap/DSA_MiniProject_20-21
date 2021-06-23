#include<stdlib.h>
#include "stack.h"

//Stack implementation to store number list.
//Initialisation of Number storing stack
void finit(fstack *s) {
	*s = NULL;
}
//Pushing elements into the stack
void fpush (fstack *s, largeno *t) {
	fstack temp;
	temp = (fnode *)malloc(sizeof(fnode));
	temp->a = t;
	temp->p = *s;
	*s = temp;
}
//Pop out the number from stack
largeno *fpop(fstack *s) {
	largeno *t;
	fstack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}

int fisempty (fstack *s) {
	return *s == NULL;
}
//  Stack implementation to store character Operators.
//Initialisation of stack
void sinit(ostack *s) {
	*s = NULL;
}
//Push operation
void spush (ostack *s, char t) {
	ostack temp;
	temp = (snode *)malloc(sizeof(snode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}
//Pop operation
char spop(ostack *s) {
	char t;
	ostack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}

int sisempty (ostack *s) {
	return *s == NULL;
}
//Returns the character at top
char stop(ostack *s) {
	char ch;
	ch = spop(s);
	spush(s, ch);
	return ch;
}
