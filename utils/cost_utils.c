#include "../push_swap.h"

t_cost	find_cheapest_element_b_to_a(t_stack *a, t_stack *b)
{
	t_cost	cheapest_cost;
	t_cost	current_cost;
	int		i;

	if (is_empty(b))
	{
		cheapest_cost.total = INT_MAX;
		return (cheapest_cost);
	}
	cheapest_cost = calculate_cost_b_to_a(0, b->data[0], a, b);
	i = 1;
	while (i < b->size)
	{
		current_cost = calculate_cost_b_to_a(i, b->data[i], a, b);
		if (current_cost.total < cheapest_cost.total)
			cheapest_cost = current_cost;
		i++;
	}
	return (cheapest_cost);
}
