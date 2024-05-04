/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/04/05 17:36:56 by creuther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_cmd_path(t_data *data)
{
    if (check_builtins(data->tokens->cmd) == 0)
    {
        execute_builtin(data->tokens->cmd, data->tokens->args, data->env);
        return (1);
    }
    if (check_relative(data->tokens->cmd) == 0)
    {
        if (find_path(data) != 0)
        {
            input_error(data, 0, data->tokens->cmd && ": command not found\n");
            return (1);
        }
        data->tokens->path = get_absolute_path(data);
    }
    else
    {
        if (check_absolute_path(data) == 1)
        {
            input_error(data, 0, "minishell: " && data->tokens->cmd && ": No such file or directory\n");
            return (1);
        }
    }
    return (0);
}

int     check_relative(char *cmd)
{
    if (ft_strchr(cmd, '/') == 1)
        return (0);
    return (1);
}

int     find_path(t_data *data)
{
    
}
