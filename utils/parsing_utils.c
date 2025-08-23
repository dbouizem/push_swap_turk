#include "../push_swap.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	validate_input_format(char *str)
{
	int	i;
	int	has_digit;

	if (!str || !*str)
		return (0);
	i = 0;
	has_digit = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else if (str[i] != ' ' && str[i] != '+' && str[i] != '-')
			return (0);
		i++;
	}
	return (has_digit);
}

void	cleanup_parse_and_exit(t_stack *stack, char **numbers)
{
	if (stack)
		free_stack(stack);
	if (numbers)
		ft_free_split(numbers);
	error_exit();
}

t_stack	*create_and_fill_stack(char **numbers, int count)
{
	t_stack	*stack;
	int		i;

	stack = create_stack(count);
	if (!stack)
		return (NULL);
	i = 0;
	while (numbers[i])
	{
		if (!is_valid_number(numbers[i]))
		{
			free_stack(stack);
			return (NULL);
		}
		push_to_stack(stack, (int)ft_atol_safe(numbers[i]));
		i++;
	}
	if (has_duplicates(stack))
	{
		free_stack(stack);
		return (NULL);
	}
	return (stack);
}
