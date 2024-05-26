/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:26:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 13:21:36 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_token_value(char *token, char **env, int exit_status)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	var = NULL;
	value = NULL;
	while (env[i] != NULL)
	{
		var = ft_strchr_before_c(env[i], '=');
		value = ft_strchr_after_c(env[i], '=');
		if (ft_strcmp(var, token) == 0)
		{
			if (value && value[0] == '$')
			{
				value = expand_token(value, env, exit_status);
				if (value != NULL)
					return (ft_strdup(value));
			}
			free(var);
			return (ft_strdup(value));
		}
		free(var);
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_token(char *token, char **env, int status)
{
	char	*resolved_value;

	resolved_value = NULL;
	if (ft_strnum(token))
		return (ft_strdup(token));
	resolved_value = resolve_token_value(token, env, status);
	return (resolved_value);
}

void	expand_cmd(t_token *token, char **env, int status)
{
	char	*expanded_cmd;

	expanded_cmd = NULL;
	if (check_expand_var(token->cmd))
	{
		expanded_cmd = expander_fun(token->cmd, env, status);
		if (expanded_cmd != NULL)
		{
			free(token->cmd);
			token->cmd = expanded_cmd;
		}
	}
}

char	valid_delim_expand(char c)
{
	if ((c >= 32 && c <= 33) || c == 35 || (c >= 36 && c <= 47) || (c >= 58
			&& c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)
		|| c == 34 || c == 39)
		return (c);
	return (0);
}

char	*expand_variable(char *var, char **env, int status)
{
	char	*expanded;
	expanded = expand_token(var, env, status);
	if (expanded)
		return (expanded);
	else
		return (ft_strdup(var));
}


void	expand_args(t_token *token, char **env, int status)
{
	char	*expanded_arg;
	int		i;

	expanded_arg = NULL;
	i = 0;
	while (token->args[i] != NULL)
	{
		if (token->args_num == 1)
		{	
			expanded_arg = expander_fun(token->args[i], env, status);
			if (expanded_arg != NULL)
			{
				free(token->args[i]);
				token->args[i] = expanded_arg;
			}
		}
		else if (token->args_num > 1)
		{
			if (check_expand_args(&token->args[i]) == 1)
			{
				expanded_arg = expander_fun(token->args[i], env, status);
				if (expanded_arg != NULL)
				{
					free(token->args[i]);
					token->args[i] = expanded_arg;
				}
			}
		}
		i++;
	}
}