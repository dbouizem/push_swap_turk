#include "../push_swap.h"

void	sa(t_stack *a)
{
	int	temp;

	if (!a || a->size < 2)
		return ;
	temp = a->data[0];
	a->data[0] = a->data[1];
	a->data[1] = temp;
	ft_putstr_fd("sa\n", 1);
}

void	sb(t_stack *b)
{
	int	temp;

	if (!b || b->size < 2)
		return ;
	temp = b->data[0];
	b->data[0] = b->data[1];
	b->data[1] = temp;
	ft_putstr_fd("sb\n", 1);
}

void	ss(t_stack *a, t_stack *b)
{
	int	temp;

	if (a && a->size >= 2)
	{
		temp = a->data[0];
		a->data[0] = a->data[1];
		a->data[1] = temp;
	}
	if (b && b->size >= 2)
	{
		temp = b->data[0];
		b->data[0] = b->data[1];
		b->data[1] = temp;
	}
	ft_putstr_fd("ss\n", 1);
}
