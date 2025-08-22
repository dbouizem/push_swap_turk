#include "../push_swap.h"

void	ra_silent(t_stack *a)
{
	int	temp;
	int	i;

	if (!a || a->size < 2)
		return ;
	temp = a->data[0];
	i = 0;
	while (i < a->size - 1)
	{
		a->data[i] = a->data[i + 1];
		i++;
	}
	a->data[a->size - 1] = temp;
}

void	rb_silent(t_stack *b)
{
	int	temp;
	int	i;

	if (!b || b->size < 2)
		return ;
	temp = b->data[0];
	i = 0;
	while (i < b->size - 1)
	{
		b->data[i] = b->data[i + 1];
		i++;
	}
	b->data[b->size - 1] = temp;
}

void	rr_silent(t_stack *a, t_stack *b)
{
	ra_silent(a);
	rb_silent(b);
}

void	rra_silent(t_stack *a)
{
	int	temp;
	int	i;

	if (!a || a->size < 2)
		return ;
	temp = a->data[a->size - 1];
	i = a->size - 1;
	while (i > 0)
	{
		a->data[i] = a->data[i - 1];
		i--;
	}
	a->data[0] = temp;
}

void	rrb_silent(t_stack *b)
{
	int	temp;
	int	i;

	if (!b || b->size < 2)
		return ;
	temp = b->data[b->size - 1];
	i = b->size - 1;
	while (i > 0)
	{
		b->data[i] = b->data[i - 1];
		i--;
	}
	b->data[0] = temp;
}
