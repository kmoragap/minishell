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

t_token *split_input1(char *input)
{
    t_token *tokens;
    t_token *start;

    tokens = malloc(sizeof(t_token));
    start = tokens;
    fill_tokens(tokens, input);
}

void    fill_token(t_token *tokens, char *input)
{
    char    *text;
    int     i;
    int     t;

    i = 0;
    t = 0;
    while (input[i])
    {
        if (input[i] == ' ')
        {
            i++;
            if (input[i] == 34)
            {
                i++;
                while (input[i] && input[i] != 34)
                {
                    t++;
                    i++;
                }
                if (!input[i])
                {
                    free_tokens(tokens);
                    error("some error message", 2); // idea for an error function: give it the error message it should print out & a code (int), which describes what we have to free (e.g.: 1 = free the very first malloc we created, 2 = free the first 2 mallocs)
                }
                
            }
            if (input[i] == 39)
            check_delimiter

        }
    }
}

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