/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:07:09 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/10 18:41:15 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int is_n_option(char *arg)
{
    int i;

    if (arg[0] != '-')
        return (0);
    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void ft_echo(t_data *data)
{
    t_token *curr_token;
    int newline;
    int i;
    char *processed_arg;

    curr_token = data->tokens;
    newline = 1;
    while (curr_token->args_num > 0 && is_n_option(curr_token->args[0]))
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
        processed_arg = remove_outer_quotes(curr_token->args[i]);
        printf("%s", processed_arg);
        free(processed_arg);
        i++;
    }
    if (newline)
        printf("\n");
}