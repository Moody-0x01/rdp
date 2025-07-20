#include <parser.h>

// Expression → Term (('+' | '-') Term)*
// Term       → Factor (('*' | '/') Factor)*
// Factor     → Number | '(' Expression ')'

Node *create_num_node(int value)
{
	Node *node = allocate(sizeof(Node));
	if (!node)
		return (NULL);
	node->type = NUMBER_NODE;
	node->data.value = value;
	return (node);
}

Node *create_op_node(char op, Node *left, Node *right)
{
	Node *node = allocate(sizeof(Node));
	if (!node)
		return (NULL);
	node->type = BINOP;
	node->data.binary_op.left = left;
	node->data.binary_op.right = right;
	node->data.binary_op.operator = op;
	return (node);
}

Node  *parse_term(TokenScanner *scanner) // + | -
{
	Node *left;
	Node *right;

	left = parse_factor(scanner);
	while ((scanner->pos < scanner->end) && ((scanner->tokens[scanner->pos].type == DEV)
		|| scanner->tokens[scanner->pos].type == MUL))
	{
		char operator = scanner->tokens[scanner->pos].data.operator;
		scanner->pos++;
		right = parse_factor(scanner);
		left = create_op_node(operator, left, right);
	}
	return (left);
}

Node  *parse_factor(TokenScanner *scanner) // Number | ( | )
{
	Node *node;

	node = NULL;
	switch (scanner->tokens[scanner->pos].type)
	{
		case NUMBER: {
			node = create_num_node(atoi(scanner->tokens[scanner->pos].data.lexeme));
			scanner->pos++;
			return (node);
		} break;
		case OPAREN: {
			scanner->pos++; // Jump (
			{
				node = parse_expression(scanner);
			}
			if (scanner->tokens[scanner->pos].type != CPAREN)
			{
				fprintf(stderr, "expected ) but found %s\n", type_asstr(scanner->tokens[scanner->pos].type));
				exit(1);
			}
			scanner->pos++; // Jump )
			return (node);
		} break;
		default: {};
	}
	fprintf(stderr, "expected NUMBER or OPAREN(\'(\') but found %s\n", type_asstr(scanner->tokens[scanner->pos].type));
	exit(1);
	return (NULL);
}

Node  *parse_expression(TokenScanner *scanner)
{
	Node *left;
	Node *right;

	left = parse_term(scanner);
	while ((scanner->pos < scanner->end) && ((scanner->tokens[scanner->pos].type == PLUS) || scanner->tokens[scanner->pos].type == MINUS))
	{
		char operator = scanner->tokens[scanner->pos].data.operator;
		scanner->pos++;
		if (scanner->pos == scanner->end)
		{
			// TODO: there is a - or a + that expected a number but a number was not found
			fprintf(stderr, "expected a number or an OPAREN but found %s\n", type_asstr(scanner->tokens[scanner->pos].type));
			exit(1);
		}
		right = parse_term(scanner);
		left = create_op_node(operator, left, right);
	}
	return (left);
}

Node  *parse(TokenScanner *scanner)
{
	return (parse_expression(scanner));
}

void print_ast(Node *root, int level)
{
	if (root == NULL)
		return ;
	if (root->type == NUMBER_NODE)
	{
		printf("%*i\n", level, root->data.value);
	} else {
		printf("%*c\n", level, root->data.binary_op.operator);
		print_ast(root->data.binary_op.left, level + 1);
		print_ast(root->data.binary_op.right, level + 1);
	}
}
