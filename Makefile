# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 18:30:46 by tschmitt          #+#    #+#              #
#    Updated: 2021/11/24 12:42:41 by tblaase          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMMANDS & FLAGS
CC = gcc
CC_FLAGS = -Wall -Werror -Wextra
INCLUDE_FLAGS = -I ./include/ -I $(LIBFT_PATH)include/
RM = rm -f

# EXECUTABLE
NAME = ./minishell
LIBFT_NAME = $(LIBFT_PATH)lib/libft.a

# PATHS
SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIBFT_PATH = ./libft/

# FILES
SRC = $(SRC_PATH)main.c \
		$(SRC_PATH)inbuilt/export.c $(SRC_PATH)inbuilt/echo.c $(SRC_PATH)inbuilt/env.c $(SRC_PATH)inbuilt/cd.c $(SRC_PATH)inbuilt/pwd.c $(SRC_PATH)inbuilt/unset.c \
		$(SRC_PATH)inbuilt/utils/export_special.c $(SRC_PATH)inbuilt/utils/env_utils.c $(SRC_PATH)inbuilt/utils/export_input_error.c $(SRC_PATH)inbuilt/utils/export_only.c
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
	@$(CC) $(OBJ) $(CC_FLAGS) $(INCLUDE_FLAGS) $(LIBFT_NAME) -o $(NAME)
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


.PHONY: all, clean, fclean, re, norm
