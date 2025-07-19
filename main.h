#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_TOKENS 128
// TODO: Make a mini tokenizer
// TODO: Make parser to parse the tokens
typedef enum TType {
	PLUS = 0,
	MINUS,
	MUL,
	DEV,
	NUMBER,
	OPAREN,
	CPAREN,
	UNKNOWN,
	COUNT,
	END
} TType;

typedef enum NodeType {
	NUMBER_NODE,
	BINOP
} NodeType;
typedef struct Node Node;
typedef struct Node {
	NodeType type;
	int   value;
	union {
		int value;
		struct {
            char operator;
            Node* left;
            Node* right;
        } binary_op;
    } data;
} Node;

typedef struct Token {
	TType type;
	union {
		char  operator;
		char  lexeme[128]; // for the number
	} data;
} Token;

typedef struct TokenScanner
{
	Token *tokens;
	size_t pos;
	size_t end;
} TokenScanner;

void  tokenize(TokenScanner *scanner, char *src);
char  *type_asstr(int t);
void  *allocate(size_t size);

Node  *parse(TokenScanner *scanner);
Node  *parse_term(TokenScanner *scanner); // + | -
Node  *parse_factor(TokenScanner *scanner); // Number | ( | )
Node  *parse_expression(TokenScanner *scanner); // Expr
//
void print_ast(Node *root, int level);

int eval(Node *tree);
#endif // !MAIN_H
