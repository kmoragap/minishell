/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:36:48 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/04 16:35:25 by kmoraga          ###   ########.fr       */
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
}