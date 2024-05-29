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
			return (free_ar(ar));
		if (var != NULL && ft_strcmp(var, ar) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(arg);
			free_two(var, ar);
			if (!data->env[i])
				return (0);
			return (1);
		}
		free(var);
	}
	return (free_ar(ar));
}

void	free_two(char *var, char *ar)
{
	free(var);
	free(ar);
}

int	free_ar(char *ar)
{
	free(ar);
	return (0);
}
