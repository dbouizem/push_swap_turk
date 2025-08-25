#include "../push_swap.h"

t_stack	*create_stack(int capacity)
{
	t_stack	*stack;

	if (capacity <= 0)
		return (NULL);
	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->data = (int *)malloc(sizeof(int) * capacity);
	if (!stack->data)
	{
		free(stack);
		return (NULL);
	}
	stack->size = 0;
	stack->capacity = capacity;
	return (stack);
}

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	if (stack->data)
		free(stack->data);
	free(stack);
}

int	is_empty(t_stack *stack)
{
	if (!stack)
		return (1);
	return (stack->size == 0);
}

int	is_full(t_stack *stack)
{
	if (!stack)
		return (1);
	return (stack->size >= stack->capacity);
}

