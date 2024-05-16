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

void    close_pipes(t_data *data)
{
    int     i;

    i = 0;
    if (data->childn->cnt_childn == 1)
        return ;
    while (i < data->childn->cnt_childn && data->childn->pipes && data->childn->pipes[i])
    {
        if (data->childn->pipes[i][0] != STDIN_FILENO)
            close(data->childn->pipes[i][0]);
        if (data->childn->pipes[i][1] != STDOUT_FILENO)
            close(data->childn->pipes[i][1]);
        i++;
    }
    free_pipes(data->childn->pipes, data);
}
