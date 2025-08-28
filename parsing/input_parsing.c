#include "../push_swap.h"

t_stack	*parse_single_string(char *str)
{
	char	**numbers;
	t_stack	*stack;
	int		count;

	if (!str || !*str || is_only_spaces(str))
		error_exit();
	numbers = ft_split(str, ' ');
	if (!numbers)
		error_exit();
	count = 0;
	while (numbers[count])
		count++;
	if (count == 0)
	{
		ft_free_split(numbers);
		error_exit();
	}
	stack = create_and_fill_stack(numbers, count);
	if (!stack)
		cleanup_parse_and_exit(NULL, numbers);
	ft_free_split(numbers);
	return (stack);
}

static void	validate_and_add_arg(t_stack *stack, char *arg)
{
	int	converted_value;

	if (!arg || !*arg || is_only_spaces(arg))
	{
		free_stack(stack);
		error_exit();
	}
	if (!validate_and_convert(arg, &converted_value))
	{
		free_stack(stack);
		error_exit();
	}
	push_to_stack(stack, converted_value);
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
		validate_and_add_arg(stack, av[i]);
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
		return (NULL);
	if (ac == 2)
		return (parse_single_string(av[1]));
	return (parse_multiple_args(ac, av));
}
