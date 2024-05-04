/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:50 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/18 15:40:26 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * tratar de hacer una funcion de estados para saber en que estado estoy ejecutando
 * a la hora de ejecutar los comandos
*/
                                    //data->env
t_data  *execute_token(t_data *data)
{
    //pipe & redirect everthing 
    create_children(data);
    //if is builtin
    if(check_builtins(data->tokens->cmd) == 1)
        execute_builtin(data->tokens->cmd, data->tokens->args, data->env);
    //else
        //execute_nb(data);
}