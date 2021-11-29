# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 18:30:46 by tschmitt          #+#    #+#              #
#    Updated: 2021/11/29 19:56:19 by tschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMMANDS & FLAGS
CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -g
INCLUDE_FLAGS = -I ./include/ -I $(LIBFT_PATH)include/
L_FLAGS = -lreadline
RM = rm -f

# EXECUTABLE
NAME = ./minishell
LIBFT_NAME = $(LIBFT_PATH)lib/libft.a

# PATHS
SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIBFT_PATH = ./libft/
BRAIN_PATH = $(SRC_PATH)brain/
LEXER_UTILS_PATH = $(BRAIN_PATH)utils/lexer_utils/
BRAIN_GETTER_SETTER_PATH = $(BRAIN_PATH)utils/getter_setter/
PARSER_UTILS_PATH = $(BRAIN_PATH)utils/parser_utils/

# FILES
SRC = 	$(SRC_PATH)main.c \
		$(BRAIN_PATH)lexer.c $(BRAIN_PATH)parser.c $(BRAIN_PATH)expander.c $(BRAIN_PATH)executor.c \
		$(LEXER_UTILS_PATH)subshell_token_utils.c $(LEXER_UTILS_PATH)token_utils.c $(LEXER_UTILS_PATH)join_quotes.c \
		$(BRAIN_GETTER_SETTER_PATH)envp_get_set.c $(BRAIN_GETTER_SETTER_PATH)iter_get_set.c $(BRAIN_GETTER_SETTER_PATH)lexer_get_set.c $(BRAIN_GETTER_SETTER_PATH)par_tok_get_set.c \
		$(PARSER_UTILS_PATH)check_syntax.c $(PARSER_UTILS_PATH)get_tokens_utils.c $(PARSER_UTILS_PATH)get_tokens.c $(PARSER_UTILS_PATH)interprete_vars.c $(PARSER_UTILS_PATH)parser_utils.c $(PARSER_UTILS_PATH)tok_redir_utils.c
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)
	@printf "\n"
	@echo $(G)"       _     _     _       _ _ "$(X)
	@echo $(G)" _____|_|___|_|___| |_ ___| | |"$(X)
	@echo $(G)"|     | |   | |_ -|   | -_| | |"$(X)
	@echo $(G)"|_|_|_|_|_|_|_|___|_|_|___|_|_|"$(X)
	@printf "\n\n"

$(NAME): $(OBJ) $(LIBFT_NAME)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(OBJ) ./libft/obj/*.o $(CC_FLAGS) $(INCLUDE_FLAGS) $(L_FLAGS)  -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

$(LIBFT_NAME):
	@echo $(Y)Compiling [$(LIBFT_NAME)]...$(X)
	@make -C $(LIBFT_PATH) all

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(INCLUDE_FLAGS) -o $@ -c $<
	@printf $(UP)$(CUT)
	@echo $(G)Finished [$@]$(X)
	@printf $(UP)$(CUT)

clean:
	@make -C $(LIBFT_PATH) clean
	@if [ -d "$(OBJ_PATH)" ]; then \
		$(RM) -r $(OBJ_PATH); \
		echo $(R)Cleaning" "[$(OBJ_PATH)]...$(X); \
	fi;

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@if [ -f "$(NAME)" ]; then \
		$(RM) $(NAME); \
		echo $(R)Cleaning" "[$(NAME)]...$(X); \
	fi;

re: fclean all

# TESTING RULES
norm:
	@echo $(G)Checking Norminette...$(X)
	norminette
	@echo $(G)Done$(X)

run: all
	$(NAME)


.PHONY: all, clean, fclean, re, norm
