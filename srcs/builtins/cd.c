/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:48:53 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 20:24:38 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data)
{
	char	*old_pwd;
	char	*path;
	char	*new_path;

	new_path = NULL;
	path = NULL;
	if (check_arg_num(data) == 1)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		write(2, "Failed to get current directory\n", 32);
		data->exit_code = 1;
		return ;
	}
	if (data->tokens->args_num > 0)
		path = get_env(data, path);
	else
		path = getenv("HOME");
	if (ft_strncmp(data->tokens->args[0], "~/", 2) == 0)
		new_path = path;
	execute_cd(data, path, old_pwd);
	if (new_path)
		free(new_path);
	free(old_pwd);
}

int	check_arg_num(t_data *data)
{
	if (data->tokens->args_num > 1)
	{
		input_error(data, 0, 1, "minishell: cd: too many arguments\n");
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

char	*get_env(t_data *data, char *path)
{
	if (ft_strcmp(data->tokens->args[0], "~") == 0)
		return (getenv("HOME"));
	else if (ft_strncmp(data->tokens->args[0], "~/", 2) == 0)
		return (ft_strjoin(getenv("HOME"), data->tokens->args[0] + 1));
	else if (ft_strcmp(data->tokens->args[0], "-") == 0)
	{
		path = getenv("OLDPWD");
		write(STDOUT_FILENO, path, ft_strlen(path));
		write(STDOUT_FILENO, "\n", 1);
		return (path);
	}
	else
		return (data->tokens->args[0]);
}

void	execute_cd(t_data *data, char *path, char *old_pwd)
{
	char	*new_pwd;

	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		input_error(data, 0, 1, "minishell: No such file or directory\n");
		data->exit_code = 1;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		input_error(data, 0, 1, "Failed to get new directory\n");
		data->exit_code = 1;
		return ;
	}
	update_env_vars(data, old_pwd, new_pwd);
	free(new_pwd);
	data->exit_code = 0;
}
