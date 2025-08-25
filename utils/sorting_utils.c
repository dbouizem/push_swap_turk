#include "../push_swap.h"

void	sort_three_operations(t_stack *a, int first, int second, int third)
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

/*
[B, A, C]
[A, C, B]
[C, A, B]
[B, C, A]
[C, B, A]
*/
