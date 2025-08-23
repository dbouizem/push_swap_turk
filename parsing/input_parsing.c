#include "../push_swap.h"

void	push_to_stack(t_stack *stack, int value)
{
	if (!stack || is_full(stack))
		error_exit();
	stack->data[stack->size] = value;
	stack->size++;
}

t_stack	*parse_single_string(char *str)
{
	char	**numbers;
	t_stack	*stack;
	int		count;

	if (!str || !*str)
		exit(0);
	numbers = ft_split(str, ' ');
	if (!numbers)
		error_exit();
	count = 0;
	while (numbers[count])
		count++;
	if (count == 0)
	{
		ft_free_split(numbers);
		exit(0);
	}
	stack = create_and_fill_stack(numbers, count);
	if (!stack)
		cleanup_parse_and_exit(NULL, numbers);
	ft_free_split(numbers);
	return (stack);
}

static void	validate_and_push(t_stack *stack, char *arg)
{
	if (!is_valid_number(arg))
	{
		free_stack(stack);
		error_exit();
	}
	push_to_stack(stack, (int)ft_atol_safe(arg));
}

t_stack	*parse_multiple_args(int ac, char **av)
{
	t_stack	*stack;
	int		i;

	stack = create_stack(ac - 1);
	if (!stack)
		error_exit();
	i = 1;
	while (i < ac)
	{
		validate_and_push(stack, av[i]);
		i++;
	}
	if (has_duplicates(stack))
	{
		free_stack(stack);
		error_exit();
	}
	return (stack);
}

t_stack	*parse_arguments(int ac, char **av)
{
	if (ac == 1)
		exit(0);
	if (ac == 2)
		return (parse_single_string(av[1]));
	return (parse_multiple_args(ac, av));
}
