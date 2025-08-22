#include "../push_swap.h"

t_cost	calculate_cost_a_to_b(int pos_a, int value, t_stack *a, t_stack *b)
{
	t_cost	cost;
	int		target_pos_b;
	int		common_r;
	int		common_rr;

	// Initialisation
	cost.total = 0;
	cost.ra_count = 0;
	cost.rra_count = 0;
	cost.rb_count = 0;
	cost.rrb_count = 0;
	cost.element_index = pos_a;

	// Trouver la position cible dans B
	target_pos_b = find_target_position_in_b(value, b);

	// Calculer les mouvements pour amener l'Ã©lÃ©ment au sommet de A
	if (pos_a <= a->size / 2)
		cost.ra_count = pos_a;
	else
		cost.rra_count = a->size - pos_a;

	// Calculer les mouvements pour prÃ©parer la position dans B
	if (b->size == 0)
	{
		// Pile B vide, pas de rotation nÃ©cessaire
		cost.rb_count = 0;
		cost.rrb_count = 0;
	}
	else if (target_pos_b <= b->size / 2)
		cost.rb_count = target_pos_b;
	else
		cost.rrb_count = b->size - target_pos_b;

	// Calculer les rotations simultanÃ©es possibles
	common_r = min_value(cost.ra_count, cost.rb_count);
	common_rr = min_value(cost.rra_count, cost.rrb_count);

	// FORMULE CORRECTE :
	// Total = rotations simultanÃ©es + rotations restantes + 1 push
	cost.total = common_r + common_rr +
				 (cost.ra_count - common_r) + (cost.rra_count - common_rr) +
				 (cost.rb_count - common_r) + (cost.rrb_count - common_rr) + 1;

	return (cost);
}

t_cost	calculate_cost_b_to_a(int pos_b, int value, t_stack *a, t_stack *b)
{
	t_cost	cost;
	int		target_pos_a;
	int		common_r;
	int		common_rr;

	// Initialisation
	cost.total = 0;
	cost.ra_count = 0;
	cost.rra_count = 0;
	cost.rb_count = 0;
	cost.rrb_count = 0;
	cost.element_index = pos_b;

	// Trouver la position cible dans A
	target_pos_a = find_target_position_in_a(value, a);

	// Calculer les mouvements pour amener l'Ã©lÃ©ment au sommet de B
	if (pos_b <= b->size / 2)
		cost.rb_count = pos_b;
	else
		cost.rrb_count = b->size - pos_b;

	// Calculer les mouvements pour prÃ©parer la position dans A
	if (a->size == 0)
	{
		// Pile A vide, pas de rotation nÃ©cessaire
		cost.ra_count = 0;
		cost.rra_count = 0;
	}
	else if (target_pos_a <= a->size / 2)
		cost.ra_count = target_pos_a;
	else
		cost.rra_count = a->size - target_pos_a;

	// Calculer les rotations simultanÃ©es possibles
	common_r = min_value(cost.ra_count, cost.rb_count);
	common_rr = min_value(cost.rra_count, cost.rrb_count);

	// FORMULE CORRECTE
	cost.total = common_r + common_rr +
				 (cost.ra_count - common_r) + (cost.rra_count - common_rr) +
				 (cost.rb_count - common_r) + (cost.rrb_count - common_rr) + 1;

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
