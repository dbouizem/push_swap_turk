#include "../push_swap.h"

static void	reverse_rotate_stack(t_stack *stack)
{
	int	temp;
	int	i;

	if (stack->size < 2)
		return ;
	temp = stack->data[stack->size - 1];
	i = stack->size - 1;
	while (i > 0)
	{
		stack->data[i] = stack->data[i - 1];
		i--;
	}
	stack->data[0] = temp;
}

void	rra(t_stack *a)
{
	reverse_rotate_stack(a);
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stack *b)
{
	reverse_rotate_stack(b);
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate_stack(a);
	reverse_rotate_stack(b);
	ft_putstr_fd("rrr\n", 1);
}
