/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:55:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 18:42:32 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_question(char **result, int *end)
{
	char	*temp;
	char	*new_result;

	temp = ft_itoa(g_sigint);
	new_result = ft_strjoin(*result, temp);
	free(*result);
	if (temp)
		free(temp);
	*end += 2;
	*result = new_result;
}

static void	handle_question_dolar(char **result)
{
	char	*temp;
	char	*new_result;

	temp = ft_itoa(g_sigint);

	new_result = ft_strjoin(*result, temp);
	free(*result);
	if(temp)
		free(temp);
	*result = new_result;
}

int	find_end(char *arg, int i, char quote)
{
	i++;
	while (arg[i] && arg[i] != quote)
		i++;
	return (i);
}

static char	*remove_single_quotes(char *arg)
{
	char	*result;
	int		i;
	int		j;

	result = ft_calloc_norm(ft_strlen(arg) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] != '\'')
		{
			result[j] = arg[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*expand_work(char *arg, char **env)
{
	char	*result;
	
	if (arg[0] == '\'')
		result = remove_single_quotes(arg);
	else if (arg[0] == '"')
		result = handle_double_quotes(arg, env);
	else if (arg[0] == '$' && arg[1] == '?')
	{
		result = ft_strdup("");
		handle_question_dolar(&result);
	}
	else
		result = handle_no_quotes(arg, env);
	return (result);
}
