/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/28 17:03:48 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error(char *str1, char *str2, char *str3, int exit_code)
{
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	return (exit_code);
}

void	create_env_var(t_data *data, int arg_num)
{
	char	**env;
	int		i;

	if (ft_calloc(data, F_TOKCMD, (void **)&env, sizeof(char *) * (data->env_len
				+ 2)))
		return ;
	i = -1;
	while (++i < data->env_len)
		env[i] = data->env[i];
	if (!ft_isdigit(data->tokens->args[arg_num][0]))
	{
		env[i] = ft_strdup(data->tokens->args[arg_num]);
		if (!env[i])
			return (free(env));
	}
	else
		data->exit_code = write_error("export: ", data->tokens->args[arg_num],
				": not a valid identifier\n", 1);
	if (env[i] == NULL)
		return (free(env));
	free(data->env);
	data->env = env;
	data->env_len = i + 1;
}

int	replace_var_env(t_data *data, char *arg)
{
	char	*ar;
	char	*var;
	int		i;

	ar = ft_strchr_before_c(arg, 61);
	if (!ar)
		return (0);
	i = -1;
	while (data->env[++i] != NULL)
	{
		var = ft_strchr_before_c(data->env[i], '=');
		if (!var)
		{
			free(ar);
			return (0);
		}
		if (var != NULL && ft_strcmp(var, ar) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(arg);
			if (!data->env[i])
				return (0);
			free(var);
			free(ar);
			return (1);
		}
		free(var);
	}
	free(ar);
	return (0);
}

char	**cpy_envi(char **env_cpy)
{
	int		i;
	int		swapped;
	char	*temp;

	i = 0;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env_cpy[i + 1])
		{
			if (ft_strcmp(env_cpy[i], env_cpy[i + 1]) > 0)
			{
				temp = env_cpy[i];
				env_cpy[i] = env_cpy[i + 1];
				env_cpy[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
	return (env_cpy);
}

void	write_env(char *str)
{
	char	*var;
	char	*value;

	var = NULL;
	value = NULL;
	var = ft_strchr_before_c(str, '=');
	if (!var)
		return ;
	value = ft_strchr_after_c(str, '=');
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, var, ft_strlen(var));
	if (value)
	{
		write(STDOUT_FILENO, "=\"", 3);
		write(STDOUT_FILENO, value, ft_strlen(value));
		write(STDOUT_FILENO, "\"\n", 2);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
	if (var)
		free(var);
}
