/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:15 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/21 15:47:58 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * from parser we have our command ready to be execute
 * here:
 * [] check for the pipes and excute them
 * [] check for the redirs and wait until the end to save te output on the file
*/


void execute(t_token *token, char **env, int is_pipe, int is_redir)
{
    (void)is_pipe;
    (void)is_redir;
    (void)token;
    (void)env;    
}



