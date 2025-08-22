#include "../push_swap.h"

void	ra(t_stack *a)
{
	int	temp;
	int	i;

	if (a->size < 2)
		return ;
	temp = a->data[0];
	i = 0;
	while (i < a->size - 1)
	{
		a->data[i] = a->data[i + 1];
		i++;
	}
	a->data[a->size - 1] = temp;

	ft_putstr_fd("ra\n", 1);
}

void	rb(t_stack *b)
{
	int	temp;
	int	i;

	if (b->size < 2)
		return ;
	temp = b->data[0];
	i = 0;
	while (i < b->size - 1)
	{
		b->data[i] = b->data[i + 1];
		i++;
	}
	b->data[b->size - 1] = temp;
	ft_putstr_fd("rb\n", 1);
}

void	rr(t_stack *a, t_stack *b)
{
	int	temp;
	int	i;

	if (a->size >= 2)
	{
		temp = a->data[0];
		i = 0;
		while (i < a->size - 1)
		{
			a->data[i] = a->data[i + 1];
			i++;
		}
		a->data[a->size - 1] = temp;
	}
	if (b->size >= 2)
	{
		temp = b->data[0];
		i = 0;
		while (i < b->size - 1)
		{
			b->data[i] = b->data[i + 1];
			i++;
		}
		b->data[b->size - 1] = temp;
	}
	ft_putstr_fd("rr\n", 1);
}
