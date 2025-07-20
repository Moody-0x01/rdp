#include <parser.h>

int main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	char *expr = av[1];
	TokenScanner scanner = {0};
	printf("expr: %s\n", expr);
	tokenize(&scanner, expr);
	for (size_t i = 0; i < scanner.end; ++i)
		printf("%s(%s) ", type_asstr(scanner.tokens[i].type), scanner.tokens[i].data.lexeme);
	printf("\n");
	Node *root = parse(&scanner);
	printf("Parsed with success\n");
	print_ast(root, 0);

	int v = eval(root);
	printf("Final: %i\n", v);
	free(scanner.tokens);
	return (0);
}
