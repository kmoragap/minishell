/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/28 15:57:38 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_case(t_data *data)
{
	int		i;
	char	**env_cpy;

	env_cpy = ft_calloc_norm(data->env_len + 1, sizeof(char *));
	if (!env_cpy)
		return ;
	i = 0;
	while (i < data->env_len)
	{
		env_cpy[i] = ft_strdup(data->env[i]);
		if (!env_cpy[i])
			return (free(env_cpy));
		i++;
	}
	env_cpy[i] = NULL;
	env_cpy = cpy_envi(env_cpy);
	i = 0;
	while (env_cpy[i])
		write_env(env_cpy[i++]);
	i = -1;
	while (env_cpy[++i])
		free(env_cpy[i]);
	free(env_cpy);
	return ;
}

int	do_export_loop(t_data *data, char *var, int i)
{
	var = ft_strchr_before_c(data->tokens->args[i], '=');
	if (var[0] == '\0')
	{
		input_error(data, 0, 1, "export: not a valid identifier\n");
		free(var);
		return (1);
	}
	else if (!ft_isalnum(var[ft_strlen(var) - 1]))
	{
		input_error(data, 0, 1, "export: not a valid identifier\n");
		free(var);
		return (1);
	}
	else if (var != NULL)
	{
		if (replace_var_env(data, data->tokens->args[i]) == 0)
			create_env_var(data, i);
		free(var);
	}
	return (0);
}

void	execute_export_builtin(t_data *data)
{
	int		i;
	char	*var;

	var = NULL;
	if (data->tokens->args_num == 0)
		return (sort_env_case(data));
	i = 0;
	while (i < data->tokens->args_num && data->tokens->args[i] != NULL)
	{
		if (do_export_loop(data, var, i))
			break ;
		i++;
	}
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
