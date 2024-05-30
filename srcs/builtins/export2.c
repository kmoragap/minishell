/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 22:20:53 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_case(t_data *data)
{
	int		i;
	char	**env_cpy;

	env_cpy = ft_calloc_norm(data->env_len + 1, sizeof(char *));
	if (!env_cpy)
	{
		data->exit_code = 1;
		return ;
	}
	i = 0;
	while (i < data->env_len)
	{
		env_cpy[i] = ft_strdup(data->env[i]);
		if (!env_cpy[i])
		{
			data->exit_code = 1;
			return (free(env_cpy));
		}
		i++;
	}
	sort_env_case2(data, env_cpy, i);
}

void	sort_env_case2(t_data *data, char **env_cpy, int i)
{
	env_cpy[i] = NULL;
	env_cpy = cpy_envi(env_cpy);
	i = 0;
	while (env_cpy[i])
		write_env(env_cpy[i++]);
	i = -1;
	while (env_cpy[++i])
		free(env_cpy[i]);
	free(env_cpy);
	data->exit_code = 0;
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
			create_env_var(data, i, NULL);
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
