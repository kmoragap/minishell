/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:15 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/28 15:31:17 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * from parser we have our command ready to be execute
 * here:
 * [] check for the pipes and excute them
 * 
*/






void execute_helper(t_token *token, char **env, int is_pipe, int is_redir, int is_builtins) 
{
    //if (is_pipe)
        // Implementa la lógica para manejar la ejecución con tuberías
    //else if (is_redir) 
        // Implementa la lógica para manejar la ejecución con redirecciones
    //else if (is_builtins) 
        // Implementa la lógica para manejar la ejecución de los builtins
    //else
        //execute_command(token, env);
}



