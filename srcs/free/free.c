/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:36:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_all(t_data *data)
{
    if (data->free_code >= F_TOKS || data->free_code == NO_FREE)
        free_toks(data);
    if (data->free_code >= F_TOKCMD || data->free_code == NO_FREE)
        free(data->tokens->cmd);
    if (data->free_code >= F_EMPTOK || data->free_code == NO_FREE) 
        free(data->tokens);
    if (data->free_code >= F_INPUT || data->free_code == NO_FREE)
        free(data->input);
    //if (data->free_code >= F_PIPES || data->free_code == NO_FREE)
    //    free_pipes(data->childn->pipes, data);
    if (data->free_code >= F_PIDS || data->free_code == NO_FREE)
        free(data->childn->pids);
    if (data->free_code != F_EXITSTATE || data->free_code == NO_FREE)
    reinit_data(data);
}
// finishhhhhhhhhh! --> free toks isn't done yet! and add a new initializer for the data 
void    free_toks(t_data *data)
{
    while (data->tokens->next)
    {
        if (data->tokens->args_num == 0)
            free(data->tokens->args[0]);
        while (data->tokens->args_num > 0)
        {
            free(data->tokens->args[data->tokens->args_num]);
            data->tokens->args_num -= 1;
        }
        free(data->tokens->args);
        free(data->tokens->cmd);
        data->tokens = data->tokens->next;
        if (data->tokens->prev)
            free(data->tokens->prev);
    }
}

void    free_pipes(int **pipes, t_data *data)
{
    int     i;

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

void    reinit_data(t_data *data)
{
    data->err_code = ER_NO;
    data->free_code = NO_FREE;
}
