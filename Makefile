NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I libft
RM = rm -rf

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MAKE_LIBFT = $(MAKE) --no-print-directory -C $(LIBFT_DIR)

OBJ_DIR = obj

SRCS =	push_swap.c \
		parsing/input_parsing.c \
		parsing/input_validation.c \
		operations/swap.c \
		operations/push.c \
		operations/rotate.c \
		operations/reverse_rotate.c \
		operations/operations_silent.c \
		operations/rotate_silent.c \
		operations/combined_silent.c \
		sorting/small_sort.c \
		sorting/turk_algorithm.c \
		sorting/cost_calculation.c \
		sorting/movement_execution.c \
		utils/stack_utils.c \
		utils/position_utils.c \
		utils/validation_utils.c \
		utils/math_utils.c \
		utils/error_utils.c \
		utils/parsing_utils.c \
		utils/sorting_utils.c \
		utils/cost_utils.c \
		utils/debug_utils.c

BONUS_SRCS = bonus/checker_bonus.c \
			bonus/operation_bonus.c \
			bonus/checker_utils_bonus.c \
			parsing/input_parsing.c \
			parsing/input_validation.c \
			utils/parsing_utils.c \
			operations/operations_silent.c \
			operations/rotate_silent.c \
			operations/combined_silent.c \
			utils/position_utils.c \
			utils/validation_utils.c \
			utils/math_utils.c \
			utils/error_utils.c \
			utils/stack_utils.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
RESET = \033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) ready$(RESET)"

bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo "$(GREEN)✓ $(BONUS_NAME) ready$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE_LIBFT) clean
	@echo "$(CYAN)clean done$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE_LIBFT) fclean
	@echo "$(CYAN)fclean done$(RESET)"

$(LIBFT):
	@$(MAKE_LIBFT)

re: fclean all

.PHONY: all bonus clean fclean re
