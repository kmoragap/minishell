/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:36:48 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/25 16:54:43 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void execute_builtin(t_data *data)
{
    int type;
    type = check_builtins_type(data->tokens->cmd);
    printf("estoy en builtin\n");
    if(type == EXPORT)
        execute_export_builtin(data);
    
}