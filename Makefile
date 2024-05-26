# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 14:39:22 by kmoraga           #+#    #+#              #
#    Updated: 2024/05/26 17:26:00 by kmoraga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = 	srcs/main.c \
		srcs/token/tokenizer.c \
		srcs/token/check_input.c \
		srcs/token/check_special.c \
		srcs/token/get_cmd.c \
		srcs/token/get_args.c \
		srcs/token/input_args.c \
		srcs/parse/parser.c \
		srcs/expansion/expansion.c \
		srcs/expansion/expansion_utils.c \
		srcs/expansion/expand_special_cases.c \
		srcs/expansion/expander.c \
		srcs/expansion/expander_work.c \
		srcs/expansion/handle_doubles_quotes.c \
		srcs/execution/check_cmd_path.c \
		srcs/execution/check_cmd_path2.c \
		srcs/execution/children.c \
		srcs/execution/dup_pipes.c \
		srcs/execution/dup_pipes2.c \
		srcs/execution/close_pipes.c \
		srcs/execution/execution.c \
		srcs/execution/join_cmd_arg.c \
		srcs/execution/parent_wait.c \
		srcs/execution/piping.c \
		srcs/free/free.c \
		srcs/signal/signal.c \
		srcs/error/error.c \
		srcs/utils/shlvl.c \
		srcs/utils/utils.c \
		srcs/utils/utils2.c \
		srcs/utils/utils3.c \
		srcs/utils/utils4.c \
		srcs/utils/utils5.c \
		srcs/utils/utils6.c \
		srcs/utils/ft_split.c \
		srcs/utils/strtok.c \
		srcs/utils/strtok2.c \
		srcs/builtins/export.c \
		srcs/builtins/export2.c \
		srcs/builtins/builtins_utils.c \
		srcs/builtins/env.c \
		srcs/builtins/unset.c \
		srcs/builtins/pwd.c \
		srcs/builtins/exit.c \
		srcs/builtins/echo.c \
		srcs/builtins/cd.c \
		srcs/heredoc/heredoc.c \
		srcs/utils/ft_strtrim.c \
		srcs/utils/get_next_line/get_next_line.c \
		srcs/utils/get_next_line/get_next_line_utils.c

INC = includes/ 

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC)
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
	@echo "$(RED) Cleaning object files...$(RESET)"
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