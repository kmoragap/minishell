/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:35:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    parser(t_data **data)
{
    t_token     *move;

    move = (*data)->tokens;
    while (move->id < (*data)->token_num)
    {
        if (check_empty_cmd(move) == 1)
            exit(0); //error         
        else if (check_expand(move) == 1)
            move->type = EXPAND;
        else if (check_file(move) == 1)
            move->type = FLE;
        else if (check_fd(move) == 1)
            move->type = FD;
        else
            move->type = CMD;
        if (move->id == ((*data)->token_num - 1))
            break;
        move = move->next;
    }
}

int     check_empty_cmd(t_token *move)
{
    if (move->cmd && move->cmd[0])
        return (0);
    return (1);
}

int     check_expand(t_token *move)
{
    if (move->cmd[0] == '$' && ((move->cmd[1] >= 'a' && move->cmd[1] <= 'z') || (move->cmd[1] >= 'A' && move->cmd <= 'Z')))
        return (1);
    else if (move->cmd[0] == 34 && move->cmd[1] == '$' && ((move->cmd[2] >= 'a' && move->cmd[2] <= 'z') || (move->cmd[2] >= 'A' && move->cmd[2] <= 'Z')))
        return (1);
    return (0);
}

int     check_file(t_token *move)
{
    
}
