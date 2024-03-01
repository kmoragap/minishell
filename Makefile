# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 14:39:22 by kmoraga           #+#    #+#              #
#    Updated: 2024/03/01 14:21:37 by kmoraga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = 	srcs/main.c \
		srcs/parser.c \
		srcs/lexer.c \
		srcs/read_input.c \
		srcs/execute.c \
		debug/check_tokens_lst.c \

OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
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
	@$(CC) $(CFLAGS) -c $< -o $@

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