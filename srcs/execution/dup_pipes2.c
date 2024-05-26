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

void	check_redir_out(t_data *data, int child_id)
{
	int	i;
	int	fd;

	i = 0;
	if (dup2(data->childn->pipes[child_id][1], STDOUT_FILENO) == -1)
		error_in_child(data, 1, "dup2", "dup2 failed");
	while (data->tokens->next && data->tokens->next->delim != PIPE)
	{
		if (data->tokens->next->delim == REDIR_O
			|| data->tokens->next->delim == REDIR_A)
		{
			fd = redir_out(data);
			if (dup2(fd, STDOUT_FILENO) == -1)
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

int	redir_in(t_data *data)
{
	int	fd;

	fd = 0;
	if (data->tokens->next->delim == REDIR_H)
		fd = open(".heredoc_tmp", O_RDONLY | O_CREAT, S_IRWXU);
	else if (data->tokens->next->delim == REDIR_I)
	{
		fd = open(data->tokens->next->cmd, O_RDONLY, S_IRWXU);
		if (access(data->tokens->next->cmd, F_OK) == -1)
			error_in_child(data, 2, data->tokens->next->cmd,
				"No such file or directory");
		if (access(data->tokens->next->cmd, R_OK) == -1)
			error_in_child(data, 1, data->tokens->next->cmd,
				"Permission denied");
	}
	if (fd == -1)
		error_in_child(data, 2, data->tokens->next->cmd,
			"No such file or directory");
	return (fd);
}

int	redir_out(t_data *data)
{
	int	fd;

	fd = 0;
	if (data->tokens->next->delim == REDIR_A)
		fd = open(data->tokens->next->cmd,
				O_RDONLY | O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (data->tokens->next->delim == REDIR_O)
		fd = open(data->tokens->next->cmd,
				O_RDONLY | O_TRUNC | O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (access(data->tokens->next->cmd, F_OK | W_OK) == -1)
		error_in_child(data, 1, data->tokens->next->cmd, "Permission denied");
	if (fd == -1)
		error_in_child(data, 2, data->tokens->next->cmd,
			"No such file or directory");
	return (fd);
}
