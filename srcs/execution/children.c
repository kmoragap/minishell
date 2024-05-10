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

void    create_children(t_data *data)
{
    int     child_id;
    char    **cmd_arg;

    child_id = 0;
    cmd_arg = NULL;
    data->childn->cnt_childn = count_pipes(data);
    data->childn->pids = ft_calloc_norm(data->childn->cnt_childn, sizeof(pid_t));
    while (child_id < data->childn->cnt_childn)
    {
        data->childn->pids[child_id] = fork();
        if (data->childn->pids[child_id] == 0 || data->childn->pids[child_id] == -1)
            child_routine(data, child_id, cmd_arg); //have to check if pid == -1 and return if so
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

void    child_routine(t_data *data, int child_id, char **cmd_arg)
{
    if (data->childn->pids[child_id] == -1)
    {
        input_error(data, 0, "Error: cannot fork a process\n");
        exit (0);
    }
    get_token(data, child_id);
    if (check_cmd_path(data) == 1)
        exit (0);
    cmd_arg = join_cmd_arg(data);
    execve(data->tokens->path, cmd_arg, data->env);
    //error code ? / exit code?
    exit (0);    
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
