/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/10 19:48:46 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    parent_wait(t_data *data)
{
    int     i;

    i = 0;
    ft_calloc(data, 0, (void *)&data->childn->exit_state, data->childn->cnt_childn + 1);
    while (i < (data->childn->cnt_childn - 1))
    {
        if (waitpid(data->childn->pids[i], &data->childn->exit_state[i], 0) == -1)
            printf("error\n");
        if (WIFEXITED(data->childn->exit_state[i]))
            printf("Exit-State = %d\n", WEXITSTATUS(data->childn->exit_state[i]));
        if (WIFSIGNALED(data->childn->exit_state[i]))
        {
            if (WTERMSIG(data->childn->exit_state[i]) == SIGSEGV)
                printf("Segmentation fault\n");
            else if (WTERMSIG(data->childn->exit_state[i]) == SIGQUIT)
                printf("Quit\n");
            if (WCOREDUMP(data->childn->exit_state[i]))
                printf("Core Dumped = %d\n", WCOREDUMP(data->childn->exit_state[i]));
        }
        i++;
    }
}