/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_work2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:42:12 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/28 16:59:25 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_fragment(char *arg, int *i)
{
	char	*fragments;

	if (arg[*i] == '"')
		fragments = extract_quoted(arg, i, '"');
	else if (arg[*i] == '\'')
		fragments = extract_quoted(arg, i, '\'');
	else if (arg[*i] == '$')
		fragments = extract_variable(arg, i);
	else
		fragments = extract_regular(arg, i);
	return (fragments);
}

static char	*expand_value(char *value, char **env)
{
	if (value && value[0] == '$')
	{
		value = expand_token(value, env);
		if (value != NULL)
			return (ft_strdup(value));
	}
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

char	*resolve_token_value(char *token, char **env)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	if (!token)
		return (NULL);
	while (env[++i] != NULL)
	{
		var = ft_strchr_before_c(env[i], '=');
		value = ft_strchr_after_c(env[i], '=');
		if (ft_strcmp(var, token) == 0)
		{
			free(var);
			return (expand_value(value, env));
		}
		free(var);
	}
	return (ft_strdup(""));
}
