/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:19:53 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/28 22:29:55 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void check_tokens_lst(t_token *tokens)
{
    while (tokens->next != NULL)
    {
        printf("content: %s\n", tokens->content);
        if(tokens->type == WORD)
            printf("type: WORD\n");
        else if(tokens->type == PIPE)
            printf("type: PIPE\n");
        else if(tokens->type == REDIR_O)
            printf("type: REDIR_O\n");
        else if(tokens->type == REDIR_I)
            printf("type: REDIR_I\n");
        printf("id: %d\n", tokens->id);
        tokens = tokens->next;
    }
}