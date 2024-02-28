/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:46:13 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/28 22:46:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"


int check_type_tk(char *token)
{
    if (strcmp(token, "|") == 0)
        return (PIPE);
    if (strcmp(token, ">") == 0)
        return (REDIR_O);
    if (strcmp(token, "<") == 0)
        return (REDIR_I);
    return (WORD);
}

/*
    *is not complete yet :(
    *is a very simple version, has to be improved bc it does not handle errors
    *it does not free the memory...
    *have to be more efficient tokenizing the input, bc is not working on somes cases, like "ls|wc"
*/

t_token *split_input(char *input)
{
    t_token *tokens;
    t_token *start;
    char *token;
    int i;

    tokens = malloc(sizeof(t_token));
    start = tokens;
    i = 0;

    token = strtok(input, " ");
    while (token != NULL)
    {
        tokens->content = token;
        tokens->type = check_type_tk(token);
        tokens->id = i;
        tokens->next = malloc(sizeof(t_token));
        tokens = tokens->next;
        token = strtok(NULL, " ");
        i++;
    }
    tokens->next = NULL;
    return start;
}

void lexer(t_data **data)
{
    (*data)->tokens = split_input((*data)->input);
    check_tokens_lst((*data)->tokens);
}