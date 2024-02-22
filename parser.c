/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:37 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/22 14:50:55 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_input(t_data **data)
{
    const char *delim;
    char *tok;

	delim = " \t\r\n\a";
    (*data)->cmd = malloc(sizeof(t_cmd));
    //handle this part of malloc
    
    tok = strtok((*data)->input, delim);
    while(tok != NULL)
    {
        (*data)->cmd->content = tok;
        printf("content: %s\n", (*data)->cmd->content);
        (*data)->cmd = (*data)->cmd->next;
        tok = strtok(NULL, delim);
    }
    (*data)->cmd->content = NULL;
}