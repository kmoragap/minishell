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
        return (NULL);
    args[0] = get_cmd_for_args(data);
    printf("args = %s\n", args[0]);
    if (!args[0])
    {
        free(args);
        return (NULL);
    }    
    args = cpy_token_args(data, args, &args_cntr);
    if (!args)
        return (NULL);
    if (size > (data->tokens->args_num + 1))
        args = cpy_next_token_args(data, args, &args_cntr);
    if (!args)
        return (NULL);
    args[size] = NULL;
    return (args);
}

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
    if (ft_calloc(data, 0, (void *)&cmd, len + 1) != 0) //other free code!
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
            //error / free_code;
            return (NULL);
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
            //error / free_code;
            return (NULL);
        }
        cntr++;
        *args_cntr += 1;
    }
    return (args);
}

void    free_args(char **args, int *cnt)
{
    int     i;

    i = 0;
    if (!cnt)
    {
        while (args[i])
        {
            free(args[i]);
            i++;
        }
    }
    else
    {
        while (*cnt > 0)
        {
            free(args[*cnt]);
            *cnt -= 1;
        }
    }
    free(args);
}
