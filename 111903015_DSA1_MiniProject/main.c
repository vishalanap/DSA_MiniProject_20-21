#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"
#include "fun.h"
#include "link.h"
#include "listop.h"
#include "get_tokens.h"

/*Name : Anap Vishal Bhausaheb
Mis : 111903015
Batch : S1*/

//Function for checking precedence of different operators.
int precedance(char o) {
	switch(o) {
		case ')' :
			return 10;
			break;
		case '+' :
		case '-' :
			return 20;
			break;
		case '*' :
		case '/' :
			return 30;
			break;
		case '%' :
        case '^' :
        //case 'R' :
			return 40;
			break;
		case '(' :
			return 50;
			break;
		default :
			return 60;
			break;
	}
	return 60;
}

//Function for Evaluation of Infix Expression:
largeno *infix(char *exp) {
	token t;
	char curr_op, prev_op, ch;
	int cnt_ob = 0, cnt_cb = 0, reset  = 1, curr, prev;
	largeno *a, *b, *z;
	a = (largeno *)malloc(sizeof(largeno));
	b = (largeno *)malloc(sizeof(largeno));
	z = (largeno *)malloc(sizeof(largeno));
	init(a);
	init(b);
	init(z);
	fstack fs;
	ostack os;
	finit(&fs);
	sinit(&os);
	prev = ERR;
	while(1) {
		t = get_token(exp, &reset);
		curr = t.type;
		if(curr == prev && prev == OPERAND) {
			//return INT_MIN;
			return NULL;
		}
		if(t.type == OPERAND){
			fpush(&fs, t.num);
		}
		else if(t.type == OPERATOR){
			curr_op = t.op;
			if(curr_op == '(')
				cnt_ob++;
			if(curr_op == ')')
				cnt_cb++;
			if(cnt_cb > cnt_ob)
				//return INT_MIN;
				return NULL;
			if(!sisempty(&os)) {
				prev_op = stop(&os);
				//To find out the Square Root of the number
				/*switch(prev_op) {
					case 'R':
						spop(&os);
						a = fpop(&fs);
						z = square_root(a);
						fpush(&fs, z);
						//spush(&os, curr_op);
						break;
					default :
						break;

				}*/
				while(precedance(prev_op) >= precedance(curr_op)) {
					prev_op = spop(&os);
					if(!fisempty(&fs)) {
						a = fpop(&fs);
					}
					else{
						spush(&os, prev_op);
						break;
					}
					if(!fisempty(&fs)) {
						b = fpop(&fs);
					}
					else {
						spush(&os, prev_op);
						fpush(&fs, a);
						break;
					}
					if((prev_op == '/' || prev_op == '%') && a == 0) {
                                                fprintf(stderr, "Mathematical error\n");
                                                //return INT_MIN;
                                        	return NULL;
                                        }
					switch (prev_op) {
						case '+' :
							//z = b + a;
							z = add(a, b);
							fpush(&fs, z);
							break;
						case '-' :
							//z = b - a;
							z = sub(b, a);
							fpush(&fs, z);
							break;
						case '*' :
							//z = b * a;
							z = mult(b, a);
							fpush(&fs, z);
							break;
						case '/' :
							//z = b / a;
							z = division(b, a);
							fpush(&fs, z);
							break;
						case '%' :
							//z = b % a;
							z = modulus(b, a);
							fpush(&fs, z);
							break;
                        case '^' :
                            //z = b ^ a;
                            z = power(b, a);
							fpush(&fs, z);
							break;
						case '(' :
							spush(&os, prev_op);
							fpush(&fs, b);
							fpush(&fs, a);
							break;
						default :
							//return INT_MIN;
							return NULL;
					}
					if (prev_op == '(')
						break;
					if(!sisempty(&os))
						prev_op = stop(&os);
					else
						break;
				}
			}
			spush(&os, t.op);
			if(curr_op == ')') {
				ch = spop(&os);
				cnt_cb--;
				ch = spop(&os);
				cnt_ob--;
			}
		}
		else if(t.type == END) {
			if(cnt_ob == cnt_cb) {
				while(!sisempty(&os)) {
					if(!fisempty(&fs)) {
						a = fpop(&fs);
					}
					else {
						fprintf(stderr, "Less Number Of Operands\n");
                                                //return INT_MIN;
                                                return NULL;
					}
					if(!fisempty(&fs)) {
						b = fpop(&fs);
					}
					else {
						fprintf(stderr, "Less Number Of Operands\n");
                                                //return INT_MIN;
                                                return NULL;
					}
					ch = spop(&os);
					if((ch == '/' || ch == '%') && a == 0) {
						fprintf(stderr, "Mathematical error\n");
						//return INT_MIN;
						return NULL;
					}
					switch(ch) {
						case '+' :
							z = add(b, a);
							fpush(&fs, z);
							break;
						case '-' :
							z = sub(b, a);
							fpush(&fs, z);
							break;
						case '*' :
							z = mult(b, a);
							fpush(&fs, z);
							break;
						case '/' :
							z = division(b, a);
							fpush(&fs, z);
							break;
						case '%' :
							z = modulus(b, a);
							fpush(&fs, z);
							break;
                        case '^' :
                            z = power(b,a);
                            fpush(&fs, z);
                            break;
						default :
							//return INT_MIN;
							return NULL;
					}
				}
			}
			else {
				fprintf(stderr, "Error in Expression\n");
				//return INT_MIN;
				return NULL;
			}
			if(!fisempty(&fs)){
				z = fpop(&fs);
				if(fisempty(&fs))
					return z;
				else {
                                	fprintf(stderr, "Less Number Of Operators\n");
                                	//return INT_MIN;
                                	return NULL;
                        	}
			}
			else {
				fprintf(stderr, "Less Number Of Operands\n");
				return NULL;
			}
		}
		else if(t.type == ERR) {
			return NULL;
		}
		prev = curr;
	}
}

//Function to modify the expression and to make it suitable for infix evaluation
void modification(char *expression) {
	int i;
	for(i = 0; i < strlen(expression); i++) {
		if(expression[i] == '(') {
			int j = 1;
			while(1) {
				if(expression[i + j] == ' ') {
					j++;
				}
				else {
					break;
				}
			}
			if((expression[i + j] == '-') || (expression[i + j] == '+')) {
				int temp = strlen(expression);
				while(temp >= i + j) {
					expression[temp + 1] = expression[temp];
					temp--;
				}
				expression[i + j] = '0';
			}
		}
	}
}

//Function used to read the expression entered by user:
int read_expr(char *expression, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			expression[i++] = '\0';
			return i - 1;
		}
		else
			expression[i++] = ch;
	}
	expression[len - 1] = '\0';
	return len - 1;
}
int main(int argc, char *argv[]) {
    printf("\nMis - 111903015\n\n");
    printf("************ Binary Calculator ************");
    printf("\n\nThe Calculator allows you to perform basic operations in expression :\n1.Addition \n2.Subtraction \n3.Multiplication \n4.Division \n5.Moduluds \n6.Power.");
    printf("\n\nEnter Your Expressions:\n\n");

    //Input From User
	largeno *r;
	char expression[3000];
	while(read_expr(expression, 3000)) {
		modification(expression);
		r = infix(expression);
		if(r != NULL)
			print(*r);
		else
			fprintf(stderr, "Error in Expression\n");
	}
	return 0;
}
