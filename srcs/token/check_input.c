/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/26 16:30:36 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(t_data *data)
{
	if (check_andslash(data->input) == 1 || check_quotes(data->input) == 1
		|| check_pipe(data->input) == 1)
	{
		data->err_code = ER_INPUT;
		data->free_code = F_INPUT;
		write(2, "minishell: syntax error due to invalid input\n", 46);
		data->exit_code = 2;
		return (1);
	}
	if (ft_strlen(data->input) == 0)
	{
		data->err_code = ER_INPUT;
		data->free_code = F_INPUT;
		return (1);
	}
	return (0);
}

int	check_pipe(char *input)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(input);
	if (input[len - 1] == '|')
		return (1);
	while (i < len)
	{
		if (input[i] == '|')
		{
			skip_whitespace(&i, input);
			if (input[i + 1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_quotes(char *input)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (input[i])
	{
		if (input[i] == 34)
			squote++;
		if (input[i] == 39)
			dquote++;
		i++;
	}
	if (squote % 2 != 0 || dquote % 2 != 0)
		return (1);
	return (0);
}

int	check_andslash(char *input)
{
	int	i;

	i = 0;
	if (!input || !input[0])
		return (0);
	while (input[i])
	{
		if (input[i] == '&')
			return (1);
		if (input[i] == 92)
			return (1);
		if (input[i] == ';')
			return (1);
		if (input[i] == '<' && input[i + 1] == '>')
			return (1);
		if (input[i] == '>' && input[i + 1] == '<')
			return (1);
		i++;
	}
	if (input[ft_strlen(input) - 1] == '<' || input[ft_strlen(input)
		- 1] == '>')
		return (1);
	if (input[0] == '<' || input[0] == '>')
		return (1);
	return (0);
}
