/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:38:32 by kmoraga           #+#    #+#             */
/*   Updated: 2024/05/04 16:39:41 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo esto malo malo
*/

void unset_env(t_data *data, int arg_num)
{
    char **env;
    char *var;
    char *arg;
    int i;
    int j;
    
    env = malloc(sizeof(char *) * (data->env_len - 1));
    arg = ft_strchr_before_c(data->tokens->args[arg_num], 61);
    i = 0;
    j = 0; 

    while (j < data->env_len) 
    {
        var = ft_strchr_before_c(data->env[j], 61);
        if (var == NULL || ft_strcmp(var, arg) != 0) 
            env[i++] = data->env[j++];
        else
            free(data->env[j++]);
    }

    free(data->env); 
    data->env = env; 
    data->env_len -= 1;
}

void ft_unset(t_data *data)
{
    int i;

    i = 0;

    while(i < data->tokens->args_num)
    {
        unset_env(data, data->tokens->args_num);
        i++;
    }
}