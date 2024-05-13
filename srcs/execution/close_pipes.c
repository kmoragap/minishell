/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/10 17:27:35 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    dup_pipes(t_data *data, int child_id)
{
    dup2(1, data->childn->pipes[child_id + 1][1]);
    dup2(0, data->childn->pipes[child_id][0]);
}

void    close_pipes(t_data *data)
{
    int     i;

    i = 0;
    while (i <= data->childn->cnt_childn && data->childn->pipes[i])
    {
        close(data->childn->pipes[i][0]);
        close(data->childn->pipes[i][1]);
        i++;
    }
}
