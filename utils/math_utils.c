#include "../push_swap.h"

int	min_value(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
