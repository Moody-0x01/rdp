#include <parser.h>

static int is_op(char op) { return (op == ')' || op == '+' || op == '-' || op == '/' || op == '*');}
int parse_factor_(t_expr *const expr)
{
	int n;
	static int lvl;

	n = 0;
	if (!lvl)
		lvl = 1;
	while (isspace(expr->src[expr->cur]) && expr->src[expr->cur])
		expr->cur++;
	if (isdigit(expr->src[expr->cur]))
	{
		while (isdigit(expr->src[expr->cur]) && expr->src[expr->cur])
		{
			n = n * 10 + (expr->src[expr->cur] - '0');
			expr->cur++;
		}
	} else if (expr->src[expr->cur] == '(')
	{
		expr->cur++; // J (
		lvl *= 2;
		{
			n = parse_(expr);
		}
		while (isspace(expr->src[expr->cur]) && expr->src[expr->cur])
			expr->cur++;
		lvl /= 2;
		expr->cur++; // J )
		if (expr->src[expr->cur - 1] != ')' && !expr->on_error )
		{
			printf("Expected ) or a number but found: `%c`\n",
				expr->src[expr->cur - 1]);
			expr->on_error = 1;
		}
	} else if (lvl == 1) {
		printf("Expected ( or a number but found: `%c`\n",
			expr->src[expr->cur]);
		expr->on_error = 1;
	}
	return (n);
}

int parse_term_(t_expr *const expr)
{
	int n = parse_factor_(expr);

	while (isspace(expr->src[expr->cur]) && expr->src[expr->cur])
		expr->cur++;
	while ((expr->src[expr->cur] == '*' || expr->src[expr->cur] == '/') && !expr->on_error)
	{
		if (expr->src[expr->cur] == '*' )
		{
			expr->cur++;
			n *= parse_factor_(expr);
		}
		else if (expr->src[expr->cur] == '/')
		{
			expr->cur++;
			int din = parse_factor_(expr);
			if (din != 0)
				n /= din;
			else
			{
				printf("can not devide: %i/%i\n", n, din);
				expr->on_error = 1;
			}
		}
		while (isspace(expr->src[expr->cur]) && expr->src[expr->cur])
			expr->cur++;
	}
	if (!is_op(expr->src[expr->cur]) && expr->src[expr->cur] && !expr->on_error)
	{
		printf("Expected an op[*, +, /, -] but found: `%c`\n",
			expr->src[expr->cur]);
		expr->on_error = 1;
	}
	return (n);
}

int	parse_(t_expr *const expr)
{
	int n = parse_term_(expr);

	while (isspace(expr->src[expr->cur]) && expr->src[expr->cur])
		expr->cur++;
	while ((expr->src[expr->cur] == '+' || expr->src[expr->cur] == '-') && !expr->on_error && (expr->src[expr->cur]))
	{
		if (expr->src[expr->cur] == '+' )
		{
			expr->cur++;
			n += parse_term_(expr);
		}
		else if (expr->src[expr->cur] == '-' )
		{
			expr->cur++;
			n -= parse_term_(expr);
		}
	}
	if (!is_op(expr->src[expr->cur]) && expr->src[expr->cur] && !expr->on_error)
	{
		printf("Expected an op[*, +, /, -] but found: `%c`\n",
			expr->src[expr->cur]);
		expr->on_error = 1;
	}
	return (n);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, "Usage: %s <Expression>\n", av[0]);
		return (0);
	}
	t_expr s = {.on_error = 0, .cur = 0, .src = av[1]};
	int val = parse_(&s);

	if (!s.on_error && !s.src[s.cur])
		printf("%i\n", val);
	return (0);
}
