/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:24:20 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/25 17:31:40 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_builtins(char *cmd)
{
    if(strcmp(cmd, "echo") == 0)
        return (1);
    else if(strcmp(cmd, "export") == 0)
        return (1);
    else if(strcmp(cmd, "cd") == 0)
        return (1);
    else if(strcmp(cmd, "env") == 0)
        return (1);
    else if(strcmp(cmd, "pwd") == 0)
        return (1);
    else if(strcmp(cmd, "unset") == 0)
        return (1);
    else if(strcmp(cmd, "exit") == 0)
        return (1);
    else
        return (0);
}

int check_builtins_type(char *cmd)
{
    if(strcmp(cmd, "echo") == 0)
        return (ECHO);
    else if(strcmp(cmd, "export") == 0)
        return (EXPORT);
    else if(strcmp(cmd, "cd") == 0)
        return (CD);
    else if(strcmp(cmd, "env") == 0)
        return (ENV);
    else if(strcmp(cmd, "pwd") == 0)
        return (PWD);
    else if(strcmp(cmd, "unset") == 0)
        return (UNSET);
    else if(strcmp(cmd, "exit") == 0)
        return (EXIT);
    else
        return (-1);
}