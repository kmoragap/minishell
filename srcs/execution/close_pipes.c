/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/25 14:21:51 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_data *data, int child_id)
{
	int	i;

	i = 0;
	if (data->childn->cnt_childn == 1)
		return ;

    while (i < data->childn->cnt_childn && data->childn->pipes
        && data->childn->pipes[i])
    {
        if (i == child_id - 1)
            close (data->childn->pipes[i][0]);
        if (i == child_id)
            close (data->childn->pipes[i][1]);
        else
        {
            close(data->childn->pipes[i][0]);
            close(data->childn->pipes[i][1]);
        }
        i++;
    }
	free_pipes(data->childn->pipes, data);
}

void	free_pipes(int **pipes, t_data *data)
{
	int	i;

	i = 0;
	if (data->childn->cnt_childn == 1)
		return ;
	while (pipes && pipes[i] && i <= data->childn->cnt_childn)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
