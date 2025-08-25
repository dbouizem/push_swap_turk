
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

/* ================ STRUCTURES ===============*/

typedef struct s_stack
{
	int	*data;
	int	size;
	int	capacity;
}	t_stack;

typedef struct s_cost
{
	int	total;
	int	ra_count;
	int	rra_count;
	int	rb_count;
	int	rrb_count;
	int	element_index;
}	t_cost;

/* ================ STACK MANAGEMENT =============== */

t_stack	*create_stack(int capacity);
void	free_stack(t_stack *stack);
int		is_empty(t_stack *stack);
int		is_full(t_stack *stack);
void	push_to_stack(t_stack *stack, int value);


/* ============== PARSING & VALIDATION =============== */

t_stack	*parse_arguments(int ac, char **av);
t_stack	*parse_single_string(char *str);
int		is_valid_number(char *str);
long	ft_atol_safe(char *str);
int		has_duplicates(t_stack *stack);

/* ============== UTILITY FUNCTIONS ================ */

/* Position utils */
int		find_min(t_stack *stack);
int		find_max(t_stack *stack);
int		find_position(int value, t_stack *stack);
int		find_target_position_in_a(int value, t_stack *a);
int		find_target_position_in_b(int value, t_stack *b);

/* Validation utils */
int		is_sorted(t_stack *stack);

/* Math utils */
int		min_value(int a, int b);
int		abs_value(int n);

/* Error utils */
void	error_exit(void);
void	cleanup_and_exit(t_stack *a, t_stack *b);

/* Parsing utils */
void	ft_free_split(char **split);
int		validate_input_format(char *str);
void	cleanup_parse_and_exit(t_stack *stack, char **numbers);
t_stack	*create_and_fill_stack(char **numbers, int count);

/* Sorting utils */
void	sort_three_operations(t_stack *a, int first, int second, int third);

/* Cost_utils */
t_cost	find_cheapest_element_b_to_a(t_stack *a, t_stack *b);

/* Stack utils  */
t_stack	*create_stack(int capacity);
void	free_stack(t_stack *stack);

/* Debug utils  */
void	print_stack(t_stack *stack, char name);
void	print_both_stacks(t_stack *a, t_stack *b);

/* =================== OPERATIONS =================== */

/* Swap operations */
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);

/* Push operations */
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

/* Rotate operations */
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);

/* Reverse rotate operations */
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/* Silent operations (bonus) */
void	sa_silent(t_stack *a);
void	sb_silent(t_stack *b);
void	ss_silent(t_stack *a, t_stack *b);
void	pa_silent(t_stack *a, t_stack *b);
void	pb_silent(t_stack *a, t_stack *b);
void	ra_silent(t_stack *a);
void	rb_silent(t_stack *b);
void	rr_silent(t_stack *a, t_stack *b);
void	rra_silent(t_stack *a);
void	rrb_silent(t_stack *b);
void	rrr_silent(t_stack *a, t_stack *b);

/* ============== MAIN ALGORITHM FUNCTIONS =============== */

void	push_swap(t_stack *a, t_stack *b);
void	turk_algorithm(t_stack *a, t_stack *b);

/* Small sorting */
void	sort_two(t_stack *a);
void	sort_three(t_stack *a);
void	sort_four(t_stack *a, t_stack *b);
void	sort_five(t_stack *a, t_stack *b);
void	sort_small_stack(t_stack *a, t_stack *b);

/* ================ COST CALCULATION ===================== */

t_cost	calculate_cost_a_to_b(int pos_a, int value, t_stack *a, t_stack *b);
t_cost	calculate_cost_b_to_a(int pos_b, int value, t_stack *a, t_stack *b);
t_cost	find_cheapest_element_a_to_b(t_stack *a, t_stack *b);
t_cost	find_cheapest_element_b_to_a(t_stack *a, t_stack *b);

/* =============== MOVEMENT EXECUTION ================= */

void	execute_optimal_moves(t_stack *a, t_stack *b, t_cost cost);
void	bring_min_to_top(t_stack *a);

/* ================ CHECKER (BONUS) ================ */

int		execute_instruction_silent(char *instruction, t_stack *a, t_stack *b);

// utils bonus
char	*read_line_from_stdin(void);
char	*clean_instruction(char *instruction);

#endif
