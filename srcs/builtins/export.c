/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/18 11:55:51 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * TODO:
 * -Iterate the env
 * -Create a new env variable at the start of the env
 * -Update the env
 * -Debe no funcionar cuando no hay export o eso es lo q creo (??????)
 * -No 
*/

static void create_env_var(t_data *data, int arg_num)
{
  char **env;
  int i;
  if (ft_calloc(data, F_TOKCMD, (void **)&env, sizeof(char *) * (data->env_len + 2)))
    return ;
  i = 0;

  while(i < data->env_len)
  {
    env[i] = data->env[i];
    i++;
  }

  if(!ft_isdigit(data->tokens->args[arg_num][0]))
    env[i] = ft_strdup(data->tokens->args[arg_num]);
  else
    printf("export: %s: not a valid identifier\n", data->tokens->args[arg_num]);
  if(env[i] == NULL)
    return ;
  data->env = env;
  data->env_len = i + 1;
}

int replace_var_env(t_data *data, char *arg)
{

    char *ar;

    ar = ft_strchr_before_c(arg, 61);
    if(!arg)
        return 0;

    char *var;
    char **env_cpy;
    int i;

    var = NULL;
    env_cpy = NULL;
    i = 0;
    env_cpy = data->env;
    while(env_cpy[i] != NULL)
    {
        var = ft_strchr_before_c(env_cpy[i], '=');
        if(var != NULL && ft_strcmp(var, ar) == 0)
        {
            free(data->env[i]);
            data->env[i] = ft_strdup(arg);
            free(var);
            return 1;
        }
        i++;
        free(var);
    }
    return 0;
}



void execute_export_builtin(t_data *data)
{

    if(data->tokens->args_num == 0)
    {
      put_env(data);
      return ;
    }
    int i;
    char **args;
    char *var;

    var = NULL;
    args = data->tokens->args;
    i = 0;
    
    while(i < data->tokens->args_num)
    {
        var = ft_strchr_before_c(args[i], '=');
        if(var != NULL)
            if(replace_var_env(data, args[i]) == 0)
                if(is_valid_expand_var(args[i], '=') == 1)
                    create_env_var(data, i);
        i++;
    }
//  free(args);
//  free(var);
}