/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doubles_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:46:39 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/26 01:22:48 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * sacar el int status de las funciones porque no se necesitan
*/

static void	handle_var_expansion(char **result, char *arg, int *i, char **env,
		int status)
{
	int		start;
	char	*var;
	char	*expanded_var;
	char	*new_result;

	start = *i + 1;
	while (arg[start] && !valid_delim_expand(arg[start]))
		start++;
	if (start > *i + 1)
	{
		var = ft_strndup(&arg[*i + 1], start - *i - 1);
		expanded_var = expand_variable(var, env, status);
		new_result = ft_strjoin(*result, expanded_var);
		free(*result);
		free(var);
		free(expanded_var);
		*result = new_result;
		*i = start;
	}
	else
	{
		new_result = ft_strnjoin(*result, "$", 1);
		*result = new_result;
		(*i)++;
	}
}

static void	handle_char_append(char **result, char c)
{
	char	str[2];
	char	*new_result;

	str[0] = c;
	str[1] = '\0';
	new_result = ft_strjoin(*result, str);
	free(*result);
	*result = new_result;
}

char	*handle_double_quotes(char *arg, char **env, int status)
{
	int		i;
	char	*result;

	i = 1;
	result = ft_strdup("");
	while (arg[i] && arg[i] != '"')
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] == '?')
				handle_dollar_question(&result, &i, status);
			else
				handle_var_expansion(&result, arg, &i, env, status);
		}
		else
		{
			handle_char_append(&result, arg[i]);
			i++;
		}
	}
	return (result);
}

char *handle_no_quotes(char *arg, char **env, int status)
{
    int i;
    char *result;

	result = ft_strdup("");
	i = 0;
    while (arg[i])
    {
        if (arg[i] == '$')
        {
            if (arg[i] == '?')
            {
                handle_dollar_question(&result, &i, status);
            }
            else
                handle_var_expansion(&result, arg, &i, env, status);
        }
        else
        {
            handle_char_append(&result, arg[i]);
            i++;
        }
    }
    return result;
}
