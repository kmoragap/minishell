/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 18:36:30 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd_path(t_data *data)
{
	if (check_builtins(data->tokens->cmd) > -1)
	{
		execute_builtin(data);
		exit(0);
	}
	if (check_relative(data->tokens->cmd) == 0)
	{
		if (find_path(data) == 1)
			error_in_child(data, 127, data->tokens->cmd, "command not found");
	}
	else
		check_absolute_path(data);
	return ;
}

t_data	*remove_quotes(char *cmd, t_data *data)
{
	int		i;
	int		check;
	char	*new;

	i = 0;
	check = 0;
	while (cmd[i] && check == 0)
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			check = cmd[i];
		i++;
	}
	if (check == 0)
		return (data);
	new = ft_strndup(cmd, i - 1);
	while (cmd[i])
		loop_quotes(cmd, &new, &i, &check);
	free(data->tokens->cmd);
	if (new)
		data->tokens->cmd = new;
	i = 0;
	return (data);
}

char	*remove_quotes_args(char *arg)
{
	int		i;
	int		check;
	char	*new;

	i = 0;
	check = 0;
	while (arg[i] && check == 0)
	{
		if (arg[i] == 34 || arg[i] == 39)
			check = arg[i];
		i++;
	}
	if (check == 0)
		return (arg);
	new = ft_strndup(arg, i - 1);
	while (arg[i])
		loop_quotes(arg, &new, &i, &check);
	if (!new)
		return (arg);
	free(arg);
	return (new);
}

void	loop_quotes(char *cmd, char **new, int *i, int *check)
{
	int	j;

	j = 0;
	while (cmd[*i + j] != *check && cmd[*i + j])
		j++;
	*new = ft_strnjoin(*new, &cmd[*i], j);
	*i = *i + j;
	if (!cmd[*i])
		return ;
	if (cmd[*i] && (cmd[*i] == 34 || cmd[*i] == 39))
		*check = cmd[*i];
	*i = *i + 1;
}

int	check_relative(char *cmd)
{
	if (ft_strchr(cmd, '/') == 1)
		return (0);
	return (1);
}
