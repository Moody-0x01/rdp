#include <parser.h>

int eval(Node *tree)
{
	int val;

	val = 0;
	if (!tree)
		return (val);
	// TODO: Go left left left....
	switch (tree->type)
	{
		case NUMBER_NODE: {
			val = tree->data.value;
		} break;
		case BINOP: {
			// binary_op
			char op = tree->data.binary_op.operator;
			Node *left = tree->data.binary_op.left;
			Node *right = tree->data.binary_op.right;
			
			int lvalue = eval(left);
			int rvalue = eval(right);
			switch (op)
			{
				case '*': {
					val = lvalue * rvalue;
				} break;
				case '+': {
					val = lvalue + rvalue;
				} break;
				case '/': {
					val = lvalue / rvalue;
				} break;
				case '-': {
					val = lvalue - rvalue;
				} break;
				default: {
					fprintf(stderr, "the op %c is not supported yet.\n", op);
					exit(1);
				};
			}
		} break;
	}
	return (val);
}
