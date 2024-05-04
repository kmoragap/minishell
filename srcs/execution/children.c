/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:36:56 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_children(t_data *data)
{
    int     child_id;

    child_id = 0;
    data->childn->cnt_childn = count_pipes(data);
    data->childn->pids = ft_calloc_norm(data->childn->cnt_childn, sizeof(int));
    while (child_id < data->childn->cnt_childn)
    {
        data->childn->pids[child_id] = fork();
        if (data->childn->pids[child_id] == 0 || data->childn->pids[child_id] == -1)
        {
            child_routine(data, child_id); //have to check if pid == -1 and return if so
            break;
        }
        child_id++;
    }
    parent_wait(data);
}

int     count_pipes(t_data *data)
{
    int     cnt;
    int     pipe_num;

    cnt = 1;
    pipe_num = 1;
    if (data->tokens->next)
        data->tokens = data->tokens->next;
    while (cnt <= data->token_num && data->tokens)
    {
        if (data->tokens->delim == PIPE)
            pipe_num++;
        cnt++;
        if(data->tokens->next)
            data->tokens = data->tokens->next;
    }
    data->tokens = move_to_first_token(data->tokens);
    return (pipe_num);
}

void    child_routine(t_data *data, int child_id)
{
    char    **cmd_arg;

    if (data->childn->pids[child_id] == -1)
    {
        input_error(data, 0, "Error: cannot fork a process\n");
        exit ;
    }
    get_token(data, child_id);
    if (check_cmd_path(data) == 1)
        exit ;
    cmd_arg = join_cmd_arg(data);
    execute_bash(data, cmd_arg);
    free(cmd_arg); //does it have to be freed?
    exit ;    
}

void    get_token(t_data *data, int child_id)
{
    while (child_id > 0)
    {
        if (!data->tokens->next)
            return ;
        data->tokens = data->tokens->next;
        child_id--;
    }
}
