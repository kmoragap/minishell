/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:34:33 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 20:41:13 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expand_var(char *var)
{
	if (var[0] == '$' && (is_valid_variable_char(var[1])))
		return (1);
	else if (var[0] == 34 && var[1] == '$' && is_valid_variable_char(var[2]))
		return (1);
	return (0);
}

int	is_valid_variable_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_' || c == '?' || c == '(' || c == ')'
		|| c == '"');
}

int	check_expand_args(char **args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == '$' && args[i][j + 1] != '\0' && args[i][j
				+ 1] != ' ')
			{
				k = j + 1;
				while (is_valid_variable_char(args[i][k]))
					k++;
				if (k > j + 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	valid_delim_expand(char c)
{
	if ((c >= 32 && c <= 33) || c == 35 || (c >= 36 && c <= 47) || (c >= 58
			&& c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)
		|| c == 34 || c == 39)
		return (c);
	return (0);
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
