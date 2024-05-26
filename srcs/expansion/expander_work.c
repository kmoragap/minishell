/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_work.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:42:12 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 18:39:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_quoted(char *arg, int *i, char quote)
{
	char	*temp;
	int		start;
	int		end;

	start = *i;
	end = find_end(arg, start, quote);
	temp = ft_strndup(&arg[start], end - start + 1);
	if(!temp)
		return (arg);
	*i = end + 1;
	return (temp);
}

static char	*extract_regular(char *arg, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (arg[*i] && arg[*i] != '"' && arg[*i] != '\'' && arg[*i] != '$')
		(*i)++;
	temp = ft_strndup(&arg[start], *i - start);
	if(!temp)
		return (arg);
	return (temp);
}

static char	*extract_variable(char *arg, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	(*i)++;
	if (arg[*i] == '?')
		(*i)++;
	else
	{
		while (arg[*i] && !valid_delim_expand(arg[*i]) && arg[*i] != '"'
			&& arg[*i] != '\'')
			(*i)++;
	}
	temp = ft_strndup(&arg[start], *i - start);
	if(!temp)
		return (arg);
	return (temp);
}

static char	*expand_and_join(char **fragments, int frag_count, char **env)
{
	int		j;
	char	*expanded;
	char	*new_result;
	char	*result;

	result = ft_strdup("");
	j = 0;
	while (j < frag_count)
	{
		expanded = expand_work(fragments[j], env);
		new_result = ft_strjoin(result, expanded);
		if (result)
			free(result);
		free(expanded);
		free(fragments[j]);
		result = new_result;
		j++;
	}
	return (result);
}

char	*expander_fun(char *arg, char **env)
{
	char	*result;
	char	**fragments;
	int		len;
	int		frag_index;
	int		i;

	len = ft_strlen(arg);
	fragments = ft_calloc_norm(len, sizeof(char *));
	if (!fragments)
		return (NULL);
	frag_index = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
			fragments[frag_index++] = extract_quoted(arg, &i, '"');
		else if (arg[i] == '\'')
			fragments[frag_index++] = extract_quoted(arg, &i, '\'');
		else if (arg[i] == '$')
			fragments[frag_index++] = extract_variable(arg, &i);
		else
			fragments[frag_index++] = extract_regular(arg, &i);
		if (!fragments[frag_index - 1])
		{
			free(fragments);
			return (NULL);
		}
	}
	result = expand_and_join(fragments, frag_index, env);
	free(fragments);
	return (result);
}
