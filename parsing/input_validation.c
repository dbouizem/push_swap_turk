#include "../push_swap.h"

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol_safe(char *str)
{
	long	result;
	int		sign;
	int		i;

	if (!str)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			error_exit();
		i++;
	}
	return (result * sign);
}

int	has_duplicates(t_stack *stack)
{
	int	i;
	int	j;

	if (!stack || stack->size <= 1)
		return (0);
	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		while (j < stack->size)
		{
			if (stack->data[i] == stack->data[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_space_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	count_valid_numbers(char *str)
{
	int	count;
	int	in_number;
	int	i;

	if (!str)
		return (0);
	count = 0;
	in_number = 0;
	i = 0;
	while (str[i])
	{
		if (!is_space_char(str[i]) && !in_number)
		{
			in_number = 1;
			count++;
		}
		else if (is_space_char(str[i]))
			in_number = 0;
		i++;
	}
	return (count);
}
