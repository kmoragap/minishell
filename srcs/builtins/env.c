/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:19:13 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/29 22:33:37 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_equal_sign(const char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void	put_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->tokens->args_num > 0)
	{
		write(2, "env: too many arguments\n", 24);
		return ;
	}
	else
	{
		while (data->env[i])
		{
			if (has_equal_sign(data->env[i]))
			{
				write(1, data->env[i], ft_strlen(data->env[i]));
				write(1, "\n", 1);
			}
			i++;
		}
	}
}
