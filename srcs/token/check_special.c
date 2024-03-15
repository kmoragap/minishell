/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/03/01 23:37:05 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    check_special(int *i, char *input, t_token *tokens, t_data **data)
{
    if (input[*i] == '|' && tokens->id == 0)
        error; //error_function to do
    if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
        add_delim(i, input, tokens);
    if ((input[*i] == 34 || input[*i] == 39) && check_whitespaces(input, i) == 1)
        error; //error_function to do
}

void    add_delim(int *i, char *input,t_token *tokens)
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
