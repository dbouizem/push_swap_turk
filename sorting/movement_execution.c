#include "../push_swap.h"

static void	execute_remaining_moves(t_stack *a, t_stack *b, t_cost *moves)
{
	while (moves->ra_count > 0)
	{
		ra(a);
		moves->ra_count--;
	}
	while (moves->rra_count > 0)
	{
		rra(a);
		moves->rra_count--;
	}
	while (moves->rb_count > 0)
	{
		rb(b);
		moves->rb_count--;
	}
	while (moves->rrb_count > 0)
	{
		rrb(b);
		moves->rrb_count--;
	}
}

void	execute_optimal_moves(t_stack *a, t_stack *b, t_cost cost)
{
	t_cost	moves;

	moves.ra_count = cost.ra_count;
	moves.rra_count = cost.rra_count;
	moves.rb_count = cost.rb_count;
	moves.rrb_count = cost.rrb_count;
	while (moves.ra_count > 0 && moves.rb_count > 0)
	{
		rr(a, b);
		moves.ra_count--;
		moves.rb_count--;
	}
	while (moves.rra_count > 0 && moves.rrb_count > 0)
	{
		rrr(a, b);
		moves.rra_count--;
		moves.rrb_count--;
	}
	execute_remaining_moves(a, b, &moves);
}

void	bring_min_to_top(t_stack *a)
{
	int	min_val;
	int	min_pos;

	if (is_empty(a))
		return ;

	min_val = find_min(a);
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
