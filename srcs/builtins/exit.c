/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:15:14 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/17 22:01:05 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * only numeric arg, but the input is a string, so i have to create a func that check if is a string num:
 *  - numeric argument required
 * Exit with a true value: exit 0
 * Exit with a false value: exit 1
 * 126: A file to be executed was found, but it was not  an  executable utility.
 * 127: A utility to be executed was not found.
 * >128: A command was interrupted by a signal.
 * in case of: exit ARG_NUM ARG_NUM:
 *  bash: exit: too many arguments
 * 

*/

int is_valid_number(char *str) 
{
    if (*str == '-' || *str == '+') 
        str++;
    if (*str == '\0') 
        return 1;
    while (*str) 
    {
        if (!ft_isdigit((unsigned char)*str)) 
            return 1;
        str++;
    }
    return 0;
}

//	- If no argument are provided, it should take the previous exit code

void ft_exit(t_data *data)
{
    char **args;
    int exit_status;

    exit_status = 0;
    args = data->tokens->args;


    if (args[0] != NULL) 
    {
        if (is_valid_number(args[0]) == 0) 
        {
            exit_status = ft_atoi(args[0]);
            if (args[1] != NULL) 
            {
                perror("exit: too many arguments\n");
                return;
            }
        } 
        else 
        {
            write(2, "exit: ", 6);
            write(2, args[0], ft_strlen(args[0]));
            perror(": numeric argument required\n");
            exit_status = 255;
        }
    }
    data->free_code = F_ENV;
    free_all(data);
    //printf("exit\n");
    exit(exit_status % 256);
}