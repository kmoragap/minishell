/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:50 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/27 17:27:44 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * tratar de hacer una funcion de estados para saber en que estado estoy ejecutando
 * a la hora de ejecutar los comandos
*/
void execute_token(t_data *data)
{
    //if is builtin
    if(check_builtins(data->tokens->cmd) != -1)
        execute_builtin(data);
}