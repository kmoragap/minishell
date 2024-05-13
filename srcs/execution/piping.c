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

t_data  *piping(t_data *data)
{
    data->childn->cnt_childn = count_pipes(data);
    if (malloc_fds(data) != 0)
        return (data);
    data = dup_pipe(data);
    return (data);
}

int     count_pipes(t_data *data)
{
    int     cnt;
    int     pipe_num;

    cnt = 1;
    pipe_num = 1;
    if (data->tokens->next)
        data->tokens = data->tokens->next;
    while (cnt < data->token_num && data->tokens)
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

int     malloc_fds(t_data *data)
{
    int     i;

    i = 0;
    if (ft_calloc(data, F_INPUT, (void *)&data->childn->pipes, sizeof(int *) * (data->childn->cnt_childn + 1)) == 1)
        return (1);
    while(i <= data->childn->cnt_childn)
    {
        if (ft_calloc(data, F_PIPES, (void *)&data->childn->pipes[i], sizeof(int) * 3) == 1)
            return (1);
        i++;
    }
    i = 0;
    while(i <= data->childn->cnt_childn)
    {
        if (pipe(data->childn->pipes[i]) == -1)
        {
            input_error(data, F_PIPES, "Error: pipe creation failed");
            return (1);
        }
        i++;
    }
    return (0);
}

t_data  *dup_pipe(t_data *data)
{
    int     cnt;

    cnt = 0;
    while (cnt < data->token_num && data->err_code == ER_NO && data->tokens->next)
    {
        if (data->tokens->next->delim == REDIR_I)
            redir_in(data, cnt);
        else if (data->tokens->next->delim == REDIR_A)
            redir_ap(data, cnt);
        else if (data->tokens->next->delim == REDIR_O)
            redir_out(data, cnt);
        // else if (data->tokens->next->delim == REDIR_H)
            // redir_herdoc(data, cnt);
        if (data->tokens->next)
            data->tokens = data->tokens->next;
        if (data->tokens->delim == PIPE)
            cnt++;        
    }
    return (data);
}

//input = read from own num
//output = write in next num

void    redir_in(t_data *data, int cnt)
{
    int     fd;

    fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT, S_IRWXU);
    if (fd == -1)
    {
        input_error(data, F_PIPES, "Error: opening file failed");
        return ;
    }
    data->childn->pipes[cnt][0] = fd;
    //dup2(data->childn->pipes[cnt][0], fd);
}

void    redir_ap(t_data *data, int cnt)
{
    int     fd;

    fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT | O_APPEND, S_IRWXU);
    if (fd == -1)
    {
        input_error(data, F_PIPES, "Error: opening file failed");
        return ;
    }
    data->childn->pipes[cnt + 1][1] = fd;
    //dup2(data->childn->pipes[cnt + 1][1], fd);
}

void    redir_out(t_data *data, int cnt)
{
    int     fd;

    fd = open(data->tokens->next->cmd, O_RDONLY | O_CREAT, S_IRWXU);
    if (fd == -1)
    {
        input_error(data, F_PIPES, "Error: opening file failed");
        return ;
    }
    data->childn->pipes[cnt + 1][1] = fd;
    //dup2(data->childn->pipes[cnt + 1][1], fd);
}
