#include "../push_swap.h"

void	sa_silent(t_stack *a)
{
	int	temp;

	if (!a || a->size < 2)
		return ;
	temp = a->data[0];
	a->data[0] = a->data[1];
	a->data[1] = temp;
}

void	sb_silent(t_stack *b)
{
	int	temp;

	if (!b || b->size < 2)
		return ;
	temp = b->data[0];
	b->data[0] = b->data[1];
	b->data[1] = temp;
}

void	ss_silent(t_stack *a, t_stack *b)
{
	sa_silent(a);
	sb_silent(b);
}

void	pa_silent(t_stack *a, t_stack *b)
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
}

void	pb_silent(t_stack *a, t_stack *b)
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
}
