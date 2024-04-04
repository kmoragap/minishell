/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/03/23 09:15:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    get_args(int *i, char *input, t_token *tokens, t_data **data)
{
    int     total_arg_len;

    total_arg_len = 0;
    while(input[*i + total_arg_len] && input[*i + total_arg_len] != '|' && input[*i + total_arg_len] != '<' && input[*i + total_arg_len] != '>')
        total_arg_len++;
    get_args_num(input, i, tokens, total_arg_len);
    if (malloc_args(input, i, tokens, total_arg_len) != 0)
        error; // error_function to do
}

void    get_args_num(char *input, int *i, t_token *tokens, int total_arg_len)
{
    int     j;
    int     quote;
    int     zero;

    zero = 0;
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
                text_in_quotes(quote, zero, &j, input);
            if (delim_space(input[j]) != 0)
                break;
        }
        tokens->args_num += 1;
    }
}

int     malloc_args(char *input, int *i, t_token *tokens, int total_arg_len)
{
    int     arg;
    int     len;

    arg = 0;
    tokens->args = malloc(sizeof(char *) * tokens->args_num);
    if (!tokens->args)
        return (1);
    while (arg <= tokens->args_num)
    {
        len = get_arg_len(input, i);
        tokens->args[arg] = malloc(len + 1);
        if (!tokens->args[arg])
            return (1);
        input_arg(input, i, len, &(tokens->args[arg]));
        arg++;
    }
    return (0);
}

int     get_arg_len(char *input, int *i)
{
    int     len;
    int     skip;
    int     quote;

    len = 0;
    skip = *i;
    quote = 0;
    while (input[skip + len])
    {
        skip_whitespace(&skip, input);
        while (quote = 0 && delim_space(input[skip + len]) == 0)
            check_quote(input[skip + len], &quote, &len);
        if (quote != 0)
            text_in_quotes(quote, skip, &len, input);
        if (delim_space(input[skip + len]) != 0)
            break;
    }
    return (len);
}

void    input_arg(char *input, int *i, int len, char **arg)
{
    int     n;

    n = 0;
    while (n < len)
    {
        *(arg[n]) = input[*i];
        n++;
        *i += 1;
    }
    *(arg[n]) = '\0';
}
