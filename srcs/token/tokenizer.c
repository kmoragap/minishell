/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:35:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    tokenizer(t_data *data)
{
    t_token *tokens;

    tokens = malloc(sizeof(t_token));
    if (!tokens)
        exit (0);//error; //error_function to do
    data->tokens = tokens;
    create_tokens(data->input, &tokens, data);
}

void    create_tokens(char *input, t_token **tokens, t_data *data)
{
    int     i;
    int     id;

    i = 0;
    id = 0;
    while (input[i])
    {
        (*tokens)->id = id;
        skip_whitespace(&i, input);
        check_special(&i, input, tokens, data);
        skip_whitespace(&i, input);
        get_cmd(&i, input, tokens);
        skip_whitespace(&i, input);
        get_args(&i, input, tokens, data);
        id++;
        (data)->token_num = id; 
        tokens = next_token(tokens);
        if (!input[i])
            break ;
    }
}

t_token **next_token(t_token **tokens)
{
    t_token *temp;
    
    if ((*tokens)->id == 0)
        (*tokens)->prev = NULL;
    temp = malloc(sizeof(t_token));
    if (!temp)
        exit (0); //error_function to do
    (*tokens)->next = temp;
    temp->prev = (*tokens);
    (*tokens) = (*tokens)->next;
    (*tokens)->next = NULL;
    return (tokens);
}



void    skip_whitespace(int *i, char *input)
{
    while (input[*i] && (input[*i] == ' ' || input[*i] == '\n' || input[*i] == '\t' || input[*i] == '\v' || input[*i] == '\f' || input[*i] == '\r'))
        *i += 1;
}
