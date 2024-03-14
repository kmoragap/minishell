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

void tokenizer(t_data **data)
{
    t_token *tokens;
    t_token *start;

    tokens = malloc(sizeof(t_token));
    start = tokens;
    (*data)->tokens = tokens;
    create_tokens((*data)->input, (*data)->tokens);
}

void    create_tokens(char *input, t_token *tokens)
{
    int     i;

    i = 0;
    while (input[i])
    {
        
    }
}

void    first_word(char *input, t_token *tokens)
{
    int     i;

    i = 0;
    while (iswhitespace(input[i]) == 0 && input[i])
        i++;
    
}

void    fill_tokens(t_token *tokens, char *input)
{
    int     i;

    i = 0;
    while (input[i] && input[i] == ' ');
        i++;
    while (input[i])
    {
        if (input[i] == 34)
        {
            if (tokenize_quote(input, &i, tokens) == 1)
                error_tokens(tokens, "some error text");
        }
        else if (input[i] == 39)
        {
            if (tokenize_single_quote(input, &i, tokens) == 1)
                error_tokens(tokens, "some error text");
        }
        else if (input[i] == '|')
            tokenize_pipe(tokens, &i);
        else if (input[i] == ' ')
            skip_spaces(input, &i);
        else
            tokenize_txt(input, &i, tokens);
    }
}
