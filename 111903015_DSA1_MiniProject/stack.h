#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "link.h"

//Stack for storing number entered in the form of list.
typedef struct fnode {
	largeno *a;
	struct fnode *p;
}fnode;

typedef fnode *fstack;
void finit(fstack *s);
void fpush(fstack *s, largeno *a);
largeno *fpop(fstack *s);
int fisempty(fstack *s);

// Stack for storing character Operators.
typedef struct snode {
	char a;
	struct snode *p;
}snode;

typedef snode *ostack;
void sinit(ostack *s);
void spush(ostack *s, char t);
char spop(ostack *s);
int sisempty(ostack *s);
char stop(ostack *s);

#endif // STACK_H_INCLUDED
