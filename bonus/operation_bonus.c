#include "../push_swap.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	max_len;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (1);
	max_len = len1;
	if (len2 > max_len)
		max_len = len2;
	return (ft_strncmp(s1, s2, max_len));
}

static int	execute_basic_ops(char *instruction, t_stack *a, t_stack *b)
{
	if (ft_strcmp(instruction, "sa") == 0)
		sa_silent(a);
	else if (ft_strcmp(instruction, "sb") == 0)
		sb_silent(b);
	else if (ft_strcmp(instruction, "ss") == 0)
		ss_silent(a, b);
	else if (ft_strcmp(instruction, "pa") == 0)
		pa_silent(a, b);
	else if (ft_strcmp(instruction, "pb") == 0)
		pb_silent(a, b);
	else
		return (0);
	return (1);
}

static int	execute_rotate_ops(char *instruction, t_stack *a, t_stack *b)
{
	if (ft_strcmp(instruction, "ra") == 0)
		ra_silent(a);
	else if (ft_strcmp(instruction, "rb") == 0)
		rb_silent(b);
	else if (ft_strcmp(instruction, "rr") == 0)
		rr_silent(a, b);
	else if (ft_strcmp(instruction, "rra") == 0)
		rra_silent(a);
	else if (ft_strcmp(instruction, "rrb") == 0)
		rrb_silent(b);
	else if (ft_strcmp(instruction, "rrr") == 0)
		rrr_silent(a, b);
	else
		return (0);
	return (1);
}

int	execute_instruction_silent(char *instruction, t_stack *a, t_stack *b)
{
	if (!instruction)
		return (0);
	if (execute_basic_ops(instruction, a, b))
		return (1);
	if (execute_rotate_ops(instruction, a, b))
		return (1);
	return (0);
}
