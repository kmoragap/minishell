/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creuther <creuther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/09 20:39:41 by creuther         ###   ########.fr       */
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
    char    **path;
    int     lop;

    path = ft_split(path_from_env(data->env), ':');
    if (!path)
        return (1);
    lop = 0;
    while (path[lop])
    {
        path[lop] = ft_strjoin(path[lop], data->tokens->cmd);
        if (access(path[lop], F_OK) != 0)
        {
            //error code == 126
            //free code!
            return (1);
        }
        if (access(path[lop], X_OK) == 0 && !data->tokens->path)
            data->tokens->path = ft_strdup(path[lop]);
        lop++;
    }
    if (data->tokens->path)
        return (0);
    return (1);
}

char    *path_from_env(char **env)
{
    int     lop;
    char    *path;

    lop = 0;
    while (env[lop])
    {
        if (env[lop][0] == 'P' && env[lop][1] == 'A' && env[lop][2] == 'T' && env[lop][3] == 'H' && env[lop][4] == '=')
        {
            path = ft_strdup(env[lop]);
            return (path);
        }
        lop++;
    }
    return (NULL);
}

int     check_absolute_path(t_data *data)
{
    if (access(data->tokens->cmd, F_OK) != 0)
    {
        //error code == 126
        //free code!
        return (1);
    }
    if (access(data->tokens->cmd, X_OK) != 0)
    {
        //error code == 126
        //free code!
        return (1);
    }
    data->tokens->path = ft_strdup(data->tokens->cmd);
    return (0);
}
