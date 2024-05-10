/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:50 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/10 11:44:25 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_builtin(t_data *data)
{
    int type;
    type = check_builtins(data->tokens->cmd);
    if(type == EXPORT)
        execute_export_builtin(data);
    if(type == ENV)
        put_env(data);
    if(type == PWD)
        get_pwd();
    if(type == UNSET)
        ft_unset(data);
    if(type == ECHO)
        ft_echo(data);
    if(type == CD)
        ft_cd(data);
}

void execute_token(t_data *data)
{
    //if is builtin
    if(check_builtins(data->tokens->cmd) != -1)
        execute_builtin(data);
}