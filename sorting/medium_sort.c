#include "../push_swap.h"

void	move_min_to_top(t_stack *a, int min_val)
{
	int	min_pos;

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

void	sort_five(t_stack *a, t_stack *b)
{
	int	min_val;
	int	second_min_val;

	if (a->size != 5)
		return ;

	// Étape 1: Trouver et pousser le minimum
	min_val = find_min(a);
	move_min_to_top(a, min_val);
	pb(a, b);

	// Étape 2: Trouver et pousser le deuxième minimum
	second_min_val = find_min(a);
	move_min_to_top(a, second_min_val);
	pb(a, b);

	// Étape 3: Trier les 3 éléments restants dans A
	sort_three(a);

	// Étape 4: Remettre les éléments dans l'ordre
	// ATTENTION: Vérifier l'ordre dans B avant de remettre
	if (b->size == 2 && b->data[0] > b->data[1])
	{
		// Si le plus grand des deux minimums est au sommet de B
		// Il faut d'abord récupérer le plus petit
		pa(a, b);  // Récupère le deuxième minimum
		pa(a, b);  // Récupère le minimum
	}
	else
	{
		// L'ordre est correct dans B
		pa(a, b);  // Récupère le deuxième minimum
		pa(a, b);  // Récupère le minimum
	}
}

// Version alternative plus sûre
void	sort_five_safe(t_stack *a, t_stack *b)
{
	int	moves;
	int	min_val;

	if (a->size != 5)
		return ;

	// Pousser les 2 plus petits éléments vers B
	while (a->size > 3)
	{
		min_val = find_min(a);
		moves = find_position(min_val, a);

		// Optimisation: choisir la rotation la plus efficace
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

	// Trier les 3 éléments restants
	sort_three(a);

	// Remettre les éléments de B vers A
	while (b->size > 0)
		pa(a, b);
}
