#include "../push_swap.h"

void	error_exit(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	cleanup_and_exit(t_stack *a, t_stack *b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	error_exit();
}
