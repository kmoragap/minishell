/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/20 11:09:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../../includes/minishell.h"

t_data  *print(t_data *data)
{
    int         x;

    if (!data->input[0])
        return (data);
    while (data->tokens->id < (data)->token_num)
    {
        x = 0;
        printf("Token_ID: %d\n", data->tokens->id);
        printf("cmd: %s\n", data->tokens->cmd);
        printf("arg_num: %d\n", data->tokens->args_num);
        while (data->tokens->args[x] && data->tokens->args[x][0])
        {
            printf("arg: %s\n", data->tokens->args[x]);
            x++;
        }
        printf("delim: %d\n", data->tokens->delim);
        printf("type: %d\n", data->tokens->type);
        write(1, "---------------------------------\n", 34);
        if (data->tokens->id == ((data)->token_num - 1))
            break;
        data->tokens = data->tokens->next;
    }
    return (data);
}
