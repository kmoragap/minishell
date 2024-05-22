/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/20 00:01:53 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_args_num(char *input, int *i, int total_arg_len, t_token **tokens)
{
	int	j;

	j = *i;
	(*tokens)->args_num = 0;
	while (input[j] && (j - *i) < (total_arg_len))
	{
		while (input[j] && (j - *i) < (total_arg_len))
		{
			arg_num_loop(input, &j);
			if (delim_space(input[j]) != 0)
			{
				skip_whitespace(&j, input);
				break ;
			}
		}
		(*tokens)->args_num += 1;
	}
}

void	arg_num_loop(char *input, int *j)
{
	int	quote;

	quote = 0;
	skip_whitespace(j, input);
	while (quote == 0 && delim_space(input[*j]) == 0 && input[*j])
		check_quote(input[*j], &quote, j);
	if (quote != 0)
	{
		text_in_quotes(quote, 0, j, input);
		*j += 1;
	}
}

int	malloc_args(char *input, int *i, t_token **tokens)
{
	int	arg;
	int	len;

	arg = 0;
	(*tokens)->args = ft_calloc_norm(((*tokens)->args_num + 1), sizeof(char *));
	if (!(*tokens)->args)
		return (1);
	while (arg < (*tokens)->args_num)
	{
		len = get_arg_len(input, i);
		(*tokens)->args[arg] = ft_calloc_norm(len + 1, sizeof(char));
		if (!(*tokens)->args[arg])
		{
			free((*tokens)->args);
			return (1);
		}
		input_arg(input, i, tokens, arg);
		arg++;
	}
	(*tokens)->args[(*tokens)->args_num] = NULL;
	return (0);
}

int	get_arg_len(char *input, int *i)
{
	int	len;
	int	skip;
	int	quote;

	len = 0;
	skip = *i;
	quote = 0;
	while (input[skip + len])
	{
		skip_whitespace(&skip, input);
		while (quote == 0 && delim_space(input[skip + len]) == 0 && input[skip
				+ len])
			check_quote(input[skip + len], &quote, &len);
		if (quote != 0)
		{
			text_in_quotes(quote, skip, &len, input);
			len++;
		}
		if (delim_space(input[skip + len]) != 0)
			break ;
	}
	return (len);
}

void	input_arg(char *input, int *i, t_token **tokens, int arg)
{
	int	n;
	int	len;

	len = get_arg_len(input, i);
	n = 0;
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\n'
			|| input[*i] == '\t' || input[*i] == '\v' || input[*i] == '\f'
			|| input[*i] == '\r'))
		*i += 1;
	while (n < len)
	{
		(*tokens)->args[arg][n] = input[*i];
		n++;
		*i += 1;
	}
	(*tokens)->args[arg][n] = '\0';
}