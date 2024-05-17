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

    if (data->childn->cnt_childn == 1)
    {
        single_redir(data);
        return ;
    }
    if(child_id == 0)
    {
        dup2(check_redir_out(data, child_id), STDOUT_FILENO);
        check_redir_in_first(data);
    }
    else if (child_id == (data->childn->cnt_childn - 1))
    {
        dup2(check_redir_in(data, child_id), STDIN_FILENO);
        check_redir_out_last(data);
    }
    else 
    {
        dup2(check_redir_out(data, child_id), STDOUT_FILENO);
        dup2(check_redir_in(data, child_id), STDIN_FILENO);
    }
}

void    single_redir(t_data *data)
{
    int     fd;

    if (!data->tokens->next)
        return ;
    if (data->tokens->next->delim == REDIR_I)
    {
        fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT, S_IRWXU);
        if (fd == -1)
        {
            input_error(data, F_PIPES, "Error: opening file failed");
            return ;
        }
        dup2(fd, STDIN_FILENO);
        return ;
    }
    if (data->tokens->next->delim == REDIR_A)
        fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT | O_APPEND, S_IRWXU);
    else if (data->tokens->next->delim == REDIR_O)
        fd = open(data->tokens->next->cmd, O_RDONLY | O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
    if (fd == -1)
    {
        input_error(data, F_PIPES, "Error: opening file failed");
        return ;
    }
    dup2(fd, STDOUT_FILENO);
}

void    check_redir_out_last(t_data *data)
{
    int     fd;

    if (data->tokens->next && data->tokens->next->delim == REDIR_A)
        fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT | O_APPEND, S_IRWXU);
    else if (data->tokens->next && data->tokens->next->delim == REDIR_O)
        fd = open(data->tokens->next->cmd, O_RDONLY | O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
    else
    {
        write(1, "no redirection1\n", 16);
        return ;
    }
    if (fd == -1)
    {
        input_error(data, F_PIPES, "Error: opening file failed");
        return ;
    }
    dup2(fd, STDOUT_FILENO);    
}

void    check_redir_in_first(t_data *data)
{
    int     fd;

    if (data->tokens->next && data->tokens->next->delim == REDIR_I)
        fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT, S_IRWXU);
    else
    {
        write(1, "no redirection2\n", 16);
        return ;
    }
    if (fd == -1)
    {
        input_error(data, F_PIPES, "Error: opening file failed");
        return ;
    }
    write(1, "redirection in in_first\n", 24);
    dup2(fd, STDIN_FILENO);  
}

int     check_redir_in(t_data *data, int child_id)
{
    int     fd;

    fd = child_id;
    if (data->tokens->next && data->tokens->next->delim == REDIR_I)
    {
        fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT, S_IRWXU);
        if (fd == -1)
        {
            input_error(data, F_PIPES, "Error: opening file failed");
            return (-1);
        }
        return (fd);
    }
    write(1, "no redirection3\n", 16);
    return (data->childn->pipes[child_id - 1][0]);
}

int     check_redir_out(t_data *data, int child_id)
{
    int     fd;

    fd = child_id;
    if (data->tokens->next && data->tokens->next->delim == REDIR_O)
    {
        fd = open(data->tokens->next->cmd, O_RDONLY | O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU);
        if (fd == -1)
        {
            input_error(data, F_PIPES, "Error: opening file failed");
            return (-1);
        }
        return (fd);
    }
    else if (data->tokens->next && data->tokens->next->delim == REDIR_A)
    {
        fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
        if (fd == -1)
        {
            input_error(data, F_PIPES, "Error: opening file failed");
            return (-1);
        }
        return (fd);
    }
    write(1, "no redirection4\n", 16);
    return (data->childn->pipes[child_id][1]);
}
