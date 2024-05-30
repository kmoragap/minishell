/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 21:57:32 by kmoraga          ###   ########.fr       */
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

void	write_env(char *str)
{
	char	*var;
	char	*value;

	if (str[0] == '_')
		return ;
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
		write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, value, ft_strlen(value));
		write(STDOUT_FILENO, "\"\n", 2);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
	if (var)
		free(var);
}
