/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:15 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/05 15:09:07 by kmoraga          ###   ########.fr       */
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





void execute_helper(t_token *token, char **env, int is_pipe, int is_redir, int is_builtins) 
{
    (void)env;
    (void)token;
    printf("prev: %p\n", token->prev);
    if (token && (is_pipe || (token->prev && token->prev->delim == PIPE)))
        printf("aquí pipe\n");
        // Implementa la lógica para manejar la ejecución con tuberías
    if (is_redir)
        printf("aquí redir: %d\n", token->delim); 
        // Implementa la lógica para manejar la ejecución con redirecciones
    if (is_builtins)
        printf("aquí builtin\n"); 
        // Implementa la lógica para manejar la ejecución de los builtins
    if(token->prev == NULL && is_pipe != PIPE && is_redir == FALSE && is_builtins == FALSE)
        printf("ejecutando...\n");

}

