# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 18:30:46 by tschmitt          #+#    #+#              #
#    Updated: 2021/12/15 23:18:28 by tschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMMANDS & FLAGS
CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -g
INCLUDE_FLAGS = -I ./include/ -I $(LIBFT_PATH)include/
L_FLAGS = -lreadline
READLINE = -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC = -I /Users/$(USER)/.brew/opt/readline/include
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
EXPANDER_UTILS_PATH = $(BRAIN_PATH)utils/expander_utils/

# FILES
SRC = $(SRC_PATH)main.c \
		$(SRC_PATH)utils/env_var_utils.c $(SRC_PATH)utils/envv_get_set.c $(SRC_PATH)utils/error_utils.c $(SRC_PATH)utils/handle_signal.c\
		$(SRC_PATH)inbuilt/export.c $(SRC_PATH)inbuilt/echo.c $(SRC_PATH)inbuilt/env.c $(SRC_PATH)inbuilt/cd.c $(SRC_PATH)inbuilt/pwd.c $(SRC_PATH)inbuilt/unset.c $(SRC_PATH)inbuilt/exit.c \
		$(SRC_PATH)inbuilt/utils/export_special.c $(SRC_PATH)inbuilt/utils/export_input_error.c $(SRC_PATH)inbuilt/utils/export_only.c \
		$(BRAIN_PATH)lexer.c $(BRAIN_PATH)parser.c $(BRAIN_PATH)expander.c $(BRAIN_PATH)executor.c \
		$(LEXER_UTILS_PATH)subshell_token_utils.c $(LEXER_UTILS_PATH)token_utils.c $(LEXER_UTILS_PATH)join_quotes.c $(LEXER_UTILS_PATH)check_syntax.c \
		$(LEXER_UTILS_PATH)join_quotes_utils.c $(LEXER_UTILS_PATH)join_quotes_utils_two.c \
		$(BRAIN_GETTER_SETTER_PATH)envp_get_set.c $(BRAIN_GETTER_SETTER_PATH)iter_get_set.c $(BRAIN_GETTER_SETTER_PATH)lexer_get_set.c $(BRAIN_GETTER_SETTER_PATH)par_tok_get_set.c $(BRAIN_GETTER_SETTER_PATH)expander_get_set.c \
		$(PARSER_UTILS_PATH)get_tokens_utils.c $(PARSER_UTILS_PATH)get_tokens.c $(PARSER_UTILS_PATH)interprete_env_var.c $(PARSER_UTILS_PATH)parser_utils.c $(PARSER_UTILS_PATH)tok_redir_utils.c $(PARSER_UTILS_PATH)get_dir_items.c \
		$(EXPANDER_UTILS_PATH)heredoc_utils.c $(EXPANDER_UTILS_PATH)handle_redirs_utils.c $(EXPANDER_UTILS_PATH)handle_pipes.c $(EXPANDER_UTILS_PATH)set_pipe_type.c $(EXPANDER_UTILS_PATH)expander_utils.c \
		$(SRC_PATH)brain/utils/executor_utils/executor_utils.c
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))
LIBFT_SRC = $(LIBFT_PATH)src/*/*.c

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

# @$(CC) $(CC_FLAGS) $(INCLUDE_FLAGS) $(L_FLAGS) $(LIBFT_NAME) $(OBJ) -o $(NAME)
$(NAME): $(OBJ) $(LIBFT_NAME)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(OBJ) $(READLINE) $(READLINE_INC) $(CC_FLAGS) $(LIBFT_PATH)lib/libft.a $(L_FLAGS) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

$(LIBFT_NAME): $(LIBFT_SRC)
	@echo $(Y)Compiling [$(LIBFT_NAME)]...$(X)
	@make -C $(LIBFT_PATH) all

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(READLINE_INC) $(INCLUDE_FLAGS) -o $@ -c $<
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
	norminette | grep Error | egrep --color '.*Error!|$$'
	@echo $(G)Done$(X)

run: all
	$(NAME)


.PHONY: all, clean, fclean, re, norm
