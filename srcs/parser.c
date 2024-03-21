/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:37 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/21 16:18:49 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void parser(t_data **data)
{
    t_token *tokens;
    t_token *prev;
    char **env;
    int is_pipe;
    int is_redir;
    
    tokens = (*data)->tokens;
    prev = NULL;
    env = (*data)->env;
    
    while(tokens != NULL)
    {
        is_pipe = 0;
        is_redir = 0;
        
        expand_token(tokens, env);
        printf("cmd: %s\n", tokens->cmd);
        printf("args: %s\n", tokens->args);
        if(tokens->delim == PIPE)
            is_pipe = PIPE;
        if(tokens->delim == REDIR_I)
            is_redir = REDIR_I;
        else if(tokens->delim == REDIR_O)
            is_redir = REDIR_O;
        else
            is_redir = 0;
        execute(tokens, env, is_pipe, is_redir);
        tokens->prev = prev;
        tokens = tokens->next;
        prev = tokens;
    }
}






