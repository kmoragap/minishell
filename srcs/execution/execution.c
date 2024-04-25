/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:35:50 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/25 17:31:50 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * tratar de hacer una funcion de estados para saber en que estado estoy ejecutando
 * a la hora de ejecutar los comandos
*/
                                    //data->env
void execute_token(t_data *data)
{
    //if is builtin
    if(check_builtins_type(data->tokens->cmd) != -1)
        execute_builtin(data);
}