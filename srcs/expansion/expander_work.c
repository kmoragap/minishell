/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_work.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:42:12 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 20:39:26 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted(char *arg, int *i, char quote)
{
	char	*temp;
	int		start;
	int		end;

	start = *i;
	end = find_end(arg, start, quote);
	temp = ft_strndup(&arg[start], end - start + 1);
	if (!temp)
		return (arg);
	*i = end + 1;
	return (temp);
}

char	*extract_regular(char *arg, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (arg[*i] && arg[*i] != '"' && arg[*i] != '\'' && arg[*i] != '$')
		(*i)++;
	temp = ft_strndup(&arg[start], *i - start);
	if (!temp)
		return (arg);
	return (temp);
}

char	*extract_variable(char *arg, int *i)
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
	if (!temp)
		return (arg);
	return (temp);
}

char	*expand_and_join(char **fragments, int frag_count, char **env,
		int status)
{
	int		j;
	char	*expanded;
	char	*new_result;
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	j = 0;
	while (j < frag_count)
	{
		expanded = expand_work(fragments[j], env, status);
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

char	*expander_fun(char *arg, char **env, int status)
{
	char	*result;
	char	**fragments;
	int		frag_index;
	int		i;

	fragments = ft_calloc_norm(ft_strlen(arg), sizeof(char *));
	if (!fragments)
		return (NULL);
	frag_index = 0;
	i = 0;
	while (arg[i])
	{
		fragments[frag_index] = get_fragment(arg, &i);
		if (!fragments[frag_index])
		{
			free(fragments);
			return (NULL);
		}
		frag_index++;
	}
	result = expand_and_join(fragments, frag_index, env, status);
	free(fragments);
	return (result);
}
