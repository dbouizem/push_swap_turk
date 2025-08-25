#include "../push_swap.h"

void	turk_algorithm(t_stack *a, t_stack *b)
{
	t_cost	cheapest_cost;

	if (a->size > 3)
	{
		pb(a, b);
		if (a->size > 3)
			pb(a, b);
	}
	while (a->size > 3)
	{
		cheapest_cost = find_cheapest_element_a_to_b(a, b);
		execute_optimal_moves(a, b, cheapest_cost);
		pb(a, b);
	}
	sort_three(a);
	while (!is_empty(b))
	{
		cheapest_cost = find_cheapest_element_b_to_a(a, b);
		execute_optimal_moves(a, b, cheapest_cost);
		pa(a, b);
	}
	bring_min_to_top(a);
}
