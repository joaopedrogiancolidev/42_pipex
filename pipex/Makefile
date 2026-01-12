# Name
NAME = pipex

# Flags and compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./inc -I../../libft -I../../ft_printf/includes

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# Libft path
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ../ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Dir files
SRCS = $(SRC_DIR)/pipex.c \
		$(SRC_DIR)/pipex_path.c \
		$(SRC_DIR)/pipex_process.c \
       $(SRC_DIR)/pipex_utils.c

# Src objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output-colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# All
all: $(NAME)

# Obj dir create
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# libft compiler
$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft compiled!$(RESET)"

# printf compiler
$(PRINTF):
	@echo "$(YELLOW)Compiling ft_printf...$(RESET)"
	@make -C $(PRINTF_DIR)
	@echo "$(GREEN)✓ ft_printf compiled!$(RESET)"

# objects compiler
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# executable
$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compile success!$(RESET)"

# obj clean
clean:
	@echo "$(RED)objs cleaning...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean
	@echo "$(GREEN)✓ Objects removed!$(RESET)"

# all clean
fclean: clean
	@echo "$(RED)executable cleaning...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	@echo "$(GREEN)✓ ALl clear!$(RESET)"

# Recompile
re: fclean all

# Tests for pipex
test: all
	@echo "$(YELLOW)Basic test...$(RESET)"
	@echo "apple\nbanana\napricot" > input.txt
	@./pipex input.txt "grep a" "wc -l" output.txt
	@echo "$(GREEN)Test result:$(RESET)"
	@cat output.txt
	@rm -f input.txt output.txt

# Tests for valgrind
valgrind: all
	@echo "$(YELLOW)valgrind...$(RESET)"
	@echo "test" > input.txt
	@valgrind --leak-check=full --show-leak-kinds=all \
		./pipex input.txt "cat" "grep test" output.txt
	@rm -f input.txt output.txt

# Norminette
norm:
	@echo "$(YELLOW)Norm check...$(RESET)"
	@norminette $(SRC_DIR) $(INC_DIR)

.PHONY: all clean fclean re test valgrind norm