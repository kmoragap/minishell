/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:55:00 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 22:17:57 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(t_data *data, int arg_num, char *arg)
{
	if (arg)
		return (ft_strdup(arg));
	return (ft_strdup(data->tokens->args[arg_num]));
}

static int	handle_invalid_identifier(t_data *data, char *env_var)
{
	data->exit_code = write_error("export: ", env_var,
			": not a valid identifier\n", 1);
	free(env_var);
	return (1);
}

static int	copy_existing_env_vars(t_data *data, char **env)
{
	int	i;

	i = -1;
	while (++i < data->env_len)
		env[i] = data->env[i];
	return (i);
}

void	create_env_var(t_data *data, int arg_num, char *arg)
{
	char	**env;
	char	*env_var;
	int		i;

	if (ft_calloc(data, F_TOKCMD, (void **)&env, sizeof(char *) * (data->env_len
				+ 2)))
		return ;
	i = copy_existing_env_vars(data, env);
	env_var = get_env_var(data, arg_num, arg);
	if (!env_var)
		return (free(env));
	if (!ft_isdigit(env_var[0]))
	{
		env[i] = ft_strdup(env_var);
		if (!env[i])
			return (free(env));
	}
	else if (handle_invalid_identifier(data, env_var))
		return (free(env));
	if (env[i] == NULL)
		return (free(env));
	free(data->env);
	free(env_var);
	data->env = env;
	data->env_len = i + 1;
}
