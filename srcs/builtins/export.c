/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/01 16:49:17 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * TODO:
 * -Iterate the env
 * -Create a new env variable at the start of the env
 * -Update the env
 * 
*/


/**
 * asignar memoria a una variable
 * anadir esta variable al array de la lista
*/



static void create_env_var(t_data *data)
{
  int env_len;
  static int i; 
  char **env;

  env = data->env;
  env_len = data->env_len;
  i = i + 1;
  
  
  free(env[env_len - i]);
  env[env_len - i] = ft_strdup(data->tokens->args[0]);
  env[env_len + i] = NULL;

  data->env = env;
  data->env_len = env_len + 2;
}


static int check_env(t_data *data)
    {
    int i;
    char *arg;
    char *var;
    char **env_cpy;

    arg = NULL;
    var = NULL;
    env_cpy = NULL;
    i = 0;
    env_cpy = data->env;
    arg = ft_strchr_before_c(data->tokens->args[0], 61);
    while(env_cpy[i] != NULL)
    {
        var = ft_strchr_before_c(env_cpy[i], 61);
        if(var != NULL && ft_strcmp(var, arg) == 0)
        {
            free(data->env[i]);
            data->env[i] = ft_strdup(arg);
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

    if(check_env(data) == 0)
        create_env_var(data);
      
    
}