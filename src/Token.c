#include <parser.h>

void *allocate(size_t size)
{
	void *p;

	printf("Tryna allocate: %zu\n", size);
	p = malloc(size);
	if (!p)
		return p;
	memset(p, 0, size);
	return (p);
}

void tokenize(TokenScanner *scanner, char *src)
{
	Token *token_array;
	int index;
	size_t token_index;

	index = 0;
	token_index = 0;
	token_array = allocate(sizeof(*token_array) * MAX_TOKENS);

	while (src[index])
	{
		while (isspace(src[index])) index++;
		switch (src[index])
		{
			case '(': {
				token_array[token_index].type = OPAREN;
				token_array[token_index].data.operator = '(';
				index++;
			} break;
			case ')': {
				token_array[token_index].type = CPAREN;
				token_array[token_index].data.operator = ')';
				index++;
			} break;
			case '-': {
				token_array[token_index].type = MINUS;
				token_array[token_index].data.operator = '-';
				index++;
			} break;
			case '+': {
				token_array[token_index].type = PLUS;
				token_array[token_index].data.operator = '+';
				index++;
			} break;
			case '*': {
				token_array[token_index].type = MUL;
				token_array[token_index].data.operator = '*';
				index++;
			} break;
			case '/': {
				token_array[token_index].type = DEV;
				token_array[token_index].data.operator = '/';
				index++;
			} break;
			default: {
				int n = 0;
				while (isdigit(src[index]))
				{
					token_array[token_index].data.lexeme[n++] = src[index];
					token_array[token_index].type = NUMBER;
					index++;
				}
				if (!n)
				{
					fprintf(stderr, "UNKNOWN symbol found!\n");
					free(token_array);
					exit(1);
					// UNKNOWN
				}
			};
		}
		token_index++;
		while (isspace(src[index])) index++;
	}
	token_array[token_index].type = END;
	scanner->end = token_index;
	scanner->tokens = token_array;
}

char *type_asstr(int t)
{
	char *r[COUNT] = {
		"PLUS",
		"MINUS",
		"MUL",
		"DEV",
		"NUMBER",
		"OPAREN",
		"CPAREN",
		"UNKNOWN",
	};
	if (t < COUNT)
		return r[t];
	if (t == END)
		return ("END");
	return "Unrecognized type";
}

// TODO: parse into tree
