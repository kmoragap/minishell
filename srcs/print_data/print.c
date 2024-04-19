/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/17 16:13:23 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print(t_data **data)
{
    t_token     **move;

    move = (*data)->tokens;
    while ((*move)->id < (*data)->token_num)
    {
        printf("Token_ID: %d\n", (*move)->id);
        printf("cmd: %s\n", (*move)->cmd);
        printf("arg_num: %d\n", (*move)->args_num);
        printf("arg: %s\n", (*move)->args[0]);
        printf("arg: %s\n", (*move)->args[1]);
        //printf("arg: %s\n", (*move)->args[2]);
        printf("delim: %d\n", (*move)->delim);
        printf("type: %d\n", (*move)->type);
        write(1, "---------------------------------\n", 34);
        if ((*move)->id == ((*data)->token_num - 1))
            break;
        *move = (*move)->next;
    }
}