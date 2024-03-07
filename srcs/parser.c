/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:37 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/07 12:38:40 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/**
 * no se si es necesario crear esto, ver en casa como hacer que esto funcione sin un tree. hay que revisar los pros y contras
 * quizas tratar de crear una estructura de simples comandos y otra de comandos mas completos
 * sss
*/


#include <string.h>


int check_expand_args(char *args)
{
    int i;

    i = 0;
    while(args[i] != '\0')
    {
        if(args[i] == '$' && args[i+1] != '\0')
            return (1);
        i++;
    }
    return (0);
}

/**
 * [] check if there are expansions and expand them
 * [] check if there are pipes
 * [] check if there are redirections
 * preparar el input:
 *
*/



void parser(t_data **data)
{
    t_token *tokens;
    t_token *prev;
    int is_pipe;
    int is_redir;
    
    tokens = (*data)->tokens;
    prev = NULL;

    while(tokens != NULL)
    {
        is_pipe = 0;
        is_redir = 0;
        if(tokens->type == EXPAND || check_expand_args(tokens->args))
            ; // to-do
        if(tokens->delim == PIPE)
            is_pipe = PIPE;
        if(tokens->delim == REDIR_I || tokens->delim == REDIR_O)
            is_redir = 1;
        execute(tokens, is_pipe, is_redir);     
        tokens->prev = prev;   
        tokens = tokens->next;
        prev = tokens;
    }
}