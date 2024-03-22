/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/03/01 23:37:05 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    get_args(int *i, char *input, t_token *tokens, t_data **data)
{
    int     total_arg_len;

    total_arg_len = 0;
    get_total_args_len(input, i, &total_arg_len);
    get_args_num(input, i, tokens, total_arg_len);
    if (malloc_args(input, i, tokens, total_arg_len) != 0)
        error;
    if (fill_args(input, i, tokens, total_arg_len) != 0)
        error;
}

void    get_total_args_len(char *input, int *i, int *total_arg_len)
{
    while(input[*i + *total_arg_len] && input[*i + *total_arg_len] != '|' && input[*i + *total_arg_len] != '<' && input[*i + *total_arg_len] != '>')
        *total_arg_len += 1;
}

void    get_args_num(char *input, int *i, t_token *tokens, int total_arg_len)
{
    int     j;
    int     quote;

    quote = 0;
    j = *i;
    tokens->args_num = 0;
    while (input[j] && (j - *i) < total_arg_len)
    {
        while (input[j] && (j - *i) < total_arg_len)
        {
            skip_whitespace(&j, input);
            while (quote = 0 && delim_space(input[j]) == 0)
                check_quote(input[j], &quote, &j);
            if (quote != 0)
                text_in_quotes(quote, &0, &j, input);
            if (delim_space(input[*j] != 0))
                break;
        }
        tokens->args_num += 1;
    }
}

int    malloc_args(char *input, int *i, t_token *tokens, int total_arg_len)
{
    int     arg;
    int     str;

    arg = 0;
    str = 0;
    tokens->args = malloc(sizeof(char *) * tokens->args_num);
    
    


}



void    old_get_args(int *i, char *input, t_token *tokens, t_data **data)
{
    int     j;
    int     column; 

    j = 0;
    column = 0;
    while (input[*i + j])
    {
        while (input[*i + j])
        {
            while (column == 0 && delim_space(input[*i + j]) == 0)
                check_quote(input[*i + j], &column, &j);
            if (column != 0)
                text_in_quotes(column, i, &j, input);
            if (delim_space(input[*i + j] != 0))
                break;
        }
        inputcpy_args(input, i, j, tokens);
        if (input[*i + j] == '|' || input[*i + j] == '<' || input[*i + j] == '>')
            break;
    }
}

void    inputcpy_args(char *input, int *i, int j, t_token *tokens)
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

