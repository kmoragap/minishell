/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 17:37:55 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd(int *i, char *input, t_token **tokens, t_data *data)
{
	int	j;
	int	quote;

	j = 0;
	while (input[*i + j])
	{
		quote = 0;
		while (quote == 0 && delim_space(input[*i + j]) == 0 && input[*i + j])
			check_quote(input[*i + j], &quote, &j);
		if (quote != 0)
		{
			if (text_in_quotes_cmd(quote, *i, &j, input) != 0)
				input_error(data, F_TOKS, 1,
					"minishell: syntax error due to unclosed quote\n");
			j += 1;
		}
		if (!input[*i + j - 1] || !input[*i + j] || delim_space(input[*i
					+ j]) != 0)
			break ;
	}
	if (input_cmd(input, i, j, tokens) != 0)
		malloc_error(data, F_EMPTOK);
}

int	delim_space(char c)
{
	if (!c)
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (1);
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	text_in_quotes_cmd(int quote, int i, int *j, char *input)
{
	while (input[i + *j])
	{
		if (quote == 1 && input[i + *j] == 39)
			return (0);
		if (quote == 2 && input[i + *j] == 34)
			return (0);
		*j += 1;
	}
	if (!input[i + *j])
		return (1);
	if (input[i + *j] == input[i + *j - 1])
		*j += 1;
	return (0);
}

int	text_in_quotes(int quote, int i, int *j, char *input)
{
	i--;
	*j += 1;
	while (input[i + *j])
	{
		if (quote == 1 && input[i + *j] == 39)
			return (0);
		if (quote == 2 && input[i + *j] == 34)
			return (0);
		*j += 1;
	}
	if (!input[i + *j])
		return (1);
	return (0);
}

int	input_cmd(char *input, int *i, int j, t_token **tokens)
{
	int	n;

	n = 0;
	(*tokens)->cmd = ft_calloc_norm((j + 1), sizeof(char));
	if (!(*tokens)->cmd)
		return (1);
	while (n < j && input[*i])
	{
		(*tokens)->cmd[n] = input[*i];
		n++;
		*i += 1;
	}
	(*tokens)->cmd[n] = '\0';
	return (0);
}
