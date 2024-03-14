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
        check_special(&i, input, &tokens, data);
        skip_whitespace(&i, input),
        get_cmd(&i, input, &tokens, data);
        skip_whitespace(&i, input);
        get_args(&i, input, &tokens, data);
        id++;
        temp = malloc(sizeof(t_token));
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

void    check_special(int *i, char *input, t_token **tokens, t_data **data)
{
    if (input[*i] == '|' && tokens->id == 0)
        error; //error_function to do
    if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
        add_delim(i, input, tokens);
    if ((input[*i] == 34 || input[*i] == 39) && check_whitespaces(input, i) == 1)
        error; //error_function to do
}

void    add_delim(int *i, char *input,t_token **tokens)
{
    if (input[*i] == '|')
        tokens->delim = PIPE;
    else if (input[*i] == '<' && input[*i + 1] == '<')
    {
        *i += 1;
        tokens->delim = REDIR_H;
    }
    else if (input[*i] == '>' && input[*i + 1] == '>')
    {
        *i += 1;
        tokens->delim = REDIR_A;
    }
    else if (input[*i] == '>')
        tokens->delim = REDIR_O;
    else
        tokens->delim = REDIR_I;
    *i += 1;
}

int     check_whitespaces(char *input, int *i)
{
    int     j;

    j = 0;
    while (input[*i + j] && input[*i + j] != 34 && input[*i + j] != 39)
    {
        if (input[*i + j] != ' ' && input[*i + j] != '\t' && input[*i + j] != '\n' && input[*i + j] != '\v' && input[*i + j] != '\f' && input[*i + j] != '\r')
            return (0);
        j++;
    }
    return (1);
}
