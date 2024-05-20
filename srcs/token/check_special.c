/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/18 17:36:33 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_special(int *i, char *input, t_token **token, t_data *data)
{
	skip_whitespace(i, input);
	check_special(i, input, token, data);
	if (data->err_code != ER_NO)
		return ;
	skip_whitespace(i, input);
	return ;
}

void	check_special(int *i, char *input, t_token **tokens, t_data *data)
{
	(*tokens)->delim = 0;
	if (input[*i] == '|' && (*tokens)->id == 0)
		input_error(data, F_EMPTOK, 2,
			"minishell: syntax error near unexpected token `|'\n");
	if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
	{
		add_delim(i, input, tokens);
		return ;
	}
	if ((input[*i] == 34 || input[*i] == 39) && check_whitespaces(input,
			i) == 1)
		input_error(data, F_EMPTOK, 127, "\n");
}

void	add_delim(int *i, char *input, t_token **tokens)
{
	if (input[*i] == '|')
		(*tokens)->delim = PIPE;
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 1;
		(*tokens)->delim = REDIR_H;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 1;
		(*tokens)->delim = REDIR_A;
	}
	else if (input[*i] == '>')
		(*tokens)->delim = REDIR_O;
	else
		(*tokens)->delim = REDIR_I;
	*i += 1;
}

int	check_whitespaces(char *input, int *i)
{
	int	j;

	j = 1;
	while (input[*i + j] && input[*i + j] != input[*i])
	{
		if (input[*i + j] != ' ' && input[*i + j] != '\t' && input[*i
			+ j] != '\n' && input[*i + j] != '\v' && input[*i + j] != '\f'
			&& input[*i + j] != '\r')
			return (0);
		j++;
	}
	return (1);
}
