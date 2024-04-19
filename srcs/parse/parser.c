/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/17 16:28:30 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    parser(t_data **data)
{
    t_token     **move;
    t_token     *start;

    move = (*data)->tokens;
    start = *((*data)->tokens);
    printf("start = %d\n", (*move)->id);
    while ((*move)->id < (*data)->token_num)
    {
        if (check_empty_cmd(move) == 1)
            exit(0); //error         
        else if (check_expand(move, (*data)->env) == 1)
            (*move)->type = EXPAND;
        else if (check_fd(move) == 1)
            (*move)->type = FD;
        else if (check_file(move) == 1)
            (*move)->type = FLE;
        else
            (*move)->type = CMD;
        if ((*move)->id == ((*data)->token_num - 1))
            break;
        *move = (*move)->next;
    }
    *((*data)->tokens) = start;
}

int     check_empty_cmd(t_token **move)
{
    if ((*move)->cmd && (*move)->cmd[0])
        return (0);
    return (1);
}

int check_expand(t_token **move, char **env)
{
    if (check_expand_var((*move)->cmd))
    {
        expand_cmd(move, env);
        return (1);
    }

    if((*move)->args_num != 0)
    {
       expand_args(move, env);
       return (1);   
    }
    return (0);
}

int     check_fd(t_token **move)
{
    if ((*move)->delim == 6 || (*move)->delim == 7 || (*move)->delim == 8 || (*move)->delim == 9)
    {
        if ((*move)->cmd[0] == '&' && (*move)->cmd[1] >= '0' && (*move)->cmd[1] <= '9')
            return (1);
    }
    return (0);
}

int     check_file(t_token **move)
{
    if ((*move)->delim == 6 || (*move)->delim == 7 || (*move)->delim == 8 || (*move)->delim == 9)
        return (1);
    return (0);
}
