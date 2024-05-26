/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 18:31:13 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path(t_data *data)
{
	char	**path;
	int		lop;
	char	*tmp;

	tmp = path_from_env(data->env);
	path = ft_split(tmp, ':');
	free(tmp);
	if (!path)
		return (1);
	lop = 0;
	while (path[lop])
	{
		tmp = ft_strjoin(path[lop], "/");
		free(path[lop]);
		path[lop] = ft_strjoin(tmp, data->tokens->cmd);
		free(tmp);
		if (access(path[lop], F_OK) == 0 && access(path[lop], X_OK) == 0
			&& !data->tokens->path)
			data->tokens->path = ft_strdup(path[lop]);
		lop++;
	}
	free_args(path, &lop);
	if (data->tokens->path && data->tokens->path[0])
		return (0);
	return (1);
}

char	*path_from_env(char **env)
{
	int		lop;
	char	*path;
	char	*tmp;

	lop = 0;
	while (env[lop])
	{
		if (env[lop][0] == 'P' && env[lop][1] == 'A' && env[lop][2] == 'T'
			&& env[lop][3] == 'H' && env[lop][4] == '=')
		{
			tmp = ft_strdup(env[lop]);
			path = ft_strdup(&tmp[5]);
			free(tmp);
			return (path);
		}
		lop++;
	}
	return (NULL);
}

void	check_absolute_path(t_data *data)
{
	if (access(data->tokens->cmd, F_OK) != 0)
		error_in_child(data, 2, data->tokens->cmd, "No such file or directory");
	if (access(data->tokens->cmd, X_OK) != 0)
		error_in_child(data, 126, data->tokens->cmd, "Permission denied");
	data->tokens->path = ft_strdup(data->tokens->cmd);
}
