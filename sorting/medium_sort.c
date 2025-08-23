#include "../push_swap.h"

void	move_min_to_top(t_stack *a, int min_val)
{
	int	min_pos;

	min_pos = find_position(min_val, a);
	if (min_pos <= a->size / 2)
	{
		while (a->data[0] != min_val)
			ra(a);
	}
	else
	{
		while (a->data[0] != min_val)
			rra(a);
	}
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	min_val;
	int	second_min_val;

	if (a->size != 5)
		return ;
	min_val = find_min(a);
	move_min_to_top(a, min_val);
	pb(a, b);
	second_min_val = find_min(a);
	move_min_to_top(a, second_min_val);
	pb(a, b);
	sort_three(a);
	if (b->size == 2 && b->data[0] > b->data[1])
	{
		pa(a, b);
		pa(a, b);
	}
	else
	{
		pa(a, b);
		pa(a, b);
	}
}

void	sort_five_safe(t_stack *a, t_stack *b)
{
	int	moves;
	int	min_val;

	if (a->size != 5)
		return ;
	while (a->size > 3)
	{
		min_val = find_min(a);
		moves = find_position(min_val, a);
		if (moves <= a->size / 2)
		{
			while (moves-- > 0)
				ra(a);
		}
		else
		{
			moves = a->size - moves;
			while (moves-- > 0)
				rra(a);
		}
		pb(a, b);
	}
	sort_three(a);
	while (b->size > 0)
		pa(a, b);
}
