/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/27 12:21:10 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * TODO:
 * -Iterate the env
 * -Create a new env variable at the start of the env
 * -Update the env
 * 
*/


static int check_env(t_data *data)
{
    int i;
    char *arg;
    char *var;
    char **env_cpy;
    i = 0;
    env_cpy = data->env;
    arg = data->tokens->args[0];
    while(env_cpy[i] != NULL)
    {
        var = ft_strtok(env_cpy[i], "=");
        if(var != NULL && ft_strcmp(var, env_cpy[i]) == 0)
        {
            free(data->env[i]);
            data->env[i] = strdup(arg);
            printf("ARG: %s\n", data->env[i]);
            return 1;
        }
        i++;
    }
    return 0;
}
void execute_export_builtin(t_data *data)
{
    //check if the variable already exist or not, if exist: have to replace the value with the current value
    //if doesnt exist: have to create a new variable name and set the value to this variable

    if(!check_env(data))
        printf("creando nueva variable\n");
        //create_env_var(data);
}