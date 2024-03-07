/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:15 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/07 14:10:24 by kmoraga          ###   ########.fr       */
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
    int id_p;
    //verificar si hay pipe
    if(is_pipe == PIPE)
        //prepare pipe: that's means create the pipe and cpy the cmd/args and wait for the next command
        //check the next commmand id an set id_p to the next command id
    if(id_p == token->id && token->prev->delim == PIPE)
        //check the std_i
        //execute command and the previus one;
    //verificar si hay redir
}