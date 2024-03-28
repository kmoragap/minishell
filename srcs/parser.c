/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:37 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/28 15:35:58 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* TODO:
 * [] check builtins func
 * [] expand token when is $0, $?, etc
 * [] maybe add the ints values used here to the data structure 
*/

    /*
        each time a command is executed it will be stored in a variable called last_exit_status added to each token structure, 
        this means that it can be tracked by the exit status of the previous/next token and when the $? expander is called, 
        it can be easily tracked what was the last existing status in the exxpand variable.

        Also, the especial cases in the expand could be handle easily returning a empty string, for example with $0
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
        if(check_builtins(tokens) == 1)
                is_builtins = TRUE;
        if(tokens->delim == PIPE)
            is_pipe = PIPE;
        if(tokens->delim == REDIR_I)
            is_redir = REDIR_I;
        else if(tokens->delim == REDIR_O)
            is_redir = REDIR_O;
        else
            is_redir = FALSE;
        execute_helper(tokens, env, is_pipe, is_redir, is_builtins);
        tokens->prev = prev;
        tokens = tokens->next;
        prev = tokens;
    }
}






