/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/10 17:27:35 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_pipes(t_data *data, int child_id)
{
	if (data->childn->cnt_childn == 1)
	{
		single_redir(data);
		return ;
	}
	if (child_id == 0)
	{
		check_redir_out(data, child_id);
		check_redir_in_first(data);
	}
	else if (child_id == (data->childn->cnt_childn - 1))
	{
		check_redir_in(data, child_id);
		check_redir_out_last(data);
	}
	else
	{
		check_redir_out(data, child_id);
		check_redir_in(data, child_id);
	}
}

void	single_redir(t_data *data)
{
	int	fd;

	if (!data->tokens->next)
		return ;
	while (data->tokens->next)
	{
		if (data->tokens->next->delim == REDIR_I
			|| data->tokens->next->delim == REDIR_H)
		{
			fd = redir_in(data);
			if (dup2(fd, STDIN_FILENO) == -1)
				error_in_child(data, 1, "dup2", "dup2 failed");
			close(fd);
		}
		if (data->tokens->next->delim == REDIR_O
			|| data->tokens->next->delim == REDIR_A)
		{
			fd = redir_out(data);
			if (dup2(fd, STDOUT_FILENO) == -1)
				error_in_child(data, 1, "dup2", "dup2 failed");
			close(fd);
		}
		if (data->tokens->next)
			data->tokens = data->tokens->next;
	}
}

void	check_redir_out_last(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (data->tokens->next && data->tokens->next->delim != PIPE)
	{
		if (data->tokens->next->delim == REDIR_O
			|| data->tokens->next->delim == REDIR_A)
		{
			fd = redir_out(data);
			if (dup2(fd, STDOUT_FILENO) == -1)
				error_in_child(data, 1, "dup2", "dup2 failed");
			close(fd);
			i++;
		}
		if (data->tokens->next && data->tokens->next->delim != PIPE)
			data->tokens = data->tokens->next;
	}
	while (i > 0)
	{
		data->tokens = data->tokens->prev;
		i--;
	}
}

void	check_redir_in_first(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (data->tokens->next && data->tokens->next->delim != PIPE)
	{
		if (data->tokens->next->delim == REDIR_I
			|| data->tokens->next->delim == REDIR_H)
		{
			fd = redir_in(data);
			if (dup2(fd, STDIN_FILENO) == -1)
				error_in_child(data, 1, "dup2", "dup2 failed");
			close(fd);
			i++;
		}
		if (data->tokens->next && data->tokens->next->delim != PIPE)
			data->tokens = data->tokens->next;
	}
	while (i > 0)
	{
		data->tokens = data->tokens->prev;
		i--;
	}
}

void	check_redir_in(t_data *data, int child_id)
{
	int	i;
	int	fd;

	i = 0;
	if (dup2(data->childn->pipes[child_id - 1][0], STDIN_FILENO) == -1)
		error_in_child(data, 1, "dup2", "dup2 failed");
	while (data->tokens->next && data->tokens->next->delim != PIPE)
	{
		if (data->tokens->next->delim == REDIR_I
			|| data->tokens->next->delim == REDIR_H)
		{
			fd = redir_in(data);
			if (dup2(fd, STDIN_FILENO) == -1)
				error_in_child(data, 1, "dup2", "dup2 failed");
			close(fd);
		}
		if (data->tokens->next && data->tokens->next->delim != PIPE)
		{
			data->tokens = data->tokens->next;
			i++;
		}
	}
	while (i-- > 0)
		data->tokens = data->tokens->prev;
}
