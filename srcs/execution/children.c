/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/18 19:31:32 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data    *create_children(t_data *data)
{
    int     child_id;

    child_id = 0;
    if (data->childn->cnt_childn == 1)
    {
        if (check_builtins(data->tokens->cmd) > -1)
        {
            execute_builtin(data);
            data->free_code = NO_FREE_PIDS;
            return (data);
        }
    }
    if (ft_calloc(data, F_INPUT, (void *)&data->childn->pids, sizeof(pid_t) * data->childn->cnt_childn + 1) == 1)
        return (data);
    while (child_id < (data->childn->cnt_childn) || child_id == 0)
    {
        data->childn->pids[child_id] = fork();
        if (!data->childn->pids[child_id])
        {
            child_routine(data, child_id);
            break ;
        }
        else if (data->childn->pids[child_id] == -1)
        {
            input_error(data, 0, 10, "minishell: No child processes\n");
            exit (0);
        }
        child_id++;
    }
    close_pipes(data);
    parent_wait(data);
    return (data);
}

void    child_routine(t_data *data, int child_id)
{
    char    **cmd_arg; 

    get_token(data, child_id);
    dup_pipes(data, child_id);
    close_pipes(data);
    check_cmd_path(data);
    cmd_arg = join_cmd_arg(data);
    execve(data->tokens->path, cmd_arg, data->env);
    free(data->tokens->path);
    free_args(cmd_arg, NULL);
    exit (1);    
}

void    get_token(t_data *data, int child_id)
{
    while (child_id > 0)
    {
        if (!data->tokens->next)
            return ;
        data->tokens = data->tokens->next;
        if (data->tokens->delim == PIPE)
            child_id--;
    }
}

void    error_in_child(t_data *data, int exit_code, char *cmd, char *error_message)
{
    if (data->tokens->path)
        free(data->tokens->path);
    write(2, "minishell: ", 11);
    write(2, cmd, ft_strlen(cmd));
    write(2, ": ", 2);
    write(2, error_message, ft_strlen(error_message));
    write(2, "\n", 1);
    exit (exit_code);
}
