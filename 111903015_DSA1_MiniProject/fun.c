#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "link.h"
#include "listop.h"
#include "fun.h"


//ADDITION OPERATION
//return num1+num2
largeno *add(largeno *a, largeno *b) {
	largeno *ans;
	ans = (largeno *)malloc(sizeof(largeno));
	init(ans);
	decimal_equal(a, b);
	if(a->sign != b->sign) {
		if(a->sign == NEGATIVE) {
			a->sign = POSITIVE;
			ans = sub(b, a);
		}
		else if(b->sign == NEGATIVE) {
			b->sign = POSITIVE;
			ans = sub(a, b);
		}
	}
	else if(a->sign == b->sign) {
		int i, n1, n2, carry = 0, sum;
		int len_a, len_b;
		node *t1 = a->tail;
		node *t2 = b->tail;
		len_a = length(*a);
		len_b = length(*b);
		if(a->sign == NEGATIVE)
			ans->sign = NEGATIVE;
		else
			ans->sign = POSITIVE;
		if(len_a >= len_b) {
			for(i = 1; i <= len_b; i++) {
				n1 = t1->data;
				n2 = t2->data;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				append_left(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_a - len_b; i++) {
				n1 = t1->data;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				append_left(ans, sum);
				t1 = t1->prev;
			}
		}else {
			for(i = 1; i <= len_a; i++) {
				n1 = t1->data;
				n2 = t2->data;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				append_left(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_b - len_a; i++) {
				n1 = t2->data;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				append_left(ans, sum);
				t2 = t2->prev;
			}
		}
		ans->deci = a->deci;
		if(carry != 0)
			append_left(ans, carry);
	}
	return ans;
}

//SUBTRACTION OPERATION.
//return num1-num2
largeno *sub(largeno *a, largeno *b) {
	largeno *ans;
	ans = (largeno *)malloc(sizeof(largeno));
	init(ans);
	//decimal digits and length made equal.
	decimal_equal(a, b);
	length_equal(a, b);
	if(a->sign != b->sign) {
		if(a->sign == NEGATIVE) {
			a->sign = POSITIVE;
			ans = add(a, b);
			ans->sign = NEGATIVE;
		}
		else if(b->sign == NEGATIVE) {
			b->sign = POSITIVE;
			ans = add(a, b);
			ans->sign = POSITIVE;
		}
	}
	else if(a->sign == b->sign) {
		if(a->sign == NEGATIVE) {
			a->sign = b->sign = POSITIVE;
			ans = sub(b, a);
		}
		else if(a->sign == POSITIVE) {
			int n1, n2, diff, borrow = 0, i, len;
			node *t1 = a->tail;
			node *t2 = b->tail;
			//length of both numbers is same now because of length_equal.
			len = length(*b);
			if(compare_equal(*a, *b) == 1) {
				for(i = 1; i <= len; i++) {
					n1 = t1->data;
					n2 = t2->data;
					n1 = n1 - borrow;
					if(n1 >= n2) {
						diff = n1 - n2;
						borrow = 0;
						append_left(ans, diff);
					}
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						append_left(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(compare_equal(*a, *b) == -1) {
				ans->sign = NEGATIVE;
				for(i = 1; i <= len; i++) {
					n1 = t1->data;
					n2 = t2->data;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						append_left(ans, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						append_left(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else {
				if(compare_equal(*a, *b) == 0) {
					append_left(ans, 0);
				}
			}
		}
	}
	ans->deci = a->deci;
	return ans;
}

//MULTIPLICATION OPERATION
//returns num1*num2
largeno *mult(largeno *a, largeno *b) {
	largeno *ans = (largeno *)malloc(sizeof(largeno));
	init(ans);
	//checks if any one of the numbers is zero.
	if((zero_number(*a) == 0) || (zero_number(*b) == 0)) {
		add_Digit(ans, 0);
		return ans;
	}
	int len_diff;
	if(a->sign == b->sign) {
		ans->sign = POSITIVE;
		a->sign = b->sign = POSITIVE;
	}
	else {
		ans->sign = NEGATIVE;
		a->sign = b->sign = POSITIVE;
	}
	len_diff = length(*a) - length(*b);
	if(len_diff < 0) {
		ans = mult(b, a);
		return ans;
	}
	else {
		node *t1, *t2;
		int len_a = length(*a);
		int len_b = length(*b);
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_a];
		for(i = 0; i < 2 *len_a; i++)
			tempresult[i] = 0;
		int k = 2 * len_a - 1;
		t2 = b->tail;
		for(i = 0; i < len_b; i++) {
			t1 = a->tail;
			int carry1 = 0, carry2 = 0;
			for(j = k - i; j > len_a - 2; j--) {
				if(t1 != NULL && t2 != NULL) {
					n1 = t1->data * t2->data + carry1;
					t1 = t1->prev;
					carry1 = n1 / 10;
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + carry2;
					carry2 = n2 / 10;
					n2 = n2 % 10;
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}
			tempresult[j] = carry1 + carry2 + tempresult[j];
			len_a--;
			t2 = t2->prev;
		}
		for(i= k; i >= len_a - 1 && i >= 0; i--) {
			append_left(ans, tempresult[i]);
		}
		ans->deci = a->deci + b->deci;
		return ans;
	}
}

//DIVISION OPERATION
//returns num1/num2
largeno *division(largeno *m, largeno *n){
	if(zero_number(*n) == 0) {
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}
	zero_remove(m);
	zero_remove(n);

	int k = m->deci > n->deci ? m->deci : n->deci;
	int i = 0;

	while(i < k) {
		if(m->deci > 0)
			m->deci--;
		else
			add_Digit(m, 0);
		if(n->deci > 0)
			n->deci--;
		else
			add_Digit(n, 0);
		i++;
	}
	i = 9;
	largeno *c, *d, *ans, *q, *pro;
	c = (largeno *)malloc(sizeof(largeno));
	d = (largeno *)malloc(sizeof(largeno));
	ans = (largeno *)malloc(sizeof(largeno));
	pro = (largeno *)malloc(sizeof(largeno));
	q = (largeno *)malloc(sizeof(largeno));

	init(ans);
	init(c);
	init(q);
	init(d);
	if(m->sign == n->sign) {
		q->sign = POSITIVE;
		m->sign = n->sign = POSITIVE;
	}
	else {
		q->sign = NEGATIVE;
		m->sign = n->sign = POSITIVE;
	}
	node *p = m->head;
	int x = p->data ;
	add_Digit(d, x);
	while(q->deci < SCALE){
		while(i >= 0){
			append_left(c, i);
			pro = mult(n, c);
			ans = sub(d, pro);
			if(ans->sign != NEGATIVE) {
				add_Digit(q, i);
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			else{
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--;
			}
		}
		d = ans;
		if(p->next != NULL) {
			p = p->next;
			x = p->data;
			add_Digit(d, x);
		}
		else{
			q->deci++;
			add_Digit(d, 0);
		}
		i = 9;
		node *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	q->deci--;
	return q;
}

//MODULUS OPERATION
//returns reminder
largeno *modulus(largeno *a, largeno *b) {
	if(zero_number(*b) == 0) {
		printf("ERROR : Modulo by Zero is not allowed.\n");
		return NULL;
	}
	int tempsign;
	if(a->sign == NEGATIVE) {
		tempsign = NEGATIVE;
		a->sign = b->sign = POSITIVE;
	}
	else {
		tempsign = POSITIVE;
		a->sign = b->sign = POSITIVE;
	}
	decimal_equal(a, b);
	int a_deci = a->deci;
	largeno *ans = (largeno *)malloc(sizeof(largeno));
	largeno *temp = (largeno *)malloc(sizeof(largeno));
	init(ans);
	init(temp);
	temp = division(a, b);
	if(temp->deci != 0) {
		int pos = length(*temp) - 1;
		while(temp->deci != 0) {
			removes(temp, pos);
			temp->deci--;
			pos--;
		}
	}
	temp = mult(temp, b);
	ans = sub(a, temp);
	ans->sign = tempsign;
	ans->deci = a_deci;
	return ans;
}

//POWER OF THE NUMBERS
//returns a^b
largeno *power(largeno *a, largeno *b) {
	largeno *ans = (largeno *)malloc(sizeof(largeno));
	init(ans);
	add_Digit(ans, 1);
	largeno *n1 = (largeno *)malloc(sizeof(largeno));
	init(n1);
	add_Digit(n1, 1);
	largeno *n2 = (largeno *)malloc(sizeof(largeno));
	init(n2);
	add_Digit(n2, 2);
	largeno *n0 = (largeno *)malloc(sizeof(largeno));
	init(n0);
	add_Digit(n0, 0);

	largeno *c = (largeno *)malloc(sizeof(largeno));
	init(c);
	copies(b, c);
	int sign = a->sign;
	if(b->sign == POSITIVE) {
		while(zero_number(*c) != 0) {
			ans = mult(ans, a);
			c = sub(c, n1);
		}
	}
	else if(b->sign == NEGATIVE) {
		while(zero_number(*c) != 0) {
			ans = division(ans, a);
			c = add(c, n1);
		}
	}
	a->sign = sign;
	if(a->sign == NEGATIVE) {
		largeno *temp;
		temp = modulus(b, n2);
		if(compare_equal(*temp, *n0) == 0)
			ans->sign = POSITIVE;
		else
			ans->sign = NEGATIVE;
	}
	return ans;
}

//SQUARE ROOT OF THE NUMBER
//code is not working:
/*largeno *square_root(largeno *a){
    if(a->sign = NEGATIVE){
        printf("Invalid Input);
    }
    else{
        largeno *ans=(largeno *)malloc(sizeof(largeno));
        largeno *c=(largeno *)malloc(sizeof(largeno));
        init(ans);
        init(c);
        add_Digit(ans,0);
        largeno x;
        init(x);
        add_Digit(x,1);

        while(compare_equal(*a,*ans)==1){
            c=mult(ans,ans);
            if(compare_equal(*c,*a)==1){
                ans=sub(ans,x);
                return ans;
            }
        }
    }
}*/

