/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:07:09 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/09 09:01:30 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_data *data)
{
    t_token *curr_token;
    int newline;
    int i;
    
    newline = 1;
    curr_token = data->tokens;

    if (curr_token->args_num > 0 && ft_strcmp(curr_token->args[0], "-n") == 0)
    {
        newline = 0;
        curr_token->args++;
        curr_token->args_num--;
    }

    i = 0;
    while (i < curr_token->args_num)
    {
        if (i > 0)
            printf(" ");
        printf("%s", curr_token->args[i]);
        i++;
    }

    if (newline)
        printf("\n");
}