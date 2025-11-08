# Nome do executável
NAME = pipex

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./inc -I../../libft -I../../ft_printf/includes

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# Bibliotecas
LIBFT_DIR = ../../libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ../../ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Arquivos fonte
SRCS = $(SRC_DIR)/pipex.c \
       $(SRC_DIR)/pipex_utils.c

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Cores para output bonito
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Regra principal
all: $(NAME)

# Criar diretório de objetos
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compilar libft
$(LIBFT):
	@echo "$(YELLOW)Compilando libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft compilada!$(RESET)"

# Compilar ft_printf
$(PRINTF):
	@echo "$(YELLOW)Compilando ft_printf...$(RESET)"
	@make -C $(PRINTF_DIR)
	@echo "$(GREEN)✓ ft_printf compilada!$(RESET)"

# Compilar objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compilando $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Criar executável
$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	@echo "$(YELLOW)Linkando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

# Limpar objetos
clean:
	@echo "$(RED)Limpando objetos...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean
	@echo "$(GREEN)✓ Objetos removidos!$(RESET)"

# Limpar tudo
fclean: clean
	@echo "$(RED)Limpando executável...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	@echo "$(GREEN)✓ Tudo limpo!$(RESET)"

# Recompilar tudo
re: fclean all

# Testar o programa
test: all
	@echo "$(YELLOW)Rodando testes básicos...$(RESET)"
	@echo "apple\nbanana\napricot" > input.txt
	@./pipex input.txt "grep a" "wc -l" output.txt
	@echo "$(GREEN)Resultado do teste:$(RESET)"
	@cat output.txt
	@rm -f input.txt output.txt

# Testar com valgrind
valgrind: all
	@echo "$(YELLOW)Rodando valgrind...$(RESET)"
	@echo "test" > input.txt
	@valgrind --leak-check=full --show-leak-kinds=all \
		./pipex input.txt "cat" "grep test" output.txt
	@rm -f input.txt output.txt

# Norminette
norm:
	@echo "$(YELLOW)Checando norminette...$(RESET)"
	@norminette $(SRC_DIR) $(INC_DIR)

.PHONY: all clean fclean re test valgrind norm