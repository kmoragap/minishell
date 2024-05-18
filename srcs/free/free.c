/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/18 11:59:49 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_all(t_data *data)
{
    if (data->free_code >= F_TOKS || data->free_code == NO_FREE)
        free_toks(data);
    if (data->free_code >= F_EMPTOK || data->free_code == NO_FREE)
        free(data->tokens);
    if (data->free_code >= F_INPUT || data->free_code == NO_FREE)
        free(data->input);
    if (data->free_code != NO_FREE_PIDS && (data->free_code >= F_PIDS || data->free_code == NO_FREE))
        free(data->childn->pids);
    if (data->free_code != F_EXITSTATE || data->free_code == NO_FREE)
    reinit_data(data);
}
// finishhhhhhhhhh! --> free toks isn't done yet! and add a new initializer for the data 
void    free_toks(t_data *data)
{
    while (data->tokens)
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
        if (!data->tokens->next)
        {
            //free(data->tokens);
            break ;
        }
        data->tokens = data->tokens->next;
        if (data->tokens->prev)
            free(data->tokens->prev);
    }
}

void free_env(t_data *data)
{
    int i;
    
    i = 0;
    if (data) 
    {
        if (data->env) 
        {
            while (i < data->env_len)
            {
                if (data->env[i]) 
                    free(data->env[i]);
                i++;
            }
            free(data->env);
        }
    }
    if(data->childn)
        free(data->childn);
    free(data);
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

void    free_args(char **args, int *cnt)
{
    int     i;

    i = 0;
    if (args[0][0] == '\0')
        free(args[0]);
    else if (!cnt && args && args[0])
    {
        while (args[i])
        {
            free(args[i]);
            i++;
        }
    }
    else
    {
        while (*cnt > 0)
        {
            free(args[*cnt]);
            *cnt -= 1;
        }
    }
    free(args);
}

void    reinit_data(t_data *data)
{
    data->err_code = ER_NO;
    data->free_code = NO_FREE;
}
