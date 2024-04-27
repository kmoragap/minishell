/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/20 11:09:27 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void    tokenizer(t_data *data)
{
    t_token *tokens;

    tokens = ft_calloc(1, sizeof(t_token));
    if (!tokens)
    {
        malloc_error(data, F_INPUT);
        return ;
    }
    data->tokens = tokens;
    create_tokens(data->input, &tokens, data);
}

void    create_tokens(char *input, t_token **tokens, t_data *data)
{
    int     i;
    int     id;

    i = 0;
    id = 0;
    while (input[i] && data->err_code == ER_NO)
    {
        (*tokens)->id = id;
        (*tokens)->exit_status = NOTHING;
        skip_whitespace(&i, input);
        check_special(&i, input, tokens, data);
        if (data->err_code != ER_NO)
            break ;
        skip_whitespace(&i, input);
        get_cmd(&i, input, tokens, data);
        if (data->err_code != ER_NO)
            break ;
        skip_whitespace(&i, input);
        get_args(&i, input, tokens, data);
        if (data->err_code != ER_NO)
            break ;
        id++;
        (data)->token_num = id; 
        tokens = next_token(tokens, data);
    }
}

t_token **next_token(t_token **tokens, t_data *data)
{
    t_token *temp;
    
    if ((*tokens)->id == 0)
        (*tokens)->prev = NULL;
    temp = ft_calloc(1, sizeof(t_token));
    if (!temp)
        malloc_error(data, F_TOKS);
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
