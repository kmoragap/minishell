/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:26:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 17:15:54 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_token_value(char *token, char **env)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	var = NULL;
	value = NULL;
	while (env[++i] != NULL)
	{
		var = ft_strchr_before_c(env[i], '=');
		value = ft_strchr_after_c(env[i], '=');
		if (ft_strcmp(var, token) == 0)
		{
			if (value && value[0] == '$')
			{
				value = expand_token(value, env);
				if (value != NULL)
					return (ft_strdup(value));
			}
			free(var);
			return (ft_strdup(value));
		}
		free(var);
	}
	return (ft_strdup(""));
}

char	*expand_token(char *token, char **env)
{
	char	*resolved_value;

	resolved_value = NULL;
	if (ft_strnum(token))
		return (ft_strdup(token));
	resolved_value = resolve_token_value(token, env);
	return (resolved_value);
}

static void	expand_single_arg(char **arg, char **env)
{
	char	*expanded_arg;

	expanded_arg = expander_fun(*arg, env);
	if (expanded_arg != NULL)
	{
		free(*arg);
		*arg = expanded_arg;
	}
}

static void	expand_multiple_args(t_token *token, char **env)
{
	char	*expanded_arg;
	int		i;

	i = 0;
	while (token->args[i] != NULL)
	{
		if (check_expand_args(&token->args[i]) == 1)
		{
			expanded_arg = expander_fun(token->args[i], env);
			if (expanded_arg != NULL)
			{
				free(token->args[i]);
				token->args[i] = expanded_arg;
			}
		}
		i++;
	}
}

void	expand_args(t_token *token, char **env)
{
	int	i;

	i = 0;
	while (token->args[i] != NULL)
	{
		if (token->args_num == 1)
			expand_single_arg(&token->args[i], env);
		else if (token->args_num > 1)
			expand_multiple_args(token, env);
		i++;
	}
}
