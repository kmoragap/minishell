/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/17 17:21:26 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token  *tokenizer(t_data *data)
{
    if (ft_calloc(data, F_INPUT, (void *)&(data->tokens), sizeof(t_token)) == 1)
        return (data->tokens);
    create_tokens(data->input, &data->tokens, data);
    data->tokens = move_to_first_token(data->tokens);
    return (data->tokens);
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
        skip_whitespace(&i, input);
        id++;
        (data)->token_num = id;
        if (input[i])
            tokens = next_token(tokens, data);
    }
}

t_token **next_token(t_token **tokens, t_data *data)
{
    t_token *temp;
    
    if ((*tokens)->id == 0)
        (*tokens)->prev = NULL;
    temp = ft_calloc_norm(1, sizeof(t_token));
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
