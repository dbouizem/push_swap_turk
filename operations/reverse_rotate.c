#include "../push_swap.h"

void	rra(t_stack *a)
{
	int	temp;
	int	i;

	if (a->size < 2)
		return ;
	temp = a->data[a->size - 1];
	i = a->size - 1;
	while (i > 0)
	{
		a->data[i] = a->data[i - 1];
		i--;
	}
	a->data[0] = temp;
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stack *b)
{
	int	temp;
	int	i;

	if (b->size < 2)
		return ;
	temp = b->data[b->size - 1];
	i = b->size - 1;
	while (i > 0)
	{
		b->data[i] = b->data[i - 1];
		i--;
	}
	b->data[0] = temp;
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_stack *a, t_stack *b)
{
	int	temp;
	int	i;

	if (a->size >= 2)
	{
		temp = a->data[a->size - 1];
		i = a->size - 1;
		while (i > 0)
		{
			a->data[i] = a->data[i - 1];
			i--;
		}
		a->data[0] = temp;
	}
	if (b->size >= 2)
	{
		temp = b->data[b->size - 1];
		i = b->size - 1;
		while (i > 0)
		{
			b->data[i] = b->data[i - 1];
			i--;
		}
		b->data[0] = temp;
	}
	ft_putstr_fd("rrr\n", 1);
}
