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
void execute_token(t_token **token, char **env)
{
    //if is builtin
    if(check_builtins((*token)->cmd) == 1)
        execute_builtin((*token)->cmd, (*token)->args, env);
}