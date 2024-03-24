/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:37 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/24 16:01:39 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* TODO:
 * [] check builtins func
 * [] expand token when is $0, $?, etc
 * [] maybe add the ints values used here to the data structure 
*/

void parser(t_data **data)
{
    t_token *tokens;
    t_token *prev;
    char **env;
    int is_pipe;
    int is_redir;
    int is_builtins;
    
    tokens = (*data)->tokens;
    prev = NULL;
    env = (*data)->env;
    
    while(tokens != NULL)
    {
        is_pipe = FALSE;
        is_redir = FALSE;
        is_builtins = FALSE;
        
        expand_token(tokens, env);
        //if(check builtins func)
                //is_builtins = TRUE;
        if(tokens->delim == PIPE)
            is_pipe = PIPE;
        if(tokens->delim == REDIR_I)
            is_redir = REDIR_I;
        else if(tokens->delim == REDIR_O)
            is_redir = REDIR_O;
        else
            is_redir = FALSE;
        execute(tokens, env, is_pipe, is_redir);
        tokens->prev = prev;
        tokens = tokens->next;
        prev = tokens;
    }
}






