/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:07:09 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/18 12:45:29 by kmoraga          ###   ########.fr       */
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
    i = 0;
    while (curr_token->args_num > 0 && is_n_option(curr_token->args[i]))
    {
        newline = 0;
        i++;
    }
    
    while (i < curr_token->args_num)
    {
        processed_arg = remove_outer_quotes(curr_token->args[i]);
        write(1, processed_arg, ft_strlen(processed_arg));
        free(processed_arg);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
}