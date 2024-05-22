/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:19:13 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/22 14:24:45 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_env(t_data *data)
{
	int i;

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
			write(1, data->env[i], ft_strlen(data->env[i]));
			write(1, "\n", 1);
			i++;
		}
	}
}