/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:26:56 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/20 11:07:27 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *expand_token(char *token, char **env, int exit_status) 
{
    char *value;
    char *var;
    char *nested_value;
    int i;
    
    value = NULL;
    var = NULL;
    nested_value = NULL;

    /*if(check_expand_quotes(token) == 1)
        return NULL;

    value = check_special_expand(token, exit_status);
    if(value != NULL)
        return value;*/

    token++;
    
    value = getenv(token);
    if (value != NULL) 
        return strdup(value);

    i = 0;
    while (env[i] != NULL) 
    {
        var = strtok(env[i], "=");
        value = strtok(NULL, "=");
        if (strcmp(var, token) == 0) {
            nested_value = expand_token(value, env, exit_status);
            if (nested_value != NULL)
                return strdup(nested_value);
            return strdup(value);
        }
        i++;
    }
    return NULL;
}


void expand_cmd(t_token *token, char **env) 
{
    char *expanded_cmd;
    expanded_cmd = NULL;

    if (check_expand_var(token->cmd)) 
    {
        printf("llegue aqui\n");
        //funcion para alloc mem in expanded variable
        expanded_cmd = expand_token(token->cmd, env, token->exit_status);
        if (expanded_cmd != NULL) 
        {
            free(token->cmd); 
            token->cmd = expanded_cmd; 
        }
        else
            printf("Error\n");
    }
}

void expand_args(t_token *token, char **env) 
{
    char *expanded_arg;
    int i;
    
    expanded_arg = NULL;
    i = 0;

    while(token->args[i] != NULL)
    {
        printf("llegue aqui\n");
        if(check_expand_args(&token->args[i]) == 1)
        {
            //funcion para alloc mem in expanded variable
            expanded_arg = expand_token(token->args[i], env, token->exit_status);
            if (expanded_arg != NULL) 
            {
                free(token->args[i]); 
                token->args[i] = expanded_arg;
            }
            else
                printf("Error\n"); 
        }
        else
            printf("Error\n");        
        i++;
    }    
}
