/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:48:53 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/27 15:48:18 by kmoraga          ###   ########.fr       */
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
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		write(2, "Failed to get current directory\n", 31);
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
}

char	*ft_concat(char *old, char *old_pwd)
{
	ft_strcat(old, "OLDPWD=");
	ft_strcat(old, old_pwd);
	return (old);
}

void	update_env_vars(t_data *data, char *old_pwd, char *new_pwd)
{
	char	*old;
	char	*new;
	size_t	old_len;
	size_t	new_len;

	old_len = ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1;
	new_len = ft_strlen("PWD=") + ft_strlen(new_pwd) + 1;
	old = ft_calloc_norm(old_len, sizeof(char));
	new = ft_calloc_norm(new_len, sizeof(char));
	if (old == NULL || new == NULL)
	{
		malloc_error(data, F_PIDS);
		if (old)
			free(old);
		return ;
	}
	old = ft_concat(old, old_pwd);
	ft_strcat(new, "PWD=");
	ft_strcat(new, new_pwd);
	if (replace_var_env(data, old) == 0)
		return ;
	if (replace_var_env(data, new) == 0)
		return ;
	free(old);
	free(new);
}
