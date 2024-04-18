/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:36:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// t_data **data --> eigentlich rein für error function

void    get_cmd(int *i, char *input, t_token **tokens) 
{
    int     j;
    int     quote; 

    j = 0;
    quote = 0;
    while (input[*i + j])
    {
        while (quote == 0 && delim_space(input[*i + j]) == 0 && input[*i + j])
            check_quote(input[*i + j], &quote, &j);
        if (quote != 0)
        {
            if (text_in_quotes(quote, *i, &j, input) != 0)
                exit (0); //error
            j += 1;
        }
        if (delim_space(input[*i + j]) != 0)
            break;
    }
    input_cmd(input, i, j, tokens);
    if (!(*tokens)->cmd)
        exit (0); //error
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

int    text_in_quotes(int quote, int i, int *j, char *input)
{
    if (input[i + *j] == 34 && input[i + *j + 1] == '|' && input[i + *j + 2] == 34)
        return (1); 
    if (input[i + *j] == 39 && input[i + *j + 1] == '|' && input[i + *j + 2] == 39)
        return (1);
    *j += 1;
    while (input[i + *j])
    {
        if (quote == 1 && input[i + *j] == 39)
            return (0);
        if (quote == 2 && input[i + *j] == 34)
            return (0);
        *j += 1;
    }
    if (!input[i + *j])
        return (1);
    return (0);
}

int    input_cmd(char *input, int *i, int j, t_token **tokens)
{
    int     n;

    n = 0;
    (*tokens)->cmd = malloc(sizeof(char) * (j + 1));
    if (!(*tokens)->cmd)
        return (1);
    while (n < j)
    {
        (*tokens)->cmd[n] = input[*i];
        n++;
        *i += 1;
    }
    (*tokens)->cmd[n] = '\0';
    return (0);
}
