/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/23 20:05:48 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * TODO:
 * -Iterate the env
 * -Create a new env variable at the start of the env
 * -Update the env
 * -Debe no funcionar cuando no hay export o eso es lo q creo (??????)
 * -No
 */

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
	i = 0;
	while (i < data->env_len)
	{
		env[i] = data->env[i];
		i++;
	}
	if (!ft_isdigit(data->tokens->args[arg_num][0]))
		env[i] = ft_strdup(data->tokens->args[arg_num]);
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
	i = 0;
	while (data->env[i] != NULL)
	{
		var = ft_strchr_before_c(data->env[i], '=');
		if (var != NULL && ft_strcmp(var, ar) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(arg);
			free(var);
			free(ar);
			return (1);
		}
		free(var);
		i++;
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
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "\n", 1);
}
