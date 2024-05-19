/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:45 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/19 14:40:29 by kmoraga          ###   ########.fr       */
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
  {
    write(2, "export: ", 8);
    write(2, data->tokens->args[arg_num], ft_strlen(data->tokens->args[arg_num]));
    perror(": not a valid identifier\n");
  }
  if(env[i] == NULL)
    return ;
  data->env = env;
  data->env_len = i + 1;
}

int replace_var_env(t_data *data, char *arg)
{

    char *ar;

    ar = ft_strchr_before_c(arg, 61);
    if(!ar)
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


static void sort_env_case(t_data *data)
{
  int i;
  char *temp;
  int swapped;
  char **env_cpy;

  swapped = 1;
  env_cpy = ft_calloc_norm(data->env_len + 1, sizeof(char *));
  i = 0;

  while(i < data->env_len)
  {
    env_cpy[i] = ft_strdup(data->env[i]);
    i++;
  }
  
  env_cpy[i] = NULL;
  
  while(swapped)
  {
      swapped = 0;
      i = 0;
      while(env_cpy[i+1])
      {
          if(ft_strcmp(env_cpy[i], env_cpy[i + 1]) > 0)
          {
              temp = env_cpy[i];
              env_cpy[i] = env_cpy[i + 1];
              env_cpy[i + 1] = temp;
              swapped = 1;
          }
          i++;
      }
  }
  i = 0;
  while(env_cpy[i])
  {
      write(1, "declare -x ", 11);
      write(1, env_cpy[i], ft_strlen(env_cpy[i]));
      write(1, "\n", 1);
      i++;
  }

  i = 0;

  while (env_cpy[i])
  {
    free(env_cpy[i]);
    i++;
  }

  free(env_cpy);
  return ;
}

void execute_export_builtin(t_data *data)
{

  int i;
  
    if(data->tokens->args_num == 0)
    {
        sort_env_case(data);
        return ;
    }
    
    char **args;
    char *var;

    var = NULL;
    args = data->tokens->args;
    i = 0;
    
    while(i < data->tokens->args_num)
    {
        var = ft_strchr_before_c(args[i], '=');
      
        if(!ft_isalnum(var[ft_strlen(var) - 1]))
        {
          //msg?
          free(var);
          break;
        }
        else if(var != NULL)
            if(replace_var_env(data, args[i]) == 0)
                if(is_valid_expand_var(args[i], '=') == 1)
                    create_env_var(data, i);
        i++;
    }
}