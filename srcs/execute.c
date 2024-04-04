/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:15 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/04 16:46:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * from parser we have our command ready to be execute
 * maybe put all the int true/false variables in the data structure bc is not allowed more than 5 args in a func
 * 
 * 
 * 
 * 
*/

void execute_command(t_token *token, char **env)
{
    /**
     * execute simple command
     * 
    */
}




void execute_helper(t_token *token, char **env, int is_pipe, int is_redir, int is_builtins) 
{
    (void)is_pipe;
    (void)is_redir;
    (void)is_builtins;
    (void)env;
    (void)token;
    //if (is_pipe)
        // Implementa la lógica para manejar la ejecución con tuberías
    //else if (is_redir) 
        // Implementa la lógica para manejar la ejecución con redirecciones
    //else if (is_builtins) 
        // Implementa la lógica para manejar la ejecución de los builtins
    //else
        //execute_command(token, env);
}



