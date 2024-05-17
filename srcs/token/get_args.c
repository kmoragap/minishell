/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/17 16:11:36 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_args(int *i, char *input, t_token **tokens, t_data *data)
{
    int     total_arg_len;
    t_data  *temp;

    if (!input[*i])
    {
        create_empty_args(tokens, data);
        return ;
    }
    temp = data;
    data = temp;
    total_arg_len = get_total_arg_len(input, *i);
    if (total_arg_len == 0)
    {
        create_empty_args(tokens, data);
        return ;    
    }
    get_args_num(input, i, total_arg_len, tokens);
    if (malloc_args(input, i, tokens) != 0)
        malloc_error(data, F_TOKCMD);
}

int     get_total_arg_len(char *input, int i)
{
    int     len;
    int     temp;

    len = 0;
    while (input[i + len])
    {
        if (input[i + len] == 34 || input[i + len] == 39)
        {
            temp = i + len;
            len++;
            while (input[i + len] != input[temp] && input[i + len])
                len++;
        }
        if (input[i + len] == '|' || input[i + len] == '<' || input[i + len] == '>')
            break ;
        len++;
    }
    return (len);
}

void    create_empty_args(t_token **tokens, t_data *data)
{
    (*tokens)->args = ft_calloc_norm(1, sizeof(char *));
    if (!(*tokens)->args)
    {
        malloc_error(data, F_TOKCMD);
        return ;
    }
    (*tokens)->args[0] = ft_calloc_norm(1, sizeof(char));
    if (!(*tokens)->args[0])
    {
        free((*tokens)->args);
        malloc_error(data, F_TOKCMD);
        return ;
    }
    (*tokens)->args[0][0] = '\0';
    (*tokens)->args_num = 0;
}

void    get_args_num(char *input, int *i, int total_arg_len, t_token **tokens)
{
    int     j;
    int     quote;
    int     zero;

    zero = 0;
    j = *i;
    (*tokens)->args_num = 0;
    while (input[j] && (j - *i) < (total_arg_len))
    {
        while (input[j] && (j - *i) < (total_arg_len))
        {
            quote = 0;
            skip_whitespace(&j, input);
            while (quote == 0 && delim_space(input[j]) == 0 && input[j])
                check_quote(input[j], &quote, &j);
            if (quote != 0)
                text_in_quotes(quote, zero, &j, input);
            if (delim_space(input[j]) != 0)
            {
                skip_whitespace(&j, input);
                break;
            }
        }
        (*tokens)->args_num += 1;
    }
}

int     malloc_args(char *input, int *i, t_token **tokens)
{
    int     arg;
    int     len;

    arg = 0;
    (*tokens)->args = ft_calloc_norm(((*tokens)->args_num + 1), sizeof(char *));
    if (!(*tokens)->args)
        return (1);
    while (arg < (*tokens)->args_num)
    {
        len = get_arg_len(input, i);
        (*tokens)->args[arg] = ft_calloc_norm(len + 1, sizeof(char));
        if (!(*tokens)->args[arg])
        {
            free((*tokens)->args);
            return (1);
        }
        input_arg(input, i, len, tokens, arg);
        arg++;
    }
    (*tokens)->args[(*tokens)->args_num] = NULL;
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
        while (quote == 0 && delim_space(input[skip + len]) == 0 && input[skip + len])
            check_quote(input[skip + len], &quote, &len);
        if (quote != 0)
        {
            text_in_quotes(quote, skip, &len, input);
            len++;
        }
        if (delim_space(input[skip + len]) != 0)
            break;
    }
    return (len);
}

void    input_arg(char *input, int *i, int len, t_token **tokens, int arg)
{
    int     n;

    n = 0;
    while (input[*i] && (input[*i] == ' ' || input[*i] == '\n' || input[*i] == '\t' || input[*i] == '\v' || input[*i] == '\f' || input[*i] == '\r'))
        *i += 1;
    while (n < len)
    {
        (*tokens)->args[arg][n] = input[*i]; 
        n++;
        *i += 1;
    }
    (*tokens)->args[arg][n] = '\0';
}
