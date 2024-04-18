/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:36:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    check_special(int *i, char *input, t_token **tokens, t_data *data)
{
    t_data  *temp;

    temp = data;
    data = temp;
    (*tokens)->delim = 0;
    //data mitgegeben für error, muss deshalb temp kreieren (sonst unused variable)
    if (input[*i] == '|' && (*tokens)->id == 0)
        exit (0); //error; //error_function to do
    if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
    {
        add_delim(i, input, tokens);
        return ;
    }
    if ((input[*i] == 34 || input[*i] == 39) && check_whitespaces(input, i) == 1)
        exit (0);//error; //error_function to do
}

void    add_delim(int *i, char *input, t_token **tokens)
{
    if (input[*i] == '|')
        (*tokens)->delim = PIPE;
    else if (input[*i] == '<' && input[*i + 1] == '<')
    {
        *i += 1;
        (*tokens)->delim = REDIR_H;
    }
    else if (input[*i] == '>' && input[*i + 1] == '>')
    {
        *i += 1;
        (*tokens)->delim = REDIR_A;
    }
    else if (input[*i] == '>')
        (*tokens)->delim = REDIR_O;
    else
        (*tokens)->delim = REDIR_I;
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
