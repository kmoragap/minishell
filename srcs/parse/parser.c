/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 20:27:24 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*parser(t_data *data)
{
	if (!data->input[0])
		return (data);
	while ((data)->tokens->id < (data)->token_num)
	{
		if (check_empty_cmd(data->tokens, data) == 1)
			return (data);
		else if (check_expand(data) == 1)
			(data->tokens)->type = EXPAND;
		else if (check_fd(data->tokens) == 1)
			(data->tokens)->type = FD;
		else if (check_file(data->tokens) == 1)
			(data->tokens)->type = FLE;
		else
			(data->tokens)->type = CMD;
		if ((data->tokens)->id == ((data)->token_num - 1))
			break ;
		data->tokens = (data->tokens)->next;
	}
	data->tokens = move_to_first_token(data->tokens);
	return (data);
}

int	check_empty_cmd(t_token *move, t_data *data)
{
	if ((move)->cmd && (move)->cmd[0])
		return (0);
	input_error(data, F_TOKS, 32, "\n");
	return (1);
}

int	check_expand(t_data *data)
{
	if (data->tokens->delim == REDIR_H && has_quotes(data->tokens->cmd) == 1)
		data->tokens->quotes = 1;
	data = remove_quotes(data->tokens->cmd, data);
	if (check_expand_var(data->tokens->cmd))
	{
		expand_cmd(data->tokens, data->env, data->exit_code);
		return (1);
	}
	if (data->tokens->args_num != 0)
	{
		if (check_expand_args(data->tokens->args) == 1)
		{
			expand_args(data->tokens, data->env, data->exit_code);
			return (1);
		}
	}
	remove_quotes_from_args(data);
	return (0);
}

int	check_fd(t_token *move)
{
	if ((move)->delim == 6 || (move)->delim == 7 || (move)->delim == 8
		|| (move)->delim == 9)
	{
		if ((move)->cmd[0] == '&' && (move)->cmd[1] >= '0'
			&& (move)->cmd[1] <= '9')
			return (1);
	}
	return (0);
}

int	check_file(t_token *move)
{
	if ((move)->delim == 6 || (move)->delim == 7 || (move)->delim == 8
		|| (move)->delim == 9)
		return (1);
	return (0);
}
