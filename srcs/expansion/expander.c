/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:55:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/25 15:12:30 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_and_process(char **result, char *arg, int start, int end,
		char **env, int status)
{
	char	*var_name;
	char	*temp;
	char	*new_result;

	if(arg[start - 1] == 39 || arg[start - 1] !=  '$')
	{
		var_name = ft_strndup(&arg[start], end - start);
		new_result = ft_strjoin(*result, var_name);
		free(*result);
		free(var_name);
	}
	else
	{
		var_name = ft_strndup(&arg[start], end - start);
		temp = expand_variable(var_name, env, status);
		new_result = ft_strjoin(*result, temp);
		free(*result);
		free(temp);
		free(var_name);
	}
	*result = new_result;
}

static void	handle_dollar_question(char **result, int *end, int status)
{
	char	*temp;
	char	*new_result;

	temp = ft_itoa(status);
	new_result = ft_strjoin(*result, temp);
	free(*result);
	free(temp);
	*end += 2;
	*result = new_result;
}

static void	handle_delimiter(char **result, char delim)
{
	char	new_result[2];
	char	*final_result;

	new_result[0] = delim;
	new_result[1] = '\0';
	final_result = ft_strjoin(*result, new_result);
	free(*result);
	*result = final_result;
}

char	*check_expand_quotes(char *arg, char **env, int status)
{
	char	*result;
	char	delim;
	int		start;
	int		end;
	int		len;

	result = ft_strdup("");
	start = 0;
	end = 0;
	len = ft_strlen(arg);
	while (end <= len)
	{
		if (arg[end] == '\0' || valid_delim_expand(arg[end]) || (arg[end] == '$'
				&& end > start))
		{
			if (end > start)
				expand_and_process(&result, arg, start, end, env, status);
			if (arg[end] != '\0')
			{
				delim = arg[end];
				if (delim == '$' && arg[end + 1] == '?')
				{
					handle_dollar_question(&result, &end, status);
					start = end;
				}
				else
				{
					if (delim != '$')
						handle_delimiter(&result, delim);
					start = end + 1;
				}
			}
			else
				start = end + 1;
		}
		end++;
	}
	return (result);
}
