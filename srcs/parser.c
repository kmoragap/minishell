/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:37 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/06 13:02:54 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/**
 * no se si es necesario crear esto, ver en casa como hacer que esto funcione sin un tree. hay que revisar los pros y contras
 * quizas tratar de crear una estructura de simples comandos y otra de comandos mas completos
 * sss
*/





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

void create_pipe(t_token *prev, t_token *next, t_data **data)
{
    
}
/**
 * [] check if there are expansions and expand them
 * [] check if there are pipes
 * [] check if there are redirections
*/


void parser(t_data **data)
{
    t_token *tokens = (*data)->tokens;
    t_token *start = tokens;
    t_token *prev = NULL;
    
    while(tokens != NULL)
    {
        if(tokens->type == EXPAND || check_expand_args(tokens->args))
        {
            //expand the token and replace it with the expanded token
            //if the token is a command, expand the command and also check if there are arguments to expand
        }
        //continuar.. mñn
    }
    (*data)->tokens = start;
}
