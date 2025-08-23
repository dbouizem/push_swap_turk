#include "../push_swap.h"

static void	move_counts_a_to_b(t_cost *cost, int pos_a, int target_pos_b,
	t_stack *stacks[2])
{
	if (pos_a <= stacks[0]->size / 2)
		cost->ra_count = pos_a;
	else
		cost->rra_count = stacks[0]->size - pos_a;
	if (stacks[1]->size == 0)
	{
		cost->rb_count = 0;
		cost->rrb_count = 0;
	}
	else if (target_pos_b <= stacks[1]->size / 2)
		cost->rb_count = target_pos_b;
	else
		cost->rrb_count = stacks[1]->size - target_pos_b;
}

static void	move_counts_b_to_a(t_cost *cost, int pos_b, int target_pos_a,
	t_stack *stacks[2])
{
	if (pos_b <= stacks[1]->size / 2)
		cost->rb_count = pos_b;
	else
		cost->rrb_count = stacks[1]->size - pos_b;
	if (stacks[0]->size == 0)
	{
		cost->ra_count = 0;
		cost->rra_count = 0;
	}
	else if (target_pos_a <= stacks[0]->size / 2)
		cost->ra_count = target_pos_a;
	else
		cost->rra_count = stacks[0]->size - target_pos_a;
}

t_cost	calculate_cost_a_to_b(int pos_a, int value, t_stack *a, t_stack *b)
{
	t_cost		cost;
	int			target_pos_b;
	int			common_r;
	int			common_rr;
	t_stack		*stacks[2];

	stacks[0] = a;
	stacks[1] = b;
	cost.total = 0;
	cost.ra_count = 0;
	cost.rra_count = 0;
	cost.rb_count = 0;
	cost.rrb_count = 0;
	cost.element_index = pos_a;
	target_pos_b = find_target_position_in_b(value, b);
	move_counts_a_to_b(&cost, pos_a, target_pos_b, stacks);
	common_r = min_value(cost.ra_count, cost.rb_count);
	common_rr = min_value(cost.rra_count, cost.rrb_count);
	cost.total = common_r + common_rr
		+ (cost.ra_count - common_r) + (cost.rra_count - common_rr)
		+ (cost.rb_count - common_r) + (cost.rrb_count - common_rr) + 1;
	return (cost);
}

t_cost	calculate_cost_b_to_a(int pos_b, int value, t_stack *a, t_stack *b)
{
	t_cost		cost;
	int			target_pos_a;
	int			common_r;
	int			common_rr;
	t_stack		*stacks[2];

	stacks[0] = a;
	stacks[1] = b;
	cost.total = 0;
	cost.ra_count = 0;
	cost.rra_count = 0;
	cost.rb_count = 0;
	cost.rrb_count = 0;
	cost.element_index = pos_b;
	target_pos_a = find_target_position_in_a(value, a);
	move_counts_b_to_a(&cost, pos_b, target_pos_a, stacks);
	common_r = min_value(cost.ra_count, cost.rb_count);
	common_rr = min_value(cost.rra_count, cost.rrb_count);
	cost.total = common_r + common_rr
		+ (cost.ra_count - common_r) + (cost.rra_count - common_rr)
		+ (cost.rb_count - common_r) + (cost.rrb_count - common_rr) + 1;
	return (cost);
}

t_cost	find_cheapest_element_a_to_b(t_stack *a, t_stack *b)
{
	t_cost	cheapest_cost;
	t_cost	current_cost;
	int		i;

	if (is_empty(a))
	{
		cheapest_cost.total = INT_MAX;
		return (cheapest_cost);
	}
	cheapest_cost = calculate_cost_a_to_b(0, a->data[0], a, b);
	i = 1;
	while (i < a->size)
	{
		current_cost = calculate_cost_a_to_b(i, a->data[i], a, b);
		if (current_cost.total < cheapest_cost.total)
			cheapest_cost = current_cost;
		i++;
	}
	return (cheapest_cost);
}
