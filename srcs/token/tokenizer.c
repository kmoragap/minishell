/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/15 17:21:43 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    tokenizer(t_data **data)
{
    t_token *tokens;
    t_token *start;

    tokens = malloc(sizeof(t_token));
    if (!tokens)
        exit (0);//error; //error_function to do
    start = tokens;
    (*data)->tokens = &tokens;
    create_tokens((*data)->input, (*data)->tokens, data);
    (*data)->tokens = &start;
    printf("start = %d", start->id);
    parser(data);
}

void    create_tokens(char *input, t_token **tokens, t_data **data)
{
    int     i;
    int     id;
    t_token *temp;

    i = 0;
    id = 0;
    while (input[i])
    {
        (*tokens)->id = id;
        //printf("Token_ID: %d\n", id);
        skip_whitespace(&i, input);
        check_special(&i, input, tokens, data);
        skip_whitespace(&i, input);
        get_cmd(&i, input, tokens);
        //printf("cmd: %s\n", (*tokens)->cmd);
        skip_whitespace(&i, input);
        get_args(&i, input, tokens, data);
        //printf("arg: %s\n", (*tokens)->args[0]);
        //printf("arg: %s\n", (*tokens)->args[1]);
        //printf("arg: %s\n", (*tokens)->args[2]);
        //printf("delim: %d\n", (*tokens)->delim);
        id++;
        (*data)->token_num = id; 
        if (!input[i])
            break ;
        temp = malloc(sizeof(t_token));
        if (!temp)
            exit (0);//error; //error_function to do
        (*tokens)->next = temp;
        temp->prev = (*tokens);
        (*tokens) = (*tokens)->next;
        (*tokens)->next = NULL;
        //write(1, "---------------------------------\n", 33);
    }
}

void    skip_whitespace(int *i, char *input)
{
    while (input[*i] && (input[*i] == ' ' || input[*i] == '\n' || input[*i] == '\t' || input[*i] == '\v' || input[*i] == '\f' || input[*i] == '\r'))
        *i += 1;
}
