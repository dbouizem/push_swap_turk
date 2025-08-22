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

	// 6 cas possibles pour 3 éléments, traitons-les tous explicitement
	if (first < second && second < third)
		return ; // [1,2,3] déjà trié
	else if (first > second && second < third && first < third)
		sa(a); // [2,1,3] -> sa -> [1,2,3]
	else if (first < second && second > third && first < third)
	{
		// [1,3,2] -> rra -> [2,1,3] -> sa -> [1,2,3]
		rra(a);
		sa(a);
	}
	else if (first > second && second < third && first > third)
		ra(a); // [3,1,2] -> ra -> [1,2,3]
	else if (first < second && second > third && first > third)
		rra(a); // [2,3,1] -> rra -> [1,2,3]
	else if (first > second && second > third && first > third)
	{
		// [3,2,1] -> sa -> [2,3,1] -> rra -> [1,2,3]
		sa(a);
		rra(a);
	}
}

void	sort_four(t_stack *a, t_stack *b)
{
	int	min_val;
	int	min_pos;

	if (a->size != 4)
		return ;

	min_val = find_min(a);
	min_pos = find_position(min_val, a);

	// Amener le minimum au sommet
	if (min_pos == 1)
		sa(a);
	else if (min_pos == 2)
	{
		ra(a);
		ra(a);
	}
	else if (min_pos == 3)
		rra(a);

	// Pousser le minimum vers B
	pb(a, b);

	// Trier les 3 Ã©lÃ©ments restants
	sort_three(a);

	// RÃ©cupÃ©rer le minimum
	pa(a, b);
}
