#ifndef GET_TOKENS_H_INCLUDED
#define GET_TOKENS_H_INCLUDED

#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400

//Structure for tokens:
typedef struct token{
	int type;
	largeno *num;
	char op;
}token;

/*enumeration is user defined data type which is used to
assign names to constants which makes a program easy to read and maintain*/
enum state { NUMBER, DOT, OPERAT , FINISH, ERROR, SPACE };

token get_token(char *expr, int *reset);

#endif // GET_TOKENS_H_INCLUDED
