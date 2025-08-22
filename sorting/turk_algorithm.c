#include "../push_swap.h"

void	turk_algorithm(t_stack *a, t_stack *b)
{
	t_cost	cheapest_cost;

	// Phase 1: Pousser les premiers éléments vers B pour initialiser
	if (a->size > 3)
	{
		pb(a, b);
		if (a->size > 3)
			pb(a, b);
	}

	// Phase 2: Déplacer tous les éléments sauf 3 vers B de manière optimale
	while (a->size > 3)
	{
		// Trouver l'élément le moins coûteux à déplacer vers B
		cheapest_cost = find_cheapest_element_a_to_b(a, b);

		// Exécuter les mouvements optimaux pour positionner l'élément au sommet
		execute_optimal_moves(a, b, cheapest_cost);

		// L'élément est maintenant au sommet de A, le pousser vers B
		pb(a, b);
	}

	// Phase 3: Trier les 3 éléments restants dans A
	sort_three(a);

	// Phase 4: Rapatrier tous les éléments de B vers A de manière optimale
	while (!is_empty(b))
	{
		// Trouver l'élément le moins coûteux à rapatrier vers A
		cheapest_cost = find_cheapest_element_b_to_a(a, b);

		// Exécuter les mouvements optimaux pour positionner les piles
		execute_optimal_moves(a, b, cheapest_cost);

		// L'élément est maintenant au sommet de B, le pousser vers A
		pa(a, b);
	}

	// Phase 5: Amener le minimum au sommet pour finaliser le tri
	bring_min_to_top(a);
}

void	push_swap(t_stack *a, t_stack *b)
{
	// Vérifier si la pile est déjà triée ou vide
	if (!a || a->size <= 1 || is_sorted(a))
		return ;

	// Choisir l'algorithme selon la taille
	if (a->size <= 5)
		sort_small_stack(a, b);
	else
		turk_algorithm(a, b);
}
