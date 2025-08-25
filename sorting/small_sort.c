#include "../push_swap.h"

void	sort_two(t_stack *a)
{
	if (a->size != 2)
		return ;
	if (a->data[0] > a->data[1])
		sa(a);
}

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (a->size != 3)
		return ;
	first = a->data[0];
	second = a->data[1];
	third = a->data[2];
	if (first < second && second < third)
		return ;
	sort_three_operations(a, first, second, third);
}

void	sort_four(t_stack *a, t_stack *b)
{
	int	min_val;
	int	min_pos;

	if (a->size != 4)
		return ;

	min_val = find_min(a);
	min_pos = find_position(min_val, a);
	if (min_pos == 1)
		sa(a);
	else if (min_pos == 2)
	{
		ra(a);
		ra(a);
	}
	else if (min_pos == 3)
		rra(a);
	pb(a, b);
	sort_three(a);
	pa(a, b);
}

void	sort_five(t_stack *a, t_stack *b)
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

void	sort_small_stack(t_stack *a, t_stack *b)
{
	if (!a || is_sorted(a))
		return ;
	if (a->size == 2)
		sort_two(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
}
