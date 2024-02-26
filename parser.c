/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:37 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/26 10:47:51 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_operator(char *tok)
{
    if(strcmp(tok, "|") == 0)
        return 1;
    if(strcmp(tok, ">") == 0)
        return 1;
    if(strcmp(tok, ">>") == 0)
        return 1;
    if(strcmp(tok, "<") == 0)
        return 1;
    return 0;
}

void parse_input(t_data **data)
{
    const char *delim;
    char *tok;
    t_node *current;
    t_node *previous;

    current = NULL;
    previous = NULL;
    
    delim = " \t\r\n\a";
    tok = strtok((*data)->input, delim);
    while(tok != NULL)
    {
        current = malloc(sizeof(t_node));
        current->content = tok;
        current->next = NULL;
        current->child = NULL;

        if(previous != NULL)
        {
            if(is_operator(tok))
                previous->child = current;
            else
                previous->next = current;
        }
        if((*data)->node == NULL)
            (*data)->node = current;
        printf("content: %s\n", current->content);

        previous = current;
        tok = strtok(NULL, delim);
    }
    
}