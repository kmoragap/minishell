/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/18 17:55:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void     check_cmd_path(t_data *data)
{
    if (check_builtins(data->tokens->cmd) > -1)
    {
        execute_builtin(data);
        //free everything malloced in execute_builtin
        exit (0);
    }
    data = remove_quotes(data->tokens->cmd, data); 
    if (check_relative(data->tokens->cmd) == 0)
    {
        if (find_path(data) == 1)
            error_in_child(data, 127, data->tokens->cmd, "command not found");
    }
    else
        check_absolute_path(data);
    return ;
}

t_data    *remove_quotes(char *cmd, t_data *data)
{
    int     i;
    int     check;
    char    *new;

    i = 0;
    check = 0;
    while (cmd[i] && check == 0)
    {
        if (cmd[i] == 34 || cmd[i] == 39)
            check = cmd[i];
        i++;
    }
    if (check == 0)
        return (data);
    new = ft_strndup(cmd, i - 1);
    while (cmd[i])
    {
        loop_quotes(cmd, &new, &i, &check);
    }
    free(data->tokens->cmd);
    data->tokens->cmd = new;
    return (data);
}

void    loop_quotes(char *cmd, char **new, int *i, int *check)
{
    int     j;

    j = 0;
    while (cmd[*i + j] != *check && cmd[*i + j])
        j++;
    *new = ft_strnjoin(*new, &cmd[*i], j);
    *i = *i + j;
    if (cmd[*i] && (cmd[*i] == 34 || cmd[*i] == 39))
        *check = cmd[*i];
    *i = *i + 1;
}

int     check_relative(char *cmd)
{
    if (ft_strchr(cmd, '/') == 1)
        return (0);
    return (1);
}


void print_arr(char **arr){
    int i = 0;
    while (arr[i])
        printf("%s\n", arr[i++]);
}

int     find_path(t_data *data)
{
    char    **path;
    int     lop;
    char    *tmp;

    tmp = path_from_env(data->env);
    path = ft_split(tmp, ':');
    free(tmp);
    if (!path)
        return (1);
    lop = 0;
    while (path[lop])
    {
        tmp = ft_strjoin(path[lop],"/");
        free(path[lop]);
        path[lop] = ft_strjoin(tmp, data->tokens->cmd);
        free(tmp);
        if (access(path[lop], F_OK) == 0 && access(path[lop], X_OK) == 0 && !data->tokens->path)
            data->tokens->path = ft_strdup(path[lop]);
        lop++;
    }
    free_args(path, &lop);
    if (data->tokens->path && data->tokens->path[0])
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

void     check_absolute_path(t_data *data)
{
    if (access(data->tokens->cmd, F_OK) != 0)
        error_in_child(data, 2, data->tokens->cmd, "No such file or directory");
    if (access(data->tokens->cmd, X_OK) != 0)
        error_in_child(data, 126, data->tokens->cmd, "Permission denied");
    data->tokens->path = ft_strdup(data->tokens->cmd);
}
