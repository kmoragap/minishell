/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/03/01 23:37:05 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    tokenizer(t_data **data)
{
    t_token *tokens;
    t_token *start;

    tokens = malloc(sizeof(t_token));
    if (!tokens)
        error; //error_function to do
    start = tokens;
    (*data)->tokens = tokens;
    create_tokens((*data)->input, (*data)->tokens, data);
}

void    create_tokens(char *input, t_token *tokens, t_data **data)
{
    int     i;
    int     id;
    t_token temp;

    i = 0;
    id = 0;
    while (input[i])
    {
        tokens->id = id;
        skip_whitespace(&i, input);
        check_special(&i, input, tokens, data);
        skip_whitespace(&i, input),
        get_cmd(&i, input, tokens, data);
        skip_whitespace(&i, input);
        get_args(&i, input, tokens, data);
        id++;
        temp = malloc(sizeof(t_token));
        if (!temp)
            error; //error_function to do
        temp = tokens->next;
        temp->prev = tokens;
        tokens = temp;
    }
}

void    skip_whitespace(int *i, char *input)
{
    while (input[*i] == ' ' || input[*i] == '\n' || input[*i] == '\t' || input[*i] == '\v' || input[*i] == '\f' || input[*i] == '\r')
        *i += 1;
}
