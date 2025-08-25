#include "../push_swap.h"

static void	handle_instruction_error(char *instruction, t_stack *a, t_stack *b)
{
	if (instruction)
		free(instruction);
	ft_putstr_fd("Error\n", 2);
	free_stack(a);
	free_stack(b);
	exit(1);
}

static void	process_instructions(t_stack *a, t_stack *b)
{
	char	*instruction;

	instruction = read_line_from_stdin();
	while (instruction != NULL)
	{
		instruction = clean_instruction(instruction);
		if (!instruction || !*instruction)
		{
			free(instruction);
			instruction = read_line_from_stdin();
			continue ;
		}
		if (!execute_instruction_silent(instruction, a, b))
			handle_instruction_error(instruction, a, b);
		free(instruction);
		instruction = read_line_from_stdin();
	}
}

static void	print_result(t_stack *a, t_stack *b)
{
	if (is_sorted(a) && is_empty(b))
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;

	if (ac == 1)
		return (0);
	a = parse_arguments(ac, av);
	if (!a)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	b = create_stack(a->capacity);
	if (!b)
	{
		free_stack(a);
		error_exit();
	}
	process_instructions(a, b);
	print_result(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
