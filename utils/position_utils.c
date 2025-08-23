#include "../push_swap.h"

int	find_position(int value, t_stack *stack)
{
	int	i;

	if (!stack)
		return (-1);
	i = 0;
	while (i < stack->size)
	{
		if (stack->data[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

int	find_target_position_in_a(int value, t_stack *a)
{
	int	i;
	int	max_val;
	int	min_val;

	if (is_empty(a))
		return (0);
	max_val = find_max(a);
	min_val = find_min(a);
	if (value > max_val || value < min_val)
		return (find_position(min_val, a));
	i = 0;
	while (i < a->size - 1)
	{
		if (a->data[i] < value && value < a->data[i + 1])
			return (i + 1);
		i++;
	}
	if (a->data[a->size - 1] < value && value < a->data[0])
		return (0);

	return (0);
}

int	find_target_position_in_b(int value, t_stack *b)
{
	int	max_val;
	int	min_val;
	int	i;

	if (is_empty(b))
		return (0);
	max_val = find_max(b);
	min_val = find_min(b);
	if (value > max_val || value < min_val)
		return (find_position(max_val, b));
	i = 0;
	while (i < b->size - 1)
	{
		if (b->data[i] > value && value > b->data[i + 1])
			return (i + 1);
		i++;
	}

	if (b->data[b->size - 1] > value && value > b->data[0])
		return (0);

	return (0);
}

int	find_min(t_stack *stack)
{
	int	min;
	int	i;

	if (!stack || stack->size <= 0)
		error_exit();
	min = stack->data[0];
	i = 1;
	while (i < stack->size)
	{
		if (stack->data[i] < min)
			min = stack->data[i];
		i++;
	}
	return (min);
}

int	find_max(t_stack *stack)
{
	int	max;
	int	i;

	if (!stack || stack->size <= 0)
		error_exit();
	max = stack->data[0];
	i = 1;
	while (i < stack->size)
	{
		if (stack->data[i] > max)
			max = stack->data[i];
		i++;
	}
	return (max);
}
