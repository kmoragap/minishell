/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:16:48 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/21 18:24:14 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_valid_variable_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

int check_expand_args(char *args)
{
    int i; 
    int j;
    
    i = 0;
    j = 0;
    while (args[i] != '\0') {
        if (args[i] == '$' && args[i + 1] != '\0' && args[i + 1] != ' ') {
            j = i + 1;
            while (is_valid_variable_char(args[j])) {
                j++;
            }
            if (j > i + 1) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}

char *expand_cmd(char *cmd, char **env) 
{
    char *value;
    char *var;
    char *nested_value;
    int i;
    
    cmd++;
    value = getenv(cmd);
    if (value != NULL) 
        return strdup(value);

    i = 0;
    while (env[i] != NULL) {
        var = strtok(env[i], "=");
        value = strtok(NULL, "=");
        if (strcmp(var, cmd) == 0) {
            nested_value = expand_cmd(value, env);
            if (nested_value != NULL)
                return strdup(nested_value);
            return strdup(value);
        }
        i++;
    }
    return NULL;
}

void expand_token(t_token *token, char **env) 
{
    char *expanded_cmd;
    char *expanded_args;
    
    expanded_cmd = NULL;
    expanded_args = NULL;
    if (token->type == EXPAND) 
    {
        expanded_cmd = expand_cmd(token->cmd, env);
        if (expanded_cmd != NULL) 
        {
            free(token->cmd); 
            token->cmd = expanded_cmd; 
        }
        /*
        else 
            // keep the original string
            ;
        */
    }
    //I'm not sure about this else if
    else if (check_expand_args(token->args)) 
    {
        expanded_args = expand_cmd(token->args, env);
        if (expanded_args != NULL) 
        {
            free(token->args); 
            token->args = expanded_args;
        } 
        /*
        else 
            // keep the original string
            ;
        */
    }
}