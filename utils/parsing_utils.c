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

int	is_only_spaces(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	validate_and_convert(char *str, int *result)
{
	long	value;

	if (!is_valid_number(str))
		return (0);
	value = ft_atol(str);
	if (value == LONG_MIN)
		return (0);
	*result = (int)value;
	return (1);
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
	int		converted_value;
	int		i;

	stack = create_stack(count);
	if (!stack)
		return (NULL);
	i = 0;
	while (numbers[i])
	{
		if (!validate_and_convert(numbers[i], &converted_value))
		{
			free_stack(stack);
			return (NULL);
		}
		push_to_stack(stack, converted_value);
		i++;
	}
	if (has_duplicates(stack))
	{
		free_stack(stack);
		return (NULL);
	}
	return (stack);
}
