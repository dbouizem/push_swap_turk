#include "../push_swap.h"

void	pa(t_stack *a, t_stack *b)
{
	int	i;

	if (is_empty(b) || is_full(a))
		return ;
	i = a->size;
	while (i > 0)
	{
		a->data[i] = a->data[i - 1];
		i--;
	}
	a->data[0] = b->data[0];
	a->size++;
	i = 0;
	while (i < b->size - 1)
	{
		b->data[i] = b->data[i + 1];
		i++;
	}
	b->size--;
	ft_putstr_fd("pa\n", 1);
}

void	pb(t_stack *a, t_stack *b)
{
	int	i;

	if (is_empty(a) || is_full(b))
		return ;
	i = b->size;
	while (i > 0)
	{
		b->data[i] = b->data[i - 1];
		i--;
	}
	b->data[0] = a->data[0];
	b->size++;
	i = 0;
	while (i < a->size - 1)
	{
		a->data[i] = a->data[i + 1];
		i++;
	}
	a->size--;
	ft_putstr_fd("pb\n", 1);
}
