#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "plot.h"

/*
Grammar:

<expr>   ::= <term>
           | <term> ('+'|'-') <expr>
<term>   ::= <factor>
           | <factor> ('*'|'/') <term>
<factor> ::= <number>
           | '(' <expr> ')'
<number> ::= <sequence of digits 0-9>

*/

typedef enum {
	NUM,
	ADD,
	SUB,
	MUL,
	DIV
} node_type;

struct parsenode;
typedef struct parsenode parsenode_t;

struct parsenode
{
	node_type type;
	int value;
	parsenode_t *left;
	parsenode_t *right;
};

static void fatal_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

static char *concatenate(int nstrings, char **strings)
{
	char *s, *result;
	int i, n = 1;
	for (i = 0; i < nstrings; i++)
		n += strlen(strings[i]);
	result = s = calloc(n + nstrings, 1);
	if (s == NULL)
		fatal_error("out of memory");
	for (i = 0; i < nstrings; i++)
	{
		if (i > 0)
			*s++ = ' ';
		strcpy(s, strings[i]);
		while (*s)
			s++;
	}
	return result;
}

static parsenode_t *newnode(node_type type, int value, parsenode_t *left, parsenode_t *right)
{
	parsenode_t *node = calloc(sizeof(parsenode_t), 1);
	if (node == NULL)
		fatal_error("out of memory");
	node->type = type;
	node->value = value;
	node->left = left;
	node->right = right;
	return node;
}

typedef struct context
{
	char *input;
	char *p;
} context_t;

static parsenode_t *parse_expr(context_t *context);
static parsenode_t *parse_term(context_t *context);
static parsenode_t *parse_factor(context_t *context);
static parsenode_t *parse_number(context_t *context);

static void skipwhitespace(context_t *context)
{
	while (context->p[0] == ' ')
		context->p++;
}

/*
<expr>   ::= <term>
           | <term> ('+'|'-') <expr>
*/
static parsenode_t *parse_expr(context_t *context)
{
	parsenode_t *t2, *t = parse_term(context);
	if (context->p[0] == '+')
	{
		context->p++;
		t2 = parse_expr(context);
		return newnode(ADD, 0, t, t2);
	}
	else if (context->p[0] == '-')
	{
		context->p++;
		t2 = parse_expr(context);
		return newnode(SUB, 0, t, t2);
	}
	return t;
}

/*
<term>   ::= <factor>
           | <factor> ('*'|'/') <term>
*/
static parsenode_t *parse_term(context_t *context)
{
	parsenode_t *f2, *f = parse_factor(context);
	if (context->p[0] == '*')
	{
		context->p++;
		f2 = parse_term(context);
		return newnode(MUL, 0, f, f2);
	}
	else if (context->p[0] == '/')
	{
		context->p++;
		f2 = parse_term(context);
		return newnode(DIV, 0, f, f2);
	}
	return f;
}

/*
<factor> ::= <number>
           | '(' <expr> ')'
*/
static parsenode_t *parse_factor(context_t *context)
{
	skipwhitespace(context);
	if (context->p[0] == '(')
	{
		parsenode_t *e;
		context->p++;
		e = parse_expr(context);
		skipwhitespace(context);
		if (context->p[0] == ')')
			context->p++;
		else
			fatal_error("Missing )");
		skipwhitespace(context);
		return e;
	}
	else
	{
		return parse_number(context);
	}
}

static parsenode_t *parse_number(context_t *context)
{
	char *q;
	int value;

	skipwhitespace(context);
	q = context->p;
	while (*q >= '0' && *q <= '9')
	{
		q++;
	}
	if (context->p == q)
	{
		printf("Not a number: %s\n", context->p);
		fatal_error("Exiting");
	}
	value = atoi(context->p);
	context->p = q;
	skipwhitespace(context);
	return newnode(NUM, value, NULL, NULL);
}

static parsenode_t *parse(char *input)
{
	parsenode_t *result;
	context_t context;
	context.input = input;
	context.p = input;
	result = parse_expr(&context);
	if (*context.p)
	{
		printf("Unparsed input: \"%s\"\n", context.p);
		fatal_error("Exiting");
	}
	return result;
}

static int evaluate(parsenode_t *expr)
{
	int n;
	switch (expr->type)
	{
	case NUM:
		return expr->value;
	case MUL:
		return evaluate(expr->left) * evaluate(expr->right);
	case DIV:
		n = evaluate(expr->right);
		if (n == 0)
			fatal_error("Division by zero");
		return evaluate(expr->left) / n;
	case ADD:
		return evaluate(expr->left) + evaluate(expr->right);
	case SUB:
		return evaluate(expr->left) - evaluate(expr->right);
	}
	fatal_error("Unknown node type");
	return 0;
}

char *strnode(char *name, parsenode_t *n)
{
	switch (n->type)
	{
	case NUM:
		sprintf(name, "%d", n->value);
		break;
	case MUL:
		sprintf(name, "*");
		break;
	case DIV:
		sprintf(name, "/");
		break;
	case ADD:
		sprintf(name, "+");
		break;
	case SUB:
		sprintf(name, "-");
		break;
	}

	return name;
}

void _calc_print(plot_t *plot, parsenode_t *current)
{
	char from[128];
	char to[128];

	if (current == NULL)
		return;

	strnode(from, current);
	if (current->left != NULL)
	{
		plot_addlink2(plot, current, current->left, from, strnode(to, current->left));
	}

	if (current->right != NULL)
	{
		plot_addlink2(plot, current, current->right, from, strnode(to, current->right));
	}

	_calc_print(plot, current->left);
	_calc_print(plot, current->right);
}

void calc_print(parsenode_t *parse)
{
	plot_t *plot;

	plot = plot_create("calc");
	_calc_print(plot, parse);
	plot_doplot(plot);
}

int main(int argc, char **argv)
{
	char *input = concatenate(argc - 1, argv + 1);
	parsenode_t *expr = parse(input);
	int result = evaluate(expr);
	printf("%s = %d\n", input, result);
	calc_print(expr);

	free(input);
	return 0;
}