# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 14:39:22 by kmoraga           #+#    #+#              #
#    Updated: 2024/04/27 14:40:04 by kmoraga          ###   ########.fr        #
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
		srcs/utils/utils.c \
		srcs/free/free.c \
		srcs/error/error.c

INC = includes/ \
		srcs/utils/utils2.c \
		srcs/utils/strtok.c \
		srcs/builtins/builtins_utils.c \
		srcs/builtins/export.c \
		srcs/execution/execution.c \
		srcs/execution/execute_builtin.c \

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