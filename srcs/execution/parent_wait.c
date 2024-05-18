/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/18 00:03:14 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    parent_wait(t_data *data)
{
    int     i;

    i = 0;
    while (i < (data->childn->cnt_childn))
    {
        if (waitpid(data->childn->pids[i], &data->childn->exit_state, 0) == -1)
            perror("minishell: waitpid error\n");
        i++;
    }
    if (WIFEXITED(data->childn->exit_state))
        data->exit_code = WEXITSTATUS(data->childn->exit_state);
    else if (WIFSIGNALED(data->childn->exit_state))
        data->exit_code = WTERMSIG(data->childn->exit_state);
}