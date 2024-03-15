/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/03/01 23:37:05 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    get_cmd(int *i, char *input, t_token *tokens, t_data **data)
{
    int     j;
    int     column; 

    j = 0;
    column = 0;
    while (input[*i + j])
    {
        while (column == 0 && delim_space(input[*i + j]) == 0)
            check_quote(input[*i + j], &column, &j);
        if (column != 0)
            text_in_quotes(column, i, &j, input);
        if (delim_space(input[*i + j] != 0))
            break;
    }
    inputcpy(input, i, j, tokens);
}

void    check_quote(char c, int *column, int *j)
{
    if (c == 39)
        *column = 1;
    else if (c == 34)
        *column = 2;
    *j += 1;
}

void    delim_space(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    if (c == ' ' || c == '\n' || c  == '\t' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

void    text_in_quotes(int column, int *i, int *j, char *input)
{
    if (input[*i + *j] == 34 && input[*i + *j + 1] == '|' && input[*i + *j + 2] == 34)
        error; 
    if (input[*i + *j] == 39 && input[*i + *j + 1] == '|' && input[*i + *j + 2] == 39)
        error;
    *j += 1;
    while (input[*i + *j])
    {
        if (column == 1 && input[*i + *j] == 39)
            return;
        if (column == 2 && input[*i + *j] == 34)
            return;
        *j += 1;
    }
}

void    inputcpy(char *input, int *i, int j, t_token *tokens)
{
    int     n;

    n = 0;
    tokens->cmd = malloc(j + 1);
    if (!tokens->cmd)
        error; //error_function to do
    while (n < j)
    {
        tokens->cmd[n] = input[*i + n]
        n++;
        *i += 1;
    }
    tokens->cmd[n] = '\0';
}
