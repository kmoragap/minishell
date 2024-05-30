/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:07:09 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 17:30:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_data *data)
{
	t_token	*curr_token;
	int		newline;
	int		i;

	curr_token = data->tokens;
	newline = 1;
	i = 0;
	while (curr_token->args_num > 0 && is_n_option(curr_token->args[i])
		&& curr_token->args[i] != NULL)
	{
		newline = 0;
		i++;
	}
	while (i < curr_token->args_num)
	{
		write(STDOUT_FILENO, curr_token->args[i],
			ft_strlen(curr_token->args[i]));
		if (i + 1 < curr_token->args_num)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	check_next_token(curr_token, &newline);
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	data->exit_code = 0;
}

void	check_next_token(t_token *curr_token, int *newline)
{
	int	i;

	while (curr_token && curr_token->next && curr_token->next->delim != PIPE)
	{
		curr_token = curr_token->next;
		i = 0;
		if (curr_token->prev->args_num == 0)
		{
			while (curr_token->args_num > 0 && is_n_option(curr_token->args[i])
				&& curr_token->args[i] != NULL)
			{
				*newline = 0;
				i++;
			}
		}
		while (i < curr_token->args_num)
		{
			write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, curr_token->args[i],
				ft_strlen(curr_token->args[i]));
			i++;
		}
	}
}
