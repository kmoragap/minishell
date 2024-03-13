/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:15 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/13 18:04:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * from parser we have our command ready to be execute
 * here:
 * [] check for the pipes and excute them
 * [] check for the redirs and wait until the end to save te output on the file
*/


void execute(t_token *token, int is_pipe, int is_redir)
{

    (void)is_pipe;
    (void)is_redir;
    //verificar si hay pipe
    //verificar si hay redir
    //if(is_redir == REDIR_I || is_redir == REDIR_O && (token->delim == REDIR_I || token->delim == REDIR_O))
    //    ;
    char *args[] = {token->args, NULL};
    execvp(token->cmd, args);
    //seguir implementando, solo estoy probando esta parte.
}