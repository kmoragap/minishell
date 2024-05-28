/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/27 15:55:11 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reinit_data(t_data *data)
{
	data->err_code = ER_NO;
	data->free_code = NO_FREE;
}

void	free_args(char **args, int *cnt)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	if (!args[0])
	{
		free(args);
		return ;
	}
	free_args2(args, cnt, i);
	free(args);
}

void	free_args2(char **args, int *cnt, int i)
{
	if (args[0][0] == '\0')
		free(args[0]);
	else if (cnt == 0 && args && args[0])
	{
		while (args[i])
			i++;
		while (i >= 0)
		{
			free(args[i]);
			i--;
		}
	}
	else
	{
		while (*cnt >= 0)
		{
			free(args[*cnt]);
			*cnt -= 1;
		}
	}
}
