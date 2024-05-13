# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: creuther <creuther@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 14:39:22 by kmoraga           #+#    #+#              #
#    Updated: 2024/05/10 16:34:37 by creuther         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = 	srcs/main.c \
		srcs/token/tokenizer.c \
		srcs/token/check_special.c \
		srcs/token/get_cmd.c \
		srcs/token/get_args.c \
		srcs/parse/parser.c \
		srcs/print_data/print.c \
		srcs/expansion/expansion.c \
		srcs/expansion/expansion_utils.c \
		srcs/execution/check_cmd_path.c \
		srcs/execution/children.c \
		srcs/execution/close_pipes.c \
		srcs/execution/execution.c \
		srcs/execution/join_cmd_arg.c \
		srcs/execution/parent_wait.c \
		srcs/execution/piping.c \
		srcs/utils/utils.c \
		srcs/utils/ft_split.c \
		srcs/free/free.c \
		srcs/error/error.c

INC = includes/

OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I $(INC)
LDFLAGS = -lreadline

#Colores
YELLOW = \033[1;33m
RESET = \033[1m
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW) Compiling...$(RESET)"
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN) Compilation completed.$(RESET)"
	@echo "$(BLUE)"
	@echo "$(BLUE) Minishell is ready to use $(RESET)"

$(OBJ): %.o: %.c
	@echo "$(YELLOW) Compiling object files $@...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED) Cleaning object files...(RESET)"
	@rm -f $(OBJ) $(B_OJBS)
	@echo "$(GREEN) Object files cleaned.$(RESET)"

fclean:
	@echo "$(RED) Cleaning object files...$(RESET)"
	@rm -f $(OBJ) $(B_OJBS)
	@echo "$(GREEN) Object files cleaned.$(RESET)"
	@echo "$(RED) Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN) Executable cleaned.$(RESET)"	


re: fclean all