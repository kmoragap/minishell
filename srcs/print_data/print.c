/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:35:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print(t_data **data)
{
    t_token     **move;
    int         i;

    i = 0;
    move = (*data)->tokens;
    while ((*move)->id < (*data)->token_num)
    {
        printf("Token_ID: %d\n", (*move)->id);
        printf("cmd: %s\n", (*move)->cmd);
        while ((*move)->args[i] && (*move)->args[i][0])
        {
            printf("arg: %s\n", (*move)->args[i]);
            i++;
        }
        printf("delim: %d\n", (*move)->delim);
        printf("type: %d\n", (*move)->type);
        write(1, "---------------------------------\n", 34);
        if ((*move)->id == ((*data)->token_num - 1))
            break;
        *move = (*move)->next;
    }
}