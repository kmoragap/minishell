/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:36:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_all(t_data *data)
{
    if (data->free_code >= F_TOKS)
        free_toks(data);
    if (data->free_code >= F_TOKCMD)
        free(data->tokens->cmd);
    if (data->free_code >= F_EMPTOK)
        free(data->tokens);
    if (data->free_code >= F_INPUT)
        free(data->input);
}
// finishhhhhhhhhh! --> free toks isn't done yet! and add a new initializer for the data 
void    free_toks(t_data *data)
{
    while (data->tokens->args_num >= 0)
    {
        free(data->tokens->args[data->tokens->args_num]);
        data->tokens->args_num -= 1;
    }
    free(data->tokens->args);
}
