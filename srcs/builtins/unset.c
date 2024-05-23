/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:38:32 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/23 20:26:41 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * change voids func to -> int
 */

void	unset_env(t_data *data, int arg_num)
{
	char	**env;
	char	*arg;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var = NULL;
	arg = ft_strchr_before_c(data->tokens->args[arg_num], '=');
	if (ft_calloc(data, F_TOKCMD, (void **)&env, sizeof(char *)
			* (data->env_len + 2)))
	{
		free(arg);
		return ;
	}
	while (j < data->env_len)
	{
		var = ft_strchr_before_c(data->env[j], '=');
		if (var == NULL || ft_strcmp(var, arg) != 0)
			env[i++] = data->env[j];
		else
			free(data->env[j]);
		j++;
		free(var);
	}
	free(arg);
	free(data->env);
	data->env = env;
	data->env_len = i;
}

void	ft_unset(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tokens->args_num)
	{
		unset_env(data, i);
		i++;
	}
}
