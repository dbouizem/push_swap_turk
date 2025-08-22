#include "../push_swap.h"

int	is_sorted(t_stack *stack)
{
	int	i;

	if (!stack || stack->size <= 1)
		return (1);
	i = 1;
	while (i < stack->size)
	{
		if (stack->data[i - 1] > stack->data[i])
			return (0);
		i++;
	}
	return (1);
}
