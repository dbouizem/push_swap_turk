#include "../push_swap.h"

static void	rotate_stack(t_stack *stack)
{
	int	temp;
	int	i;

	if (stack->size < 2)
		return ;
	temp = stack->data[0];
	i = 0;
	while (i < stack->size - 1)
	{
		stack->data[i] = stack->data[i + 1];
		i++;
	}
	stack->data[stack->size - 1] = temp;
}

void	ra(t_stack *a)
{
	rotate_stack(a);
	ft_putstr_fd("ra\n", 1);
}

void	rb(t_stack *b)
{
	rotate_stack(b);
	ft_putstr_fd("rb\n", 1);
}

void	rr(t_stack *a, t_stack *b)
{
	rotate_stack(a);
	rotate_stack(b);
	ft_putstr_fd("rr\n", 1);
}
