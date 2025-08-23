#include "../push_swap.h"

void	sort_two(t_stack *a)
{
	if (a->size != 2)
		return ;
	if (a->data[0] > a->data[1])
		sa(a);
}

static void	sort_three_operations(t_stack *a, int first, int second, int third)
{
	if (first > second && second < third && first < third)
		sa(a);
	else if (first < second && second > third && first < third)
	{
		rra(a);
		sa(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first > third)
		rra(a);
	else if (first > second && second > third && first > third)
	{
		sa(a);
		rra(a);
	}
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
