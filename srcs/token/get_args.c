/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/20 00:01:53 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_args(int *i, char *input, t_token **tokens, t_data *data)
{
	int	total_arg_len;

	if (!input[*i])
	{
		create_empty_args(tokens, data);
		return ;
	}
	total_arg_len = get_total_arg_len(input, *i);
	if (total_arg_len == 0)
	{
		create_empty_args(tokens, data);
		return ;
	}
	get_args_num(input, i, total_arg_len, tokens);
	if (malloc_args(input, i, tokens) != 0)
		malloc_error(data, F_TOKCMD);
}

void	create_empty_args(t_token **tokens, t_data *data)
{
	(*tokens)->args = ft_calloc_norm(1, sizeof(char *));
	if (!(*tokens)->args)
	{
		malloc_error(data, F_TOKCMD);
		return ;
	}
	(*tokens)->args[0] = ft_calloc_norm(1, sizeof(char));
	if (!(*tokens)->args[0])
	{
		free((*tokens)->args);
		malloc_error(data, F_TOKCMD);
		return ;
	}
	(*tokens)->args[0][0] = '\0';
	(*tokens)->args_num = 0;
}

int	get_total_arg_len(char *input, int i)
{
	int	len;
	int	temp;

	len = 0;
	while (input[i + len])
	{
		if (input[i + len] == 34 || input[i + len] == 39)
		{
			temp = i + len;
			len++;
			while (input[i + len] != input[temp] && input[i + len])
				len++;
		}
		if (input[i + len] == '|' || input[i + len] == '<' || input[i
				+ len] == '>')
			break ;
		len++;
	}
	return (len);
}
