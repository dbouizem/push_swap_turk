#include "../push_swap.h"

// Fonction strcmp locale utilisant ft_strncmp de libft
static int	ft_strcmp_local(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	max_len;

	if (!s1 || !s2)
		return (0);

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);

	if (len1 != len2)
		return (1);  // DiffÃ©rentes longueurs = diffÃ©rentes chaÃ®nes

	max_len = len1;
	if (len2 > max_len)
		max_len = len2;

	return (ft_strncmp(s1, s2, max_len));
}

int	execute_instruction_silent(char *instruction, t_stack *a, t_stack *b)
{
	if (!instruction)
		return (0);

	// Utiliser notre fonction locale basÃ©e sur ft_strncmp
	if (ft_strcmp_local(instruction, "sa") == 0)
		sa_silent(a);
	else if (ft_strcmp_local(instruction, "sb") == 0)
		sb_silent(b);
	else if (ft_strcmp_local(instruction, "ss") == 0)
		ss_silent(a, b);
	else if (ft_strcmp_local(instruction, "pa") == 0)
		pa_silent(a, b);
	else if (ft_strcmp_local(instruction, "pb") == 0)
		pb_silent(a, b);
	else if (ft_strcmp_local(instruction, "ra") == 0)
		ra_silent(a);
	else if (ft_strcmp_local(instruction, "rb") == 0)
		rb_silent(b);
	else if (ft_strcmp_local(instruction, "rr") == 0)
		rr_silent(a, b);
	else if (ft_strcmp_local(instruction, "rra") == 0)
		rra_silent(a);
	else if (ft_strcmp_local(instruction, "rrb") == 0)
		rrb_silent(b);
	else if (ft_strcmp_local(instruction, "rrr") == 0)
		rrr_silent(a, b);
	else
		return (0);  // Instruction invalide
	return (1);
}
