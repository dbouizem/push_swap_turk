
#include "push_swap.h"

void	print_stack(t_stack *stack, char name)
{
	int i;

	if (!stack)
	{
		ft_putstr_fd("Stack ", 2);
		ft_putchar_fd(name, 2);
		ft_putstr_fd(": NULL\n", 2);
		return;
	}

	ft_putstr_fd("Stack ", 2);
	ft_putchar_fd(name, 2);
	ft_putstr_fd(": [", 2);

	i = 0;
	while (i < stack->size)
	{
		ft_putnbr_fd(stack->data[i], 2);
		if (i < stack->size - 1)
			ft_putstr_fd(", ", 2);
		i++;
	}
	ft_putstr_fd("]\n", 2);
}

void	print_both_stacks(t_stack *a, t_stack *b)
{
	ft_putstr_fd("=== État des piles ===\n", 2);
	print_stack(a, 'A');
	print_stack(b, 'B');
	ft_putstr_fd("=====================\n", 2);
}
