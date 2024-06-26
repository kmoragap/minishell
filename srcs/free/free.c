/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 20:27:47 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_child(t_data *data)
{
	if (data->free_code == 100)
	{
		free_env(data);
		return ;
	}
	if (data->free_code >= F_TOKS || data->free_code == NO_FREE)
		free_toks(data);
	if (data->free_code >= F_EMPTOK || data->free_code == NO_FREE)
		free(data->tokens);
	if (data->free_code >= F_INPUT || data->free_code == NO_FREE)
		free(data->input);
	if (data->childn->pids && (data->free_code >= F_PIDS
			|| data->free_code == NO_FREE))
		free(data->childn->pids);
	if (data->free_code == F_ENV)
		free_env(data);
}

void	free_all(t_data *data)
{
	if (data->free_code == 100)
	{
		free_env(data);
		return ;
	}
	if (data->free_code >= F_TOKS || data->free_code == NO_FREE)
		free_toks(data);
	if (data->free_code >= F_EMPTOK || data->free_code == NO_FREE)
		free(data->tokens);
	if (data->free_code >= F_INPUT || data->free_code == NO_FREE)
		free(data->input);
	if (data->childn->pids && (data->free_code >= F_PIDS
			|| data->free_code == NO_FREE))
	{
		free(data->childn->pids);
		data->childn->pids = NULL;
	}
	if (data->free_code == F_ENV)
	{
		free_env(data);
		return ;
	}
	reinit_data(data);
}

void	free_toks(t_data *data)
{
	if (!data || !data->tokens)
		return ;
	data->tokens = move_to_first_token(data->tokens);
	while (data->tokens)
	{
		while (data->tokens->args && data->tokens->args_num >= 0)
		{
			free(data->tokens->args[data->tokens->args_num]);
			data->tokens->args_num -= 1;
		}
		if (data->tokens->args)
			free(data->tokens->args);
		if (data->tokens->cmd)
			free(data->tokens->cmd);
		if (data->tokens->delim == REDIR_H)
			unlink(".heredoc_tmp");
		if (!data->tokens->next)
			break ;
		data->tokens = data->tokens->next;
		if (data->tokens->prev)
			free(data->tokens->prev);
	}
}

void	free_env(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->env)
		{
			while (i < data->env_len)
			{
				if (data->env[i])
					free(data->env[i]);
				i++;
			}
			free(data->env);
		}
	}
	if (data->childn)
		free(data->childn);
	free(data);
}
