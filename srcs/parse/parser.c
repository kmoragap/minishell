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

t_data  *parser(t_data *data)
{
    while ((data)->tokens->id < (data)->token_num)
    {
        if (check_empty_cmd(data->tokens) == 1)
            exit(0); //error         
        else if (check_expand(data->tokens) == 1)
            (data->tokens)->type = EXPAND;
        else if (check_fd(data->tokens) == 1)
            (data->tokens)->type = FD;
        else if (check_file(data->tokens) == 1)
            (data->tokens)->type = FLE;
        else
            (data->tokens)->type = CMD;
        if ((data->tokens)->id == ((data)->token_num - 1))
            break;
        data->tokens = (data->tokens)->next;
    }
    while (data->tokens->prev)
        data->tokens = data->tokens->prev;
    return (data);
}

int     check_empty_cmd(t_token *move)
{
    if ((move)->cmd && (move)->cmd[0])
        return (0);
    return (1);
}

int     check_expand(t_token *move)
{
    if ((move)->cmd[0] == '$' && (((move)->cmd[1] >= 'a' && (move)->cmd[1] <= 'z') || ((move)->cmd[1] >= 'A' && (move)->cmd[1] <= 'Z')))
        return (1);
    else if ((move)->cmd[0] == 34 && (move)->cmd[1] == '$' && (((move)->cmd[2] >= 'a' && (move)->cmd[2] <= 'z') || ((move)->cmd[2] >= 'A' && (move)->cmd[2] <= 'Z')))
        return (1);
    return (0);
}

int     check_fd(t_token *move)
{
    if ((move)->delim == 6 || (move)->delim == 7 || (move)->delim == 8 || (move)->delim == 9)
    {
        if ((move)->cmd[0] == '&' && (move)->cmd[1] >= '0' && (move)->cmd[1] <= '9')
            return (1);
    }
    return (0);
}

int     check_file(t_token *move)
{
    if ((move)->delim == 6 || (move)->delim == 7 || (move)->delim == 8 || (move)->delim == 9)
        return (1);
    return (0);
}
