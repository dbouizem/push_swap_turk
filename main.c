#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;

	if (ac == 1)
		return (0);
	a = parse_arguments(ac, av);
	if (!a)
		return (1);
	if (is_sorted(a))
	{
		free_stack(a);
		return (0);
	}
	b = create_stack(a->capacity);
	if (!b)
	{
		free_stack(a);
		error_exit();
	}
	push_swap(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
