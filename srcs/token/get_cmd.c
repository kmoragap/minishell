/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/03/23 09:15:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    get_cmd(int *i, char *input, t_token *tokens, t_data **data)
{
    int     j;
    int     quote; 

    j = 0;
    quote = 0;
    while (input[*i + j])
    {
        while (quote == 0 && delim_space(input[*i + j]) == 0)
            check_quote(input[*i + j], &quote, &j);
        if (quote != 0)
            text_in_quotes(quote, *i, &j, input);
        if (delim_space(input[*i + j] != 0))
            break;
    }
    input_cmd(input, i, j, tokens);
}

void    check_quote(char c, int *quote, int *j)
{
    if (c == 39)
        *quote = 1;
    else if (c == 34)
        *quote = 2;
    *j += 1;
}

int    delim_space(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    if (c == ' ' || c == '\n' || c  == '\t' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

void    text_in_quotes(int quote, int i, int *j, char *input)
{
    if (input[*i + *j] == 34 && input[*i + *j + 1] == '|' && input[*i + *j + 2] == 34)
        error; 
    if (input[*i + *j] == 39 && input[*i + *j + 1] == '|' && input[*i + *j + 2] == 39)
        error;
    *j += 1;
    while (input[*i + *j])
    {
        if (quote == 1 && input[*i + *j] == 39)
            return;
        if (quote == 2 && input[*i + *j] == 34)
            return;
        *j += 1;
    }
}

void    input_cmd(char *input, int *i, int j, t_token *tokens)
{
    int     n;

    n = 0;
    tokens->cmd = malloc(j + 1);
    if (!tokens->cmd)
        error; //error_function to do
    while (n < j)
    {
        tokens->cmd[n] = input[*i];
        n++;
        *i += 1;
    }
    tokens->cmd[n] = '\0';
}
