#include "../push_swap.h"

void	execute_optimal_moves(t_stack *a, t_stack *b, t_cost cost)
{
	// CrÃ©er des copies locales pour Ã©viter de modifier la structure originale
	int	ra_moves = cost.ra_count;
	int	rra_moves = cost.rra_count;
	int	rb_moves = cost.rb_count;
	int	rrb_moves = cost.rrb_count;

	// Phase 1: Rotations simultanÃ©es normales (rr)
	while (ra_moves > 0 && rb_moves > 0)
	{
		rr(a, b);
		ra_moves--;
		rb_moves--;
	}

	// Phase 2: Rotations simultanÃ©es inverses (rrr)
	while (rra_moves > 0 && rrb_moves > 0)
	{
		rrr(a, b);
		rra_moves--;
		rrb_moves--;
	}

	// Phase 3: Rotations restantes pour la pile A
	while (ra_moves > 0)
	{
		ra(a);
		ra_moves--;
	}
	while (rra_moves > 0)
	{
		rra(a);
		rra_moves--;
	}

	// Phase 4: Rotations restantes pour la pile B
	while (rb_moves > 0)
	{
		rb(b);
		rb_moves--;
	}
	while (rrb_moves > 0)
	{
		rrb(b);
		rrb_moves--;
	}
}

void	bring_min_to_top(t_stack *a)
{
	int	min_val;
	int	min_pos;

	if (is_empty(a))
		return ;

	min_val = find_min(a);
	min_pos = find_position(min_val, a);

	// Choisir la rotation la plus efficace
	if (min_pos <= a->size / 2)
	{
		// Rotation normale plus efficace
		while (a->data[0] != min_val)
			ra(a);
	}
	else
	{
		// Rotation inverse plus efficace
		while (a->data[0] != min_val)
			rra(a);
	}
}
