/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/10 16:10:01 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **join_cmd_arg(t_data *data)
{
    char    **args;
    int     size;
    int     args_cntr;

    size = size_of_args(data);
    if (ft_calloc(data, 0, (void *)&args, (size + 2) * sizeof(char *)) == 1)
        exit(12);
    args[0] = get_cmd_for_args(data);
    if (!args[0])
    {
        free(args);
        exit(12);
    }    
    // if (data->tokens->args_num == 0 && data->tokens->next && data->tokens->next->delim == REDIR_H)
    // {
    //     args = heredoc_as_arg(data, args);
    //     return (args);
    // }
    args = cpy_token_args(data, args, &args_cntr);
    if (!args)
        exit(12);
    if (size > (data->tokens->args_num + 1))
        args = cpy_next_token_args(data, args, &args_cntr);
    if (!args)
        exit(12);
    args[size] = NULL;
    return (args);
}

// char    **heredoc_as_arg(t_data *data, char **args)
// {
//     int     i;
//     char    **heredoc;
//     char    **new;

//     i = 0;
//     heredoc = ft_split(data->tokens->heredoc, '\n');
//     if (!heredoc)
//     {
//         free_args(args, 0);
//         exit (12);
//     }
//     while (heredoc[i])
//         i++;
//     if (ft_calloc(data, 0, (void *)&new, i + 2) == 1)
//     {
//         free_args(args, 0);
//         free_args(heredoc, 0);
//         return (NULL);
//     }
//     new[0] = ft_strdup(args[0]);
//     if (!new[0])
//     {
//         free_args(args, 0);
//         free_args(heredoc, 0);
//         free(new);
//         return (NULL);
//     }
//     while (heredoc[i])
//     {
//         new[i + 1] = ft_strdup(heredoc[i]);
//         if (!new[i + 1])
//         {
//             free_args(args, &i);
//             free_args(heredoc, 0);
//             free_args(new, 0);
//             return (NULL);
//         }
//         i++;
//     }
//     free_args(args, 0);
//     free_args(heredoc, 0);
//     return (new);
// }

int     size_of_args(t_data *data)
{
    int     size;

    size = 1;
    size = size + data->tokens->args_num;
    if (data->tokens->next && data->tokens->next->delim != PIPE)
    size = size + data->tokens->next->args_num;
    return (size);
}

char    *get_cmd_for_args(t_data *data)
{
    char    *pntr;
    int     len;
    char    *cmd;
    int     cntr;
    
    if (check_relative(data->tokens->cmd) != 0)
        pntr = ft_strrchr(data->tokens->cmd, '/');
    else
        pntr = data->tokens->cmd;
    len = ft_strlen(pntr);
    if (ft_calloc(data, 0, (void *)&cmd, len + 1) != 0) //free!!
        return (NULL);
    cntr = 0;
    while (cntr < len && *pntr)
    {
        cmd[cntr] = *pntr;
        cntr++;
        pntr++;
    }
    cmd[cntr] ='\0';
    return (cmd);
}

char    **cpy_token_args(t_data *data, char **args, int *args_cntr)
{
    int     cntr;

    *args_cntr = 1;
    cntr = 0;
    while (cntr < data->tokens->args_num)
    {
        args[*args_cntr] = ft_strdup(data->tokens->args[cntr]);
        if (!args[*args_cntr])
        {
            free_args(args, args_cntr);
            exit(12);
        }
        cntr++;
        *args_cntr += 1;
    }
    return (args);
}

char    **cpy_next_token_args(t_data *data, char **args, int *args_cntr)
{
    int     cntr;
    
    cntr = 0;
    while (cntr < data->tokens->next->args_num)
    {
        args[*args_cntr] = ft_strdup(data->tokens->next->args[cntr]);
        if (!args[*args_cntr])
        {
            free_args(args, args_cntr);
            exit(12);
        }
        cntr++;
        *args_cntr += 1;
    }
    return (args);
}
